// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "DataSet.h"

using namespace ::testing;

TEST_F(Test, CurrentDisplacementFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	ASSERT_EQ(180, data.getCurrentDisplacement());
}

TEST_F(Test, CurrentDisplacementEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getCurrentDisplacement() * 1000.0) / 1000.0;
	ASSERT_EQ(108.925, res);
}

TEST_F(Test, CurrentDisplacementHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getCurrentDisplacement() * 1000.0) / 1000.0;
	ASSERT_EQ(101.929, res);
}

TEST_F(Test, SpeedFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	ASSERT_EQ(0, data.getSpeed());
}

TEST_F(Test, SpeedEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(1.716, res);
}

TEST_F(Test, SpeedHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(2.302, res);
}

TEST_F(Test, PotentionalEnergyFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getPotentionalEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(0, res);
}

TEST_F(Test, PotentionalEnergyEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getPotentionalEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(16.187, res);
}

TEST_F(Test, PotentionalEnergyHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getPotentionalEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(15.755, res);
}

TEST_F(Test, KineticEnergyFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getKineticEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(0, res);
}

TEST_F(Test, KineticEnergyEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getKineticEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(3.237, res);
}

TEST_F(Test, KineticEnergyHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getKineticEnergy() * 1000.0) / 1000.0;
	ASSERT_EQ(5.827, res);
}

TEST_F(Test, PeriodFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getPeriod() * 1000.0) / 1000.0;
	ASSERT_EQ(2.104, res);
}

TEST_F(Test, PeriodEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getPeriod() * 1000.0) / 1000.0;
	ASSERT_EQ(2.104, res);
}

TEST_F(Test, PeriodHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getPeriod() * 1000.0) / 1000.0;
	ASSERT_EQ(2.104, res);
}

TEST_F(Test, FrequencyFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getFrequency() * 1000.0) / 1000.0;
	ASSERT_EQ(0.475, res);
}

TEST_F(Test, FrequencyEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getFrequency() * 1000.0) / 1000.0;
	ASSERT_EQ(0.475, res);
}

TEST_F(Test, FrequencyHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getFrequency() * 1000.0) / 1000.0;
	ASSERT_EQ(0.475, res);
}

TEST_F(Test, MaximalDisplacementFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	ASSERT_TRUE(data.getIfMaximalDisplacement());
}

TEST_F(Test, MaximalDisplacementEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	ASSERT_FALSE(data.getIfMaximalDisplacement());
}

TEST_F(Test, MaximalDisplacementHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	ASSERT_FALSE(data.getIfMaximalDisplacement());
}

TEST_F(Test, AccelerationFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(7.859, res);
}

TEST_F(Test, AccelerationEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-8.416, res);
}

TEST_F(Test, AccelerationHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-9.664, res);
}

TEST_F(Test, AngularAccelerationFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getAngularAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(7.145, res);
}

TEST_F(Test, AngularAccelerationEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getAngularAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-7.651, res);
}

TEST_F(Test, AngularAccelerationHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getAngularAcceleration() * 1000.0) / 1000.0;
	ASSERT_EQ(-8.785, res);
}

TEST_F(Test, AngularSpeedFirst) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	double res = round(data.getAngularSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(2.527, res);
}

TEST_F(Test, AngularSpeedEasy) {
	DataSet data(0, 1.1, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	double res = round(data.getAngularSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(2.342, res);
}

TEST_F(Test, AngularSpeedHard) {
	DataSet data(0.35, 0.35, 0, 0, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	double res = round(data.getAngularSpeed() * 1000.0) / 1000.0;
	ASSERT_EQ(1.172, res);
}
