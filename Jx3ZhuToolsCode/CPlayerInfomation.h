#pragma once
#include <math.h>
//玩家对象信息
enum PLAYER_OFFSET
{
	PLAYER_ID_OFFSET = 0x10,//ID偏移
	PLAYER_OBJECT_OFFSET = 0x14,//对象地址偏移
	PLAYER_POINT_X_OFFSET = 0x8,//X坐标偏移
	PLAYER_POINT_Y_OFFSET = 0xC,//Y坐标偏移
	PLAYER_POINT_Z_OFFSET = 0x10,//Z坐标偏移
	PLAYER_NAME_OFFSET = 0x58,//名称偏移
	PLAYER_LEVEL_OFFSET = 0xDC,//等级偏移
	PLAYER_TREE_FLAG_OFFSET = 0xD//二叉标识偏移
};

class CCPlayerInfomation
{
private:
	int TREE_ADDR;//树地址
	int PLAYER_ID;//玩家ID
	int PLAYER_OBJECT_ADDR;//玩家对象地址
	int PLAYER_POINT_X;//玩家X坐标
	int PLAYER_POINT_Y;//玩家Y坐标
	int PLAYER_POINT_Z;//玩家Z坐标
	int PLAYER_LEVEL;//玩家等级
	string PLAYER_NAME;//玩家名称
	int TREE_FLAG;//玩家二叉标识

public:
	CCPlayerInfomation(void);
	~CCPlayerInfomation(void);
	CCPlayerInfomation(int addr);
	//内联
	//获取Tree地址
	int getTreeAddr()
	{
		return TREE_ADDR;
	}
	//获取Tree地址
	int getTreeFlag()
	{
		TREE_FLAG = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				TREE_FLAG = *(BYTE *)(TREE_ADDR + PLAYER_TREE_FLAG_OFFSET);
			}
		__CATCH("获取二叉树标识出错!")
		return TREE_FLAG;
	}
	//获取玩家全写ID
	int getPlayerALLID()
	{
		PLAYER_ID = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				PLAYER_ID = *(int *)(TREE_ADDR + PLAYER_ID_OFFSET);
			}
		__CATCH("获取玩家对象All_ID出错!")
		return PLAYER_ID;
	}
	//获取玩家坐标X
	int getPlayerX()
	{
		PLAYER_POINT_X = 0;
		__TRY
			if(PLAYER_OBJECT_ADDR && IsReadAddrInt((PVOID)PLAYER_OBJECT_ADDR))
			{
				PLAYER_POINT_X = *(int *)(PLAYER_OBJECT_ADDR + PLAYER_POINT_X_OFFSET);
			}
			__CATCH("获取玩家坐标X出错!")
				return PLAYER_POINT_X;
	}
	//获取玩家等级
	int getPlayerLevel()
	{
		PLAYER_LEVEL = 0;
		__TRY
			if(PLAYER_OBJECT_ADDR && IsReadAddrInt((PVOID)PLAYER_OBJECT_ADDR))
			{
				PLAYER_LEVEL = *(int *)(PLAYER_OBJECT_ADDR + PLAYER_LEVEL_OFFSET);
			}
			__CATCH("获取玩家等级出错!")
				return PLAYER_LEVEL;
	}
	//获取玩家坐标Y
	int getPlayerY()
	{
		PLAYER_POINT_Y = 0;
		__TRY
			if(PLAYER_OBJECT_ADDR && IsReadAddrInt((PVOID)PLAYER_OBJECT_ADDR))
			{
				PLAYER_POINT_Y = *(int *)(PLAYER_OBJECT_ADDR + PLAYER_POINT_Y_OFFSET);
			}
		__CATCH("获取玩家坐标Y出错!")
		return PLAYER_POINT_Y;
	}
	//获取玩家坐标Z
	int getPlayerZ()
	{
		PLAYER_POINT_Z = 0;
		__TRY
			if(PLAYER_OBJECT_ADDR && IsReadAddrInt((PVOID)PLAYER_OBJECT_ADDR))
			{
				PLAYER_POINT_Z = *(int *)(PLAYER_OBJECT_ADDR + PLAYER_POINT_Z_OFFSET);
			}
		__CATCH("获取玩家坐标Z出错!")
		return PLAYER_POINT_Z;
	}
	//获取玩家距离
	int getPlayerDsc()
	{
		int DESC = 9999;
		__TRY
		CCUserInfo _CCUserInfo;
		int PlayerPX = getPlayerX();
		int PlayerPY = getPlayerY();
		int RoleX = _CCUserInfo.getObjectPointX();
		int RoleY = _CCUserInfo.getObjectPointY();
		DESC = (int)sqrt((PlayerPX - RoleX)*(PlayerPX-RoleX)+ (PlayerPY - RoleY)*(PlayerPY-RoleY));
		__CATCH("获取玩家距离出错!")
		return DESC;
	}
	//获取玩家名称
	const char * getPlayerName()
	{
		PLAYER_NAME = "";
		__TRY
			if(PLAYER_OBJECT_ADDR && IsReadAddrInt((PVOID)PLAYER_OBJECT_ADDR))
			{
				char PlayerName[255] = {0};
				strcpy_s(PlayerName,(char *)(PLAYER_OBJECT_ADDR + PLAYER_NAME_OFFSET));
				char * U2GStr =  U2G(PlayerName);
				memset(PlayerName,0,255);
				strcpy_s(PlayerName,U2GStr);
				if(U2GStr) delete[] U2GStr;
				PLAYER_NAME = PlayerName;
			}
		__CATCH("获取玩家名称出错!")
		return PLAYER_NAME.c_str();
	}
};
//lua 封装类
class RgisterCCPlayerInfomation
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCPlayerInfomation**)lua_newuserdata(L,sizeof(CCPlayerInfomation*)) = new CCPlayerInfomation(nValue);
		luaL_getmetatable(L, "CCPlayerInfomation"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCPlayerInfomation**)lua_topointer(L,1);  
		return 0;  
	}
	
	//获取对象ALL_ID
	static int CallGetPlayerAllID(lua_State* L)  
	{ 
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getPlayerALLID());
		return 1;  
	}
	//获取X坐标
	static int CallGetPlayerLevel(lua_State* L)  
	{ 
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getPlayerLevel());
		return 1;  
	}
	//获取X坐标
	static int CallGetPlayerX(lua_State* L)  
	{ 
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getPlayerX());
		return 1;  
	}
	//获取Y坐标
	static int CallGetPlayerY(lua_State* L)  
	{ 
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getPlayerY());
		return 1;  
	}
	//获取Z坐标
	static int CallGetPlayerZ(lua_State* L)  
	{ 
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getPlayerZ());
		return 1;  
	}
	//获取距离
	static int CallGetPlayerDESC(lua_State* L)  
	{ 
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getPlayerDsc());
		return 1;  
	}
	//获取名称
	static int CallGetPlayerName(lua_State* L)  
	{  
		CCPlayerInfomation** pT = (CCPlayerInfomation**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getPlayerName());  
		return 1;
	}

	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCPlayerInfomation::CreateClass); 
		lua_setglobal(L,"CCPlayerInfomation");
		luaL_newmetatable(L,"CCPlayerInfomation"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCPlayerInfomation::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  

		lua_pushstring(L,"getPlayerALLID");  
		lua_pushcfunction(L,CallGetPlayerAllID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getPlayerLevel");  
		lua_pushcfunction(L,CallGetPlayerLevel);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getPlayerX");  
		lua_pushcfunction(L,CallGetPlayerX);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getPlayerY");  
		lua_pushcfunction(L,CallGetPlayerY);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getPlayerZ");  
		lua_pushcfunction(L,CallGetPlayerZ);
		lua_settable(L,-3);

		lua_pushstring(L,"getPlayerDsc");  
		lua_pushcfunction(L,CallGetPlayerDESC);
		lua_settable(L,-3);

		lua_pushstring(L,"getPlayerName");  
		lua_pushcfunction(L,CallGetPlayerName);
		lua_settable(L,-3);
		
		lua_pop(L,1);
	}
};
