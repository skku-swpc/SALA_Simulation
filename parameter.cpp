#include "main.h"

extern char f_matlist[50];
extern int Lx,Ly,Rx,Ry,range,per,dens_r,iaNum,n;

//	�⺻ �Ķ���� ����
void set_parameter ()
{
	strcpy (f_matlist, "data/MATlist");
	
	// �������� id�Ҵ��� 2���� �̷����
	n = 2+iaNum;

	dens_r = 100;
	Lx=Ly=0;
	range = 500;
	per = 20; // %
	Rx = MAP_X;
	Ry = MAP_Y;
}