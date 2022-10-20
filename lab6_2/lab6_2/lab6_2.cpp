#include <iostream>
#include <vector>

using namespace std;


bool check(vector<vector<int>> a, vector<int> ls, vector<int> lo)
{
	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{	
			if (!((ls[i] > lo[j] && a[i][j] == 1) || (ls[i] <= lo[j] && !(a[i][j] == 1))))
			{
				return false;
			}
		}
	}
	return true;
}


void buildSystem(vector<vector<int>>& a, vector<int>& ls, vector<int>& lo)
{	
	srand(time(0));
	
	for (int i = 0; i < ls.size(); i++)
	{
		ls[i] = rand() % 10 + 1;
	}
	for (int i = 0; i < lo.size(); i++)
	{
		lo[i] = rand() % 10 + 1;
	}

	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (ls[i] > lo[j])
			{
				a[i][j] = 1;
			}
			else
			{
				a[i][j] = 0;
			}
		}
	}
}


bool getAnswers(const vector<vector<int>>& a, vector<int>& ls, vector<int>& lo)
{
	ls.clear();
	lo.clear();

	for (int i = 0; i < a.size(); i++)
	{
		int cnt_s = 1;

		for (int j = 0; j < a[i].size(); j++)
		{
			if (a[i][j] == 1)
			{
				cnt_s++;
			}
		}

		ls.push_back(cnt_s);
	}

	for (int i = 0; i < a[0].size(); i++)
	{
		int min = 1;

		for (int j = 0; j < a.size(); j++)
		{
			if (a[j][i] == 0 && ls[j] > min)
			{
				min = ls[j];
			}
		}
		lo.push_back(min);
	}

	return check(a, ls, lo);
}



int main()
{
	vector<vector<int>> matrixA;
	int n = 7, m = 7;
	matrixA.resize(n);
	for (int i = 0; i < n; i++)
	{
		matrixA[i].resize(m);
	}
	vector<int> ls;
	ls.resize(n);
	vector<int> lo;
	lo.resize(m);
	buildSystem(matrixA, ls, lo);
	for (int i = 0; i < ls.size(); i++)
	{
		cout << ls[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < lo.size(); i++)
	{
		cout << lo[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (matrixA[i][j] == 1)
			{
				cout << "W" << " ";
			}
			else
			{
				cout << "R" << " ";
			}
		}
		cout << endl;
	}
	if (check(matrixA, ls, lo))
	{
		cout << "Sootv" << endl;
	}
	else
	{
		cout << "Ne sootv" << endl;
	}
	if (getAnswers(matrixA, ls, lo))
	{

		for (int i = 0; i < ls.size(); i++)
		{
			cout << ls[i] << " ";
		}

		cout << endl;

		for (int i = 0; i < lo.size(); i++)
		{
			cout << lo[i] << " ";
		}
	}
}