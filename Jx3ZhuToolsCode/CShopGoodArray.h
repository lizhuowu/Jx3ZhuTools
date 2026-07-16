#pragma once

#define  PER_OFFSET_SHOP_GOOD_ARRAY 0x0C //每个的偏移大小

class CCShopGoodArray
{
private:
	int BASE_ADDR;
	int COUNT;
	vector<int> vecAllShopArrayAddr;
	int shopArrayID;
public:
	CCShopGoodArray(void);
	CCShopGoodArray(int addr);
	~CCShopGoodArray(void);
	//获取数量
	int getAllShopGoodCount()
	{
		return vecAllShopArrayAddr.size();
	}
	//获取单个值
	int getAddrByIndex(int _index)
	{
		return vecAllShopArrayAddr.at(_index);
	}
	//获取单个值商店ID
	int getShopIDBuy()
	{
		return shopArrayID;
	}
};


//lua 封装类
class RgisterCCShopGoodArray
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数
		int nValue = (int)lua_tointeger(L,1); 
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCShopGoodArray**)lua_newuserdata(L,sizeof(CCShopGoodArray*)) = new CCShopGoodArray(nValue);
		luaL_getmetatable(L, "CCShopGoodArray"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCShopGoodArray**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCShopGoodArray** pT = (CCShopGoodArray**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getAllShopGoodCount()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCShopGoodArray** pT = (CCShopGoodArray**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getAddrByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	//获取单个对象
	static int CallGetObjectShopID(lua_State* L)  
	{ 
		CCShopGoodArray** pT = (CCShopGoodArray**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getShopIDBuy());
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCShopGoodArray::CreateClass); 
		lua_setglobal(L,"CCShopGoodArray");
		luaL_newmetatable(L,"CCShopGoodArray");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCShopGoodArray::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getAllShopGoodCount");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"getAddrByIndex");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getShopIDBuy");  
		lua_pushcfunction(L,CallGetObjectShopID);  
		lua_settable(L,-3);  

		lua_pop(L,1);
	}
};