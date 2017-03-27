#include "Server.h"
#include <iostream>
#include <process.h>
#include <sstream>
#include <string>
using namespace std;
CServer* CServer::m_pServer = NULL;

unsigned WINAPI ReceiveMain(void* arg);
bool CServer::initServer(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "usage: " << argv[0] << "<ip> <port>" << endl;
		return false;
	}

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}

	m_pSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_pSocket == INVALID_SOCKET)
	{
		return false;
	}

	sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(m_pSocket, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void CServer::insertData(const char name[], int score, int time)
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "insert %s %d %d end", name, score, time);
	sendMsg(msg);
}

void CServer::deleteData(const char name[])
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "delete %s end", name);
	sendMsg(msg);
	
}

void CServer::updateData(const char name[], int score, int time)
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "update %s %d %d end", name, score, time);
	sendMsg(msg);
}

int CServer::findData(const char name[])
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "find %s end", name);
	sendMsg(msg);

	char buf[100];
	int len = recv(m_pSocket, buf, 100, 0);
	buf[len] = 0;

	if (buf[0] == '!')
	{
		cout << "receive from serv: " << buf << endl;
		return -1;
	}
	int arr[2];
	int index = 0;
	for (int i = 0, j = 0; i <= strlen(buf); i++)
	{
		if (buf[i] == ' ' || buf[i] == '\0')
		{
			arr[j++] = atoi(buf + index);
			index = i + 1;
		}
	}

	cout << "receive : " << arr[0] << " and " << arr[1] << endl;

	return 0;
}

void CServer::getAllData()
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "getall end");
	sendMsg(msg);
	
	char buf[1024];
	int len = recv(m_pSocket, buf, 100, 0);
	buf[len] = '\0';
	if (buf[0] == '!')
	{
		cout << "receive from serv: " << buf << endl;
		return;
	}
	DataStruct * ds = getStructData(buf);
}

void CServer::getOneData()
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "getone end");
	sendMsg(msg);

	char buf[100];
	int len = recv(m_pSocket, buf, 100, 0);
	buf[len] = '\0';
	if (buf[0] == '!')
	{
		cout << "receive from serv: " << buf << endl;
		return;
	}

	DataStruct * ds = getStructData(buf);
}

CServer * CServer::getInstance()
{
	if (m_pServer == NULL)
	{
		return new CServer;
	}

	return m_pServer;
}

void CServer::setScore(int sc)
{
	score = sc;
}

int CServer::getScore()
{
	return score;
}

CServer::CServer()
{
}

CServer::~CServer()
{
	delete m_pServer;
}

void CServer::sendMsg(char * msg)
{
	send(m_pSocket, msg, strlen(msg), 0);
}

DataStruct * CServer::getStructData(char * msg)
{
	string command = msg;
	stringstream stream(command);
	int max = 0;
	string arr[30] = { "\0" };
	while (stream >> arr[max++])
	{
	}

	int dslen = (max - 1) / 3;
	DataStruct *ds = new DataStruct[dslen];
	int index = 0;
	for (int i = 0; i < max - 1; i++)
	{
		index = i / 3;
		switch (i % 3)
		{
		case 0:
			ds[index].name = arr[i];
			break;
		case 1:
			ds[index].score = atoi(arr[i].c_str());
			break;
		case 2:
			ds[index].time = atoi(arr[i].c_str());
			break;
		}
	}

	for (int i = 0; i < dslen; i++)
	{
		cout << ds[i].name <<  " " << ds[i].score <<  " " << ds[i].time << endl;
	}

	return ds;
}

unsigned WINAPI ReceiveMain(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	char buf[100];
	while (true)
	{
		int len = recv(sock, buf, 100, 0);
		buf[len] = 0;
		cout << "receive : " << buf << endl;

		CServer::getInstance()->setScore(atoi(buf));
	}
	
	return 0;
}
