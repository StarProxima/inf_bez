#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;


void swap(char* a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}

bool nextP(char* a, int n)
{
	int j = n - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1)
		return false;
	int k = n - 1;
	while (a[j] >= a[k]) k--;
	swap(a, j, k);
	int l = j + 1, r = n - 1;
	while (l < r)
		swap(a, l++, r--);
	return true;
}

int main()
{	
	int number;
	cin >> number;


	char perm[] = "ABCDEFGHIJKLMNOPQRSTUVWXY";

	int curNumber = 0;
	char word[5][5];
	bool trueWord = true;

	string ans = "";
	
	do {
		

		trueWord = true;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				word[i][j] = perm[i * 5 + j];
			}
		}

		for (int i = 0; i < 5 && trueWord; i++) {
			for (int j = 0; j < 4; j++) {
				//std::cout << (int)word[i][j] << " >= " << (int)word[i][j + 1] << "|";

				if ((int) word[i][j] >= (int)word[i][j + 1]) {
					trueWord = false;
					break;
				}
			}
			//std::cout << endl;
		}

		//std::cout << trueWord;

		for (int i = 0; i < 5 && trueWord; i++) {
			for (int j = 0; j < 4; j++) {

				if ((int)word[j][i] >= (int)word[j + 1][i]) {
					trueWord = false;
					break;
				}
			}
		}

		//std::cout << perm << trueWord << endl;
		
		if (trueWord) {
			curNumber++;
			/*if (curNumber % 5 == 1) {
				for (int i = 0; i < 5; i++) {
					std::cout << perm[i * 5] << perm[i * 5 + 1] << perm[i * 5 + 2] << perm[i * 5 + 3] << perm[i * 5 + 4] << " ";
				}
				std::cout << curNumber << endl;
			}*/
	
			if (curNumber == number) {
				ans = perm;
				break;
			}
		}
	
	} while (nextP(perm, 25) );


	std::cout << ans;
}

