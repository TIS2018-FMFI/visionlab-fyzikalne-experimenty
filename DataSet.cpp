#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#include "DataSet.h"
#include "RawDataExport.h"

const double gravitAcceleration = 9.81;
const double radiansToDegrees = 57.2957795;

DataSet::DataSet(double firstX, double firstY, double mX, double mY, double l, double w, long long time) {  //zavolá sa iba prvý-krát
	x.push_back(firstX);
	y.push_back(firstY);
	minX = mX;
	minY = mY;
	times.push_back(time);
	ropeLength = l;  //m
	weight = w;     //kg
	setVariables();
	calculateValues();
}

void DataSet::getValues(double coordX, double coordY, long long time) {   //volá sa opakovane
	x.push_back(coordX);
	y.push_back(coordY);
	times.push_back(time);
	calculateValues();
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
	double h = ropeLength - y.back();
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
	return 2 * M_PI * sqrt((ropeLength / gravitAcceleration));
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

void DataSet::exportGraphData() {
	vector<double> currentCalculatedValues = calculateEachValue();
	//GraphView(times.back(), currentCalculatedValues), //konštruktor novej triedy
}

void DataSet::exportRawData() {
	RawDataExport(x, y, weight, ropeLength, times, values);                    //konštruktor novej triedy
}
