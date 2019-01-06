// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include <ctime>
#include <fstream>
#include "gtest/gtest.h"

using namespace std;

#include "RawDataExport.h"
#include "DataSet.h"

using namespace ::testing;

TEST_F(Test, RawDataFirst) {
	vector<double> x = {1, 2, 3, 4, 80, 653};
	vector<double> y = {5, 8, 30, 2, 1, 50};
	double weight = 1.243;
	double length = 0.89;
	vector<long long> times = {1, 2, 3, 4, 5, 6};
	vector<double> values = {3, 5, 7, 8 ,6, 4, 5, 3, 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 };
	RawDataExport rde(x, y, weight, length, times, values);
	time_t t = time(0);   
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);
	int fileCounter = 1;
	string fileName = date + "_" + to_string(fileCounter) + ".csv";
	bool res = rde.fileExists(fileName);
	ASSERT_TRUE(res);
}

TEST_F(Test, RawDataEasy) {
	DataSet data(0, 1.1, 1.1, 2.2, 1);
	data.getValues(0.10, 0.20, 2);
	data.getValues(0.25, 0.35, 3);
	data.exportRawData();
	time_t t = time(0);
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);
	int fileCounter = 2;
	string fileName = date + "_" + to_string(fileCounter) + ".csv";
	ifstream infile(fileName.c_str());
	bool res = infile.good();
	ASSERT_TRUE(res);
}

TEST_F(Test, RawDataHard) {
	DataSet data(0.35, 0.35, 1.1, 2.2, 1);
	data.getValues(0.1, 0.2, 2);
	data.getValues(0.25, 0.35, 3);
	data.getValues(0.45, 0.10, 4);
	data.getValues(0.30, 0.37, 5);
	data.exportRawData();
	time_t t = time(0);
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);
	int fileCounter = 3;
	string fileName = date + "_" + to_string(fileCounter) + ".csv";
	ifstream infile(fileName.c_str());
	bool res = infile.good();
	ASSERT_TRUE(res);
}