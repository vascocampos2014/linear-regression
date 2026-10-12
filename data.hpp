#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <cmath>

const int MAX_POINTS = 25;

struct data_t
{
	double arrA[MAX_POINTS];
	double arrB[MAX_POINTS];
	int count;
};

data_t parseCSV(const std::string& FileName);

#endif
