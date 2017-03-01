#include <iostream>
using namespace std;
#include <string>
int main()
{
	char name[20];
	int age;
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
*/

	cin >> name;
	if (!strcmp(name, "quit"))
	{
		cout << "same" << endl;
	}
	else
		cout << "different" << endl;


	system("pause");
	return 0;
}