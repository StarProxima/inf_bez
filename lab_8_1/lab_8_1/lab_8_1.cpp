#include <iostream>
#include <vector>
using namespace std;

struct item {
	int subj_i; 
	int obj_j;
	string value;
};

struct items {
	vector<item> v;
	vector <int> deleteList;
	int n;
	int m;
};

string ruleSetGen()
{
	string M = "RW";
	int n = pow(2, M.size());
	static vector <string> fullRuleSet;
	if (fullRuleSet.size() == 0) {
		for (int i = 0; i < n; i++) {
			string buff = "";
			for (int j = 0; j < M.size(); j++) {
				if (i & (1 << j)) {
					buff += M[j];
				}
			}
			fullRuleSet.push_back(buff);
		}
		fullRuleSet[0] = "_";
	}
	string ruleSet = fullRuleSet[rand() % 4];
	return ruleSet;
}

void output(items Items)
{
	cout << "----------------------------------------" << endl;
	cout << "Вывод сгенерированной разряженной матрицы" << endl;
	cout << "В формате: имя субъекта, имя объекта, права доступа" << endl;
	cout << "" << endl;
	for (int i = 0; i < Items.v.size(); i++)
	{
		cout << Items.v[i].subj_i + 1 << " " << Items.v[i].obj_j + 1 << " " << Items.v[i].value << endl;
		cout << "------" << endl;
	}
	cout << "----------------------------------------" << endl;
}

void clearEmpty(items& Items)
{
	for (int d = 0; d < Items.v.size(); d++)
	{
		if (Items.v[d].value == "")
		{
			Items.v.erase(Items.v.begin() + d);
		}
	}
}

void changeRule(items& Items)
{
	cout << "редактирование ячейки" << endl;
	int act, i, j;
	cout << "удаление права - 1, добавление права - 2" << endl;
	cin >> act;
	string rule;
	cout << "введите право, номер субъекта, номер объекта" << endl;
	cin >> rule >> i >> j;
	i--; j--;

	bool f = false;
	for (int d = 0; d < Items.v.size(); d++)
	{
		if (Items.v[d].subj_i == i && Items.v[d].obj_j == j && act == 1)
		{
			string res = rule;
			for (int inputInd = 0; inputInd < res.size(); inputInd++)
			{
				for (int nowInd = 0; nowInd < Items.v[d].value.size(); nowInd++)
				{
					if (res[inputInd] == Items.v[d].value[nowInd])
					{
						Items.v[d].value = Items.v[d].value.substr(0, nowInd) + Items.v[d].value.substr(nowInd + 1, Items.v[d].value.size() - nowInd - 1);
						break;
					}
				}
			}
			f = true;
			break;
		}
		if (Items.v[d].subj_i == i && Items.v[d].obj_j == j && act == 2)
		{
			string res = rule;
			for (int inputInd = 0; inputInd < res.size(); inputInd++)
			{
				bool f = true;
				for (int nowInd = 0; nowInd < Items.v[d].value.size(); nowInd++)
				{
					if (res[inputInd] == Items.v[d].value[nowInd])
					{
						f = false;
						break;
					}
				}
				if (f)
				{
					Items.v[d].value += res[inputInd];
				}
			}
			f = true;
			break;
		}
	}
	if (!f && act == 2 && Items.n > i && find(Items.deleteList.begin(), Items.deleteList.end(), i) == Items.deleteList.end())
	{
		item temp;
		temp.subj_i = i;
		temp.obj_j = j;
		temp.value = rule;
		Items.v.push_back(temp);
	}
	else {
		cout << "Команду выполнить невозможно" << endl;
	}
}

void insertNewSubj(items& Items)
{
	cout << "добавление субъекта" << endl;

	item temp;
	temp.subj_i = Items.n;
	Items.n += 1;
	cout << "Индекс нового субъекта - " << Items.n << endl;
}

void deleteSubj(items& Items)
{
	cout << "удаление субъекта" << endl;
	int del_subj_i;
	cout << "введите числовой индекс удаляемого субъекта" << endl;
	cin >> del_subj_i;
	del_subj_i--;

	bool isOneOrMore = false;
	bool finded = true;
	while (finded) {
		finded = false;
		for (int i = 0; i < Items.v.size(); i++)
		{
			if (Items.v[i].subj_i == del_subj_i)
			{
				finded = true;
				Items.v.erase(Items.v.begin() + i);
				isOneOrMore = true;
				break;
			}
		}
	}

	if (!isOneOrMore) {
		cout << "Ни одного субъекта с таким именем не найдено, удаления не произошло" << endl;
	}
	else {
		Items.deleteList.push_back(del_subj_i);
	}
}


items getMatrix() {
	int n = rand() % 10 + 2;
	int m = rand() % 10 + 2;

	items Items;
	Items.v = vector<item>();
	Items.deleteList = vector<int>();
	Items.n = n;
	Items.m = m;

	cout << "генерация rw" << endl;
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < m; j++)
		{
			string temp_RW = ruleSetGen();
			if (temp_RW != "_")
			{
				item temp_item;
				temp_item.subj_i = i;
				temp_item.obj_j = j;
				temp_item.value = temp_RW;
				Items.v.push_back(temp_item);
			}
		}
	}
	return Items;
}

void compute(items Items) {
	cout << "0 - выйти" << endl;
	cout << "1 - редактирование ячейки" << endl;
	cout << "2 - добавление нового субъекта" << endl;
	cout << "3 - удаление субъекта" << endl;

	int Inp;
	do
	{
		cout << "Введите команду: ";
		cin >> Inp;
		if (Inp == 1)
		{
			changeRule(Items);
		}
		if (Inp == 2)
		{
			insertNewSubj(Items);
		}
		if (Inp == 3)
		{
			deleteSubj(Items);
		}

		clearEmpty(Items);
		output(Items);
	} while (Inp != 0);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));

	items Items = getMatrix();
	output(Items);

	compute(Items);
}