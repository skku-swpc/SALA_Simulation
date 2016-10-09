#include "main.h"


/*---------------------------------------------------*/
char f_matlist[50] = "";	// matlist 파일 이름

int iaNum, n;		// 정보가전(IA) num
int case_idx;		// case number
char case_char[9];	// case number (string)
char info[2][50];

int dens_r;
int range;			// 외심 측정 유효 범위
int per;			// R을 선택 위한 percentage
int Lx, Ly, Rx, Ry;	// Map bound
bool flag;			// boolean Flag

double densR[N];	// 탐색할 radius
double cx, cy;		// useful point

point location[NUM_CASES][N];	// original location
point median[N], dens[N], res[N];

vector<point> mat[N];		// Matlist 정보
vector<point> cir[N], chos[N];
vector<point> convex[N];	// Convex Hull 담음

vector<point> part[N][MAX_WEIGHTTABLE];
point partRes[N][MAX_WEIGHTTABLE];

map<double, double> powerMap[N]; // power, distance

point room[10][2];
point room2[100][2];

int method = 4;

/*---------------------------------------------------*/

int main()
{
	FILE * fResult = fopen("./out/result_time_error.txt", "wt");
	int algorithm = 0;
	int start_idx, end_idx;

	printf("SALA Simulation version : %s\n", getSALAversion());

	for (int i = 1; i <= 30; ++i)
		read_location(i);

	read_roomInfo("./data/room.txt");

	for (algorithm = 3; algorithm <= 3; ++algorithm)
	{
		iaNum = 10;

		// 1~120 까지가 시간을 가지고 나눈 단위

		for (int i = 10; i <= 120; i += 10) // 시간별로 진행10~120
		//for (int i = 0; i <= 200; i += 20)
		{
			double avg = 0.0;
			//	double avg[3] = { 0.0, };
			//	int cnt[3] = { 0, };

			for (int j = 1; j <= 30; ++j) // 케이스 넘기기
			{
				printf("%d   %d   %d (%d)\n", algorithm, i, j, (j - 1) * 120 + i);

				case_idx = (j - 1) * 120 + i;
				set_parameter();
				init();
				read_matlist();
				//read_matlist(i);

				if (algorithm == 1)
				{
					get_convex(mat);
					real_method(convex);
					for (int k = 2; k < 12; ++k)
					{
						if (judge(res, k) == CENTER)
							minmax(mat, k, k);
						//	average2(mat, res, k);
					}

					//	divide(mat, part); // 파워 계층 나누기
					// convex_func(mat, part, res);
				}
				else if (algorithm == 2){
					average2(mat, res);
				}
				else if (algorithm == 3)
				{
					average2(mat, res);
					/*
					char tmpstr3[30] = "./out/point_avg";
					FILE *out = fopen(strcat(strcat(tmpstr3, case_char), ".txt"), "w");
					for (int k = 2; k < n; k++)
					{
					fprintf(out, "%d %lf %lf\n", k, res[k].x, res[k].y);
					printf("%d %.2lf %.2lf\n", k, res[k].x, res[k].y);
					}
					fclose(out);
					*/
					/* new revision method 1 */

					/*for (int k = 2; k < n; k++) if (judge(res, k) != CENTER && mat[k].size() < 50)
					{
					if (abs(res[k].x) <= MARGIN)
					{
					int A = mat[k].size();
					for (int i = 0; i < A; i++)
					{
					point t = mat[k][i];
					t.x = -t.x;
					mat[k].push_back(t);
					}
					}
					if (abs(res[k].x - MAP_X) <= MARGIN)
					{
					int A = mat[k].size();
					for (int i = 0; i < A; i++)
					{
					point t = mat[k][i];
					t.x = 2 * MAP_X - mat[k][i].x;
					mat[k].push_back(t);
					}
					}
					if (abs(res[k].y) <= MARGIN)
					{
					int A = mat[k].size();
					for (int i = 0; i < A; i++)
					{
					point t = mat[k][i];
					t.y = -t.y;
					mat[k].push_back(t);
					}
					}
					if (abs(res[k].y - MAP_Y) <= MARGIN)
					{
					int A = mat[k].size();
					for (int i = 0; i < A; i++)
					{
					point t = mat[k][i];
					t.y = 2 * MAP_Y - mat[k][i].y;
					mat[k].push_back(t);
					}
					}
					}*/


					calcPowerMap(mat, res, powerMap); // powerMap 분석
					rate2(mat, res, powerMap);
					/*
					strcpy(tmpstr3, "./out/point_rev");
					out = fopen(strcat(strcat(tmpstr3, case_char), ".txt"), "w");
					for (int k = 2; k < n; k++)
					{
					fprintf(out, "%d %lf %lf\n", k, res[k].x, res[k].y);
					printf("%d %.2lf %.2lf\n", k, res[k].x, res[k].y);
					}
					fclose(out);*/
				}

				for (int k = 2; k < n; k++)
				{
					if (judge(res, k) != CENTER && mat[k].size() < 50)
					{
						point dir = PCA(mat[k]);

						res[k].x += dir.x * 30.0;
						res[k].y += dir.y * 30.0;
					}
				}

				/*	char tmpstr6[30] = "./out/point_norev_";
				FILE *out2 = fopen(strcat(strcat(tmpstr6, case_char), ".txt"), "w");
				for (int k = 2; k < n; k++)
				{
				fprintf(out2, "%d %lf %lf\n", k, res[k].x, res[k].y);
				}
				fclose(out2);*/

				// corner revision

				//	char tmpstr[30] = "./out/point_sig_";
				//	FILE *out = fopen(strcat(strcat(tmpstr, case_char), ".txt"), "w");

				/*	double R = 0; int c = 0;
				for (int k = 2; k < n; k++)
				{
				sort(mat[k].begin(), mat[k].end(), comP);

				if (judge(res, k) == CENTER)
				{
				int range = min((int) mat[k].size(), 20);
				for (int i = 0; i < range; i++)
				{
				R += (mat[k][i] - res[k]).magnitude();
				c++;
				//	fprintf(out, "%d %lf %lf\n", k, mat[k][i].x, mat[k][i].y);
				}

				}
				}
				R /= c;

				for (int k = 2; k < n; k++)
				{
				if (judge(res, k) != CENTER)
				{
				vector<point> buf;
				int range = min((int)mat[k].size(), 20);
				for (int i = 0; i < range; i++)
				{
				buf.push_back(mat[k][i]);
				}

				buf = without_convex_hull(buf);
				//buf = without_convex_hull(buf);

				//	for (int i = 0; i < buf.size(); i++)
				//	{
				//		fprintf(out, "%d %lf %lf\n", k, buf[i].x, buf[i].y);
				//	}
				res[k] = corner_revision(buf, R);
				}
				}*/
				//	fclose(out);

				/*	char tmpstr3[30] = "./out/point_cal_";
				out = fopen(strcat(strcat(tmpstr3, case_char), ".txt"), "w");
				for (int k = 2; k < n; k++)
				{
				fprintf(out, "%d %lf %lf\n", k, res[k].x, res[k].y);
				}
				fclose(out);*/


				/*
				// corner revision
				int maxcount = 3;

				for (int k = 2; k < n; ++k)
				{
				if (judge(res, k) != CENTER)
				{
				vector<point> corner;
				double x = res[k].x;
				double y = res[k].y;
				double r = 0.0;
				int ind = -1;

				bool b[M] = { false, };
				int cnt = 0;

				for (int i2 = 0; i2 < maxcount; ++i2)
				{
				double max = 0.0;
				int ind = -1;

				for (int j2 = 0; j2 < mat[k].size(); ++j2)
				{
				double diffx = mat[k][j2].x - (double)x;
				double diffy = mat[k][j2].y - (double)y;
				double diff = sqrt(diffx*diffx + diffy*diffy);
				//	diff = mat[k][j].power;

				if (diff > max && b[j2] == false)
				{
				max = diff;
				ind = j2;
				}
				}

				if (ind == -1)
				break;

				if (i2 >= 0) // 구간 설정
				{
				corner.push_back(mat[k][ind]);
				r += max;
				++cnt;
				}

				b[ind] = true;
				}

				point result = corner_revision(corner, r / (double)cnt);
				//	point result = corner_revision(corner, 124.0);
				if (result.x >= 0.0)
				res[k] = result;
				}
				}
				*/
				// corner, wall, center
				/*	for (int k = 2; k < n; ++k)
				{
				double x = location[j - 1][k].x;
				double y = location[j - 1][k].y;

				// 930, 1010

				if ((x <= MARGIN && y <= MARGIN) || (x <= MARGIN && y >= MAP_Y - MARGIN) || (x >= MAP_X - MARGIN && y <= MARGIN) || (x >= MAP_X - MARGIN && y >= MAP_Y - MARGIN)){
				avg[0] += dis(location[j - 1][k], res[k]);
				++cnt[0];
				}
				else if (x <= MARGIN || y <= MARGIN || x >= MAP_X - MARGIN || y >= MAP_Y - MARGIN){
				avg[1] += dis(location[j - 1][k], res[k]);
				++cnt[1];
				}
				else{
				avg[2] += dis(location[j - 1][k], res[k]);
				++cnt[2];
				}
				}*/

				// room
				/*	double avgPart = 0.0;
				for (int k = 2; k < n; ++k)
				{
				bool result = true;
				for (int ind = 0; ind < roomSize; ++ind)
				{
				double x1 = location[j-1][k].x;
				double y1 = location[j-1][k].y;
				double x2 = res[k].x;
				double y2 = res[k].y;
				bool r1, r2;
				r1 = room[ind][0].x <= x1 && x1 <= room[ind][1].x && room[ind][0].y <= y1 && y1 <= room[ind][1].y;
				r2 = room[ind][0].x <= x2 && x2 <= room[ind][1].x && room[ind][0].y <= y2 && y2 <= room[ind][1].y;

				if (r1 != r2)
				{
				result = false;
				break;
				}
				}

				// IoT Device별 출력
				fprintf(fResult, "%d\n", (int)result + 1);

				// 평균 출력
				//	if (result)
				//		avgPart += 1.0;
				}
				//	avg += avgPart / (double)iaNum;
				*/

				// room2
				/*double avgPart = 0.0;
				for (int k = 2; k < n; ++k)
				{
				bool result = true;
				for (int ind = 0; ind < roomSize2; ++ind)
				{
				double x1 = location[j-1][k].x;
				double y1 = location[j-1][k].y;
				double x2 = res[k].x;
				double y2 = res[k].y;
				bool r1, r2;
				r1 = room2[ind][0].x <= x1 && x1 <= room2[ind][1].x && room2[ind][0].y <= y1 && y1 <= room2[ind][1].y;
				r2 = room2[ind][0].x <= x2 && x2 <= room2[ind][1].x && room2[ind][0].y <= y2 && y2 <= room2[ind][1].y;

				if (r1 != r2)
				{
				result = false;
				break;
				}
				}

				// IoT Device별 출력
				//fprintf(fResult, "%d\n", (int)result + 1);

				// 평균 출력
				if (result)
				avgPart += 1.0;
				}*/
				//	avg += avgPart / (double)iaNum;


				// IoT Device별 출력
				//	for (int k = 2; k < n; ++k)
				//		fprintf(fResult, "%lf\n", dis(location[0][k], res[k]));

				// 평균 출력
				double avgPart = 0.0;
				for (int k = 2; k < n; ++k)
					avgPart += dis(location[j - 1][k], res[k]);

				//avg += avgPart / (double)iaNum;

				fprintf(fResult, "%lf ", avgPart / (double)iaNum);
			}

			// corner, wall, center
			//	for (int j = 0; j < 3; ++j)
			//		fprintf(fResult, "%lf ", avg[j] / (double)cnt[j]);

			//fprintf(fResult, "%lf\n", avg / 30.0);
			//	fprintf(fResult, "%lf\n", avg);

			//	if (i == 1)
			//		--i;

			fprintf(fResult, "\n");
		}

		fprintf(fResult, "\n");
	}

	fclose(fResult);

	return 0;
}

