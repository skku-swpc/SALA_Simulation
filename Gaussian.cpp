#define _USE_MATH_DEFINES

#include "Gaussian.h"
#include <stdlib.h>
#include <math.h>

double gaussian (double mean, double standard_deviation)
{
	double U1 = (double) rand() / RAND_MAX;
	double U2 = (double) rand() / RAND_MAX;
	return mean + standard_deviation * sqrt(-2 * log(U1)) * cos(2 * M_PI * U2);
}

inline double fastexp(double x) {
	x = 1.0 + x / 1024;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x;
	return x;
}

double nomal_dist(double mean, double s, double x)
{
	// 2.50662827463 = sqrt(2*pi)
	return exp((-1) * (x-mean)*(x-mean) / (2 * s*s)) / (2.50662827463 * s);
}

double cutting (double value, double mean, double range)
{
	if (value > mean + range) return mean + range;
	if (value < mean - range) return mean - range;
	return value;
}