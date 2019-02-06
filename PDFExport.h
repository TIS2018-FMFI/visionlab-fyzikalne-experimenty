#pragma once

using namespace std;

#if !defined( _PDFEXPORT_H_ )
#define _PDFEXPORT_H_

class PDFExport {
	vector<double> userInformations = {};
	const char *graphImage = nullptr;
	const char *photo = nullptr;
	double pendulumWeight = 0;
	double ropeLength = 0;
	int number = 0; //è. pokusu
	char *comment = nullptr;
public:
	PDFExport(vector<double> uI, char *gI, char *ph, double pW, double rL, int num, char *com);
	~PDFExport();
	bool createFile();
	bool fileExists(string &fileName);
};

#endif