#pragma once
#include <math.h>
//怪物对象信息
enum MONSTER_OFFSET
{
	MONSTER_ID_OFFSET = 0x10,//怪物ID偏移
	MONSTER_OBJECT_OFFSET = 0x14,//怪物对象地址偏移
	MONSTER_POINT_X_OFFSET = 0x8,//怪物X坐标偏移
	MONSTER_POINT_Y_OFFSET = 0xC,//怪物Y坐标偏移
	MONSTER_POINT_Z_OFFSET = 0x10,//怪物Z坐标偏移
	MONSTER_NAME_OFFSET = 0x58,//怪物名称偏移
	MONSTER_TITLE_OFFSET = 0x78,//怪物称号偏移
	MONSTER_TREE_FLAG_OFFSET = 0xD//二叉标识偏移
};

class CCMonsterInformation
{
private:
	int TREE_ADDR;//树地址
	int MONSTER_ID;//怪物ID
	int MONSTER_OBJECT_ADDR;//怪物对象地址
	int MONSTER_POINT_X;//怪物X坐标
	int MONSTER_POINT_Y;//怪物Y坐标
	int MONSTER_POINT_Z;//怪物Z坐标
	string MONSTER_NAME;//怪物名称
	string MONSTER_TITLE;//怪物称号
	int MONSTER_CURRENT_BLOOD;//怪物当前血
	int MONSTER_MAX_BLOOD;//怪物最大血
	int MONSTER_CURRENT_MAGIC;//怪物当前魔法
	int MONSTER_MAX_MAGIC;//怪物最大魔法
	int TREE_FLAG;//怪物二叉标识
public:
	CCMonsterInformation(void);
	CCMonsterInformation(int addr);
	~CCMonsterInformation(void);
	//内联
	//获取Tree地址
	int getTreeAddr()
	{
		return TREE_ADDR;
	}
	//获取Object地址
	int getObjectAddr()
	{
		return MONSTER_OBJECT_ADDR;
	}
	//获取Tree地址
	int getTreeFlag()
	{
		TREE_FLAG = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				TREE_FLAG = *(BYTE *)(TREE_ADDR + MONSTER_TREE_FLAG_OFFSET);
			}
		__CATCH("获取二叉树标识出错!")
		return TREE_FLAG;
	}
	//获取怪物ID
	int getMonsterID()
	{
		MONSTER_ID = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				MONSTER_ID = *(WORD *)(TREE_ADDR + MONSTER_ID_OFFSET);
			}
		__CATCH("获取怪物对象ID出错!")
		return MONSTER_ID;
	}
	//获取怪物全写ID
	int getMonsterALLID()
	{
		MONSTER_ID = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				MONSTER_ID = *(int *)(TREE_ADDR + MONSTER_ID_OFFSET);
			}
			__CATCH("获取怪物对象All_ID出错!")
				return MONSTER_ID;
	}
	//获取怪物坐标X
	int getMonsterX()
	{
		MONSTER_POINT_X = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_POINT_X = *(int *)(MONSTER_OBJECT_ADDR + MONSTER_POINT_X_OFFSET);
			}
		__CATCH("获取怪物坐标X出错!")
		return MONSTER_POINT_X;
	}
	//获取怪物坐标Y
	int getMonsterY()
	{
		MONSTER_POINT_Y = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_POINT_Y = *(int *)(MONSTER_OBJECT_ADDR + MONSTER_POINT_Y_OFFSET);
			}
		__CATCH("获取怪物坐标Y出错!")
		return MONSTER_POINT_Y;
	}
	//获取怪物坐标Z
	int getMonsterZ()
	{
		MONSTER_POINT_Z = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_POINT_Z = *(int *)(MONSTER_OBJECT_ADDR + MONSTER_POINT_Z_OFFSET);
			}
		__CATCH("获取怪物坐标Z出错!")
		return MONSTER_POINT_Z;
	}
	//获取怪物距离
	int getMonsterDsc()
	{
		int DESC = 9999;
		__TRY
		CCUserInfo _CCUserInfo;
		int MonsterPX = getMonsterX();
		int MonsterPY = getMonsterY();
		int RoleX = _CCUserInfo.getObjectPointX();
		int RoleY = _CCUserInfo.getObjectPointY();
		DESC = (int)sqrt((MonsterPX - RoleX)*(MonsterPX-RoleX)+ (MonsterPY - RoleY)*(MonsterPY-RoleY));
		__CATCH("获取怪物距离出错!")
		return DESC;
	}
	//获取怪物名称
	const char * getMonsterName()
	{
		MONSTER_NAME = "";
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				char MonsterName[255] = {0};
				strcpy_s(MonsterName,(char *)(MONSTER_OBJECT_ADDR + MONSTER_NAME_OFFSET));
				char * U2GStr =  U2G(MonsterName);
				memset(MonsterName,0,255);
				strcpy_s(MonsterName,U2GStr);
				if(U2GStr) delete[] U2GStr;
				MONSTER_NAME = MonsterName;
			}
		__CATCH("获取怪物名称出错!")
		return MONSTER_NAME.c_str();
	}
	//获取怪物称号
	const char * getMonsterTitle()
	{
		MONSTER_TITLE = "";
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				char MonsterTitle[255] = {0};
				strcpy_s(MonsterTitle,(char *)(MONSTER_OBJECT_ADDR + MONSTER_TITLE_OFFSET));
				char * U2GStr =  U2G(MonsterTitle);
				memset(MonsterTitle,0,255);
				strcpy_s(MonsterTitle,U2GStr);
				if(U2GStr) delete[] U2GStr;
				MONSTER_TITLE = MonsterTitle;
			}
		__CATCH("获取怪物称号出错!")
		return MONSTER_TITLE.c_str();
	}
	//获取怪物当前血
	int getMonsterCurrentBlood()
	{
		MONSTER_CURRENT_BLOOD = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_CURRENT_BLOOD = *(int *)(MONSTER_OBJECT_ADDR + ROLE_CURRENT_BLOOD_OFFSET);
			}
		__CATCH("获取怪物当前血出错!")
		return MONSTER_CURRENT_BLOOD;
	}
	//获取怪物最大血
	int getMonsterMaxBlood()
	{
		MONSTER_MAX_BLOOD = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_MAX_BLOOD = *(int *)(MONSTER_OBJECT_ADDR + ROLE_CURRENT_BLOOD_OFFSET + 4);
			}
		__CATCH("获取怪物最大血出错!")
		return MONSTER_MAX_BLOOD;
	}
	//获取怪物当前魔法
	int getMonsterCurrentMagic()
	{
		MONSTER_CURRENT_MAGIC = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_CURRENT_MAGIC = *(int *)(MONSTER_OBJECT_ADDR + ROLE_CURRENT_MAGIC_OFFSET);
			}
		__CATCH("获取怪物当前魔法出错!")
		return MONSTER_CURRENT_MAGIC;
	}
	//获取怪物最大魔法
	int getMonsterMaxMagic()
	{
		MONSTER_MAX_MAGIC = 0;
		__TRY
			if(MONSTER_OBJECT_ADDR && IsReadAddrInt((PVOID)MONSTER_OBJECT_ADDR))
			{
				MONSTER_MAX_MAGIC = *(int *)(MONSTER_OBJECT_ADDR + ROLE_CURRENT_MAGIC_OFFSET + 4);
			}
		__CATCH("获取怪物最大魔法出错!")
		return MONSTER_MAX_MAGIC;
	}
};

