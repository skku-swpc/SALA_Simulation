#include "main.h"
#include "Gaussian.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <map>
#include <functional>

void reduce_multipath1(vector<point> *v, double size)
{
	for (int k = 2; k < 12; ++k)
	{
		bool b[M] = { false, };

		/*	for (int i = 0; i < v[k].size(); ++i)
		{
		bool bResult = false;
		for (int j = 0; j < v[k].size(); ++j)
		{
		if (i == j)
		continue;

		// 같은 격자 안에 있고 i가 j보다 power가 낮다
		if (floor(v[k][i].x / size) == floor(v[k][j].x / size) &&
		floor(v[k][i].y / size) == floor(v[k][j].y / size) &&
		v[k][i].power < v[k][j].power )
		{
		bResult = true;
		break;
		}
		}

		b[i] = bResult;
		}*/

		map<pair<int, int>, pair<int, double>> max;

		for (int i = 0; i < v[k].size(); ++i)
		{
			pair<int, int> p = make_pair(floor(v[k][i].x / size), floor(v[k][i].y / size));

			map<pair<int, int>, pair<int, double>>::iterator it = max.find(p);
			if (it != max.end())
			{
				if (it->second.second < v[k][i].power)
				{
					b[it->second.first] = true;
					it->second.first = i;
					it->second.second = v[k][i].power;
				}
				else
					b[i] = true;
			}
			else
				max.insert(make_pair(p, make_pair(i, v[k][i].power)));
		}

		vector<point> temp;
		for (int i = 0; i < v[k].size(); ++i)
		{
			if (b[i] == false)
				temp.push_back(v[k][i]);
		}

		v[k].assign(temp.begin(), temp.end());
	}
}

void reduce_multipath4(vector<point> *v, double size)
{
	for (int k = 2; k < 12; ++k)
	{
		bool b[M] = { false, };

		map<pair<int, int>, pair<int, double>> max;

		for (int i = 0; i < v[k].size(); ++i)
		{
			pair<int, int> p = make_pair(floor(v[k][i].x / size), floor(v[k][i].y / size));

			map<pair<int, int>, pair<int, double>>::iterator it = max.find(p);
			if (it != max.end()){
				++it->second.first;
				it->second.second += v[k][i].power;
			}
			else
				max.insert(make_pair(p, make_pair(1, v[k][i].power)));
		}

		for (int i = 0; i < v[k].size(); ++i)
		{
			pair<int, int> p = make_pair(floor(v[k][i].x / size), floor(v[k][i].y / size));

			map<pair<int, int>, pair<int, double>>::iterator it = max.find(p);
			if (it == max.end())
				b[i] = true;
			else if (abs(it->second.second / (double)it->second.first - v[k][i].power) / v[k][i].power > 0.3)
				b[i] = true;
		}

		vector<point> temp;
		for (int i = 0; i < v[k].size(); ++i)
		{
			if (b[i] == false)
				temp.push_back(v[k][i]);
		}

		v[k].assign(temp.begin(), temp.end());
	}
}

void reduce_multipath2(vector<point> *v, point * location)
{
	vector<pair<double, double>> rate[N];

	for (int k = 2; k < 12; ++k)
	{
		bool b[M] = { false, };

		for (int i = 0; i < v[k].size(); ++i)
		{
			// (Pt * lambda * lambda * Gt * Gr / (16.0 *M_PI * M_PI * pow(distance, alpha) * L))
			// Pt 15 lambda 0.124914 Gt 1 Gr 1 distance 260.192 L 1 PI 3.14159 alpha 2
			// lambda = light(299792458) / 2.4GHz
			// 299,792,458, 2,400,000,000

			double x = location[k].x - v[k][i].x;
			double y = location[k].y - v[k][i].y;
			double dist = sqrt(x*x + y*y);
			double lambda = 299792458.0 / 2400000000.0;

			double diff = abs((15.0*lambda*lambda / (16.0*M_PI*M_PI * pow(dist, 2.0))) - v[k][i].power);
			double rate = diff / v[k][i].power;

			if (rate >= 0.3)
				b[i] = true;
		}

		vector<point> temp;
		for (int i = 0; i < v[k].size(); ++i)
		{
			if (b[i] == false)
				temp.push_back(v[k][i]);
		}

		v[k].assign(temp.begin(), temp.end());
	}
}

