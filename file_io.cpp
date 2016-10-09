#include "main.h"
#include "Gaussian.h"

#define _USE_MATH_DEFINES

#include <math.h>


extern char f_matlist[50];
extern point location[NUM_CASES][N];
extern vector<point> mat[N];
extern int case_idx, iaNum;
extern char case_char[9], info[2][50];

extern point room[10][2], room2[10][2];

// 방 정보 불러오기
int read_roomInfo(char *path) {

	FILE * fin = fopen(path, "rt");

	if (fin == NULL) {
		return -1;
	}

	int roomSize, roomSize2;
	fscanf(fin, "%d", &roomSize);
	roomSize2 = roomSize * 9;
	for (int i = 0; i < roomSize; ++i)
	{
		fscanf(fin, "%lf %lf", &room[i][0].x, &room[i][0].y);
		fscanf(fin, "%lf %lf", &room[i][1].x, &room[i][1].y);

		point temp[2];
		temp[0].x = room[i][1].x;
		temp[0].y = room[i][0].y;
		temp[1].x = room[i][0].x;
		temp[1].y = room[i][1].y;

		room2[i * 9 + 0][0] = room[i][0];
		room2[i * 9 + 0][1] = room[i][0] + point(MARGIN, MARGIN);
		room2[i * 9 + 1][0] = room[i][0] + point(MARGIN, 0);
		room2[i * 9 + 1][1] = temp[0] + point(-MARGIN, -MARGIN);
		room2[i * 9 + 2][0] = temp[0] + point(-MARGIN, 0);
		room2[i * 9 + 2][1] = temp[0] + point(0, MARGIN);
		room2[i * 9 + 3][0] = room[i][0] + point(0, MARGIN);
		room2[i * 9 + 3][1] = temp[1] + point(MARGIN, -MARGIN);
		room2[i * 9 + 4][0] = temp[1] + point(0, -MARGIN);
		room2[i * 9 + 4][1] = temp[1] + point(MARGIN, 0);
		room2[i * 9 + 5][0] = temp[1] + point(MARGIN, -MARGIN);
		room2[i * 9 + 5][1] = room[i][1] + point(-MARGIN, 0);
		room2[i * 9 + 6][0] = room[i][1] + point(-MARGIN, -MARGIN);
		room2[i * 9 + 6][1] = room[i][1];
		room2[i * 9 + 7][0] = temp[0] + point(-MARGIN, MARGIN);
		room2[i * 9 + 7][1] = room[i][1] + point(0, -MARGIN);
		room2[i * 9 + 8][0] = room[i][0] + point(MARGIN, MARGIN);
		room2[i * 9 + 8][1] = room[i][1] + point(-MARGIN, -MARGIN);
	}
	fclose(fin);

	return 0;
}

// IA들의 위치 저장
void read_location(int index)
{
	int ia;
	double x, y;

	char loc[50];
	sprintf(loc, "./data/location%d.txt", index);
	FILE *in = fopen(loc, "r");
	while (~fscanf(in, "%d%lf%lf", &ia, &x, &y))
	{
		location[index - 1][ia].x = x;
		location[index - 1][ia].y = y;
	}
	fclose(in);
}

void read_matlist(int fixed)
{
	int ia;
	struct point temp;

	itoa(case_idx, case_char, 10);
	FILE *in = fopen(strcat(strcat(f_matlist, case_char), ".txt"), "r");
	//	printf ("%s\n",f_matlist);

//	char tmpstr[30] = "./out/point_with_error_";
//	FILE *out = fopen(strcat(strcat(tmpstr, case_char), ".txt"), "w");

	/*fgets (info[0], sizeof(info[0]), in);
	fgets (info[1], sizeof(info[1]), in);
	printf ("%s\n",info[1]);*/

	while (~fscanf(in, "%d %lf %lf %lf", &ia, &temp.power, &temp.x, &temp.y))
	{
		double error;
		
		if (fixed >= 0)
			error = cutting(gaussian(0, fixed), 0, fixed*2);
		else
			error = cutting(gaussian(0, 50), 0, 100);

		double angle = rand() / (double)INT_MAX * 2*M_PI;

		temp.x += error * cos(angle);
		temp.y += error * sin(angle);

	//	fprintf(out, "%d %lf %lf\n", ia, temp.x, temp.y);

		mat[ia].push_back(temp);
	}
	fclose(in);
//	fclose(out);
}

void regression()
{
	int i, j;

	FILE *input = fopen("out.txt", "r");
	for (i = 2; i<2 + iaNum; i++)
	{
		sort(mat[i].begin(), mat[i].end(), comX);
		/*for (j=0;j<mat[i].size();j++)
		printf ("(%.0f %.0f) ",mat[i][j].x,mat[i][j].y);printf("\n");*/
		/*for (j=0;j<mat[i].size();j++)
		fscanf (input,"%lf%lf",&mat[i][j].x,&mat[i][j].y);*/
	}
}