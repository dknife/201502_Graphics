#include <iostream>
using namespace std;

char& find(char str[], char ch, bool &s)
{
	int index = 0;
	while (str[index])
	{
		if (str[index] == ch)
		{
			s = true;
			return str[index];
		}
		index++;
	}
	return str[0];
}

int main()
{
	char str[100];
	char ch, newch;
	bool sucess = false;

	cout << "���ڿ� �Է�:";
	cin.getline(str, 100, '\n');
	cout << "���� �Է�:";
	cin >> ch;
	cin.ignore();
	cout << "�Էµ� ���ڿ�: " << str << endl;

	char &loc = find(str, ch, sucess);
	if (!sucess)
	{
		cout << "ã�� ���ڰ� �����ϴ�. ";
		return 0;
	}
	cout << "�ٲ� ���� �Է�:";
	cin >> newch;
	loc = newch;

	cout << "�ٲ� ���ڿ�:" << str << endl;
	return 0;
}