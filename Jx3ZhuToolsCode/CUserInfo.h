#pragma once
#include "cobjectbase.h"
#include "CUTF8.h"


enum USER_ONFO_OFFSET
{
	USER_ID_OFFSET = 4,//人物ID
	USER_POINT_X_OFFSET = 8,//坐标X
	USER_POINT_Y_OFFSET = 0xC,//坐标Y
	USER_POINT_Z_OFFSET = 0x10,//坐标Z
	USER_NAME_OFFSET = 0x58,//名字 ASCII
	USER_TITLE_OFFSET = 0x78,//称号 ASCII
	USER_LEVEL_OFFSET = 0xDC, //人物选中对象的类型偏移
	USER_SELECT_FLAG_OFFSET = 0x8B0, //人物选中对象的类型偏移
	USER_SELECT_ID_OFFSET = 0x8B4, //人物选中怪物ID
	USER_DIRECTION_OFFSET = 0x30,//人物面向偏移
	USER_MAP_OFFSET_1 = 0x44,//人物地图偏移1
	USER_MAP_OFFSET_2 = 0x14//人物地图偏移2
};

class CCUserInfo
{
private:
	unsigned int BASE_ADDR;//存在地址
	unsigned int ObjectID;//对象ID
	unsigned int ObjectPointX;//对象X坐标
	unsigned int ObjectPointY;//对象Y坐标
	unsigned int ObjectPointZ;//对象Z坐标
	unsigned int ObjectLevel;//对象等级
	string ObjectName;//对像名称
	string ObjectTitle;//对象称号
	string ObjectMap;//对象地图
	int ObjectCurrentBlood;//对象当前血
	int ObjectMaxBlood;//对象最大血
	int ObjectCurrentMagic;//对象当前魔法
	int ObjectMaxMagic;//对象最大魔法
	int ObjectSelectFlag;//对象选中标识 未选择1，选中为大于1,类别标识
	int ObjectDeiection;//人物面向
	int ObjectBellte;//人物战斗状态1.战斗 0 非战斗
	int ObjectGold;//人物金币
	int ObjectXiuWei;//人物修为
public:
	CCUserInfo(void);
	~CCUserInfo(void);
	//内联
	//获取地址
	int getBaseAddr(){return BASE_ADDR;}
	//内联函数
	//获取对象ID
	int getObjectID()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectID = *(unsigned int *)(BASE_ADDR + USER_ID_OFFSET);
		}
		return ObjectID;
	}
	//获取对象X坐标
	int getObjectPointX()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectPointX =  *(unsigned int *)(BASE_ADDR + USER_POINT_X_OFFSET);
		}
		return ObjectPointX;
	}
	//获取对象Y坐标
	int getObjectPointY()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectPointY =  *(unsigned int *)(BASE_ADDR + USER_POINT_Y_OFFSET);
		}
		return ObjectPointY;
	}
	//获取对象Z坐标
	int getObjectPointZ()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectPointZ =  *(unsigned int *)(BASE_ADDR + USER_POINT_Z_OFFSET);
		}
		return ObjectPointZ;
	}
	//获取对象等级
	int getObjectLevel()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectLevel = *(unsigned int *)(BASE_ADDR + USER_LEVEL_OFFSET);
		}
		return ObjectLevel;
	}
	//获取对象名称
	string getObjectName()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			char charStr[255] = {0};
			strcpy_s(charStr,(char *)(BASE_ADDR + USER_NAME_OFFSET));
			char * U2GStr =  U2G(charStr);
			memset(charStr,0,255);
			strcpy_s(charStr,U2GStr);
			if(U2GStr) delete[] U2GStr;
			ObjectName = charStr;
		}
		return ObjectName;
	}
	//获取对象名称
	const char * getObjectNameEx()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			char charStr[255] = {0};
			strcpy_s(charStr,(char *)(BASE_ADDR + USER_NAME_OFFSET));
			char * U2GStr =  U2G(charStr);
			memset(charStr,0,255);
			strcpy_s(charStr,U2GStr);
			if(U2GStr) delete[] U2GStr;
			ObjectName = charStr;
		}
		return ObjectName.c_str();
	}
	//获取对象称号
	string getObjectTitle()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			char charStr[255] = {0};
			strcpy_s(charStr,(char *)(BASE_ADDR + USER_TITLE_OFFSET));
			ObjectTitle = charStr;
		}
		return ObjectTitle;
	}
	//获取对象地图
	string getObjectMap()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			int MapAddr = *(int *)(BASE_ADDR + USER_MAP_OFFSET_1);
			char charStr[255] = {0};
			strcpy_s(charStr,(char *)(MapAddr + USER_MAP_OFFSET_2));
			ObjectMap = charStr;
		}
		return ObjectMap;
	}
	//获取对象当前血
	int getObjectCurrentBlood()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectCurrentBlood = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_BLOOD_OFFSET);
		}
		return ObjectCurrentBlood;
	}
	//获取对象最大血
	int getObjectMaxBlood()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectMaxBlood = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_BLOOD_OFFSET + 4);
		}
		return ObjectMaxBlood;
	}
	//获取对象当前魔法
	int getObjectCurrentMagic()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectCurrentMagic = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_MAGIC_OFFSET);
		}
		return ObjectCurrentMagic;
	}
	//获取对象最大魔法
	int getObjectMaxMagic()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectMaxMagic = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_MAGIC_OFFSET + 4);
		}
		return ObjectMaxMagic;
	}
	//获取血值百分比
	int getObjectBloodPercent()
	{
		if(getObjectMaxBlood() <=0)
		{
			return 0;
		}
		return (int)((getObjectCurrentBlood() / (getObjectMaxBlood() * 1.0)) * 100);
	}
	//获取魔法值百分比
	int getObjectMagicPercent()
	{
		if(getObjectMaxMagic() <=0)
		{
			return 0;
		}
		return (int)((getObjectCurrentMagic() / (getObjectMaxMagic() * 1.0)) * 100);
	}
	//获取人物面向
	int getObjectDirection()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectDeiection = *(unsigned int *)(BASE_ADDR + USER_DIRECTION_OFFSET);
		}
		return ObjectDeiection;
	}
	//人物战斗状态
	int getRoleBettle()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectBellte = *(unsigned int *)(BASE_ADDR + USER_ACTION_STATUS_OFFSET);
		}
		return ObjectBellte;
	}
	//人物选中对象的ID
	int getSelectObjectID()
	{
		int SelectObjectID = 0;
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			SelectObjectID = *(unsigned int *)(BASE_ADDR + ROLE_SELECT_ID_OFFSET + 0x4);
		}
		return SelectObjectID;
	}
	//人物金币
	int getRoleGold()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectGold = *(unsigned int *)(BASE_ADDR + USER_GLOD_OFFSET);
		}
		return ObjectGold;
	}
	//人物修为
	int getRoleXiuWei()
	{
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectXiuWei = *(unsigned int *)(BASE_ADDR + ROLE_XIUWEI_OFFSET);
		}
		return ObjectXiuWei;
	}
};
//lua 封装类
class RgisterCCUserInfo
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数 
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCUserInfo**)lua_newuserdata(L,sizeof(CCUserInfo*)) = new CCUserInfo();
		luaL_getmetatable(L, "CCUserInfo"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCUserInfo**)lua_topointer(L,1);  
		return 0;  
	}
	//获取人物对象地址
	static int CallgetBaseAddr(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getBaseAddr());
		return 1;  
	}
	//获取人物ID
	static int CallgetObjectID(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getObjectID());
		return 1;  
	}
	//获取人物X坐标
	static int CallgetObjectPointX(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectPointX());
		return 1;  
	}
	//获取人物Y坐标
	static int CallgetObjectPointY(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectPointY());
		return 1;  
	}
	//获取人物Z坐标
	static int CallgetObjectPointZ(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectPointZ());
		return 1;  
	}
	//获取人物等级
	static int CallgetObjectLevel(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectLevel());
		return 1;  
	}
	//获取人物名称
	static int CallgetObjectName(lua_State* L)  
	{  
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getObjectName().c_str());  
		return 1;
	}
	//获取人物称号
	static int CallgetObjectTitle(lua_State* L)  
	{  
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getObjectTitle().c_str());  
		return 1;
	}
	//获取人物地图
	static int CallgetObjectMap(lua_State* L)  
	{  
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getObjectMap().c_str());  
		return 1;
	}
	//获取人物当前血
	static int CallgetObjectCurrentBlood(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectCurrentBlood());
		return 1;  
	}
	//获取人物最大血
	static int CallgetObjectMaxBlood(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectMaxBlood());
		return 1;  
	}
	//获取人物当前魔法
	static int CallgetObjectCurrentMagic(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectCurrentMagic());
		return 1;  
	}
	//获取人物最大魔法
	static int CallgetObjectMaxMagic(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectMaxMagic());
		return 1;  
	}
	//获取血量百分比
	static int CallgetObjectBloodPercent(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectBloodPercent());
		return 1;  
	}
	//获取魔法百分比
	static int CallgetObjectMagicPercent(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectMagicPercent());
		return 1;  
	}
	//获取面向
	static int CallgetObjectDirection(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectDirection());
		return 1;  
	}
	//获取人物战斗状态面向
	static int CallgetRoleBettle(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getRoleBettle());
		return 1;  
	}
	//获取人物选中对象ID
	static int CallgetSelectObjectID(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getSelectObjectID());
		return 1;  
	}
	//获取人物金币
	static int CallgetRoleGold(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getRoleGold());
		return 1;  
	}
	//获取人物修为
	static int CallgetRoleXiuWei(lua_State* L)  
	{ 
		CCUserInfo** pT = (CCUserInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getRoleXiuWei());
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCUserInfo::CreateClass); 
		lua_setglobal(L,"CCUserInfo");
		luaL_newmetatable(L,"CCUserInfo"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCUserInfo::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getBaseAddr");  
		lua_pushcfunction(L,CallgetBaseAddr);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectID");  
		lua_pushcfunction(L,CallgetObjectID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectPointX");  
		lua_pushcfunction(L,CallgetObjectPointX);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getObjectPointY");  
		lua_pushcfunction(L,CallgetObjectPointY);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectPointZ");  
		lua_pushcfunction(L,CallgetObjectPointZ);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectLevel");  
		lua_pushcfunction(L,CallgetObjectLevel);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectName");  
		lua_pushcfunction(L,CallgetObjectName);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectTitle");  
		lua_pushcfunction(L,CallgetObjectTitle);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectCurrentBlood");  
		lua_pushcfunction(L,CallgetObjectCurrentBlood);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectMaxBlood");  
		lua_pushcfunction(L,CallgetObjectMaxBlood);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectCurrentMagic");  
		lua_pushcfunction(L,CallgetObjectCurrentMagic);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectMaxMagic");  
		lua_pushcfunction(L,CallgetObjectMaxMagic);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectBloodPercent");  
		lua_pushcfunction(L,CallgetObjectBloodPercent);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectMagicPercent");  
		lua_pushcfunction(L,CallgetObjectMagicPercent);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectDirection");  
		lua_pushcfunction(L,CallgetObjectDirection);  
		lua_settable(L,-3);

		lua_pushstring(L,"getRoleBettle");  
		lua_pushcfunction(L,CallgetRoleBettle);  
		lua_settable(L,-3);

		lua_pushstring(L,"getSelectObjectID");  
		lua_pushcfunction(L,CallgetSelectObjectID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getRoleGold");  
		lua_pushcfunction(L,CallgetRoleGold);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectMap");  
		lua_pushcfunction(L,CallgetObjectMap);  
		lua_settable(L,-3);

		lua_pushstring(L,"getRoleXiuWei");  
		lua_pushcfunction(L,CallgetRoleXiuWei);  
		lua_settable(L,-3);

		lua_pop(L,1);
	}
};

