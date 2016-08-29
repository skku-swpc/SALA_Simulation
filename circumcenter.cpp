#include "main.h"


extern vector<point> mat[N],cir[N],chos[N],convex[N];
extern int Lx,Ly,Rx,Ry,range,per,dens_r;
extern double cx,cy,densR[N];
extern bool flag;
extern char case_char[9];
extern point median[N],dens[N],res[N];


// make (cx,cy) as a circumcenter
// 주어진 세 점 x,y,z 의 외심 좌표를 (cx,cy)에 저장
void circum (point x, point y, point z)
{
    double a0,a1,b0,b1,c0,c1,d;

	a0=x.x,a1=x.y;
	b0=y.x,b1=y.y;
	c0=z.x,c1=z.y;
	d = (a0-c0)*(b1-c1) - (b0-c0)*(a1-c1);
	if (d==0)
	{
		flag=1;
		return;
	}
	cx=(((a0-c0)*(a0+c0) + (a1-c1)*(a1+c1))/2*(b1-c1) - ((b0-c0)*(b0+c0)+(b1-c1)*(b1+c1))/2*(a1-c1))/d;
	cy=(((b0-c0)*(b0+c0) + (b1-c1)*(b1+c1))/2*(a0-c0) - ((a0-c0)*(a0+c0)+(a1-c1)*(a1+c1))/2*(b0-c0))/d;
}

// N개 점들에 대해 (1,2,3), (2,3,4), .. (n-2,n-1,n) 의 외심을 cir[] 벡터에 저장
void get_circum (vector<point> *mt)
{
	int i,j;
	point temp;

	for (i=2;i<12;i++)
	{
		for (j=0;j<mt[i].size()-2;j++)
		{
			circum (mt[i][j], mt[i][j+1], mt[i][j+2]);
			if (in_range (cx,cy, mt[i][j], mt[i][j+1], mt[i][j+2]))
			{
				temp.x=cx;
				temp.y=cy;
				cir[i].push_back (temp);
			}
		}
	}
}

void get_median (vector<point> *a)
{
	int i,j;
	double x,y;
	vector<double> xx,yy;

	for (i=2;i<12;i++)
	{
		xx.clear();
		yy.clear();
		for (j=0;j<a[i].size();j++)
		{
			xx.push_back (a[i][j].x);
			yy.push_back (a[i][j].y);
		}
		sort (xx.begin(), xx.end());
		sort (yy.begin(), yy.end());

		//	Median 좌표
		median[i].x = xx[xx.size()/2];
		median[i].y = yy[yy.size()/2];

		// x,y 좌표값들의 per,100-p% 값들의 차를 이용해 반지름 계산
		x = (xx[xx.size()*(100-per)/100-1] - xx[xx.size()*per/100])/2;
		y = (yy[yy.size()*(100-per)/100-1] - yy[yy.size()*per/100])/2;
		densR[i] = sml (x,y);
		ret:
		for (j=0;j<a[i].size();j++)
		{
			if (dis (median[i], a[i][j]) < densR[i])
				chos[i].push_back (a[i][j]);
		}
		if (chos[i].size() < 1)
		{
			densR[i]+=sml (x,y);
			goto ret;
		}
	}
}


// 포인트 벡터 a의 convex hull에 해당하는 포인트들을 convex 벡터에 저장
void get_convex (vector<point> *a)
{
	int i,j,k,t,st[M];
	point temp;
	
	for (k=2;k<12;k++)
	{
		if (a[k].size() == 0)
			continue;

		sort (a[k].begin(), a[k].end(), comY);

		for (i=1;i<a[k].size();i++)
			a[k][i].rad = atan2 (a[k][i].y-a[k][0].y, a[k][i].x-a[k][0].x);
		
		sort (a[k].begin()+1, a[k].end(), comR);
		
		st[0]=t=0;
		if (a[k].size()>2)
		{
			st[1]=t=1;
			for (i=2;i<a[k].size();i++)
			{
				while (t>1 && is_clock (a[k][st[t-1]], a[k][st[t]], a[k][i]))
					t--;
				st[++t]=i;
			}
		}
		//printf ("convex %2d : %d\n",k,t);
		for (i=0;i<=t;i++)
			convex[k].push_back (a[k][st[i]]);
	}
}

void use_density (vector<point> *a)
{
	int i,j,k,p,mx,cnt;
	
	for (i=2;i<12;i++)
	{
		mx = 0;
		for (j=0;j<a[i].size();j++)
		{
			cnt=0;
			for (k=0;k<a[i].size();k++)
				if (dis (a[i][j], a[i][k]) < dens_r)
					cnt++;

			if (cnt>mx)
			{
				mx = cnt;
				p = j;
			}
		}

		for (j=0;j<a[i].size();j++)
			if (dis (a[i][j],a[i][p]) < dens_r)
			{
				dens[i].x+=a[i][j].x;
				dens[i].y+=a[i][j].y;
			}

		dens[i].x/=mx;
		dens[i].y/=mx;
	}
}

// 포인트 벡터 a 원소들의 평균좌표값을 res에 저장
void result (vector<point> *a)
{
	int i,j;

	for (i=2;i<12;i++)
	{
		for (j=0;j<a[i].size();j++)
		{
			res[i].x+=a[i][j].x;
			res[i].y+=a[i][j].y;
		}
		res[i].x/=a[i].size ();
		res[i].y/=a[i].size ();
	}
}

point O;

bool cmp_for_CV(point A, point B)
{
	point a = A - O;
	point b = B - O;
	return a * b > 0 || a * b == 0 && a.magnitude() < b.magnitude();
}

vector<point> without_convex_hull(vector<point> &p)
{
	vector<point> CV;
	vector<point> ret;
	int _O = 0;
	for (unsigned int i = 0; i < p.size(); i++)
		if (p[i].y < p[_O].y || p[i].y == p[_O].y && p[i].x > p[_O].x)
			_O = (int)i;
	swap(p[0], p[_O]);
	O = p[0];
	sort(p.begin() + 1, p.end(), cmp_for_CV);
	for (unsigned int i = 0; i < p.size(); i++)
	{
		while (CV.size() > 1 && ((CV[CV.size() - 1] - CV[CV.size() - 2]) * (p[i] - CV[CV.size() - 1])) <= 0)
		{
			ret.push_back(CV[CV.size() - 1]);
			CV.pop_back();
		}
		if (CV.empty() || CV[CV.size() - 1] != p[i])
			CV.push_back(p[i]);
	}
	return ret;
}