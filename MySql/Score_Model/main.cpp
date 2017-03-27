#include "Server.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{

	CServer * server = CServer::getInstance();
	if (!server->initServer(argc, argv))
	{
		puts("init error");
		system("pause");
		exit(1);
	}
	int state;
	string name;
	while (true)
	{
		cout << "input state (1 insert,2 delete,3 update,4 find, 5 getall, 6 getone, 0 to quit): ";
		cin >> state;
		cin.clear();
		cin.ignore();
		if (state == 0)
		{
			break;
		}
		if (state < 5)
		{
			cout << "input name: ";
			getline(cin, name);
		}
		int score;
		int time;
		switch (state)
		{
		case 1:
			cout << "input score : ";
			cin >> score;
			cout << "input time : ";
			cin >> time;
			server->insertData(name.c_str(), score, time);
			break;
		case 2:
			server->deleteData(name.c_str());
			break;
		case 3:
			cout << "input score : ";
			cin >> score;
			cout << "input time : ";
			cin >> time;
			server->updateData(name.c_str(), score, time);
			break;
		case 4:
			server->findData(name.c_str());
			//cout << name << " : " << server->getScore() << endl;
			break;
		case 5:
			server->getAllData();
			break;
		case 6:
			server->getOneData();
		default:
			break;
		}

	}

	system("pause");
	return 0;
}