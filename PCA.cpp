#include "main.h"

#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

point PCA(vector<point> &mat)
{
	// print process or not?
	bool print_flag = false;

	// data size
	int n = (int)mat.size();

	// covariance matrix
	double a, b;
	double c, d;
	a = b = c = d = 0;

	for (int i = 0; i < n; i++)
	{
		a += mat[i].x * mat[i].x;
		b = c += mat[i].x * mat[i].y;
		d += mat[i].y * mat[i].y;
	}

	// two eigenvalues are always exist and orthogonal when b = c, including covariance matrix
	double lambda1 = (a + d) / 2 + sqrt(4 * b * c + (a - d) * (a - d)) / 2;
	double lambda2 = (a + d) / 2 - sqrt(4 * b * c + (a - d) * (a - d)) / 2;

	double eigenvalue = fabs(lambda1) > fabs(lambda2) ? lambda1 : lambda2;
	point eigenvector = point(b, eigenvalue - a).normalization();

	if (b == 0.0 && eigenvalue - a == 0.0){
		eigenvector.x = 0.0;
		eigenvector.y = 0.0;
	}

	if (print_flag){
		printf("%.1lf %.1lf\n%.1lf %.1lf\n", a, b, c, d);
		printf("%.1lf %.1lf\n", lambda1, lambda2);
		printf("%.1lf <-> [%.3lf %.3lf]\n", eigenvalue, eigenvector.x, eigenvector.y);
	}

	return eigenvector;
}