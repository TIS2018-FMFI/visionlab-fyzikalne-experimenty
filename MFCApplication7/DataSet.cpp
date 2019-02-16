#include <math.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#include "stdafx.h"
#include "DataSet.h"
#include "RawDataExport.h"
#include "PDFExport.h"
#include "Pegrpapi.h"

double gravitAcceleration = 9.81;
const double radiansToDegrees = 57.2957795;

DataSet::DataSet(double firstX, double firstY, double mX, double mY, double l, double w, long long time, HWND h, double g) {  //zavolá sa iba prvý-krát
	hPE = h;
	minX = mX;
	minY = mY;
	times.push_back(time);
	ropeLength = l;  //m
	weight = w;     //kg
	gravitAcceleration = g;
	pixelConst = getCoordFromPixel(firstX, firstY);
	minX *= pixelConst;
	minY *= pixelConst;
	double xx = firstX * pixelConst;
	double yy = firstY * pixelConst;
	x.push_back(xx);
	y.push_back(yy);
	setVariables();
	calculateValues();
}

DataSet::~DataSet() {
	x.clear();
	x.shrink_to_fit();
	y.clear();
	y.shrink_to_fit();
	times.clear();
	times.shrink_to_fit();
	values.clear();
	values.shrink_to_fit();
	minX = 0;
	minY = 0;
	ropeLength = 0;
	weight = 0;
	maxPotentionalEnergy = 0;
	startingAngle = 0;
	maxAngle = 0;
	pixelConst = 0;
}

void DataSet::getValues(double coordX, double coordY, long long time) {   //volá sa opakovane
	double xx = coordX * pixelConst;
	double yy = coordY * pixelConst;
	x.push_back(xx);
	y.push_back(yy);
	times.push_back(time);
	calculateValues();
}

double DataSet::getCoordFromPixel(double valueX, double valueY) {
	double h = abs(valueY - minY);
	double w = abs(valueX - minX);
	double gamma = (2 * (atan((h / w))));
	double temp = pow(w, 2) + pow(h, 2);
	return sqrt(((2 * pow(ropeLength, 2) * (1 - cos(gamma))) / temp));

}

void DataSet::calculateValues() {
	vector<double> current = calculateEachValue();
	for (auto elem : current) {
		values.push_back(elem);
	}
}

vector<double> DataSet::calculateEachValue() {
	double currentDisplacement = getCurrentDisplacement();
	double speed = getSpeed();
	double acceleration = getAcceleration();
	double angularSpeed = getAngularSpeed();
	double angularAcceleration = getAngularAcceleration();
	double potentionalEnergy = getPotentionalEnergy();
	double kineticEnergy = getKineticEnergy();
	double period = getPeriod();
	double frequency = getFrequency();
	vector<double> res;
	res.push_back(currentDisplacement);
	res.push_back(speed);
	res.push_back(acceleration);
	res.push_back(angularSpeed);
	res.push_back(angularAcceleration);
	res.push_back(potentionalEnergy);
	res.push_back(kineticEnergy);
	res.push_back(period);
	res.push_back(frequency);
	if (currentDisplacement > 0 && currentDisplacement > maxAngle) {
		maxAngle = currentDisplacement;
	}
	else if (currentDisplacement < 0 && currentDisplacement < -1 * maxAngle) {
		maxAngle = -1 * currentDisplacement;
	}
	float fData[9];
	fData[0] = (float)currentDisplacement;
	fData[1] = (float)angularAcceleration / 10000;
	fData[2] = (float)angularSpeed;
	fData[3] = (float)kineticEnergy;
	fData[4] = (float)potentionalEnergy;
	fData[5] = (float)speed;
	fData[6] = (float)acceleration / 10000;
	fData[7] = 7.0;
	fData[8] = -7.0;
	/*
	for (int i = 0; i < 7; i++) {
		if (fData[i] > fData[7]) {
			fData[7] = fData[i];
			fData[8] = fData[i] * (-1);
		}
	}*/

	PEvset(hPE, PEP_faAPPENDYDATA, fData, 1);

	//PEreinitialize(hPE);
	//PEresetimage(hPE, 600, 500);
	return res;
}

