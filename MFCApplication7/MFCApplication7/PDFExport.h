#pragma once

using namespace std;

#if !defined( _PDFEXPORT_H_ )
#define _PDFEXPORT_H_

class PDFExport {
	vector<double> userInformations = {};
	string graphImage;
	string photo;
	double pendulumWeight = 0;
	double ropeLength = 0;
	int number = 0; //è. pokusu
public:
	PDFExport(vector<double> uI, string gI, string ph, double pW, double rL, int num);
	bool createFile();
	bool fileExists(string &fileName);
};

#endif