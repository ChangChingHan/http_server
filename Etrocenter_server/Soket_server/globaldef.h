#include "afxsock.h"
#include<stdlib.h>
#include<sys/types.h>
#include <errno.h>
#include<string>
#include <process.h>
#include <iostream>
using namespace std;

unsigned __stdcall socket_server_udp(void* pArguments);
void socket_client();
unsigned __stdcall socket_server_tcp(void* pArguments);