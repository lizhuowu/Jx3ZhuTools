#pragma once
#include "CGroundInfo.h"

//对象信息
enum GROUND_TREE_OFFSET
{
	GROUND_TREEF_SECOND_OFFSET = 0x28//二叉树第二个偏移
};

class CCGroundTree
{
private:
	int BASE_ADDR;//基址
	int BASE_VALUE;//根地址值
	int BASE_FIRST_OFFSET_VALUE;//第一个偏移值
	int BASE_SECOND_OFFSET_VALUE;//第二个偏移值
	int START_ADDR;
	int CountGround;//数量
	vector<CCGroundInfo> vecGround;//地面集合
	vector<int> vecGroundTreeBASE;//地面地址集合
public:
	CCGroundTree(void);
	~CCGroundTree(void);
	void InitVect();
	//遍历二叉树函数
	void GroundTree(int StartTreeAddr);
	//获取列表数量
	int Size();
	//根据索引获取对象
	CCGroundInfo GetGroundInformation(int _index);
	//////////////////////////////////////////////////////////////////////////
	//暴露给LUA使用
	CCGroundTree(int type);
	//LUA使用
	void LuaInitVect();
	//LUA遍历二叉树函数
	void LuaGroundTree(int StartTreeAddr);

	//LUA获取列表数量
	int LuaSize();
	//LUA根据索引获取对象
	int LuaGetGroundInfo(int _index);
};
//lua 封装类
class RgisterCCGroundTree
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{
		int nValue = (int)lua_tointeger(L,1); 
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCGroundTree**)lua_newuserdata(L,sizeof(CCGroundTree*)) = new CCGroundTree(nValue);
		luaL_getmetatable(L, "CCGroundTree"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCGroundTree**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCGroundTree** pT = (CCGroundTree**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->LuaSize()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCGroundTree** pT = (CCGroundTree**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->LuaGetGroundInfo((int)lua_tonumber(L,2)));
		return 1;  
	}

	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCGroundTree::CreateClass); 
		lua_setglobal(L,"CCGroundTree");
		luaL_newmetatable(L,"CCGroundTree");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCGroundTree::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"LuaSize");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"LuaGetGroundInfo");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};