// 벡터 a와 실제 위치(location)간 오차 출력
void print_error(point *a)
{
	int i;
	char output[50];

	strcpy(output, "out/"), strcat(strcat(output, case_char), "error.txt");
	FILE *out = fopen(output, "w");

	printf("%s\n", output);
	for (i = 2; i<n; i++)
		//		fprintf (out,"%.0f\n", dis (location[i], res[i]));
		fclose(out);
}



// 출력 부분
void print_data()
{
	int i, j;
	char output[50];
	FILE *out;

	//------ median ----------------
	strcpy(output, "out/"), strcat(strcat(output, case_char), "median.txt");
	out = fopen(output, "w");
	for (i = 2; i<n; i++) fprintf(out, "%2d %.0f %.0f\n", i, median[i].x, median[i].y); fclose(out);

	//------ circum ----------------
	strcpy(output, "out/"), strcat(strcat(output, case_char), "circum.txt");
	out = fopen(output, "w");
	for (i = 2; i<n; i++){ fprintf(out, "%d\n", cir[i].size()); for (j = 0; j<cir[i].size(); j++) fprintf(out, "%.0f %.0f\n", cir[i][j].x, cir[i][j].y); } fclose(out);

	//------ convex ----------------
	strcpy(output, "out/"), strcat(strcat(output, case_char), "convex.txt");
	out = fopen(output, "w");
	for (i = 2; i<n; i++){ fprintf(out, "%d\n", convex[i].size());	for (j = 0; j<convex[i].size(); j++) fprintf(out, "%.0f %.0f\n", convex[i][j].x, convex[i][j].y); } fclose(out);

	//------ matlist ----------------
	strcpy(output, "out/"), strcat(strcat(output, case_char), "mat.txt");
	out = fopen(output, "w");
	for (i = 2; i<n; i++){ fprintf(out, "%d\n", mat[i].size()); for (j = 0; j<mat[i].size(); j++) fprintf(out, "%.0f %.0f %e\n", mat[i][j].x, mat[i][j].y, mat[i][j].power); } fclose(out);

	//------ chosen ----------------
	strcpy(output, "out/"), strcat(strcat(output, case_char), "chosen.txt");
	out = fopen(output, "w");
	for (i = 2; i<n; i++){ fprintf(out, "%d\n", chos[i].size()); for (j = 0; j<chos[i].size(); j++) fprintf(out, "%.0f %.0f\n", chos[i][j].x, chos[i][j].y); } fclose(out);

	//------ result ----------------
	strcpy(output, "out/"), strcat(strcat(output, case_char), "result.txt");
	out = fopen(output, "w");
	for (i = 2; i<n; i++) fprintf(out, "%2d %.0f %.0f\n", i, res[i].x, res[i].y); fclose(out);

	//------ rate ----------------
	FILE * fin = fopen("data/location1.txt", "rt");

	strcpy(output, "out/"), strcat(strcat(output, case_char), "rate.txt");
	out = fopen(output, "w");
	for (i = 2; i < n; i++)
	{
		int temp;
		double x, y;
		fscanf(fin, "%d %lf %lf", &temp, &x, &y);
		x -= res[i].x;
		y -= res[i].y;
		fprintf(out, "%lf\n", sqrt(x*x + y*y));
	}

	fclose(fin);
	fclose(out);
}