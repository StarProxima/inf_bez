#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

enum gridValue { space, slash, backslash, check };

class Point {
public:
	int x;
	int y;


	Point() {
		x = 0;
		y = 0;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};


gridValue** getGrid(int& r, int& c, int& m, int& n) {

	ifstream inFile = ifstream("safe.in");

	inFile >> r >> c >> m >> n;

	gridValue** grid;
	grid = new gridValue * [r];
	/*grid = (gridValue**)malloc(sizeof(gridValue*) * r);*/
	for (int i = 0; i < r; i++) {
		grid[i] = new gridValue[c]{ space };
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

bool isSuccessHack(gridValue** grid, int r, int c, vector<Point>& poses, Point pos = Point(0, 0), Point dir = Point(0, 1)) {

	Point newPos = pos;

	//cout << "DIR: " << dir.x << " " << dir.y << endl;

	bool b;

	do { 
		if (grid[newPos.x][newPos.y] == space) {
			poses.push_back(newPos);
		}
		newPos.x += dir.x;
		newPos.y += dir.y;
		b = newPos.x >= 0 && newPos.x < r&& newPos.y >= 0 && newPos.y < c;
	} while ( b && grid[newPos.x][newPos.y] == space);


	if (!b) {
		//cout << newPos.x << " " << newPos.y << endl;
		if (newPos.x == r - 1 && newPos.y == c) return true;
		return false;
	}
	

	int sign;
	if (grid[newPos.x][newPos.y] == slash) sign = -1;
	else sign = 1;

	Point newDir = dir;
	int x = newDir.x;
	newDir.x = sign * newDir.y;
	newDir.y = sign * x;
/*	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << grid[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "------" << endl*/;

	isSuccessHack(grid, r, c, poses, newPos, newDir);

}

void print(gridValue** grid, int r, int c) {

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char ch = grid[i][j] == space ? ' ' : grid[i][j] == slash ? '/' : grid[i][j] == backslash ? '\\' : '*';
			cout << ch << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int r, c, m, n;

	vector<Point> poses;

	gridValue** grid = getGrid(r, c, m, n);

	print(grid, r, c);

	cout << isSuccessHack(grid, r, c, poses);


	for (int i = 0; i < poses.size(); i++) {
		grid[poses[i].x][poses[i].y] = check;
	}
	cout << endl;
	print(grid, r, c);





}