void DataSet::setVariables() {
	double h = abs(y.back() - minY);
	maxPotentionalEnergy = weight * gravitAcceleration * h;
	startingAngle = getCurrentDisplacement();
}

double DataSet::getCurrentDisplacement() {
	double deltaX = minX - x.back();
	double deltaY = abs(minY - y.back());
	/*if (deltaY == 0) {
		return 0;
	}*/
	return (2 *(atan((deltaY / deltaX))));
}

double DataSet::getSpeed() {
	/*double kineticEnergy = getKineticEnergy();
	return sqrt(((2 * kineticEnergy) / weight));*/
	if (x.size() < 3) {
		return 0;
	}
	double dx = abs(x.end()[-3] - x.back());
	double dy = abs(y.end()[-3] - y.back());
	double dt = abs(times.end()[-3] - times.back());
	double c = sqrt(pow(dx, 2) + pow(dy, 2));
	return 3600 * c / dt;
}

double DataSet::getPotentionalEnergy() {
	double h = abs(y.back() - minY);
	double potentionalEnergy = weight * gravitAcceleration * h;
	if (potentionalEnergy > maxPotentionalEnergy) {
		maxPotentionalEnergy = potentionalEnergy;
	}
	return  potentionalEnergy;
}

double DataSet::getKineticEnergy() {
	double potentionalEnergy = getPotentionalEnergy();
	return maxPotentionalEnergy - potentionalEnergy;
}

double DataSet::getPeriod() {
	return 2 * 3.1415 * sqrt((ropeLength / gravitAcceleration));
}

double DataSet::getFrequency() {
	return 1 / getPeriod();
}

bool DataSet::getIfMaximalDisplacement() {
	return getKineticEnergy() == 0;
}

double DataSet::getAcceleration() {
	if (x.size() < 4) {
		return 0;
	}
	double dx = abs(x.end()[-4] - x.end()[-2]);
	double dy = abs(y.end()[-4] - y.end()[-2]);
	double dt = abs(times.end()[-4] - times.end()[-2]);
	double c = sqrt(pow(dx, 2) + pow(dy, 2));

	double dt2 = abs(times.back() - times.end()[-2]);
	return 3600000 * (getSpeed() - (3600 * c / dt)) / dt2;
}

double DataSet::getAngularAcceleration() {
	return getAcceleration() / ropeLength;
}

double DataSet::getAngularSpeed() {
	double angle = getCurrentDisplacement();
	double temp = ((2 * gravitAcceleration) / ropeLength)*(cos(angle)* cos(startingAngle));
	if (temp < 0) {
		temp = abs(temp);
	}
	return sqrt(temp);
}

void DataSet::exportPDFData(char *imageName, char *graphName, const char *comment) {
	double currentDisplacement = getCurrentDisplacement();
	double speed = getSpeed();
	double acceleration = getAcceleration();
	double angularSpeed = getAngularSpeed();
	double angularAcceleration = getAngularAcceleration();
	double potentionalEnergy = getPotentionalEnergy();
	double kineticEnergy = getKineticEnergy();
	double period = getPeriod();
	double frequency = getFrequency();
	vector<double> res;
	res.push_back(currentDisplacement);
	res.push_back(speed);
	res.push_back(acceleration);
	res.push_back(angularSpeed);
	res.push_back(angularAcceleration);
	res.push_back(potentionalEnergy);
	res.push_back(kineticEnergy);
	res.push_back(period);
	res.push_back(frequency);
	char *help = (char*)comment;
	PDFExport(res, graphName, imageName, weight, ropeLength, 1, help);
}

void DataSet::exportRawData() {
	RawDataExport(x, y, weight, ropeLength, times, values);                    //konštruktor novej triedy
}
