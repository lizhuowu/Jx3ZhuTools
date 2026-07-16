#pragma once
#include "CMonsterInformation.h"

//怪物对象信息
enum MONSTER_TREE_OFFSET
{
	MONSTER_TREEF_SECOND_OFFSET = 0x1C//二叉树第二个偏移
};
class CCMonsterTree
{
private:
	int BASE_ADDR;//基址
	int BASE_VALUE;//根地址值
	int BASE_FIRST_OFFSET_VALUE;//第一个偏移值
	int BASE_SECOND_OFFSET_VALUE;//第二个偏移值
	int START_ADDR;
	int CountMonster;//数量
	vector<CCMonsterInformation> vecMonsterInfo;//怪物集合
	vector<int> vecMonsterTreeBASE;//怪物地址集合
public:
	CCMonsterTree(void);
	//暴露给LUA使用
	CCMonsterTree(int type);
	~CCMonsterTree(void);
	int Size();//获取列表数量
	//获取列表数量
	int LuaSize();
	void InitVect();
	//LUA使用
	void LuaInitVect();
	//根据索引获取对象
	CCMonsterInformation GetMonsterInformation(int _index);
	//LUA根据索引获取对象
	int LuaGetMonsterInformation(int _index);
private:
	void MonsterTree(int StartTreeAddr);
	//LUA遍历二叉树函数
	void LuaMonsterTree(int StartTreeAddr);
};
//lua 封装类
class RgisterMonsterTree
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{
		int nValue = (int)lua_tointeger(L,1); 
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCMonsterTree**)lua_newuserdata(L,sizeof(CCMonsterTree*)) = new CCMonsterTree(nValue);
		luaL_getmetatable(L, "CCMonsterTree"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCMonsterTree**)lua_topointer(L,1);  
		return 0;  
	}
	//获取怪物数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCMonsterTree** pT = (CCMonsterTree**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->LuaSize()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCMonsterTree** pT = (CCMonsterTree**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->LuaGetMonsterInformation((int)lua_tonumber(L,2)));
		return 1;  
	}
	
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterMonsterTree::CreateClass); 
		lua_setglobal(L,"CCMonsterTree");
		luaL_newmetatable(L,"CCMonsterTree");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterMonsterTree::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"LuaSize");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"LuaGetMonsterInformation");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  

		
		lua_pop(L,1);
	}
};
