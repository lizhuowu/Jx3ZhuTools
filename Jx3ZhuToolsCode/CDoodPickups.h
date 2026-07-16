#pragma once

enum DOOR_PICKUP_OFFSET
{
	DOOR_PICKUP_ADDR_OFFSET = 0xB4,//捡取对象地址
	DOOR_PICKUP_LIST_OFFSET = 0x150//捡取链表
};
class CCDoodPickups
{
private:
	int BASE_ADDR;
	int BASE_PICK_ADDR;
	int BASE_LIST;
	int COUNT;
	vector<int> PICKET_ADDRS;
public:
	CCDoodPickups(void);
	CCDoodPickups(int addr);
	~CCDoodPickups(void);
	//获取数量
	int getCount()
	{
		return COUNT;
	}
	//根据索引获取地址
	int getAddrByIndex(int _index)
	{
		if(PICKET_ADDRS.size() > 0 && COUNT > 0)
		{
			return PICKET_ADDRS.at(_index);
		} 
		return 0;
	}
};

//lua 封装类
class RgisterCCDoodPickups
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCDoodPickups**)lua_newuserdata(L,sizeof(CCDoodPickups*)) = new CCDoodPickups(nValue);
		luaL_getmetatable(L, "CCDoodPickups"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCDoodPickups**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCDoodPickups** pT = (CCDoodPickups**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getCount()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCDoodPickups** pT = (CCDoodPickups**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getAddrByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCDoodPickups::CreateClass); 
		lua_setglobal(L,"CCDoodPickups");
		luaL_newmetatable(L,"CCDoodPickups");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCDoodPickups::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getCount");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"getAddrByIndex");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};

