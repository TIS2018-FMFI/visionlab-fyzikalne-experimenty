#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

#include "stdafx.h"
#include "PDFExport.h"

#import "PDFCreatorPilot.dll"
using namespace PDFCreatorPilotLib;

using namespace std;

PDFExport::PDFExport(vector<double> uI, string gI, string ph, double pW, double rL, int num) {
	userInformations = uI;
	graphImage = gI;
	photo = ph;
	pendulumWeight = pW;
	ropeLength = rL;
	number = num;
	createFile();
}

bool PDFExport::createFile() {
	CoInitialize(NULL);

	IPDFDocument4* PDF = NULL;
	CLSID clsid;

	HRESULT hr = CLSIDFromProgID(OLESTR("PDFCreatorPilot.PDFDocument4"), &clsid);
	if (hr != S_OK) {
		return false;
	}

	hr = CoCreateInstance(clsid, 0, CLSCTX_ALL, __uuidof(IPDFDocument4), (LPVOID *)&PDF);
	if (hr != S_OK) {
		return false;
	}

	PDF->SetLicenseData("demo@demo", "demo");
	PDF->SetTitle("ResultPDF", fcANSI);
	PDF->ProducePDFA = false;
	PDF->Compression = coFlate;


	// PDF object is supposed to be created
	//long img = PDF->AddImageFromFile("toto.png");
	long graph = PDF->AddImageFromFile("lenna.png");
	PDF->ShowImage(graph, 0, 0);
	long screenshot = PDF->AddImageFromFile("lenna.jpg");
	PDF->ShowImage(screenshot, 400, 0);

	//time_t t = time(0);   // get time now
	//tm* now = localtime(&t);
	//string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);
	string date = "now";

	string fileNameString = date + "_" + to_string(number) + ".pdf";
	const char *resFile = fileNameString.c_str();

	PDF->SaveToFile(resFile, true);


	CoUninitialize();
	return true;
}

bool PDFExport::fileExists(string &fileName) {
	ifstream infile(fileName.c_str());
	return infile.good();
}
