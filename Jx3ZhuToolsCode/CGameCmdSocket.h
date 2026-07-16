#pragma once
#include <Winsock2.h>
class CCGameCmdSocket
{
public:
	SOCKET sockClient;
	SOCKET sockClientUser;
public:
	CCGameCmdSocket(void);
	~CCGameCmdSocket(void);
public:
	void InitSocketClent();
	void InitSocketUserInfo();
};
extern CCGameCmdSocket _cllSocket;//不作为类变量
