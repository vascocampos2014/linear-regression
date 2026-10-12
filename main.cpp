#include "data.hpp"
#include "linear_regression.hpp"
#include "gradient_descend.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
	string file = (argc > 1) ? argv[1] : "./data.csv";

	try
	{
		data_t data = parseCSV(file);
		if (data.count == 0)
		{
			cerr << "Error: no usable data in " << file << endl;
			return (1);
		}

		cout << fixed << setprecision(4);
		cout << "file: " << file << "    points: " << data.count << endl;

		// --- the exact answer, by algebra -------------------------------
		linear_regression exact(data);
		cout << endl << "closed form" << endl;
		cout << "  m = " << exact.getM() << "    b = " << exact.getB() << endl;

		// --- the same answer, by walking downhill ----------------------
		cout << endl << "gradient descent  (alpha " << DEFAULT_ALPHA
		     << ", " << DEFAULT_ITER << " iterations)" << endl;
		gradient_descend gd(data);
		cout << "  m = " << gd.getM() << "    b = " << gd.getB() << endl;

		// --- did the walk arrive? -------------------------------------
		cout << endl << "gap" << endl;
		cout << "  m off by " << fabs(gd.getM() - exact.getM()) << endl;
		cout << "  b off by " << fabs(gd.getB() - exact.getB()) << endl;

		double sample = data.arrA[0];
		cout << endl << "prediction at x = " << sample << endl;
		cout << "  closed form      " << exact.UseFormula(sample) << endl;
		cout << "  gradient descent " << gd.UseFormula(sample) << endl;
		cout << "  actual           " << data.arrB[0] << endl;
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return (1);
	}
	return (0);
}
