#include<iostream>
#include<string>

using namespace std;

int produceOutputIntoTxt(int produce_num) {
	return 0;
}

int dealQuestion(string path) {
	return 0;
}

int main(int argc,char **argv) {
	string path;
	if (argc == 1) {
		cout << "please input command in cmd line" << endl;
		return 0;
	}
	else {
		if (strcmp(argv[1], "-c")) {
			if (typeid(argv[2]) == typeid(int)) {
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
		else if (strcmp(argv[1], "-s")) {
			path = argv[2];
			if (dealQuestion(path) == -1) {
				cout << "error deal sokudo question" << endl;
					return -1;
			}
		}
		else {
			cout << "input cmd error!" << endl;
			return 0;
		}
	}
}
