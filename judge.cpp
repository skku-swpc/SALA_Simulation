#include "main.h"

// �ش� ��ǥ�� �߾ӿ� �ִ����� �Ǵ�
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