void reduce_multipath3(vector<point> * v, point * location, map<double, double> * powerMap)
{
	vector<pair<double, double>> rate[N];

	for (int k = 2; k < 12; ++k)
	{
		bool b[M] = { false, };

		for (int i = 0; i < v[k].size(); ++i)
		{
			double x = location[k].x - v[k][i].x;
			double y = location[k].y - v[k][i].y;
			double dist = sqrt(x*x + y*y);

			double diff = abs(getAvgDist2(powerMap[k], v[k][i].power, 10) - dist);
			double rate = diff / dist;

			if (rate >= 0.2)
				b[i] = true;
		}

		vector<point> temp;
		for (int i = 0; i < v[k].size(); ++i)
		{
			if (b[i] == false)
				temp.push_back(v[k][i]);
		}

		v[k].assign(temp.begin(), temp.end());
	}
}

void calcPowerMap(vector<point> * v, point * res, map<double, double> * powerMap)
{
	for (int k = 0; k < 12; ++k)
	{
		powerMap[k].clear();
		for (int i = 0; i < v[k].size(); ++i)
		{
			double x = v[k][i].x - res[k].x;
			double y = v[k][i].y - res[k].y;
			double dist = sqrt(x*x + y*y);
			powerMap[k].insert(make_pair(v[k][i].power, dist));
		}

		/*	map<double, double>::iterator it1 = powerMap[k].begin();
		map<double, double>::iterator it2 = powerMap[k].begin();
		map<double, double>::iterator it3 = powerMap[k].begin();
		vector<map<double, double>::iterator> error;

		while (it1 != powerMap[k].end())
		{
		if (abs(it2->second - it3->second) + abs(it2->second - it1->second) > 200)
		error.push_back(it2);

		it3 = it2;
		it2 = it1;
		++it1;
		}

		for (int i = 0; i < error.size(); ++i)
		{
		powerMap[k].erase(error[i]);
		//	error[i]->second = -1.0;
		}*/
	}
}

double getAvgDist1(map<double, double> & powerMap, double power, double range)
{
	double result = 0.0;
	int cnt = 0;

	map<double, double>::iterator it;
	for (it = powerMap.begin(); it != powerMap.end(); ++it)
	{
		if (it->first < power - range)
			continue;
		else if (it->first <= power + range){
			result += it->second;
			++cnt;
		}
		else
			break;
	}

	return result / (double)cnt;
}

double getAvgDist2(map<double, double> & powerMap, double power, int num)
{
	double result = 0.0;
	int cnt = 0;

	map<double, double, greater<double>>::iterator it;

	/*if (powerMap.size() < num){
		for (it = powerMap.begin(); it != powerMap.end(); ++it)
			result += it->second;
		return result / (double)powerMap.size();
	}*/

	it = powerMap.find(power);

	if (it != powerMap.end())
	{
		if (it->second < 0.0)
			return -1.0;

		map<double, double>::reverse_iterator left(it);
		map<double, double>::iterator right(it);

		/*if (it != powerMap.begin())*/{
			for (cnt = 0; cnt < num / 2; ++cnt)
			{
				result += left->second;

				++left;
				if (left == powerMap.rend())
					break;
			}
		}

		for (; cnt < num; ++cnt)
		{
			++right;
			if (right == powerMap.end())
				break;

			result += right->second;
		}

		for (; cnt < num; ++cnt)
		{
			++left;
			if (left == powerMap.rend())
				break;

			result += left->second;
		}

		/*	for (cnt = 0; cnt < num / 2; ++cnt)
		{
		if (left->second < 0.0)
		--cnt;
		else
		result += left->second;

		++left;
		if (left == powerMap.rend())
		break;
		}

		for (; cnt < num; ++cnt)
		{
		++right;
		if (right == powerMap.end())
		break;

		if (left->second < 0.0)
		--cnt;
		else
		result += right->second;
		}

		for (; cnt < num; ++cnt)
		{
		++left;
		if (left == powerMap.rend())
		break;

		if (left->second < 0.0)
		--cnt;
		else
		result += left->second;
		}*/

		return result / (double)cnt;
	}
	else
		return -1.0;
}

