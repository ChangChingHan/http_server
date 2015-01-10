#include "stdafx.h"
#include "globaldef.h"

unsigned __stdcall socket_server_tcp(void* pArguments)
{
	struct sockaddr_in dest, sa_from;
	memset(&dest,0x00,sizeof(dest));

	char send_message[512];
	char receive_message[512];
	memset(send_message, 0x00, sizeof(send_message));
	memset(receive_message, 0x00, sizeof(receive_message));

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	dest.sin_family = AF_INET;
	dest.sin_port = htons(8180);
	dest.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd,(struct sockaddr *)&dest,sizeof(dest)) == 0)
	{
		listen(sockfd,5);
		int clientfd = 0;

		struct sockaddr_in client_add;
		int addrlen = sizeof(client_add);
		string str;

		while ((clientfd = accept(sockfd,(struct sockaddr *)&client_add, &addrlen)) != -1)//TCP  會在此等待
		{
			int a  = 0 ,b = 0;
			while(1)
			{
				memset(&receive_message, 0x00, sizeof(receive_message));

				if ((a = recv(clientfd, receive_message, sizeof(receive_message), 0)) <= 0)
				{
					closesocket(clientfd);
					break;
				}
				int n = strlen(receive_message);
				if (n == 0)
				{
					closesocket(clientfd);
					break;
				}

				string str = receive_message;
				if (str.find("add") != string::npos)
				{
					sprintf_s(send_message, 512, "HTTP/1.0 200 OK\r\nContent-type: text/plain\r\nExpires: Thu, 01 Dec 1994 16:00:00 GMT\r\n\r\n%s",
							"{Add}");
				}
				else if (str.find("get") != string::npos)
				{
					sprintf_s(send_message, 512, "HTTP/1.0 200 OK\r\nContent-type: text/plain\r\nExpires: Thu, 01 Dec 1994 16:00:00 GMT\r\n\r\n\%s",
							"{Get}");
				}
				
				n = strlen(send_message);
				if ((b = send(clientfd, send_message, n, 0)) > 0)
				{
					closesocket(clientfd);
					break;
				}
			}
		}

		closesocket(sockfd);
	}
	return 0;
}

void socket_client()
{
	struct sockaddr_in des;
	memset(&des, 0x00, sizeof(des));

	char send_message[128];
	char receive_message[128];
	memset(send_message, 0x00, sizeof(send_message));
	memset(receive_message, 0x00, sizeof(receive_message));

	int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	des.sin_family = PF_INET;
	des.sin_port = htons(7402);
	des.sin_addr.s_addr = inet_addr("255.255.255.255");

	if (connect(socketfd, (struct sockaddr*)&des, sizeof(des)) == 0)
	{
		string str;
		while(1)
		{
			getline (cin,str);
			memset(send_message, 0x00, sizeof(send_message));
			memccpy(send_message,str.c_str(),str.length(),str.length());
			send(socketfd, send_message, sizeof(send_message), 0);

			// 			memset(&receive_message, 0x00, sizeof(receive_message));
			// 			recv(socketfd, receive_message, sizeof(receive_message), 0);
		}
		closesocket(socketfd);
	}
	closesocket(socketfd);
}

unsigned __stdcall socket_server_udp(void* pArguments)
{
	struct sockaddr_in dest, sa_from;
	memset(&dest,0x00,sizeof(dest));

	char send_message[128];
	char receive_message[128];
	memset(send_message, 0x00, sizeof(send_message));
	memset(receive_message, 0x00, sizeof(receive_message));

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	dest.sin_family=AF_INET;
	dest.sin_port=htons(7401);
	dest.sin_addr.s_addr=INADDR_ANY;
	if (bind(sockfd,(struct sockaddr *)&dest,sizeof(dest)) == 0)
	{
		int clientfd = 0;
		struct sockaddr_in client_add;
		int addrlen = sizeof(client_add);
		string str;

		memset(&receive_message, 0x00, sizeof(receive_message));

		int addr_len = sizeof(struct sockaddr_in); 
		int i = recvfrom(sockfd, receive_message,sizeof(receive_message), 0 , (struct sockaddr *)&sa_from ,&addr_len);
		if (i)
		{
			printf("buffer_rec:%s\n",inet_ntoa(sa_from.sin_addr));
			printf("buffer_rec:%s\n",receive_message);
		}
		closesocket(sockfd);
	}
	return 0;
}