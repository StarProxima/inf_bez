
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

string encode(string text, int offset)
{
	offset %= 27;
	



	


	for (int i = 0; i < text.size(); i++)
	{
		std::cout << text[i] << "|";
	}

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



	

	std::cout << endl
		<< codeStr;

	



	return codeStr ;
}

int main()
{
	ifstream inFile("input.txt");
	string text;
	getline(inFile, text);


	string ans = encode(text, -28);

	ofstream outFile("output.txt");

	outFile << ans;
}
