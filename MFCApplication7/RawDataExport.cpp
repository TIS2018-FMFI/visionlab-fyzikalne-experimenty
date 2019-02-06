#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

#include "stdafx.h"
#include "RawDataExport.h"

RawDataExport::RawDataExport(vector<double> x, vector<double> y, double weight, double length, vector<long long> time, vector<double> values, double a) {
	xCoords = x;
	yCoords = y;
	pendulumWeight = weight;
	ropeLength = length;
	measuringTimes = time;
	calculatedValues = values;
	pixel = a;
	createFile();
}

bool RawDataExport::createFile() {
	time_t t = time(0);   // get time now
	//tm* now = localtime(&t);
	//string date = to_string(now->tm_mday) + '-'+ to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900); 
	string date = "now";
	int fileCounter = 1;
	string fileName = date + "_" + to_string(fileCounter) + ".csv";
	bool fileAlreadyExists = fileExists(fileName);
	while (fileAlreadyExists) {
		fileCounter++;
		fileName = date + "_" + to_string(fileCounter) + ".csv";
		fileAlreadyExists = fileExists(fileName);
	}
	ofstream file;
	file.open(fileName);
	file << "*** pixelConst: " + to_string(pixel) + " ***\n";
	file << "*** D�tum: "+ date + " ***\n";
	file << "*** Konfigur�cia kyvadla: ***\n";
	file << "V�ha:;" + to_string(pendulumWeight)  + ";D�ka lanka:;" + to_string(ropeLength) +"\n";
	file << "Ubehnut� �as:;S�radnica x:;S�radnica y:;Aktu�lna v�chylka:;R�chlos�;Zr�chlenie:;Uhlov� r�chlos�:;Uhlov� zr�chlenie:;Potenci�lna energia:;Kinetick� energia:;Peri�da:;Frekvencia:\n";

	auto time = measuringTimes.begin();
	auto x = xCoords.begin();
	auto y = yCoords.begin();
	auto values = calculatedValues.begin();

	while (time != measuringTimes.end()){
		file << to_string(*time) + ";" + to_string(*x) + ";" + to_string(*y) + ";";
		time++;
		x++;
		y++;
		for (unsigned int i = 0; i < 8; i++) {
			file << to_string(*values) + ";";
			values++;
		}
		file << to_string(*values) + "\n";
		values++;
	}

	file.close();
	return true;
}

bool RawDataExport::fileExists(string &fileName){
	ifstream infile(fileName.c_str());
	return infile.good();
}
