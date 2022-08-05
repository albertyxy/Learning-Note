// JsonTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include "json.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"json_vc71_libmtd.lib")

int main()
{
	Json::Value root;
	Json::StyledWriter style_writer;
	Json::Reader reader;

	root["name"] = "albert";
	root["age1"] = 5;
	WSADATA wsaData;
	SOCKET SendSocket;
	sockaddr_in RecvAddr;
	int Port = 20000;
	//初始化Socket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
		printf("failed to load winsock.\n");
		return 0;
	}
	//创建Socket对象
	SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//设置服务器地址
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	std::string SendBuf = style_writer.write(root);
	//向服务器发送数据
	while(true)
	{ 
	sendto(SendSocket, SendBuf.c_str(), SendBuf.size(), 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
	}


	//关闭连接
	closesocket(SendSocket);
	WSACleanup();
	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
