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

	
	//��ʼ�����ݿ�
	if (0 == mysql_library_init(0, nullptr, nullptr))
	{
		cout << "mysql_library_init() successd" << endl;
		
	}
	else
	{
		ErrorHandling("mysql_library_init() failed");
	}
	//��ʼ�����ݽṹ
	MYSQL mydata;
	if (nullptr != mysql_init(&mydata))
	{
		cout << "mysql_init success" << endl;
	}
	else
	{
		ErrorHandling("mysql_init failed");
	}

	//���������ݿ�֮ǰ�����ö��������ѡ��. ����ʹ�� ����
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
		cout << "mysql_options success" << endl;
	}
	else
	{
		ErrorHandling("mysql_options failed");
	}
	
	//�������ݿ�
	if (NULL != mysql_real_connect(&mydata, "localhost", "root", "lgh123", "test", 3306, NULL, 0))
	{
		cout << "mysql_real_connect successed" << endl;
	}
	else
	{
		ErrorHandling("mysql_real_connect failed");
	}

	//����һ����
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

	//����в�������
	sqlstr = "insert into user_info(user_name) values('��˾����'),('һ������'),('��������'),('����С��'),('����');";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		cout << "mysql_query insert data successed" << endl;
	}
	else
	{
		ErrorHandling("mysql_query insert data failed");
	}

	//��ʾ��������� 
	sqlstr = "select user_id, user_name, user_second_sum from user_info";
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		cout << "mysql_query select data success" << endl;
		//��ȡ���ݼ�
		result = mysql_store_result(&mydata);
		//��ȡ���� 
		int rowcount = mysql_num_rows(result);
		cout << "row counts: " << rowcount << endl;
		
		//ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD * field = NULL;
		for (unsigned i = 0; i < fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}

		//��ӡ����
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

	//ɾ���ղŽ��ı� 
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
