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

	cout << "문자열 입력:";
	cin.getline(str, 100, '\n');
	cout << "문자 입력:";
	cin >> ch;
	cin.ignore();
	cout << "입력된 문자열: " << str << endl;

	char &loc = find(str, ch, sucess);
	if (!sucess)
	{
		cout << "찾는 문자가 없습니다. ";
		return 0;
	}
	cout << "바꿀 문자 입력:";
	cin >> newch;
	loc = newch;

	cout << "바뀐 문자열:" << str << endl;
	return 0;
}