double getAvgSD(map<double, double> & powerMap, double power, int num, double mean)
{
	double result = 0.0;
	int cnt = 0;

	map<double, double, greater<double>>::iterator it;

	/*if (powerMap.size() < num){
		for (it = powerMap.begin(); it != powerMap.end(); ++it)
			result += (it->second - mean)*(it->second - mean);
		return result / (double)powerMap.size();
	}*/

	it = powerMap.find(power);

	if (it != powerMap.end())
	{
		if (it->second < 0.0)
			return -1.0;

		map<double, double>::reverse_iterator left(it);
		map<double, double>::iterator right(it);

		/*if (it != powerMap.begin())*/{
			for (cnt = 0; cnt < num / 2; ++cnt)
			{
				result += (left->second - mean)*(left->second - mean);

				++left;
				if (left == powerMap.rend())
					break;
			}
		}

		for (; cnt < num; ++cnt)
		{
			++right;
			if (right == powerMap.end())
				break;

			result += (right->second - mean)*(right->second - mean);
		}

		for (; cnt < num; ++cnt)
		{
			++left;
			if (left == powerMap.rend())
				break;

			result += (left->second - mean)*(left->second - mean);
		}

		/*	for (cnt = 0; cnt < num / 2; ++cnt)
		{
		if (left->second < 0.0)
		--cnt;
		else
		result += (left->second-mean)*(left->second-mean);

		++left;
		if (left == powerMap.rend())
		break;
		}

		for (; cnt < num; ++cnt)
		{
		++right;
		if (right == powerMap.end())
		break;

		if (left->second < 0.0)
		--cnt;
		else
		result += (right->second - mean)*(right->second - mean);
		}

		for (; cnt < num; ++cnt)
		{
		++left;
		if (left == powerMap.rend())
		break;

		if (left->second < 0.0)
		--cnt;
		else
		result += (left->second-mean)*(left->second-mean);
		}*/

		return result / (double)cnt;
	}
	else
		return -1.0;
}

void divide(vector<point> * v1, vector<point> v2[N][MAX_WEIGHTTABLE])
{
	double threshold = 0.000000050;
	double range[MAX_WEIGHTTABLE - 1] = { 0.000000150, 0.000000900 };

	for (int k = 2; k < 12; ++k)
	{
		for (int i = 0; i < MAX_WEIGHTTABLE; ++i)
			v2[k][i].clear();

		for (int i = 0; i < v1[k].size(); ++i)
		{
			if (v1[k][i].power <= threshold)
				continue;

			int n;
			for (n = 0; n < MAX_WEIGHTTABLE - 1; ++n)
			{
				if (v1[k][i].power <= range[n])
					break;
			}

			v2[k][n].push_back(v1[k][i]);
		}
	}
}

extern vector<point> convex[N];	// Convex Hull 담음
extern point partRes[N][MAX_WEIGHTTABLE];

void convex_func(vector<point> * v1, vector<point> v2[N][MAX_WEIGHTTABLE], point * res)
{
	vector<point> backup[N];

	for (int i = 0; i < 12; ++i)
		backup[i].assign(v1[i].begin(), v1[i].end());

	for (int j = 0; j < MAX_WEIGHTTABLE; ++j)
	{
		for (int k = 2; k < 12; ++k)
		{
			int ind = j;
			if (v2[k][ind].size() < 10)
			{
				ind = MAX_WEIGHTTABLE - 1;
				while (v2[k][ind].size() < 10)
					--ind;
			}

			v1[k].assign(v2[k][ind].begin(), v2[k][ind].end());
			convex[k].clear();
		}

		get_convex(v1);
		real_method(convex);
		for (int k = 2; k < 12; ++k)
		{
			if (judge(res, k) == CENTER)
				minmax(v1, k, k);
		}

		for (int k = 2; k < 12; ++k)
			partRes[k][j] = res[k];
	}

	for (int j = 2; j < 12; ++j)
	{
		res[j].x = 0.0;
		res[j].y = 0.0;
	}

	double weightTable[MAX_WEIGHTTABLE] = { 0.2, 0.3, 0.5 };

	for (int j = 2; j < 12; ++j)
	{
		for (int k = 0; k < MAX_WEIGHTTABLE; ++k)
		{
			res[j].x += partRes[j][k].x * weightTable[k];
			res[j].y += partRes[j][k].y * weightTable[k];
		}
	}

	for (int i = 0; i < 12; ++i)
		v1[i].assign(backup[i].begin(), backup[i].end());
}

