#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <cmath>  

using namespace std;

#include "DataSet.h"


const double gravitAcceleration = 9.81;
const double radiansToDegrees = 57.2957795;

DataSet::DataSet(double firstX, double firstY, double l, double w) {  //zavolá sa iba prvý-krát
	x = firstX;
	y = firstY;
	ropeLength = l;  //m
	weight = w;     //kg
	setVariables();
}

void DataSet::getValues(double coordX, double coordY) {   //volá sa opakovane
	x = coordX;
	y = coordY;
	checkMin();
}

void DataSet::setVariables() {
	checkMin();
	double h = ropeLength - y;
	maxPotentionalEnergy = weight * gravitAcceleration * h;
	startingAngle = getCurrentDisplacement();
}

void DataSet::checkMin() {
	if (minY == 0) {
		setMin();
	}
	else {
		if (y < minY) {
			setMin();
		}
	}
}

void DataSet::setMin() {
	minX = x;
	minY = y;
}

double DataSet::getCurrentDisplacement() {
	double deltaX = abs(minX - x);
	double deltaY = abs(minY - y);
	if (deltaY == 0) {
		return 0;
	}
	return 180 - (2 * radiansToDegrees*(atan((deltaX / deltaY))));
}

double DataSet::getSpeed() {
	double h = ropeLength - y;    //h = distancePendulumToMin
	//double c = ropeLength - h;     //c = distancePendulumToHangPoint
	double kineticEnergy = getKineticEnergy();
	return sqrt(((2 * kineticEnergy) / weight));
}

double DataSet::getPotentionalEnergy() {
	double h = ropeLength - y;
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

void DataSet::exportData() {
	double currentDisplacement = getCurrentDisplacement();
	double speed = getSpeed();
	double kineticEnergy = getKineticEnergy();
	double potentionalEnergy = getPotentionalEnergy();
	double period = getPeriod();
	double frequency = getFrequency();
	bool isMaximalDisplacement = getIfMaximalDisplacement();
	double acceleration = getAcceleration();
	double angularAcceleration = getAngularAcceleration();
	double angularSpeed = getAngularSpeed();
	//GraphView(currentDisplacement, speed, kineticEnergy, potentionalEnergy, period, isMaximalDisplacement,
	//	acceleration, angularAcceleration, angularSpeed);   //konštruktor novej triedy
}

/*int main() {
	return 0;
}*/