//lua 封装类
class RgisterMonsterInformation
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCMonsterInformation**)lua_newuserdata(L,sizeof(CCMonsterInformation*)) = new CCMonsterInformation(nValue);
		luaL_getmetatable(L, "CCMonsterInformation"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCMonsterInformation**)lua_topointer(L,1);  
		return 0;  
	}
	//获取怪物对象地址
	static int CallGetMonsterObjectAddr(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectAddr());
		return 1;  
	}
	//获取怪物对象ID
	static int CallGetMonsterID(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getMonsterID());
		return 1;  
	}
	//获取怪物对象ALL_ID
	static int CallGetMonsterAllID(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getMonsterALLID());
		return 1;  
	}
	//获取怪物X坐标
	static int CallGetMonsterX(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterX());
		return 1;  
	}
	//获取怪物Y坐标
	static int CallGetMonsterY(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterY());
		return 1;  
	}
	//获取怪物Z坐标
	static int CallGetMonsterZ(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterZ());
		return 1;  
	}
	//获取怪物距离
	static int CallGetMonsterDESC(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getMonsterDsc());
		return 1;  
	}
	//获取怪物名称
	static int CallGetMonsterName(lua_State* L)  
	{  
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getMonsterName());  
		return 1;
	}
	//获取怪物称号
	static int CallGetMonsterTitle(lua_State* L)  
	{  
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushstring(L, (*pT)->getMonsterTitle());
		return 1;  
	}
	//获取怪物当前血值
	static int CallGetMonsterCurrentBlood(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterCurrentBlood());
		return 1;  
	}
	//获取怪物最大血值
	static int CallGetMonsterMaxBlood(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterMaxBlood());
		return 1;  
	}
	//获取怪物当前魔法
	static int CallGetMonsterCurrentMagic(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterCurrentMagic());
		return 1;  
	}
	//获取怪物最大魔法
	static int CallGetMonsterMaxMagic(lua_State* L)  
	{ 
		CCMonsterInformation** pT = (CCMonsterInformation**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getMonsterMaxMagic());
		return 1;  
	}
	
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterMonsterInformation::CreateClass); 
		lua_setglobal(L,"CCMonsterInformation");
		luaL_newmetatable(L,"CCMonsterInformation"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterMonsterInformation::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  
		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了

		lua_pushstring(L,"getObjectAddr");  
		lua_pushcfunction(L,CallGetMonsterObjectAddr);  
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterID");  
		lua_pushcfunction(L,CallGetMonsterID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterALLID");  
		lua_pushcfunction(L,CallGetMonsterAllID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterX");  
		lua_pushcfunction(L,CallGetMonsterX);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getMonsterY");  
		lua_pushcfunction(L,CallGetMonsterY);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getMonsterZ");  
		lua_pushcfunction(L,CallGetMonsterZ);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterDsc");  
		lua_pushcfunction(L,CallGetMonsterDESC);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterName");  
		lua_pushcfunction(L,CallGetMonsterName);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterTitle");  
		lua_pushcfunction(L,CallGetMonsterTitle);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterCurrentBlood");  
		lua_pushcfunction(L,CallGetMonsterCurrentBlood);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterMaxBlood");  
		lua_pushcfunction(L,CallGetMonsterMaxBlood);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterCurrentMagic");  
		lua_pushcfunction(L,CallGetMonsterCurrentMagic);
		lua_settable(L,-3);

		lua_pushstring(L,"getMonsterMaxMagic");  
		lua_pushcfunction(L,CallGetMonsterMaxMagic);
		lua_settable(L,-3);
		lua_pop(L,1);
	}
};

