#pragma once

#define  SHOP_GOOD_FLAG_OFFSET 0x8 //下标偏移
#define  SHOP_GOOD_OBJECT_OFFSET 0x8 //对象偏移
#define  SHOP_GOOD_NAME_OFFSET 0x44//名称偏移
#define  SHOP_GOOD_ID_OFFSET 0x4 //ID偏移

class CCShopGoodObject
{
private:
	int BASE_ADDR;
	int BASE_ADDR_VALUE;
	int SHOP_FLAG;
	int SHOP_GOOD_START_ADDR;
	int SHOP_GOOD_OBJECT;
	string SHOP_GOOD_NAME;
	int SHOP_GOOD_ID;
public:
	CCShopGoodObject(void);
	CCShopGoodObject(int addr);
	~CCShopGoodObject(void);
	//获取物品购物下标
	int getShopFlag()
	{
		return SHOP_FLAG;
	}
	//获取商店物品的名称
	const char * getShopGoodName()
	{
		return SHOP_GOOD_NAME.c_str();
	}
	//获取商店物品ID
	int getShopGoodID()
	{
		return SHOP_GOOD_ID;
	}

};

//lua 封装类
class RgisterCCShopGoodObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数 
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCShopGoodObject**)lua_newuserdata(L,sizeof(CCShopGoodObject*)) = new CCShopGoodObject(nValue);
		luaL_getmetatable(L, "CCShopGoodObject"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCShopGoodObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取商店物品ID
	static int CallGetShopGoodID(lua_State* L)  
	{ 
		//正确的做法
		CCShopGoodObject** pT = (CCShopGoodObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getShopGoodID()); 
		return 1;
	}
	//获取商店物品名称
	static int CallGetShopGoodName(lua_State* L)  
	{ 
		CCShopGoodObject** pT = (CCShopGoodObject**)lua_topointer(L,1);
		lua_pushstring(L,(*pT)->getShopGoodName());
		return 1;  
	}
	//获取商店物品购物ID
	static int CallGetShopFlag(lua_State* L)  
	{ 
		//正确的做法
		CCShopGoodObject** pT = (CCShopGoodObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getShopFlag()); 
		return 1;
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCShopGoodObject::CreateClass); 
		lua_setglobal(L,"CCShopGoodObject");
		luaL_newmetatable(L,"CCShopGoodObject");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCShopGoodObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getShopGoodID");  
		lua_pushcfunction(L,CallGetShopGoodID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getShopFlag");  
		lua_pushcfunction(L,CallGetShopFlag);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getShopGoodName");  
		lua_pushcfunction(L,CallGetShopGoodName);  
		lua_settable(L,-3); 

		lua_pop(L,1);
	}
};
