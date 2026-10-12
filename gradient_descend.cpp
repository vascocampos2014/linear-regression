#include "gradient_descend.hpp"

#include <iostream>

using namespace std;

gradient_descend::gradient_descend()
	:m(0), b(0), alpha(DEFAULT_ALPHA), iterations(DEFAULT_ITER), verbose(false), xMean(0), yMean(0)
{

}

gradient_descend::gradient_descend(const data_t& dataCsv)
	:m(0), b(0), alpha(DEFAULT_ALPHA), iterations(DEFAULT_ITER), verbose(true), xMean(0), yMean(0)
{
	calculateMeans(dataCsv);
	calculateZScore(dataCsv);
	gradientDescend(dataCsv);
}

gradient_descend::gradient_descend(const data_t& dataCsv, double alpha, int iterations, bool verbose)
	:m(0), b(0), alpha(alpha), iterations(iterations), verbose(verbose), xMean(0), yMean(0), s(0)
{
	calculateMeans(dataCsv);
	calculateZScore(dataCsv);
	gradientDescend(dataCsv);
}

gradient_descend::~gradient_descend()
{

}

void gradient_descend::calculateMeans(const data_t& dataCsv)
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

void gradient_descend::calculateZScore(const data_t& dataCsv)
{
	int i = 0;
	double x = 0;
	while (i < dataCsv.count)
	{
		x += (dataCsv.arrA[i] - this->xMean) * (dataCsv.arrA[i] - this->xMean);
		i++;
	}	
	this->s = sqrt(x / dataCsv.count);
	i = 0;
	cout << "\nS: " << s << endl;
	while (i < dataCsv.count)
	{
		this->ZScore[i] = (dataCsv.arrA[i] - this->xMean) / s;
		i++;
	}
}

void gradient_descend::gradientDescend(const data_t& dataCsv)
{
	int i = 0;
	double loss = 0;
	double prediction = 0;
	int j = 0;
	double error = 0;
	double dw = 0;
	double db = 0;
	while (i < this->iterations)
	{
		j = 0;
		db = 0;
		dw = 0;
		loss = 0;
		while (j < dataCsv.count)
		{
			prediction = this->m * this->ZScore[j] + this->b;
			error = prediction - dataCsv.arrB[j];
			loss += error * error;
			dw += error * 2 * this->ZScore[j];
			db += error * 2;
			j++;
		}
		dw /= dataCsv.count;
		db /= dataCsv.count;
		loss /= dataCsv.count;
		if (this->verbose && i % 25 == 0)
			cout << "  iter " << i
			     << "  loss " << loss
			     << "  m " << this->m
			     << "  b " << this->b << endl;
		this->m -= dw * this->alpha;
		this->b -= db * this->alpha;
		i++;
	}
	this->b = this->b - (this->m * this->xMean) / this->s;
	this->m /= this->s;  
}

double gradient_descend::getB() const
{
	return (this->b);
}

double gradient_descend::getM() const
{
	return (this->m);
}

double gradient_descend::getAlpha() const
{
	return (this->alpha);
}

int gradient_descend::getIterations() const
{
	return (this->iterations);
}

double gradient_descend::UseFormula(double x) const
{
	return (this->m * x + this->b);
}
