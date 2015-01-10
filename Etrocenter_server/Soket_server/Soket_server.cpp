// Soket_server.cpp : Defines the entry point for the console application.
//

//#include <winsock2.h>
//#include <winsock.h>
//#include <WS2tcpip.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include<sys/socket.h>
//#include<stdio.h>
#include "stdafx.h"
#include "globaldef.h"
HANDLE g_handle = NULL;

void tcp_socket()
{
	g_handle = (HANDLE)::_beginthreadex(NULL, 0, &socket_server_tcp, NULL, 0, NULL);

	//while(1)
 	{
 		//socket_client();
 	}

	//WaitForSingleObject( g_handle, INFINITE );
	//CloseHandle( g_handle );
}

void udp_socket()
{
	g_handle = (HANDLE)::_beginthreadex(NULL, 0, &socket_server_udp, NULL, 0, NULL);

	while(1)
	{
		socket_client();
	}

	WaitForSingleObject( g_handle, INFINITE );
	CloseHandle( g_handle );
}

int _tmain(int argc, _TCHAR* argv[])
{
 	if (!AfxSocketInit())
 	{
 		return -1;
 	}

	tcp_socket();
	//udp_socket();

	string str;
	cin>> str;

	return 0;
}