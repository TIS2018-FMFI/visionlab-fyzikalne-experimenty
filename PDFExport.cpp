#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

#include "stdafx.h"
#include "PDFExport.h"

#import "PDFCreatorPilot.dll"

using namespace PDFCreatorPilotLib;
using namespace std;

PDFExport::PDFExport(vector<double> uI, char *gI, char *ph, double pW, double rL, int num, char *com) {
	userInformations = uI;
	graphImage = gI;
	photo = ph;
	pendulumWeight = pW;
	ropeLength = rL;
	number = num;
	comment = (char*)com;
	createFile();
}

PDFExport::~PDFExport() {
	userInformations.clear();
	userInformations.shrink_to_fit();
	graphImage = nullptr;
	photo = nullptr;
	pendulumWeight = 0;
	ropeLength = 0;
	number = 0;
	comment = nullptr;
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

	long underCursiveBig = PDF->AddFont("Times New Roman", true, true, true, false, fcDefault);
	long underMedium = PDF->AddFont("Times New Roman", true, true, true, false, fcDefault);
	long medium = PDF->AddFont("Times New Roman", false, false, false, false, fcDefault);
	long small = PDF->AddFont("Times New Roman", false, false, false, false, fcDefault);

	ostringstream helpStream;
	helpStream << ropeLength;
	string rl = helpStream.str();
	const char *ropeLengthChar = rl.c_str();

	ostringstream helpStreamTwo;
	helpStreamTwo << pendulumWeight;
	string pW = helpStreamTwo.str();
	const char *pendulumWeightChar = pW.c_str();

	PDF->UseFont(underCursiveBig, 20);
	PDF->ShowTextAt(150, 30, "Fyzikálne experimenty - Kyvadlo");
	PDF->UseFont(underMedium, 17);
	PDF->ShowTextAt(10, 60, "Základné informácie:");
	PDF->UseFont(medium, 17);
	PDF->ShowTextAt(10, 80, "Objekt pokusu: ");
	PDF->UseFont(small, 13);
	PDF->ShowTextAt(117, 83, "Kyvadlo");
	PDF->UseFont(medium, 17);
	PDF->ShowTextAt(10, 100, "Merané hodnoty: ");
	PDF->UseFont(small, 13);
	PDF->ShowTextAt(130, 103, "Rýchlost, Uhlová rýchlost, Zrýchlenie, Uhlové zrýchlenie, Uhlová výchylka,");
	PDF->ShowTextAt(130, 123, "Maximálna výchylka, Potencionálna energia, Kinetická energia, Frekvencia, Perióda");
	PDF->UseFont(medium, 17);
	PDF->ShowTextAt(10, 140, "Dlzka lanka:" );
	PDF->UseFont(small, 13);
	PDF->ShowTextAt(100, 143, ropeLengthChar);
	PDF->ShowTextAt(130, 143, "m");
	PDF->UseFont(medium, 17);
	PDF->ShowTextAt(10, 160, "Váha závazia:");
	PDF->UseFont(small, 13);
	PDF->ShowTextAt(110, 164, pendulumWeightChar);
	PDF->ShowTextAt(142, 164, "kg");
	PDF->UseFont(medium, 17);
	PDF->ShowTextAt(10, 180, "Komentár:");
	PDF->UseFont(small, 13);

	int counter = strlen(comment);
	int helper = 183;
	int diff = 90;
	while (counter > 90) {
		char *b = new char[91]{};
		copy(comment + (diff-90), comment + diff, b);
		PDF->ShowTextAt(90, helper, b);
		counter -= 90;
		diff += 90;
		helper += 20;
	}
	if (counter != 0) {
		char *b = new char[91]{};
		copy(comment + (diff - 90), comment + strlen(comment), b);
		PDF->ShowTextAt(90, helper, b);
	}

	PDF->NewPage();
	PDF->UseFont(underCursiveBig, 20);
	PDF->ShowTextAt(150, 30, "Fyzikálne experimenty - Kyvadlo");
	PDF->UseFont(underMedium, 17);
	PDF->ShowTextAt(10, 60, "Screenshot záznamu:");
	long screenshot = PDF->AddImageFromFile(photo);
	PDF->ShowImage(screenshot, 0, 90);

	PDF->NewPage();
	PDF->UseFont(underCursiveBig, 20);
	PDF->ShowTextAt(150, 30, "Fyzikálne experimenty - Kyvadlo");
	PDF->UseFont(underMedium, 17);
	PDF->ShowTextAt(10, 60, "Screenshot grafu:");
	long graph = PDF->AddImageFromFile(graphImage);
	PDF->ShowImage(graph, 0, 90);

	time_t t = time(0);
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);
	string fileNameString = date + "_" + to_string(number) + ".pdf";
	bool fileAlreadyExists = fileExists(fileNameString);
	while (fileAlreadyExists) {
		number++;
		fileNameString = date + "_" + to_string(number) + ".pdf";
		fileAlreadyExists = fileExists(fileNameString);
	}
	const char *resFile = fileNameString.c_str();

	PDF->SaveToFile(resFile, true);

	CoUninitialize();
	return true;
}

bool PDFExport::fileExists(string &fileName) {
	ifstream infile(fileName.c_str());
	return infile.good();
}