void average1(vector<point> * v, point * res)
{
	for (int k = 2; k < 12; ++k)
	{
		int cnt = 0;
		for (int i = 0; i < v[k].size(); ++i)
		{
			if (v[k][i].power > 0.000001000)
			{
				res[k].x += v[k][i].x;
				res[k].y += v[k][i].y;
				++cnt;
			}
		}

		if (cnt > 0)
		{
			res[k].x /= (double)cnt;
			res[k].y /= (double)cnt;
		}
	}
}

void average2(vector<point> * v, point * res, int index)
{
	int maxcount = 3;

	for (int k = 2; k < 12; ++k)
	{
		if (index != 0)
			k = index;

		res[k].x = 0.0;
		res[k].y = 0.0;

		bool b[M] = { false, };
		int cnt = 0;

		for (int i = 0; i < maxcount; ++i)
		{
			double max = 0.0;
			int ind = -1;

			for (int j = 0; j < v[k].size(); ++j)
			{
				if (v[k][j].power > max && b[j] == false)
				{
					max = v[k][j].power;
					ind = j;
				}
			}

			if (ind == -1)
				break;

			if (i == 0)
			{
				int x = v[k][ind].x;
				int y = v[k][ind].y;
				if ((x <= MARGIN && y <= MARGIN) || (x <= MARGIN && y >= MAP_Y - MARGIN) || (x >= MAP_X - MARGIN && y <= MARGIN) || (x >= MAP_X - MARGIN && y >= MAP_Y - MARGIN))
					maxcount = 1;
				else if (x <= MARGIN || y <= MARGIN || x >= MAP_X - MARGIN || y >= MAP_Y - MARGIN)
					maxcount = 3;
				else
					maxcount = 5;
			}

			point temp = v[k][ind];

			res[k].x += v[k][ind].x;
			res[k].y += v[k][ind].y;
			b[ind] = true;
			++cnt;
		}

		if (cnt > 0)
		{
			res[k].x /= (double)cnt;
			res[k].y /= (double)cnt;
		}

		if (index != 0)
			break;
	}
}

void average3(vector<point> v[N][MAX_WEIGHTTABLE], point * res)
{
	for (int k = 2; k < 12; ++k)
	{
		int cnt = 0;
		for (int i = 0; i < MAX_WEIGHTTABLE; ++i){
			for (int j = 0; j < v[i][k].size(); ++j)
			{

			}
		}
	}
}

double weight[931][1011] = { 0, };

