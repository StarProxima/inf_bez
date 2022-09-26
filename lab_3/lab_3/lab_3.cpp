#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

bool isPrime(int num) {
	if (num < 2) return false;
	for (int i = 2; i < num / 2 + 1; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

vector<int> getPrimePos(int num) {
	vector<int> ans = vector<int>();
	for (int i = 0; i < num; i++) {
		if (isPrime(i + 1)) {
			ans.push_back(i);
		}
	}
	return ans;
}

string decrypt(vector<int> primePos, string word, int count) {
	string primes = word.substr(0, primePos.size());
	string str = word.substr(primePos.size(), word.size());

	//cout << primes  << endl << str << endl;
	for (int i = 0; i < primePos.size(); i++) {
		str = str.insert(primePos[i], 1, primes[i]);
	}
	if (count > 1) {
		return decrypt(primePos, str, count - 1);
	}


	return str;

	
}

int main()
{	
	int count;
	string word;

	cin >> count;
	cin >> word;


	vector<int> primesPos = getPrimePos(word.size());

	cout << decrypt(primesPos, word, count) << endl;

	for (int i = 0; i < primesPos.size(); i++) {
		cout << primesPos[i];
	}
}

