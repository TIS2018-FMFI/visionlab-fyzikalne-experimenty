#pragma once

using namespace std;

#if !defined( _RAWDATAEXPORT_H_ )
#define _RAWDATAEXPORT_H_

class RawDataExport {
	vector<double> xCoords = {};
	vector<double> yCoords = {};
	vector<double> calculatedValues = {};
	vector<long long> measuringTimes = {};
	double pendulumWeight = 0;
	double ropeLength = 0;
public:
	RawDataExport(vector<double> x, vector<double> y, double weight, double length, vector<long long> time, vector<double> values);
	bool createFile();
	bool fileExists(string &fileName);
};

#endif
