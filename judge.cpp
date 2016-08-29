#include "main.h"

// 해당 좌표가 중앙에 있는지를 판단
int judge (point *a, int k)
{
	double x,y;
	int i,cnt;

	x=a[k].x;
	y=a[k].y;

	if (MARGIN<=x && x<=MAP_X-MARGIN && MARGIN<=y && y<=MAP_Y-MARGIN)
		return CENTER;
	else
		return WALL + CORNER;
}