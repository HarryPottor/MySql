#include "Server.h"
#include <iostream>
#include <process.h>
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

void CServer::insertData(const char name[], int score)
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "insert %s %d end", name, score);
	sendMsg(msg);
}

void CServer::deleteData(const char name[])
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "delete %s end", name);
	sendMsg(msg);
	
}

void CServer::updateData(const char name[], int score)
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "update %s %d end", name, score);
	sendMsg(msg);
}

int CServer::findData(const char name[])
{
	memset(&msg, 0, sizeof(msg));
	sprintf(msg, "find %s end", name);
	sendMsg(msg);

	/*
	HANDLE recvHandle;
	recvHandle = (HANDLE)_beginthreadex(NULL, 0, ReceiveMain, (void*)m_pSocket, 0, NULL);
	*/
	char buf[100];
	int len = recv(m_pSocket, buf, 100, 0);
	buf[len] = 0;
	cout << "receive : " << atoi(buf) << endl;

	return 0;
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
