#pragma once
#include "CPlayerInfomation.h"

//玩家对象信息
enum PLAYER_TREE_OFFSET
{
	PLAYER_TREEF_SECOND_OFFSET = 0x10//二叉树第二个偏移
};

class CCPlayerTree
{
private:
	int BASE_ADDR;//基址
	int BASE_VALUE;//根地址值
	int BASE_FIRST_OFFSET_VALUE;//第一个偏移值
	int BASE_SECOND_OFFSET_VALUE;//第二个偏移值
	int START_ADDR;
	int CountPlayer;//数量
	vector<CCPlayerInfomation> vecPlayerInfo;//玩家集合
	vector<int> vecPlayerTreeBASE;//玩家地址集合
public:
	CCPlayerTree(void);
	~CCPlayerTree(void);
	//暴露给LUA使用
	CCPlayerTree(int type);
	int Size();//获取列表数量
	//获取列表数量
	int LuaSize();
	void InitVect();
	//LUA使用
	void LuaInitVect();
	CCPlayerInfomation GetPlayerInformation(int _index);
	int LuaGetPlayerInformation(int _index);
private:
	void MonsterTree(int StartTreeAddr);
	//LUA遍历二叉树函数
	void LuaMonsterTree(int StartTreeAddr);
};

//lua 封装类
class RgisterCCPlayerTree
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{
		int nValue = (int)lua_tointeger(L,1); 
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCPlayerTree**)lua_newuserdata(L,sizeof(CCPlayerTree*)) = new CCPlayerTree(nValue);
		luaL_getmetatable(L, "CCPlayerTree"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCPlayerTree**)lua_topointer(L,1);  
		return 0;  
	}
	//获取怪物数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCPlayerTree** pT = (CCPlayerTree**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->LuaSize()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCPlayerTree** pT = (CCPlayerTree**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->LuaGetPlayerInformation((int)lua_tonumber(L,2)));
		return 1;  
	}

	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCPlayerTree::CreateClass); 
		lua_setglobal(L,"CCPlayerTree");
		luaL_newmetatable(L,"CCPlayerTree");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCPlayerTree::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"LuaSize");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"LuaGetPlayerInformation");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};


