#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <algorithm>


using namespace std;
/*---------------------------------------------------*/

#define _SCL_SECURE_NO_WARNING
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define N 20		// Maximum I.A number
#define M 100000		
#define NUM_CASES 100

#define MAX_WEIGHTTABLE 3

#define MAP_X 930	// MAP 가로 크기
#define MAP_Y 1010	// MAP 세로 크기
#define MARGIN 100	// 벽 근처에 있다고 판단할 거리

#define INF 0xFFFFFFF

#define CENTER 0
#define WALL 1
#define CORNER 2

#define big(x,y) ((x<y)?(y):(x))
#define sml(x,y) ((x<y)?(x):(y))

struct point{
	double x, y, power, rad, ch;

	point(){}
	point(double _x, double _y){ x = _x, y = _y; }

	point operator+(point p){ return point(x + p.x, y + p.y); }
	point operator-(point p){ return point(x - p.x, y - p.y); }
	point operator*(double d){ return point(x * d, y * d); }
	point operator/(double d){ return point(x / d, y / d); }
	double operator*(point p){ return x * p.y - y * p.x; }
	bool operator==(point p){ return x == p.x && y == p.y; }
	bool operator!=(point p){ return x != p.x || y != p.y; }

	double magnitude(){ return hypot(x, y); }
	point normalization(){ return (*this) / this->magnitude(); }
	point rotate_clockwise(){ return point(y, -x); }
	point rotate_counterclockwise(){ return point(-y, x); }
};

static bool comY (point x, point y){return x.y<y.y;}
static bool comR (point x, point y){return x.rad<y.rad;}
static bool comX (point x, point y){return x.x<y.x;}
static bool comP(point x, point y){ return x.power < y.power; }


void read_location (int index);
void read_matlist(int fixed = -1);
void regression ();
void set_parameter ();

int judge (point *, int);

void circum (point, point, point);
void get_circum (vector<point> *);
void get_median (vector<point> *);
void get_convex (vector<point> *);
void use_density (vector<point> *);
void result (vector<point> *);

void longest_pair (vector<point> *);
void real_method (vector<point> *);
void minmax (vector<point> *,int,int);
void allpoint (vector<point> *);

void print_error (point *);
void print_data (int);
void print_result(int index);

void init ();
double dis (point, point);
bool is_clock (point x, point y, point z);
bool in_map (double, double);
bool in_range (double, double, point, point, point);
void internal (point x, point y, int m, int n);

// 준비작업
void reduce_multipath1(vector<point> * v, double size);
void reduce_multipath2(vector<point> * v, point * location);
void reduce_multipath3(vector<point> * v, point * location, map<double, double> * powerMap);
void reduce_multipath4(vector<point> * v, double size);

// 내부함수
void calcPowerMap(vector<point> * v, point * res, map<double, double> * powerMap);
double getAvgDist1(map<double, double> & powerMap, double power, double range);
double getAvgDist2(map<double, double> & powerMap, double power, int num);
double getAvgSD(map<double, double> & powerMap, double power, int num, double mean);
void divide(vector<point> * v1, vector<point> v2[N][MAX_WEIGHTTABLE]);

// 주요함수
void convex_func(vector<point> * v1, vector<point> v2[N][MAX_WEIGHTTABLE], point * res);
void average1(vector<point> * v, point * res);
void average2(vector<point> * v, point * res, int index = 0);
void average3(vector<point> v[N][MAX_WEIGHTTABLE], point * res);
void getStrong(vector<point> * v, bool b[12][M]);
void rate1(vector<point> v[N], point * res);
void rate2(vector<point> v[N], point * res, map<double, double> * powerMap);
void passive_reg(vector<point> * data, point * res);
point corner_revision(vector<point> &sig, double R);

vector<point> without_convex_hull(vector<point> &p);
point PCA(vector<point> &mat);
