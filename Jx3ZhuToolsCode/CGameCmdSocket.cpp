#include "stdafx.h"
#include "CGameCmdSocket.h"
#pragma comment (lib ,"ws2_32.lib")

CCGameCmdSocket _cllSocket;//不作为类变量
CCGameCmdSocket::CCGameCmdSocket(void)
{
}


CCGameCmdSocket::~CCGameCmdSocket(void)
{
}
/*
 * 初始化命令套接字
 */
void CCGameCmdSocket::InitSocketClent()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//初始化Socket
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return;
	}
	sockClient=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(8091);
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
}
/*
 * 初始化角色信息通讯套接字
 */
void CCGameCmdSocket::InitSocketUserInfo()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//初始化Socket
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return;
	}
	sockClientUser=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(8091);
	connect(sockClientUser,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
}