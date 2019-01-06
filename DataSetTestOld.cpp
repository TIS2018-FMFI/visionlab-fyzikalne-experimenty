// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "DataSet.h"

using namespace ::testing;

TEST_F(Test, CurrentDisplacementFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	ASSERT_EQ(0, data.getCurrentDisplacement());
}

TEST_F(Test, CurrentDisplacementEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.1, 0.2);
	data.getValues(0.25, 0.35);
	double res = round(data.getCurrentDisplacement() * 1000.0) / 1000.0;
	ASSERT_EQ(90, res);
}

TEST_F(Test, CurrentDisplacementHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.1, 0.2);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getCurrentDisplacement() * 1000.0) / 1000.0;
	ASSERT_EQ(121.891, res);
}

TEST_F(Test, SpeedFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	ASSERT_EQ(0, data.getSpeed());
}

TEST_F(Test, SpeedEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(2.62, res);
}

TEST_F(Test, SpeedHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(0.626, res);
}

TEST_F(Test, PotentionalEnergyFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getPotentionalEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(23.740, res);
}

TEST_F(Test, PotentionalEnergyEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getPotentionalEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(16.187, res);
}

TEST_F(Test, PotentionalEnergyHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getPotentionalEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(15.755, res);
}

TEST_F(Test, KineticEnergyFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getKineticEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(0, res);
}

TEST_F(Test, KineticEnergyEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getKineticEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(7.554, res);
}

TEST_F(Test, KineticEnergyHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getKineticEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(0.432, res);
}

TEST_F(Test, PeriodFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getPeriod() * 1000.0) / 1000.0;
	ASSERT_EQ(2.104, res);
}

TEST_F(Test, PeriodEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getPeriod() * 1000.0) / 1000.0;
	ASSERT_EQ(2.104, res);
}

TEST_F(Test, PeriodHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getPeriod() * 1000.0) / 1000.0;
	ASSERT_EQ(2.104, res);
}

TEST_F(Test, FrequencyFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getFrequency() * 1000.0) / 1000.0;
	ASSERT_EQ(0.475, res);
}

TEST_F(Test, FrequencyEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getFrequency() * 1000.0) / 1000.0;
	ASSERT_EQ(0.475, res);
}

TEST_F(Test, FrequencyHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getFrequency() * 1000.0) / 1000.0;
	ASSERT_EQ(0.475, res);
}

TEST_F(Test, MaximalDisplacementFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	ASSERT_TRUE(data.getIfMaximalDisplacement());
}

TEST_F(Test, MaximalDisplacementEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	ASSERT_FALSE(data.getIfMaximalDisplacement());
}

TEST_F(Test, MaximalDisplacementHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	ASSERT_FALSE(data.getIfMaximalDisplacement());
}

TEST_F(Test, AccelerationFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(0, res);
}

TEST_F(Test, AccelerationEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-8.77, res);
}

TEST_F(Test, AccelerationHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-5.79, res);
}

TEST_F(Test, AngularAccelerationFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getAngularAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(0, res);
}

TEST_F(Test, AngularAccelerationEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getAngularAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-7.973, res);
}

TEST_F(Test, AngularAccelerationHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getAngularAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-5.264, res);
}

TEST_F(Test, AngularSpeedFirst) {
	DataSet data(0, 0, 1.1, 2.2);
	double res = round(data.getAngularSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(4.223, res);
}

TEST_F(Test, AngularSpeedEasy) {
	DataSet data(0, 0, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	double res = round(data.getAngularSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(2.827, res);
}

TEST_F(Test, AngularSpeedHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2);
	data.getValues(0.10, 0.20);
	data.getValues(0.25, 0.35);
	data.getValues(0.45, 0.10);
	data.getValues(0.30, 0.37);
	double res = round(data.getAngularSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(3.795, res);
}
