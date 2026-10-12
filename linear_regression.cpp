#include "linear_regression.hpp"

#include <stdexcept>

using namespace std;

linear_regression::linear_regression() :m(0), b(0), xMean(0), yMean(0)
{

}

linear_regression::linear_regression(const data_t& dataCsv)
{
	calculateMeans(dataCsv);
	calculateM(dataCsv);
	calculateB();
}

linear_regression::~linear_regression()
{

}

void linear_regression::calculateMeans(const data_t& dataCsv)
{
	int i = 0;
	double x = 0;
	double y = 0;
	while (i < dataCsv.count)
	{
		x += dataCsv.arrA[i];
		y += dataCsv.arrB[i];
		i++;
	}
	this->xMean = x / dataCsv.count;
	this->yMean = y / dataCsv.count;
}

void linear_regression::calculateM(const data_t& dataCsv)
{
	double denominator = 0;
	double numerator = 0;
	int i = 0;
	while (i < dataCsv.count)
	{
		numerator += (dataCsv.arrA[i] - this->xMean) * (dataCsv.arrB[i] - this->yMean);
		denominator += ((dataCsv.arrA[i] - this->xMean) * (dataCsv.arrA[i] - this->xMean));
		i++;
	}
	if (denominator == 0)
		throw runtime_error("Error: all x values are equal -> vertical line, no slope");
	this->m = numerator / denominator;
}

void linear_regression::calculateB()
{
	this->b = this->yMean - this->m * this->xMean;
}

double linear_regression::getB() const
{
	return (this->b);
}

double linear_regression::getXMean() const
{
	return (this->xMean);
}

double linear_regression::getYMean() const
{
	return (this->yMean);
}

double linear_regression::getM() const
{
	return (this->m);
}

double linear_regression::UseFormula(double x) const
{
	return (this->m * x + this->b);
}