void rate1(vector<point> v[N], point * res)
{
	for (int k = 2; k < 12; ++k)
	{
		for (int i = 1; i <= 930; ++i){
			for (int j = 1; j <= 1010; ++j)
			{
				weight[i][j] = 0;
			}
		}

		// (Pt * lambda * lambda * Gt * Gr / (16.0 *M_PI * M_PI * pow(distance, alpha) * L))
		// Pt 15 lambda 0.124914 Gt 1 Gr 1 distance 260.192 L 1 PI 3.14159 alpha 2
		// lambda = light(299792458) / 2.4GHz
		// 299,792,458, 2,400,000,000
		// abs((15.0*lambda*lambda / (16.0*M_PI*M_PI * pow(dist, 2.0))) - v[k][i].power);
		// 15.0*lambda*lambda / (16.0*M_PI*M_PI * dist*dist) = power
		// sqrt(15.0*lambda*lambda / (16.0*M_PI*M_PI*power)) = dist

		double lambda = 299792458.0 / 2400000000.0;

		for (int i = 0; i < v[k].size(); ++i)
		{
			//	if (v[k][i].power < 0.000000050)
			//		continue;

			double dist = sqrt(15.0*lambda*lambda / (16.0*M_PI*M_PI*v[k][i].power));

			int x1 = floor(v[k][i].x - dist * 1.6);
			int y1 = floor(v[k][i].y - dist * 1.6);
			int x2 = ceil(v[k][i].x + dist * 1.6);
			int y2 = ceil(v[k][i].y + dist * 1.6);

			x1 = x1 < 1 ? 1 : x1;
			y1 = y1 < 1 ? 1 : y1;
			x2 = 930 < x2 ? 930 : x2;
			y2 = 1010 < y2 ? 1010 : y2;

			for (int x = x1; x <= x2; ++x){
				for (int y = y1; y <= y2; ++y)
				{
					double diffx = v[k][i].x - (double)x;
					double diffy = v[k][i].y - (double)y;
					double diff = abs(sqrt(diffx*diffx + diffy*diffy) - dist);

					if (diff < dist)
						weight[x][y] += 1.0 - (diff / dist);
				}
			}
		}

		double max = 0;
		double threshold = 0.05;
		int maxcount = 0;

		for (int i = 1; i <= 930; ++i){
			for (int j = 1; j <= 1010; ++j)
			{
				if (weight[i][j] > max)
					max = weight[i][j];
			}
		}

		double rx = 0.0;
		double ry = 0.0;

		for (int i = 1; i <= 930; ++i){
			for (int j = 1; j <= 1010; ++j)
			{
				if (abs(weight[i][j] - max) / max <= threshold)
				{
					++maxcount;
					rx += i;
					ry += j;
				}
			}
		}

		if (maxcount != 0)
		{
			res[k].x = rx / (double)maxcount;
			res[k].y = ry / (double)maxcount;
		}
	}
}

double inline __declspec (naked) __fastcall fastsqrt(double n)
{
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}

void rate2(vector<point> v[N], point * res, map<double, double> * powerMap)
{
	for (int k = 2; k < 12; ++k)
	{
		for (int x = 1; x <= 930; ++x){
			for (int y = 1; y <= 1010; ++y)
			{
				weight[x][y] = 0;
			}
		}

		for (int i = 0; i < v[k].size(); ++i)
		{
			if (v[k][i].power < 0.000000050)
				continue;

			//	double dist = dis(v[k][i], res[k]);
			double dist = getAvgDist2(powerMap[k], v[k][i].power, 10);
			//double s = fastsqrt(getAvgSD(powerMap[k], v[k][i].power, 10, dist));

			// new revision 2

			//if (judge(res, k) != CENTER && v[k].size() < 50)
			//	dist *= 0.9;


			if (dist < 0.0 || 200.0 < dist)
				continue;

			int x1 = floor(v[k][i].x - dist * 1.5);
			int y1 = floor(v[k][i].y - dist * 1.5);
			int x2 = ceil(v[k][i].x + dist * 1.5);
			int y2 = ceil(v[k][i].y + dist * 1.5);

			x1 = x1 < 1 ? 1 : x1;
			y1 = y1 < 1 ? 1 : y1;
			x2 = 930 < x2 ? 930 : x2;
			y2 = 1010 < y2 ? 1010 : y2;

			for (int x = x1; x <= x2; ++x){
				for (int y = y1; y <= y2; ++y)
				{
					double diffx = v[k][i].x - (double)x;
					double diffy = v[k][i].y - (double)y;
					double dist2 = fastsqrt(diffx*diffx + diffy*diffy);

					// passive
					double diff = abs(dist2 - dist);
					double rate = nomal_dist(0, 1, diff / dist * 3);

					// active
					//double rate = nomal_dist(dist, s, dist2);

					if (rate < 0)
						rate = 0;

					weight[x][y] += rate;
				}
			}
		}

		double max = 0;
		double threshold = 0.0002;
		int maxcount = 0;

		for (int i = 1; i <= 930; ++i){
			for (int j = 1; j <= 1010; ++j)
			{
				if (weight[i][j] > max)
					max = weight[i][j];
			}
		}

		double rx = 0.0;
		double ry = 0.0;

		for (int i = 1; i <= 930; ++i){
			for (int j = 1; j <= 1010; ++j)
			{
				if (abs(weight[i][j] - max) / max <= threshold)
				{
					++maxcount;
					rx += i;
					ry += j;
				}
			}
		}

		if (maxcount != 0)
		{
			res[k].x = rx / (double)maxcount;
			res[k].y = ry / (double)maxcount;
		}
	}
}

