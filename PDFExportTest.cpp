// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include <ctime>
#include <fstream>
#include "gtest/gtest.h"

using namespace std;

#include "PDFExport.h"
#include "DataSet.h"

using namespace ::testing;

TEST_F(Test, PDFData) {
	double weight = 1.243;
	double length = 0.89;
	vector<double> values = { 3, 5, 7, 8 ,6, 4, 5, 3, 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 , 3, 5, 7, 8 ,6, 4, 5, 3 };
	string graph = "lenna.png";
	string screenshot = "lenna.jpg";
	int fileCounter = 1;
	PDFExport pe = PDFExport(values, graph, screenshot, weight, length, fileCounter);
	time_t t = time(0);
	tm* now = localtime(&t);
	string date = to_string(now->tm_mday) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_year + 1900);
	string fileNameString = date + "_" + to_string(fileCounter) + ".pdf";
	bool res = pe.fileExists(fileNameString);
	ASSERT_TRUE(res);
}
