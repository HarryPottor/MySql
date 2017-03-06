#include <iostream>
#include <cstdlib>
#include <WinSock2.h>
#include <string>
#include <process.h>

using namespace std;
#define SA SOCKADDR
#define BUF_SZ 100

unsigned WINAPI SendMain(void *);
unsigned WINAPI ReceiveMain(void *);

void ErrorHandling(const char* msg)
{
	cout << msg << endl;
	system("pause");
	exit(1);
}

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	SOCKET servSock;
	SOCKADDR_IN servAddr;

	if (argc != 3)
	{
		cout << "usage: " << argv[0] << "<ip> <port>" << endl;
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		ErrorHandling("wsastartup error");
	}

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
	{
		ErrorHandling("socket error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(servSock, (SA *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect error");
	}
	else
	{
		puts("contected ...");
	}

	HANDLE send_t;
	HANDLE receive_t;

	send_t = (HANDLE)_beginthreadex(NULL, 0, SendMain, (void *)&servSock, 0, NULL);
	receive_t = (HANDLE)_beginthreadex(NULL, 0, ReceiveMain, (void *)&servSock, 0, NULL);

	WaitForSingleObject(send_t, INFINITE);
	WaitForSingleObject(receive_t, INFINITE);

	CloseHandle(send_t);
	CloseHandle(receive_t);
	
	system("pause");
	return 0;
}

unsigned WINAPI SendMain(void * arg)
{
	SOCKET serv_sock = *((SOCKET*)arg);
	char buf[BUF_SZ];
	string msg;
	while (true)
	{
		
		puts("input : ");
		//cin >> buf;
		/*
		if (!strcmp(buf, "q\n"))
		{
			puts("client disconnected");
			return 0;
		}
		send(serv_sock, buf, strlen(buf), 0);
		*/


		getline(cin, msg);
		if (msg == "quit")
		{
			puts("client disconnected");
			return 0;
		}
		send(serv_sock, msg.c_str(), msg.size(), 0);
	}
	return 0;
}

unsigned WINAPI ReceiveMain(void * arg)
{
	SOCKET serv_sock = *((SOCKET*)arg);
	char buf[BUF_SZ];
	while (true)
	{
		
		int len = recv(serv_sock, buf, BUF_SZ, 0);
		if (len == 0)
		{
			puts("server disconnected");
			return 0;
		}
		buf[len] = 0;
		cout << "receive : " << buf << endl;
		
	}
	return 0;
}