double dis(double x1, double y1, double x2, double y2)
{
	double xx = x2 - x1, yy = y2 - y1;
	return sqrt(xx*xx + yy*yy);
}

void passive_reg(vector<point> * data, point * res)
{
	struct point inp;

	int ia, i, j, k, l;
	int ax, ay;
	double time, x, y, p;
	double mul, sum, avg, dif;
	double mn;

	for (i = 2; i <= 11; i++)
	for (j = 0; j < data[i].size(); j++)
	{
		//printf("%d : %.0f %.0f %.3f\n", i, data[i][j].x, data[i][j].y, data[i][j].p);
	}

	for (ia = 2; ia <= 11; ia++)
	{
		mn = 1e10;
		for (i = 1; i <= 930; i += 5)
		for (j = 1; j <= 1010; j += 5)
		{
			dif = sum = 0;
			for (k = 0; k < data[ia].size(); k++)
			{
				sum += dis(i, j, data[ia][k].x, data[ia][k].y) * data[ia][k].power;
			}
			avg = sum / data[ia].size();

			for (k = 0; k < data[ia].size(); k++)
			{
				dif += abs(dis(i, j, data[ia][k].x, data[ia][k].y) * data[ia][k].power - avg);
			}
			if (mn > dif)
			{
				mn = dif;
				ax = i, ay = j;
			}
		B:
			continue;
		}
		res[ia].x = ax;
		res[ia].y = ay;
	}
}
/*
point corner_revision(vector<point> &sig, double R)
{
int n = (int)sig.size();
double XL, XR, YB, YT;
XL = MAP_X;
XR = 0;
YB = MAP_Y;
YT = 0;
for (int i = 0; i < n; i++)
{
XL = min(XL, sig[i].x);
XR = max(XR, sig[i].x);
YB = min(YB, sig[i].y);
YT = max(YT, sig[i].y);
}
//printf("%lf %lf %lf %lf\n", XL, XR, YB, YT);
point p, q;
double m = 99999999.;
for (p.x = XL; p.x < XR; p.x++)
{
for (p.y = YB; p.y < YT; p.y++)
{
int err = 0;
for (int i = 0; i < n; i++)
{
err += (p - sig[i]).magnitude();
}
if (err < m)
{
m = err;
q = p;
}
}
}
//printf("%d\n", n);
//printf("%lf %lf\n", q.x, q.y);
return q;
}
*/

point corner_revision(vector<point> &sig, double R)
{
	int n = (int)sig.size();
	double Mdis = 0;
	pair<point, point> Mpoint;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double dis = (sig[i] - sig[j]).magnitude();
			if (dis > Mdis)
			{
				Mdis = dis;
				Mpoint = make_pair(sig[i], sig[j]);
			}
		}
	}

	point Mvec = Mpoint.first - Mpoint.second;
	point Mmid = (Mpoint.first + Mpoint.second) / 2.;

	if (R * R < Mdis * Mdis / 4.)
		return Mmid;

	double revision_len = sqrt(R * R - Mdis * Mdis / 4.);

	point expect1 = Mmid + Mvec.rotate_clockwise().normalization() * revision_len;
	point expect2 = Mmid + Mvec.rotate_counterclockwise().normalization() * revision_len;

	//	point check;
	//	for (int i = 0; i < n; i++)
	//	{
	//		check = sig[i];
	//		if (check != Mpoint.first && check != Mpoint.second)
	//		{
	//			break;
	//		}
	//	}

	double dis1 = min(expect1.x, MAP_X - expect1.x) + min(expect1.y, MAP_Y - expect1.y);
	double dis2 = min(expect2.x, MAP_X - expect2.x) + min(expect2.y, MAP_Y - expect2.y);
	return dis1 < dis2 ? expect1 : expect2;
}
