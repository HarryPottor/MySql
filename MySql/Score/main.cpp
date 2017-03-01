#include <iostream>
#include <WinSock2.h>
#include <string>
#include <mysql.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")


void ErrorHandling(char * msg);
int main()
{
	//初始化数据库
	if (0 == mysql_library_init(0, nullptr, nullptr))
	{
		cout << "mysql_library_init() successd" << endl;
	}
	else
	{
		ErrorHandling("mysql_library_init() failed");
	}

	//初始化数据结构
	MYSQL mydb;
	if (nullptr != mysql_init(&mydb))
	{
		cout << "mysql_init success" << endl;
	}
	else
	{
		ErrorHandling("mysql_init failed");
	}

	if (0 == mysql_options(&mydb, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
		cout << "mysql_options success" << endl;
	}
	else
	{
		ErrorHandling("mysql_options failed");
	}

	if (nullptr != mysql_real_connect(&mydb, "localhost", "root", "lgh123", "score", 3306, nullptr, 0))
	{
		cout << "mysql_real_connect successed" << endl;
	}
	else
	{
		ErrorHandling("mysql_real_connect failed");
	}

	string command;
	command = "create table if not exists scoreinfo(";
	command += "id int(4) not null primary key auto_increment,";
	command += "name char(100) not null,";
	command += "score int(4) not null default 0);";

	if (0 == mysql_query(&mydb, command.c_str()))
	{
		cout << "mysql_query create table success" << endl;
	}
	else
	{
		mysql_close(&mydb);
		ErrorHandling("mysql_query create table failed");
	}

	char name[20];
	int score;
	
	char buf[100];
	command = "insert into scoreinfo (name, score) values (\'%s\' , %d);";
	fputs("name:", stdout);
	//getline(cin, name);
	cin >> name;
	while (strcmp(name, "quit"))
	{
		fputs("score:", stdout);
		cin >> score;
		sprintf_s(buf, command.c_str(), name, score);
		cout << buf << endl;
		if (0 == mysql_query(&mydb, buf))
		{
			cout << "inser data succsee" << endl;
		}
		else
		{
			ErrorHandling("insert data faile");
		}
		fputs("name:", stdout);
		//getline(cin, name);
		fflush(stdin);
		cin >> name;
	}

	cout << "show data in database" << endl;

	command = "select * from scoreinfo;";
	MYSQL_RES *result = nullptr;
	if (0 == mysql_query(&mydb, command.c_str()))
	{
		cout << "mysql_query select data success" << endl;
		result = mysql_store_result(&mydb);

		int rowcount = mysql_num_rows(result);
		cout << "row counts :" << rowcount << endl;

		unsigned fieldcount = mysql_num_fields(result);
		MYSQL_FIELD* field = nullptr;
		for (unsigned i = 0; i < fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}
		cout << endl;

		MYSQL_ROW row = nullptr;
		row = mysql_fetch_row(result);
		while (nullptr != row)
		{
			for (int i = 0; i < fieldcount; i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
			row = mysql_fetch_row(result);
		}
	}
	else
	{
		mysql_close(&mydb);
		ErrorHandling("mysql_query select data failed");
	}

	cout << "input the name :";
	cin >> name;
	command = "select score from scoreinfo where name=\'%s\';";
	while (strcmp(name, "quit"))
	{
		sprintf_s(buf, command.c_str(), name);

		if (0 == mysql_query(&mydb, buf))
		{
			MYSQL_RES * res = nullptr;
			res = mysql_store_result(&mydb);

			MYSQL_ROW row = nullptr;
			row = mysql_fetch_row(res);
			if (nullptr != row)
			{
				cout << "score = " << row[0] << endl;;
			}
			else
				cout << "not find" << endl;
			

		}
		else
		{
			mysql_close(&mydb);
			ErrorHandling("serch error");
		}

		cout << "input the name :";
		cin >> name;
	}






	system("pause");
	return 0;
}

void ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	system("pause");
	exit(-1);
}