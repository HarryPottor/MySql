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
		cout << "input state (1 insert,2 delete,3 update,4 find): ";
		cin >> state;
		cin.clear();
		cin.ignore();
		cout << "input name: ";
		getline(cin, name);
		int score;
		switch (state)
		{
		case 1:
			cout << "input score : ";
			cin >> score;
			server->insertData(name.c_str(), score);
			break;
		case 2:
			server->deleteData(name.c_str());
			break;
		case 3:
			cout << "input score : ";
			cin >> score;
			server->updateData(name.c_str(), score);
			break;
		case 4:
			server->findData(name.c_str());
			//cout << name << " : " << server->getScore() << endl;
			break;
		default:
			break;
		}

	}


	system("pause");
	return 0;
}