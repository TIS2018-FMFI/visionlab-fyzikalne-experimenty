#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

#include "stdafx.h"
#include "RawDataExport.h"

RawDataExport::RawDataExport(vector<double> x, vector<double> y, double weight, double length, vector<long long> time, vector<double> values) {
	xCoords = x;
	yCoords = y;
	pendulumWeight = weight;
	ropeLength = length;
	measuringTimes = time;
	calculatedValues = values;
	createFile();
}

RawDataExport::~RawDataExport() {
	xCoords.clear();
	xCoords.shrink_to_fit();
	yCoords.clear();
	yCoords.shrink_to_fit();
	measuringTimes.clear();
	measuringTimes.shrink_to_fit();
	calculatedValues.clear();
	calculatedValues.shrink_to_fit();
	pendulumWeight = 0;
	ropeLength = 0;
	pixel = 0;
}

bool RawDataExport::createFile() {
	time_t t = time(0);
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-'+ to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900); 
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
	file << "*** Dátum: "+ date + " ***\n";
	file << "*** Konfigurácia kyvadla: ***\n";
	file << "Váha:;" + to_string(pendulumWeight)  + ";Dåžka lanka:;" + to_string(ropeLength) +"\n";
	file << "Ubehnutý èas:;Súradnica x:;Súradnica y:;Aktuálna výchylka:;Rýchlos;Zrýchlenie:;Uhlová rýchlos:;Uhlové zrýchlenie:;Potenciálna energia:;Kinetická energia:;Perióda:;Frekvencia:\n";

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
