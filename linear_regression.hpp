#ifndef LINEAR_REGRESSION_HPP
#define LINEAR_REGRESSION_HPP

#include "data.hpp"

// Closed-form (normal equation) least-squares fit.
// Exact answer in one pass. Used here as the answer key for gradient descent.
class linear_regression
{
private:
	double m;
	double b;
	double xMean;
	double yMean;
public:
	linear_regression();
	linear_regression(const data_t& dataCsv);
	~linear_regression();
	double UseFormula(double x) const;
	void calculateM(const data_t& dataCsv);
	void calculateMeans(const data_t& dataCsv);
	void calculateB();

	//getters
	double getYMean() const;
	double getXMean() const;
	double getM() const;
	double getB() const;
};

#endif
