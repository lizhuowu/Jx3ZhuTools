#pragma once
#include "SocketStruct.h"
#include "CUserConfig.h"
#include "CGameCmdSocket.h"
class CCSocketCmd
{
public:
	CCSocketCmd(void);
	~CCSocketCmd(void);
public:
	HANDLE m_pThread_Recv;
public:	
	void InitSocketAll();
};

