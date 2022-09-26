#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

enum gridValue {space, slash, backslash};

enum direction {top, right, bottom, left};


gridValue** getGrid(int& r, int& c, int& m, int& n) {
	
	ifstream inFile = ifstream("safe.in");

	inFile >> r >> c >> m >> n;

	gridValue** grid;
	grid = new gridValue * [r];

	for (int i = 0; i < r; i++) {
		grid[i] = new gridValue[c] {space};
	}

	int r1, r2;

	for (int i = 0; i < m; i++) {
		inFile >> r1 >> r2;
		grid[r1 - 1][r2 - 1] = slash;
	}

	for (int i = 0; i < n; i++) {
		inFile >> r1 >> r2;
		grid[r1 - 1][r2 - 1] = backslash;
	}

	inFile.close();

	return grid;


}


int main()
{
	int r, c, m, n;

	gridValue** grid = getGrid(r, c, m, n);

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << grid[i][j] << ' ';
		}
		cout << endl;
	}






}
