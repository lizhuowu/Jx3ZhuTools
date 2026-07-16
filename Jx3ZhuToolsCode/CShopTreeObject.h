#pragma once

#define  TREE_ID_SHOP_TREE 0x10 //商店ID偏移

#define  TREE_ADDR_SHOP_TREE 0x14 //商店地址偏移

class CCShopTreeObject
{
private:
	int BASE_ADDR;
	int SHOP_ID;
	int SHOP_ADDR;
public:
	CCShopTreeObject(void);
	CCShopTreeObject(int Addr);
	~CCShopTreeObject(void);
	//获取商店ID
	int getShopID()
	{
		return SHOP_ID;
	}
	//获取商店地址
	int getShopAddr()
	{
		return SHOP_ADDR;
	}
};


//lua 封装类
class RgisterCCShopTreeObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数 
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCShopTreeObject**)lua_newuserdata(L,sizeof(CCShopTreeObject*)) = new CCShopTreeObject(nValue);
		luaL_getmetatable(L, "CCShopTreeObject"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCShopTreeObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取商店ID
	static int CallGetShopID(lua_State* L)  
	{ 
		//正确的做法
		CCShopTreeObject** pT = (CCShopTreeObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getShopID()); 
		return 1;
	}
	//获取商店地址
	static int CallGetShopAddr(lua_State* L)  
	{ 
		CCShopTreeObject** pT = (CCShopTreeObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getShopAddr());
		return 1;  
	}
	
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCShopTreeObject::CreateClass); 
		lua_setglobal(L,"CCShopTreeObject");
		luaL_newmetatable(L,"CCShopTreeObject");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCShopTreeObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getShopID");  
		lua_pushcfunction(L,CallGetShopID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getShopAddr");  
		lua_pushcfunction(L,CallGetShopAddr);  
		lua_settable(L,-3);  

		lua_pop(L,1);
	}
};

