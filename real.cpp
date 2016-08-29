#include "main.h"

extern double cx,cy;
extern vector<point> mat[N],cir[N],chos[N],convex[N];
extern point res[N];
extern int n;
extern char case_char[9];

void real_method (vector<point> *a)
{
	int i,j,k;
	double mx,r2,d,r,x,y,g, d1,d2;
	point p1,p2,temp;
	
//	char output[50]="out/";
//	strcat (strcat (output, case_char), "real.txt");
//	FILE *out = fopen (output,"w");

	// 가장 긴 지름
	r2=0;

	for (k=2;k<n;k++)
		for (i=0;i<a[k].size();i++)
			for (j=i;j<a[k].size();j++)
				r2 = big (r2, dis (a[k][i],a[k][j]));

	for (k=2;k<n;k++)
	{
		mx=0;
		for (i=0;i<a[k].size();i++)
			for (j=i;j<a[k].size();j++)
			{
				d = dis (a[k][i],a[k][j]);
				if (mx < d)
				{
					p1=a[k][i];
					p2=a[k][j];
					mx = d;
				}
			}

		r = sqrt (r2*r2 - mx*mx) / 4;
		g = (p1.x-p2.x)/(p1.y-p2.y);	// 기울기
		x = (p1.x+p2.x)/2; 
		y = (p1.y+p2.y)/2;

		if (r/r2 >= 0.05)
		{
			// 가능한 점이 2개가 있으므로 벽에 가까운 곳을 선택
		//	printf ("%2d : %.0f %.0f %.0f\n",k,p1.x,p1.y,r2);
			p1.x = x+r/sqrt(1+g*g);
			p1.y = y-r*g/sqrt(1+g*g);
		
			p2.x = x-r/sqrt(1+g*g);
			p2.y = y+r*g/sqrt(1+g*g);
		//	printf ("%2d : %.0f %.0f %.0f\n",k,p2.x,p2.y,r);
			d1=min (min (p1.y, abs(MAP_Y)-p1.y), min (p1.x, abs(MAP_X-p1.x)));
			d2=min (min (p2.y, abs(MAP_Y)-p2.y), min (p2.x, abs(MAP_X-p2.x)));
			if (d1>d2)
				temp=p1,p1=p2,p2=temp;
		}
		else
		{
			p1.x=p2.x=x;
			p1.y=p2.y=y;
		}
		p1.x=big (0,p1.x);
		p1.x=sml (p1.x,MAP_X);
		p1.y=big (0,p1.y);
		p1.y=sml (p1.y,MAP_Y);
		
		res[k].x = p1.x;
		res[k].y = p1.y;
		
	//	fprintf (out,"%2d %.0f %.0f\n",k,x,y);
	//	fprintf (out,"%.0f %.0f %.0f %.0f\n",p1.x,p1.y,p2.x,p2.y);
	}

//	fclose (out);
}


void longest_pair (vector<point> *a)
{
	int i,j,k;
	double d,mx,mn;
	point p1,p2,p3,ans,temp;
	
	char output[50]="out/";
	strcat (strcat (output, case_char), "long.txt");
	FILE *out = fopen (output,"w");

	for (k=2;k<12;k++)
	{
		mx=0;
		for (i=0;i<a[k].size();i++)
			for (j=i;j<a[k].size();j++)
			{
				d = dis (a[k][i], a[k][j]);
				if (mx < d)
				{
					mx = d;
					p1 = a[k][i];
					p2 = a[k][j];
				}
			}
		p3.x = (p1.x+p2.x)/2;
		p3.y = (p1.y+p2.y)/2;
		mn = M;
		for (i=0;i<a[k].size();i++)
		{
			circum (p1,p2, a[k][i]);
			if (in_range (cx,cy, p1,p2,a[k][i]))
			{
				temp.x=cx;
				temp.y=cy;
				cir[i].push_back (temp);
				
				d = dis (temp, p3);
				if (mn > d)
				{
					mn = d;
					ans = temp;
				}
			}
		}
		res[k].x=ans.x;
		res[k].y=ans.y;
		fprintf (out,"%2d %.0f %.0f\n",k,ans.x,ans.y);
		fprintf (out,"%.0f %.0f %.0f %.0f\n",p1.x,p1.y,p2.x,p2.y);
	}
	fclose (out);
}


void minmax (vector<point> *a, int s, int f)
{
	int i,j,k,x,y;
	double mnx,mny,mxx,mxy,d,inf;
	point p,ans;

	k=0;
	for (i=s;i<=f;i++)
	{
		mxx=mxy=0;
		mnx=MAP_X;
		mny=MAP_Y;
		for (j=0;j<a[i].size();j++)
		{
			mnx=sml (a[i][j].x, mnx);
			mxx=big (a[i][j].x, mxx);
			mny=sml (a[i][j].y, mny);
			mxy=big (a[i][j].y, mxy);
		}
		inf = 10000;
		for (x=mnx;x<=mxx;x++)
			for (y=mny;y<=mxy;y++)
			{
				d=0;
				for (j=0;j<a[i].size();j++)
				{
					k++;
					p.x=x,p.y=y;
					d=big (d,dis (p, a[i][j]));
				}
				if (d<inf)
				{
					ans.x=x,ans.y=y;
					inf=d;
				}
			}	
	//	printf ("%2d : %d\n",i,k);
		res[i].x=ans.x;
		res[i].y=ans.y;
	}
}

void allpoint (vector<point> *a)
{
	int i,j,k,x,y;
	double mnx,mny,mxx,mxy,d,mx;
	point p,ans;

	k=0;
	for (i=2;i<12;i++)
	{
		mxx=mxy=0;
		mnx=MAP_X;
		mny=MAP_Y;
		for (j=0;j<a[i].size();j++)
		{
			mnx=sml (a[i][j].x, mnx);
			mxx=big (a[i][j].x, mxx);
			mny=sml (a[i][j].y, mny);
			mxy=big (a[i][j].y, mxy);
		}
		mx = INF;
		for (x=mnx;x<=mxx;x++)
			for (y=mny;y<=mxy;y++)
			{
				d=0;
				p.x=x,p.y=y;
				for (j=0;j<a[i].size();j++)
					d+=dis (p, a[i][j]);
				if (mx > d)
					mx=d,ans=p;
			}	
	//	printf ("%2d : %d\n",i,k);
		res[i].x=ans.x;
		res[i].y=ans.y;
	}
}