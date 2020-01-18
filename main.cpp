/*
*@author HGY
*@class 07111707
*@time 2020.1.1
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <algorithm>

using namespace std;

typedef struct BlockForSort {
	int x, y;
	int count;
}BLFS;	//用来找最小的块


namespace DEAL {
	int col_count[9][10] = { 0 }, row_count[9][10] = { 0 }, block_count[9][10] = { 0 };
	BLFS bs[100];
	int map[9][9];
	//为了防止全局变量混乱，使用了名词空间
}

namespace STORE {
	char store[300000000] = { 0 };
	long count = 0;
}
char out[9][9];

bool judge(int x, int y, int i);
int getBlockNum(int x, int y);
bool cmp(BLFS& a, BLFS& b);
int writeSudokuFinality(char** final, FILE* fp);
int produceOutputIntoTxt(int produce_num);
int dealQuestion(char* path);
int dfs(int num, int size);
void setMark(int x, int y, int i, int flag);

int main(int argc,char **argv) {
	string path;	//数独问题文件路径，为绝对路径
	if (argc == 1) {	//未输入命令行参数，报错并返回
		cout << "please input command in cmd line" << endl;
		return 0;
	}
	else {
		if (!strcmp(argv[1], "-c")) {
			if (1||typeid(argv[2]) == typeid(int)) {
				int produce_num = atoi(argv[2]);
				if (produceOutputIntoTxt(produce_num) == -1) {
					cout << "终局生成失败" << endl;
					return -1;
				}
			}
			else {
				cout << "please input number after -c" << endl;
				return 0;
			}
		}
		else if (!strcmp(argv[1], "-s")) {
			path = argv[2];
			if (dealQuestion(argv[2]) == -1) {
				cout << "error deal sokudo question" << endl;
					return -1;
			}
		}
		else {	//错误输入，报错
			cout << "input cmd error!" << endl;
			return 0;
		}
	}
}

int getBlockNum(int x, int y) {
	return ((x / 3) * 3 + (y / 3));
}


bool cmp(BLFS& a, BLFS& b) {
	return a.count > b.count;
}

int writeSudokuFinality(char** final, FILE* fp) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			fprintf(fp, "%c ", out[i][j]);
		}
		fprintf(fp, "%c\n", out[i][8]);
	}
	fputc('\n', fp);
	return 0;
}


int produceOutputIntoTxt(int produce_num) {		//本函数用于生成数独终局
	int count = produce_num;
	int swap_1 = 0, swap_2 = 0, swap_3 = 0;	//分别代表三行的交换
	int	trans_arr[9] = { 1,2,3,4,5,6,7,8,9 };	//用来交换的数字
	int cols[9] = { 0,1,2,3,4,5,6,7,8 };	//用来交换的行
	int sub;
	string table[9] = {			//数独模板，学号后两位为89，左上角数字为9
		"912345678",
		"678912345",
		"345678912",
		"123456789",
		"789123456",
		"456789123",
		"891234567",
		"567891234",
		"234567891"
	};
	remove("./sudoku.txt");
	FILE* fp = fopen("./sudoku.txt", "wt");
	if (fp == NULL) {
		cout << "err" << endl;
		return -1;
	}
	do {//前两列的交换
		do {//三到五列交换
			do {//六到八列的交换
				do {//前八个数字的交换
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							sub = (int)(table[cols[i]][j] - '0') - 1;
							out[i][j] = trans_arr[sub] + '0';
						}
					}
					writeSudokuFinality(NULL, fp);
					count--;
					if (count <= 0) {
						fclose(fp);
						return 0;
					}
				} while (next_permutation(trans_arr, trans_arr + 8));
			} while (next_permutation(cols + 6, cols + 9));
		} while (next_permutation(cols + 3, cols + 6));
	} while (next_permutation(cols + 1, cols + 3));
	cout << "over or err" << endl;
}

int dealQuestion(char* path) {
		//数独转换后的图
	char shudu[1024];
	int _col[9] = { 0 }, _row[9] = { 0 }, _block[9] = { 0 };
	using namespace DEAL;
	//分别代表行列以及九宫格里可以填的数字。比如block_count[1][7]=1代表第块已经存在7了。
	FILE* fp = fopen(path, "rt");
	if (fp == NULL) {
		cout << "error read file,please check the question file path" << endl;
		return -1;
	}
	do {
		memset(shudu, 0, sizeof(shudu));
		/*if (fread(shudu, 162*sizeof(char),sizeof(char), fp)) {
			cout << "error read file" << endl;
			return -1;
		};*/
		fread(shudu, 162 * sizeof(char), sizeof(char), fp);
		int x, y;
		x = 0; y = 0;
		memset(bs, 0, sizeof(bs));
		for (int i = 0; i < 162; i++) {
			if (shudu[i] == ' ' || shudu[i] == '\n') continue;
			else {
				map[x][y] = int(shudu[i] - '0');
				if (y >= 8) {
					y = 0;
					x++;
				}
				else y++;
			}
		}
		//将数独文件转化为int型存储
		int count_bs = 0;
		int sub_map;
		memset(_col, 0, sizeof(_col));
		memset(_block, 0, sizeof(_block));
		memset(_row, 0, sizeof(_row));
		memset(row_count, 0, sizeof(row_count));
		memset(col_count, 0, sizeof(col_count));
		memset(block_count, 0, sizeof(block_count));
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (map[i][j] == 0) {
					bs[count_bs].x = i;
					bs[count_bs].y = j;
					count_bs++;
				}
				else {
					sub_map = map[i][j];
					setMark(i, j, sub_map, 1);
					_row[i]++;
					_col[j]++;
					_block[getBlockNum(i, j)]++;
				}
			}
		}

		x = 0; y = 0;
		for (int i = 0; i < count_bs; i++) {
			x = bs[i].x; y = bs[i].y;
			bs[i].count = _row[x] + _col[y] + _block[getBlockNum(x, y)];
		}

		sort(bs, bs + count_bs, cmp);	//排序

		if (dfs(0, count_bs) == false) {
			printf("error dfs\n");
			return -1;
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				STORE::store[STORE::count++] = char(map[i][j] + '0');
				if (j == 8)STORE::store[STORE::count++] = '\n';
				else STORE::store[STORE::count++] = ' ';
			}
		}
		STORE::store[STORE::count++] = '\n';
	} while (fgetc(fp)!=EOF);
	FILE* wrfp = fopen("./dealsokudo.txt", "wt");
	fwrite(STORE::store, sizeof(char), STORE::count, wrfp);
	fclose(wrfp);
	fclose(fp);
	return 0;
}

void setMark(int x, int y, int i, int flag) {
	DEAL::col_count[y][i] = flag;
	DEAL::row_count[x][i] = flag;
	DEAL::block_count[getBlockNum(x, y)][i] = flag;
}

int dfs(int num, int size) {
	using namespace DEAL;
	if (num == size) {
		return true;
	}
	else {
		int x = bs[num].x, y = bs[num].y;
		for (int i = 1; i <= 9; i++) {
			if (judge(x, y, i)) {
				map[x][y] = i;
				setMark(x, y, i, 1);
				if (dfs(num + 1, size)) return true;
				setMark(x, y, i, 0);
				map[x][y] = 0;
			}
		}
		return false;
	}
}

bool judge(int x, int y, int i) {
	//using namespace DEAL;
	return !DEAL::col_count[y][i] && !DEAL::row_count[x][i] && !DEAL::block_count[getBlockNum(x, y)][i];
}
