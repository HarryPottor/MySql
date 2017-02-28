#include <WinSock2.h>
#include <iostream>
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
	MYSQL mydata;
	if (nullptr != mysql_init(&mydata))
	{
		cout << "mysql_init success" << endl;
	}
	else
	{
		ErrorHandling("mysql_init failed");
	}

	//在链接数据库之前，设置额外的连接选项. 允许使用 中文
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
		cout << "mysql_options success" << endl;
	}
	else
	{
		ErrorHandling("mysql_options failed");
	}
	
	//链接数据库
	if (NULL != mysql_real_connect(&mydata, "localhost", "root", "lgh123", "test", 3306, NULL, 0))
	{
		cout << "mysql_real_connect successed" << endl;
	}
	else
	{
		ErrorHandling("mysql_real_connect failed");
	}

	//创建一个表
	string sqlstr;
	sqlstr = "create table if not exists user_info";
	sqlstr += "(";
	sqlstr += "user_id int unsigned not null auto_increment primary key comment 'Unique User ID',";
	sqlstr += "user_name varchar(100) character set gb2312 collate gb2312_chinese_ci null comment 'Name of User',";
	sqlstr += "user_second_sum int unsigned not null default 0 comment 'The summation of using time'";
	sqlstr += ");";

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		cout << "mysql_query create table success" << endl;
	}
	else
	{
		mysql_close(&mydata);
		ErrorHandling("mysql_query create table failed");
	}

	//向表中插入数据
	sqlstr = "insert into user_info(user_name) values('公司名称'),('一级部门'),('二级部门'),('开发小组'),('姓名');";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		cout << "mysql_query insert data successed" << endl;
	}
	else
	{
		ErrorHandling("mysql_query insert data failed");
	}

	//显示插入的数据 
	sqlstr = "select user_id, user_name, user_second_sum from user_info";
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		cout << "mysql_query select data success" << endl;
		//获取数据集
		result = mysql_store_result(&mydata);
		//获取行数 
		int rowcount = mysql_num_rows(result);
		cout << "row counts: " << rowcount << endl;
		
		//取得并打印各字段的名称
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD * field = NULL;
		for (unsigned i = 0; i < fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}

		//打印各行
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row)
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
		mysql_close(&mydata);
		ErrorHandling("mysql_query select data failed");
	}

	//删除刚才建的表 
	sqlstr = "drop table user_info";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		cout << "mysql_query drop table user_info succeed" << endl;
	}
	else
	{
		mysql_close(&mydata);
		ErrorHandling("mysql_query drop table user_info failed");
	}

	mysql_free_result(result);
	mysql_close(&mydata);
	mysql_server_end();


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
