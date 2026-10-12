#include "data.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

data_t parseCSV(const string& FileName)
{
	data_t dataCsv = {};
	ifstream file(FileName);
	if (!file)
		throw runtime_error("Error: Failed to open File");
	string line;
	int i = 0;
	while (getline(file, line) && i < MAX_POINTS)
	{
		istringstream ss(line);
		string field;
		if (!getline(ss, field, ','))
			return (cerr << "Error found in line " << i + 1 << endl, dataCsv);
		dataCsv.arrA[i] = stod(field);
		if (!getline(ss, field, ','))
			return (cerr << "Error found in line " << i + 1 << endl, dataCsv);
		dataCsv.arrB[i] = stod(field);
		i++;
	}
	dataCsv.count = i;
	return (dataCsv);
}
