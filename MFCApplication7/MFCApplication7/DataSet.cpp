#define _USE_MATH_DEFINES

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

const double gravitAcceleration = 9.81;
const double radiansToDegrees = 57.2957795;

DataSet::DataSet(double firstX, double firstY, double mX, double mY, double l, double w, long long time, HWND h) {  //zavolá sa iba prvý-krát
	hPE = h;
	minX = mX;
	minY = mY;
	times.push_back(time);
	ropeLength = l;  //m
	weight = w;     //kg
	pixelConst = getCoordFromPixel(firstX, firstY);
	double xx = firstX * pixelConst;
	double yy = firstY * pixelConst;
	x.push_back(xx);
	y.push_back(yy);
	setVariables();
	calculateValues();
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
	double h = valueY - minY;
	double w = valueX - minX;
	double gamma = (3.1415 - 2 * (atan((w / h)) * radiansToDegrees));
	double temp = pow(w, 2) + pow(h, 2);
	return temp / (2 * pow(ropeLength, 2) * (1 - cos(gamma)));

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
	float fData[10];
	fData[0] = (float)currentDisplacement;
	fData[1] = (float)angularAcceleration;
	fData[2] = (float)angularSpeed;
	fData[3] = (float)kineticEnergy;
	fData[4] = (float)potentionalEnergy;
	fData[5] = (float)speed;
	fData[6] = (float)acceleration;
	fData[7] = (float)maxAngle;
	fData[8] = (float)period;
	fData[9] = (float)frequency;
	PEvset(hPE, PEP_faAPPENDYDATA, fData, 1);

	//PEreinitialize(hPE);
	//PEresetimage(hPE, 600, 500);
	return res;
}

void DataSet::setVariables() {
	double h = ropeLength - y.back();
	maxPotentionalEnergy = weight * gravitAcceleration * h;
	startingAngle = getCurrentDisplacement();
}

double DataSet::getCurrentDisplacement() {
	double deltaX = abs(minX - x.back());
	double deltaY = abs(minY - y.back());
	if (deltaY == 0) {
		return 0;
	}
	return 180 - (2 * radiansToDegrees*(atan((deltaX / deltaY))));
}

double DataSet::getSpeed() {
	double h = ropeLength - y.back();    //h = distancePendulumToMin
	double kineticEnergy = getKineticEnergy();
	return sqrt(((2 * kineticEnergy) / weight));
}

double DataSet::getPotentionalEnergy() {
	double h = y.back() - minY;
	double potentionalEnergy = weight * gravitAcceleration * h;
	if (potentionalEnergy > maxPotentionalEnergy) {
		maxPotentionalEnergy = potentionalEnergy;
	}
	return potentionalEnergy;
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
	double angle = getCurrentDisplacement();
	return -gravitAcceleration * sin(angle);
}

double DataSet::getAngularAcceleration() {
	double angle = getCurrentDisplacement();
	return ((-gravitAcceleration * sin(angle)) / ropeLength);
}

double DataSet::getAngularSpeed() {
	double angle = getCurrentDisplacement();
	double temp = ((2 * gravitAcceleration) / ropeLength)*(cos(angle)* cos(startingAngle));
	if (temp < 0) {
		temp = abs(temp);
	}
	return sqrt(temp);
}

void DataSet::exportPDFData(string imageName, string graphName) {
	PDFExport(values, graphName, imageName, weight, ropeLength, 1);
}

void DataSet::exportRawData() {
	RawDataExport(x, y, weight, ropeLength, times, values);                    //konštruktor novej triedy
}
