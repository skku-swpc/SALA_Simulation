/*******************************************************************
* Gaussian.h
* ------------------------------------------------------------------
* Windows7
* Visual Studio 2012
*
* 'gaussian' returns floating value from mean and standard deviation
* 'cutting'  returns floating value with cutting range
*
* must set random number table randomly like
*                      srand (time (NULL))
* when you use before 'gaussian' function
*
*******************************************************************/

#ifndef SALAp_GAUSSIAN_H
#define SALAp_GAUSSIAN_H

double gaussian (double mean, double standard_deviation);
double nomal_dist(double mean, double s, double x);
double cutting(double value, double mean, double range);

#endif