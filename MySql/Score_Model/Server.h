#pragma once
#include <WinSock2.h>
#include <string>
struct DataStruct
{
	std::string name;
	int score;
	int time;
};


class CServer
{
public:
	bool initServer(int argc, char * argv[]);
	void insertData(const char name[], int score, int time);
	void deleteData(const char name[]);
	void updateData(const char name[], int score, int time);
	int findData(const char name[]);
	void getAllData();
	void getOneData();
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
	DataStruct* getStructData(char * msg);
	//unsigned WINAPI ReceiveMain(void* arg );
};

