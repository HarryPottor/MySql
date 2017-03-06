#pragma once
#include <WinSock2.h>

class CServer
{
public:
	bool initServer(int argc, char * argv[]);
	void insertData(const char name[], int score);
	void deleteData(const char name[]);
	void updateData(const char name[], int score);
	int findData(const char name[]);
	static CServer* getInstance();

	void setScore(int);
	int getScore();
private:
	CServer();
	~CServer();
	static CServer* m_pServer;
	SOCKET m_pSocket;
	char msg[100];
	int score;
	void sendMsg(char * msg);
	//unsigned WINAPI ReceiveMain(void* arg );
};

