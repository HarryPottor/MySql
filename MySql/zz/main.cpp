#include <iostream>

#include <string>
using namespace std;
void GetData(const char arr[], char ch, int len)
{
	int first = 0;
	int tar[10] = { 0 };
	int j = 0;

	for (int i = 0; i <= len; i++)
	{
		if (arr[i] == ch || arr[i] =='\0')
		{
			tar[j++] = atoi(arr+first);
			first = i+1;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cout << tar[i] << endl;
	}
}


int main()
{
	/*
	char name[20];
	string msg;
	getline(cin, msg);
	GetData(msg.c_str(), ' ', msg.size());

	int age;
	*/

	/*
	cout << "name : ";
	cin >> name;
	
	string nn;
	cout << "nn : ";
	cin >> nn;
	while (strcmp(name, "bye"))
	{
		fflush(stdin);
		cout << "age :";
		cin >> age;

		cout << "===================" << nn << age << endl;;
		fflush(stdin);
		cout << "nn : ";
		cin >> nn;
	}


	cin >> name;
	if (!strcmp(name, "quit"))
	{
		cout << "same" << endl;
	}
	else
		cout << "different" << endl;

*/

	/*
	string  msg = "";
	char *data[] = {
		"hello", "123", "321"
	};
	for (int i = 0; i < 3; i++)
	{
		msg = msg + data[i] + " ";
	}


	cout << msg << endl;
	*/

	int num = rand();
	while (true)
	{
		cout << rand() << endl;
	}

	system("pause");
	return 0;
}