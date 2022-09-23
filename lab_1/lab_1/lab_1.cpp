
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

string encrypt(string text, int offset)
{
	offset %= 27;

	string codeStr;

	if (offset == 0) {
		codeStr = text;
	}
	else {
		for (unsigned int j = 0; j < text.length(); j++)
		{
			unsigned char newSymb;

			unsigned char symb = text[j] == ' ' ? '@' : text[j];
			newSymb = symb + offset;

			if (newSymb > 'Z')
			{
				newSymb = 'A' + (newSymb - 'Z') - 2;
				if (newSymb == '@') newSymb = ' ';
				codeStr.push_back(newSymb);
			}
			else if (newSymb < 'A')
			{
				newSymb = 'Z' - ('A' - newSymb) + 2;
				if (newSymb == '@') newSymb = ' ';
				codeStr.push_back(newSymb);
			}
			else
			{
				codeStr.push_back(newSymb);
			}
		}
	}

	cout << codeStr;

	return codeStr;
}

int main()
{
	ifstream inFile("input.txt");

	string wordCountStr;
	vector<string> words = vector<string>();
	inFile >> wordCountStr;
	int wordCount = stoi(wordCountStr);


	for (int i = 0; i < wordCount; i++)
	{
		string word;
		inFile >> word;
		cout << word << " ";
		words.push_back(word);
	}

	string text;

	while (!inFile.eof()) {
		string str;

		inFile >> str;

		text.append(str + " ");
	}
	text.resize(text.size() - 1);


	getline(inFile, text);

	cout << endl << text << endl;


	string ans = encrypt(text, 1);

	ofstream outFile("output.txt");

	outFile << ans;
}
