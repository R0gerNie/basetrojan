#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
int main(int argc,char* argv[] ) {
	ShowWindow(FindWindow("ConsoleWindowClass", argv[0]), 0);
	while (1) {
		
		WSADATA wsa_data;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		SOCKET fd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		SOCKADDR_IN server_addr; //服务器配置
		int port = 15002; //端口号 
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);//端口号范围： 0 ~65535
		server_addr.sin_addr.s_addr = inet_addr("49.233.89.112");
		char send_buff[512] = "example";
		ret = sendto(fd_socket, send_buff, strlen(send_buff), 0, (SOCKADDR *)&server_addr, 512);
		closesocket(fd_socket);
		WSACleanup();
		Sleep(5*60*1000);
	}
}
