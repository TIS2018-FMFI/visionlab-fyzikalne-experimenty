#pragma once

using namespace std;

#if !defined( _DATASET_H_ )
#define _DATASET_H_

class DataSet {
	vector<double> x = {};
	vector<double> y = {};
	vector<long long> times = {};
	vector<double> values = {};
	double minX = 0;
	double minY = 0;
	double ropeLength = 0;
	double weight = 0;
	double maxPotentionalEnergy = 0;
	double startingAngle = 0;
public:
	DataSet(double firstX, double firstY, double mX, double mY, double l, double w, long long time);
	void getValues(double coordX, double coordY, long long time);
	void setVariables();
	double getCurrentDisplacement();
	double getSpeed();
	double getAcceleration();
	double getAngularAcceleration();
	double getAngularSpeed();
	double getKineticEnergy();
	double getPotentionalEnergy();
	double getPeriod();
	double getFrequency();
	bool getIfMaximalDisplacement();
	void exportGraphData();
	void exportRawData();
	void calculateValues();
	vector<double> calculateEachValue();
};


#endif
