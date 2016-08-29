#include "main.h"

extern char f_matlist[50];
extern int Lx,Ly,Rx,Ry,range,per,dens_r,iaNum,n;

//	기본 파라미터 설정
void set_parameter ()
{
	strcpy (f_matlist, "data/MATlist");
	
	// 정보가전 id할당이 2부터 이루어짐
	n = 2+iaNum;

	dens_r = 100;
	Lx=Ly=0;
	range = 500;
	per = 20; // %
	Rx = MAP_X;
	Ry = MAP_Y;
}