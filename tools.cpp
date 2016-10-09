#include "main.h"


extern vector<point> mat[N],cir[N],chos[N],convex[N];
extern int Lx,Ly,Rx,Ry,range,n;
extern double cx,cy;
extern point res[N];
extern point partRes[N][MAX_WEIGHTTABLE];
extern map<double, double> powerMap[N]; // power, distance

void init ()
{
	int i;

	for (i=2;i<n;i++)
	{
		mat[i].clear();
		cir[i].clear();
		chos[i].clear();
		convex[i].clear();
		powerMap[i].clear();
		res[i].x=res[i].y=0;

		for (int j = 0; j < MAX_WEIGHTTABLE; ++j){
			partRes[i][j].x = 0;
			partRes[i][j].y = 0;
		}
	}
}

// distance between two point
double dis (struct point x, struct point y)
{
    double xx,yy;
    xx=x.x-y.x;
    yy=x.y-y.y;
    return sqrt (xx*xx + yy*yy);
}

// x-y-z 가 시계방향이면 1
bool is_clock (point x, point y, point z){
    return x.x*y.y + y.x*z.y + z.x*x.y < y.x*x.y + z.x*y.y + x.x*z.y;
}


// if the point in map
bool in_map (double x, double y)
{
	if (!(x>=Lx&&y>=Ly&&x<=Rx&&y<=Ry))
		return false;
	return true;
}

bool in_range (double xx, double yy, point x, point y, point z)
{
	point a;
	a.x=xx,a.y=yy;
	if (dis(a,x)>range || dis(a,y)>range || dis(a,z)>range)
		return false;
	return true;
}

// x,y를 m:n 비중 할당
void internal (point x, point y, int m, int n)
{
	cx = (x.x*m + y.x*n) / (m+n);
	cy = (x.y*m + y.y*n) / (m+n);
}

// 버전 정보 얻기
char *getSALAversion () 
{
	return VERSION;
}