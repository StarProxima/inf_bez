#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>
using namespace std;

vector <string> allRules;

void initAllRules() {
	string rules = "RW";
	int n = pow(2, rules.size());

	string rule;
	if (allRules.size() == 0) {

		for (int i = 0; i < n; i++) {
			rule = "";
			for (int j = 0; j < rules.size(); j++) {
				if (i & (1 << j)) {
					rule += rules[j];
				}
			}
			allRules.push_back(rule);
		}
	}
	allRules[0] = "_";
}

string genRule()
{
	/*for (int i = 0; i < allRules.size(); i++) {
		cout << allRules[i] << " ";
	}
	cout << "ъ" << endl;*/
	return allRules[rand() % allRules.size()];
}

vector < vector <string> > getRuleMatr() {
	int n = rand() % 5 + 2;
	int m = rand() % 5 + 2;


	vector < vector <string> > RW(n, vector <string>(m));
	vector <int> LS(n);
	vector <int> LO(m);

	initAllRules();
	cout << "Gen matrix" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			RW[i][j] = genRule();

	ofstream matrix;
	matrix.open("matrix.txt");
	if (matrix.is_open())
	{
		matrix << n << endl;
		matrix << m << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				matrix << RW[i][j] << " ";
				cout << RW[i][j] << " ";
			}
			matrix << endl;
			cout << endl;
		}
	}
	matrix.close();


	vector <string> tmp;
	string s;

	ifstream accessMatrix("matrix.txt");
	while (getline(accessMatrix, s))
	{
		tmp.push_back(s);
	}
	accessMatrix.close();

	n = stoi(tmp[0]);
	m = stoi(tmp[1]);
	tmp.erase(tmp.begin(), tmp.begin() + 2);

	vector < vector <string> > rulesMatrix = vector < vector <string> >();

	for (int i = 0; i < n; i++) {
		rulesMatrix.push_back(vector<string>());
		string ss = "";
		for (int j = 0; j < tmp[i].size(); j++) {
			if (tmp[i][j] != ' ') {
				ss += tmp[i][j];
			}
			else {
				rulesMatrix[i].push_back(ss);
				ss = "";
			}
		}
	}
	return rulesMatrix;
}

bool canRead(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'R') {
			return true;
		}
	}
	return false;
}

bool canWrite(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'W') {
			return true;
		}
	}
	return false;
}

bool isEmptyRule(string s) {
	return !(canWrite(s) || canRead(s));
}

bool isFullRule(string s) {
	return canWrite(s) && canRead(s);
}

vector<int> taskA(vector < vector <string> > ruleMatr)
{
	vector <int> answer = vector <int>();
	for (int j = 0; j < ruleMatr[0].size(); j++) {
		bool f = true;
		for (int i = 0; i < ruleMatr.size(); i++) {
			if (!isEmptyRule(ruleMatr[i][j])) {
				f = false;
				break;
			}
		}
		if (f) {
			answer.push_back(j + 1);
		}
	}
	return answer;
}

vector<int> taskB(vector < vector <string> > ruleMatr) //
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < ruleMatr.size(); i++) {
		bool f = true;
		for (int j = 0; j < ruleMatr[i].size(); j++) {
			if (!isEmptyRule(ruleMatr[i][j])) {
				f = false;
				break;
			}
		}
		if (f) {
			answer.push_back(i + 1);
		}
	}
	return answer;
}

vector<int> taskC(vector < vector <string> > ruleMatr) // список полных субъектов
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < ruleMatr.size(); i++) {
		bool f = true;
		for (int j = 0; j < ruleMatr[i].size(); j++) {
			if (isEmptyRule(ruleMatr[i][j])) {
				f = false;
				break;
			}
		}
		if (f) {
			answer.push_back(i + 1);
		}
	}
	return answer;
}

vector<vector<int>> taskD(vector < vector <string> > ruleMatr) // список список субъектов записи по объектам
{
	vector<vector<int>> answer = vector<vector<int>>();
	for (int j = 0; j < ruleMatr[0].size(); j++) {
		answer.push_back(vector<int>());
		bool f = true;
		for (int i = 0; i < ruleMatr.size(); i++) {
			if (canWrite(ruleMatr[i][j])) {
				answer[j].push_back(i + 1);
			}
		}
	}
	return answer;
}

vector<int> taskE(vector < vector <string> > ruleMatr) // список одиноких субъектов
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < ruleMatr.size(); i++) {
		bool f = true;
		bool fullRule = false;
		for (int j = 0; j < ruleMatr[i].size(); j++) {
			if (isFullRule(ruleMatr[i][j])) {
				if (fullRule) {
					f = false;
					break;
				}
				fullRule = true;
			}
			else if (canWrite(ruleMatr[i][j])) {
				f = false;
				break;
			}
		}
		if (f) {
			answer.push_back(i + 1);
		}
	}
	return answer;
}

void printVector(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << ' ';
	}
	cout << endl << endl;
}

void printVectors(vector<vector<int>> v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));

	vector < vector <string> > matrix = getRuleMatr();
	cout << "Task a" << endl;
	printVector(taskA(matrix));
	cout << "Task b" << endl;
	printVector(taskB(matrix));
	cout << "Task c" << endl;
	printVector(taskC(matrix));
	cout << "Task d" << endl;
	printVectors(taskD(matrix));
	cout << "Task e" << endl;
	printVector(taskE(matrix));
}