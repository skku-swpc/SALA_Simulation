#include <cmath>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define N 20	// ia number
#define M 10000	// point number
#define PI 3.141592
#define X 70	// Weight 비율

#define DenS 100	// density square 크기
#define Dens 100	// 포함시킬 영역

int idx=10;		// Case Number
char index[5];	// index -> char

using namespace std;
struct point{
	double x,y,rad,ch;};

vector<struct point> mat[N];
vector<struct point> hull[N];
vector<struct point> re[N];		// convex 전
vector<struct point> rec[N];	// convex 후

double er[N],erc[N],erw[N],erd[N];	// distance error 

struct point loc[N];	// original location
struct point cir[N],circ[N];	// circumcenter
struct point dens[N],cent[N];	// density-used
struct point wcir[N],wcirc[N];	// weight-circum


void init ()
{
	for (int i=2;i<12;i++)
	{
		mat[i].clear();
		hull[i].clear();
		re[i].clear();
		rec[i].clear();
		cir[i].x=cir[i].y=0;
		circ[i].x=circ[i].y=0;
		dens[i].x=dens[i].y=0;
	}
}

/*--------------- MAIN --------------------*/
int main ()
{
	int limit;
	Lx=Ly=0, Rx=1395, Ry=780;
	range = 300;
	
	for (int i=idx;i<=limit;i++)
	{
		idx=i;
		init ();
		in_matlist ();

		before_convex ();
		get_convex ();

		make_weight ();
		print_data ();

		fflush(stdin),getchar ();
		cnt++;
	}
}
/*-----------------------------------------*/

void make_weight ()
{
	int i;

	for (i=2;i<12;i++)
	{
		if (!cnt)
		{
			wcirc[i].x=circ[i].x;
			wcirc[i].y=circ[i].y;
		}

		internal (wcirc[i], circ[i], X, 100-X);
		wcirc[i].x=cx;
		wcirc[i].y=cy;
		erw[i] = dis (loc[i],wcirc[i]);
		//printf ("%2d : %.0f %.0f / %.0f %.0f -> %.0f\n",i,loc[i].x,loc[i].y,wcirc[i].x,wcirc[i].y, erw[i]-erc[i]);
	}
}


void before_convex ()
{
	int i,j;
	struct point temp;

	for (i=2;i<12;i++)
	{
		for (j=0;j<mat[i].size()-2;j++)
		{
			circum (mat[i][j], mat[i][j+1], mat[i][j+2]);
			if (inside_dis (cx,cy, mat[i][j], mat[i][j+1], mat[i][j+2]))
			{
				temp.x=cx;
				temp.y=cy;
				re[i].push_back (temp);
				cir[i].x+=cx;
				cir[i].y+=cy;
			}
		}

		cir[i].x/=re[i].size();
		cir[i].y/=re[i].size();
		er[i] = dis (loc[i],cir[i]);
		printf ("%2d : %.0f %.0f / %d / %.0f %.0f -> %.0f\n",i,loc[i].x,loc[i].y,re[i].size(),cir[i].x,cir[i].y, er[i]);
	}
	printf ("---------------\n");
}

void get_convex ()
{
	int i,j,k,t,st[M];
	struct point temp;

	for (k=2;k<12;k++)
	{
		sort (mat[k].begin(), mat[k].end(), comY);
		for (i=1;i<mat[k].size();i++)
			mat[k][i].rad = atan2 (mat[k][i].y-mat[k][0].y, mat[k][i].x-mat[k][0].x);
		sort (mat[k].begin()+1, mat[k].end(), comR);

		st[0]=0,st[1]=t=1;
		for (i=2;i<mat[k].size();i++)
		{
			while (t>1 && clock (mat[k][st[t-1]], mat[k][st[t]], mat[k][i]))
				t--;
			st[++t]=i;
		}
		for (i=0;i<=t;i++)
			hull[k].push_back (mat[k][st[i]]);
	}
	
	for (i=2;i<12;i++)
	{
		for (j=0;j<hull[i].size()-2;j++)
		{
			circum (hull[i][j], hull[i][j+1], hull[i][j+2]);
			if (inside_dis (cx,cy, mat[i][j], mat[i][j+1], mat[i][j+2]))
			{
				temp.x=cx;
				temp.y=cy;
				rec[i].push_back (temp);
				circ[i].x+=cx;
				circ[i].y+=cy;
			}
		}

		circ[i].x/=rec[i].size();
		circ[i].y/=rec[i].size();
		erc[i] = dis (loc[i], circ[i]);

	//	printf ("%2d : %.0f %.0f / %.0f %.0f -> %.0f %.0f\n",i,loc[i].x,loc[i].y,circ[i].x,circ[i].y, erc[i], erc[i]-er[i]);
	}

	use_density ();
}

void use_density ()
{
	int i,j,k,p,mx,cnt;

	for (i=2;i<12;i++)
	{
		mx = 0;
		for (j=0;j<re[i].size();j++)
		{
			cnt=0;
			for (k=0;k<re[i].size();k++)
				if (dis (re[i][j], re[i][k]) < DenS)
					cnt++;

			if (cnt>mx)
			{
				mx = cnt;
				p = j;
			}
		}

		for (j=0;j<re[i].size();j++)
			if (dis (re[i][j],re[i][p]) < Dens)
			{
				dens[i].x+=re[i][j].x;
				dens[i].y+=re[i][j].y;
			}

		cent[i] = re[i][p];
		dens[i].x/=mx;
		dens[i].y/=mx;
		erd[i] = dis (dens[i], loc[i]);
	}
}
