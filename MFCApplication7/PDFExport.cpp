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

	long img = PDF->AddImageFromFile("toto.png");
	PDF->ShowImage(img, 0, 0);

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
	int length = strlen(comment);
	float helper = 183;
	int diff = 75;
	while (counter > 75) {
		char *b = new char[76]{};
		copy(comment + (diff-75), comment + diff, b);
		PDF->ShowTextAt(90, helper, b);
		counter -= 75;
		diff += 75;
		helper += 20;
	}
	if (counter != 0) {
		char *b = new char[76]{};
		copy(comment + (diff - 75), comment + strlen(comment), b);
		PDF->ShowTextAt(90, helper, b);
	}
	helper += 20;

	PDF->UseFont(medium, 17);
	PDF->ShowTextAt(10, helper, "Namerané hodnoty:");
	helper += 20;

	long table = PDF->AddTable(9, 2, small, 10);

	for (int i = 0; i < 9; i++) {
		PDF->SetTableColumnSize(table, i, 63);
	}

	for (int i = 0; i < 2; i++) {
		PDF->SetTableRowSize(table, i, 30);
	}

	PDF->SetRowTableFont(table, 0, underMedium);
	PDF->SetRowTableFontSize(table, 0, 10);

	for (int col = 0; col < 9; col++) {
		for (int row = 0; row < 2; row++) {
			if (row == 0) {
				char *text = getText(col);
				PDF->SetCellTableText(table, col, row, text);
				PDF->SetCellTableTextAlign(table, col, row, taCenter);
			}
			else {
				char helpo[15];
				int res = snprintf(helpo, sizeof helpo, "%f", userInformations[col]);
				PDF->SetCellTableText(table, col, row, helpo);
				PDF->SetCellTableTextAlign(table, col, row, taCenter);
			}
		}
	}
	helper += 10;
	PDF->ShowTable(table, 10, helper, 1, 1);

	helper += 60;
	if (length < 76) {
		PDF->UseFont(underMedium, 17);
		PDF->ShowTextAt(10, helper, "Screenshot záznamu a grafu:");
		helper += 20;
		long graph = PDF->AddImageFromFile(graphImage);
		PDF->ShowImage(graph, 120, helper);
		helper += 285;
		long screenshot = PDF->AddImageFromFile(photo);
		PDF->ShowImage(screenshot, 120, helper);
	}
	else {
		PDF->NewPage();
		PDF->ShowImage(img, 0, 0);
		PDF->UseFont(underCursiveBig, 20);
		PDF->ShowTextAt(150, 30, "Fyzikálne experimenty - Kyvadlo");
		PDF->UseFont(underMedium, 17);
		PDF->ShowTextAt(10, 50, "Screenshot záznamu a grafu:");
		long graph = PDF->AddImageFromFile(graphImage);
		PDF->ShowImage(graph, 120, 70);
		long screenshot = PDF->AddImageFromFile(photo);
		PDF->ShowImage(screenshot, 120, 355);
	}
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

char* PDFExport::getText(int column) {
	char* res = "Chyba";
	switch (column) {
		case 0: res = "Uhlová výchylka";
			break;
		case 1: res = "Rýchlosť";
			break;
		case 2: res = "Zrýchlenie";
			break;
		case 3: res = "Uhlová rýchlosť";
			break;
		case 4: res = "Uhlové zrýchlenie";
			break;
		case 5: res = "Potencionálna energia";
			break;        
		case 6: res = "Kinetická energia";
			break;
		case 7: res = "Perióda";
			break;
		case 8: res = "Frekvencia";
			break;
	}
	return res;
}

bool PDFExport::fileExists(string &fileName) {
	ifstream infile(fileName.c_str());
	return infile.good();
}
