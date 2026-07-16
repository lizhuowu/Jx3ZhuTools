#ifndef _STRURCT_SOCKET
#define _STRURCT_SOCKET


#define SOCKET_LINK 10 //连接服务端消息
#define SOCKET_USERINFO 11 //客户端->服务端 发送角色信息
#define SOCEKT_LOGIN_INFO 16 //登录信息
#define SOCKET_LOGIN_ACTION 18 //登录游戏命令
#define SOCKET_GAME_INFO	19 //游戏信息


#pragma pack(push)
#pragma pack(1)

/*
 * 通讯基础结构体（理论上说每条命令传递来后，通用转换的）
 */
typedef struct _Socket_Base
{
	unsigned int socketType;//通讯指令
	unsigned int gameID;//游戏的ID
}SocketBase,*PSOCKETBASE;
/*
 * 登录命令(服务端通知客户端登录)
 */
struct _Socket_Login_Cmd
{
	unsigned int socketType;//通讯指令
	unsigned int cmdID;//命令ID
};

/*
 * 服务端发来登陆的IP 和 角色索引
 */
struct _Socket_Login_UserName_Pwd
{
	unsigned int socketType;//通讯指令
	char MOLOName[30];//MOLO账号
	char AreaIP[20];//服务器IP
	unsigned int selectRole;//登录的角色索引
};

/*
 *登陆结果
 */
struct _Socket_Login_Sucess
{
	unsigned int socketType;//通讯指令
	char MOLOName[30];//MoloName
	unsigned int sucess;//成功=1 (这里直接不做失败处理)
};

/*
 *游戏信息
 */
struct __SocketGameInfo
{
	unsigned int socketType;//通讯指令
	char MOLOName[30];//MoloName
	char Message[100];//信息
};

/*
 * 向服务端发送当前的角色信息
 */
struct _User_RoleInfo
{
	unsigned int socketType;//通讯指令
	char MOLOName[30];//MoloName
	char roleName[40];//角色名
	unsigned int roleLevel;//等级
	unsigned int roleBlood;//血量
	unsigned int roleMaxBlood;//最大血
	unsigned int roleGold;//金币
};

#pragma pack(pop)

#endif