#ifndef GRADIENT_DESCEND_HPP
#define GRADIENT_DESCEND_HPP

#include "data.hpp"

const int    DEFAULT_ITER  = 500;
const double DEFAULT_ALPHA = 0.01;

// Iterative least-squares fit: guess, measure the loss, step downhill, repeat.
// Reaches the same m and b as linear_regression, the long way round.
class gradient_descend
{
private:
	double m;
	double b;
	double alpha;
	int    iterations;
	bool   verbose;
	double xMean;
	double yMean;
	double ZScore[25];
	double s;
public:
	gradient_descend();
	gradient_descend(const data_t& dataCsv);
	gradient_descend(const data_t& dataCsv, double alpha, int iterations, bool verbose);
	~gradient_descend();
	double UseFormula(double x) const;
	void gradientDescend(const data_t& dataCsv);
	void calculateMeans(const data_t& dataCsv);
	void calculateZScore(const data_t& dataCsv);
	//getters
	double getM() const;
	double getB() const;
	double getAlpha() const;
	int    getIterations() const;
};

#endif
