#include "stdafx.h"
#include "CSocketCmd.h"


CCSocketCmd::CCSocketCmd(void)
{
}


CCSocketCmd::~CCSocketCmd(void)
{
}

/*
 * 处理服务端指令消息
 */
void MessageActionRun(char *MessageBuffer)
{
	PSOCKETBASE _socketBase = (PSOCKETBASE)MessageBuffer;
	switch (_socketBase->socketType)
	{
	case SOCEKT_LOGIN_INFO:
		{
			TRACE("接收到登陆信息");
			_Socket_Login_UserName_Pwd *_SocketLoginUserNamePwd=(_Socket_Login_UserName_Pwd *)MessageBuffer;
			char bufferStr[30] = {0};
			memcpy(bufferStr,_SocketLoginUserNamePwd->MOLOName,30);
			UserMoloName = bufferStr;
			memset(bufferStr,0,30);
			memcpy(bufferStr,_SocketLoginUserNamePwd->AreaIP,20);
			UserLoginTP = bufferStr;
			_IndexRole = _SocketLoginUserNamePwd->selectRole;
			TRACE("登陆信息: UserMoloName =  %s,UserLoginTP = %s,%d",UserMoloName.c_str(),UserLoginTP.c_str(),_IndexRole);
			char linkBuffer[140] ={0};
			__SocketGameInfo *___SocketGameInfo = (__SocketGameInfo *)linkBuffer;
			strcpy(___SocketGameInfo->MOLOName,UserMoloName.c_str());
			strcpy(___SocketGameInfo->Message,"已准备登录");
			___SocketGameInfo->socketType = SOCKET_GAME_INFO;
			send(_cllSocket.sockClient,(char *)___SocketGameInfo,sizeof(__SocketGameInfo)+1,0);
		}
		break;
	case SOCKET_LOGIN_ACTION:
		{
			TRACE("开始登陆游戏");
		}
		break;
	default:
		break;
	}
}
/*
 * 接收服务端指令
 */
DWORD WINAPI runRecv(LPVOID p)
{
	while (1)
	{
		char recvBuf[4096];
		int RecvCount = recv(_cllSocket.sockClient,recvBuf,4096,0);
		if (RecvCount > 0)
		{
			MessageActionRun(recvBuf);
		}
	}
	return 0;
}
/*
 * 初始化套接字统一函数
 */
void CCSocketCmd::InitSocketAll()
{
	_cllSocket.InitSocketClent();
	_cllSocket.InitSocketUserInfo();
	//接收线程
	m_pThread_Recv =::CreateThread(NULL,0,runRecv,(LPVOID)1,0,NULL);
	//发送链接服务器命令
	char linkBuffer[30] ={0};
	PSOCKETBASE _socketBase = (PSOCKETBASE)linkBuffer;
	_socketBase->gameID = GetCurrentProcessId();
	_socketBase->socketType = SOCKET_LINK;
	send(_cllSocket.sockClient,(char *)_socketBase,sizeof(_Socket_Base)+1,0);
	TRACE("SocketCmd Socket init sucess");
}