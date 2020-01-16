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
char out[9][9];

int writeSudokuFinality(char** final, FILE* fp) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			fprintf(fp, "%c ", out[i][j]);
		}
		fprintf(fp, "%c\n", out[i][8]);
	}
	fputc('\n', fp);
	//fclose(fp);
	return 0;
}


int produceOutputIntoTxt(int produce_num) {		//本函数用于生成数独终局
	int count = produce_num;
	int swap_1 = 0, swap_2 = 0, swap_3 = 0;	//分别代表三行的交换
	int	trans_arr[9] = { 1,2,3,4,5,6,7,8,9 };	//用来交换的数字
	int cols[9] = { 0,1,2,3,4,5,6,7,8 };	//用来交换的行
	int sub;
	string table[9] = {			//数独模板
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
							sub = (int)(table[cols[i]][j] - '0')-1;
							out[i][j] = trans_arr[sub]+'0';//table[cols[i]][trans_arr[sub]-1];
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

int dealQuestion(string path) {
	return 0;
}

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
			if (dealQuestion(path) == -1) {
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
