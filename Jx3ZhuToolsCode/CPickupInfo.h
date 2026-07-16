#pragma once

enum PICKUP_OFFSET
{
	PICKUP_ID_OFFSET = 4,//捡取ID偏移
	PICKUP_OBJECT_OFFSET = 8,//捡取对象偏移
	PICKUP_GOOD_ID_OFFSET = 4,//包裹物品ID偏移
	PICKUP_NAME_OFFSET = 0x44//包裹物品名称偏移
};

class CCPickupInfo
{
private:
	int BASE_PICKUP;//包裹地址
	int BASE_PICKUP_OBJECT;//包裹物品对象
	int PICKUP_ID;//拾取用ID
	int PICKUP_GOOD_ID;//包裹物品ID
	string PICKUP_NAME;//包裹物品名称
public:
	CCPickupInfo(void);
	CCPickupInfo(int BASE_ADDR);
	~CCPickupInfo(void);
	//获取包裹跟地址
	int getPickAddr()
	{
		return BASE_PICKUP;
	}
	//获取包裹对象地址
	int getPickObjectAddr()
	{
		return BASE_PICKUP_OBJECT;
	}
	//获取拾取包裹ID
	int getPicketID()
	{
		return PICKUP_ID;
	}
	//获取拾取包裹物品ID
	int getPicketGoodID()
	{
		return PICKUP_GOOD_ID;
	}
	//获取包裹物品名称
	const char * getPickupGoodName()
	{
		return PICKUP_NAME.c_str();
	}
};

//lua 封装类
class RgisterCCPickupInfo
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCPickupInfo**)lua_newuserdata(L,sizeof(CCPickupInfo*)) = new CCPickupInfo(nValue);
		luaL_getmetatable(L, "CCPickupInfo"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCPickupInfo**)lua_topointer(L,1);  
		return 0;  
	}
	//获取拾取包裹ID
	static int CallgetPicketID(lua_State* L)  
	{ 
		CCPickupInfo** pT = (CCPickupInfo**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getPicketID());
		return 1;  
	}
	//获取拾取包裹物品ID
	static int CallgetPicketGoodID(lua_State* L)  
	{ 
		CCPickupInfo** pT = (CCPickupInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getPicketGoodID());
		return 1;  
	}
	//获取包裹物品名称
	static int CallgetPickupGoodName(lua_State* L)  
	{  
		CCPickupInfo** pT = (CCPickupInfo**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getPickupGoodName());  
		return 1;
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCPickupInfo::CreateClass); 
		lua_setglobal(L,"CCPickupInfo");
		luaL_newmetatable(L,"CCPickupInfo"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCPickupInfo::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getPicketID");  
		lua_pushcfunction(L,CallgetPicketID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getPicketGoodID");  
		lua_pushcfunction(L,CallgetPicketGoodID);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getPickupGoodName");  
		lua_pushcfunction(L,CallgetPickupGoodName);  
		lua_settable(L,-3);

		lua_pop(L,1);
	}
};
