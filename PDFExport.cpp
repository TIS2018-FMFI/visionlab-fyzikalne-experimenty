#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
//#include "pch.h"
#include <iostream>

#import "PDFCreatorPilot.dll"
using namespace PDFCreatorPilotLib;

using namespace std;

#include "PDFExport.h"

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

	// composing a watermark
	/*long wtm = PDF->AddWatermark();
	PDF->SwitchToWatermark(wtm);
	PDF->SetColorFill(0, 1, 0, 0);
	PDF->ShowTextAt(330, 530, "Watermark text");
	PDF->SwitchToCurrentPage();

	//composing 1st page
	PDF->ShowTextAt(50, 50, "Page1 with watermark.");
	PDF->AttachWatermark(0, wtm);

	//composing 2nd page
	PDF->NewPage();
	PDF->ShowTextAt(50, 50, "Page2 with watermark.");
	PDF->AttachWatermark(1, wtm);

	//composing 3rd page
	PDF->NewPage();
	PDF->ShowTextAt(50, 50, "Page3 with watermark.");
	PDF->AttachWatermark(2, wtm);*/

	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);

	string fileNameString = date + "_" + to_string(number) + ".pdf";;
	const char *resFile = fileNameString.c_str();

	PDF->SaveToFile(resFile, true);


	CoUninitialize();
	return true;
}

bool PDFExport::fileExists(string &fileName) {
	ifstream infile(fileName.c_str());
	return infile.good();
}
