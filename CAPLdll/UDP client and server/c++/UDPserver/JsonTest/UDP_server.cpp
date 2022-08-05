#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include "json.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"json_vc71_libmtd.lib")

int main()
{
	WSADATA wsaData;
	SOCKET RecvSocket;
	Json::Value root;
	Json::StyledWriter style_writer;
	Json::Reader reader;

	//初始化Socket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("failed to load winsock.\n");
		return 0;
	}
	//创建Socket对象
	RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//设置服务器地址
	sockaddr_in RecvAddr;
	int Port = 20000;
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定socket
	bind(RecvSocket, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));

	char RecvBuf[1024];
	int BufLen = 1024;
	sockaddr_in SenderAddr;
	int SendAddrSize = sizeof(SenderAddr);
	recvfrom(RecvSocket, RecvBuf, BufLen, 0, (SOCKADDR*)&SenderAddr, &SendAddrSize);

	std::string strName;
	if (reader.parse(RecvBuf, root))
	{
		strName = root["name"].asString();
	}
	std::cout << strName << std::endl;

	//关闭连接
	closesocket(RecvSocket);
	WSACleanup();
	getchar();
	return 0;
}
