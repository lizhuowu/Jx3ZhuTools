#pragma once

enum GOOD_TYPE_ENUM
{
	WEAPON = 6 ,//武器
	EQUIPMENT = 7,//装备
	OTHER_GOOD = 5//其他类别
};

enum PACK_GOOD_OFFSET
{
	ID_OFFSET_PACK = 0x10,//ID偏移 
	SELL_HANDLE_OFFSET = 0x4,//卖物句柄偏移 
	SUB_OBJECT_OFFSET_PACK = 0x8,//子类偏移
	TYPE_OFFSET_PACK = 0xC,//物品类型偏移
	GOOD_COUNT_OFFSET_PACK = 0x48,//物品数量偏移
	GOOD_NAME_OFFSET_PACK = 0x44,//物品名称偏移
	GOOD_PRICE_OFFSET_PACK = 0x18,//物品总价
	GOOD_MAKE_OFFSET_PACK = 0xC//物品使用时类别偏移
};

class CCPackObject
{
private:
	int BASE_ADDR;
	int GOOD_ID;//物品ID
	int GOOD_COUNT;//物品数量
	int SUB_OBJECT;//子类
	string GOOD_NAME;//物品名称
	int ALL_PRICE;//总价
	int GOOD_TYPE;//类别
	int GOOD_MAKE_TYPE;//物品使用类别
	int SELL_HADNLE;//卖物句柄
public:
	CCPackObject(void);
	CCPackObject(int BaseAddr);
	~CCPackObject(void);
	//获取物品ID
	int getGoodID()
	{
		return GOOD_ID;
	}
	//获取物品数量
	int getGoodCount()
	{
		return GOOD_COUNT;
	}
	//获取物品名称
	const char * getGoodName()
	{
		return GOOD_NAME.c_str();
	}
	//获取装备或者使用物品的类型
	int getMakeGoodType()
	{
		return GOOD_MAKE_TYPE;
	}
	//获取物品的总价
	int getGoodAllPrice()
	{
		return ALL_PRICE;
	}
	//获取卖物句柄
	int getSellHandle()
	{
		return SELL_HADNLE;
	}
};

//lua 封装类
class RgisterCCPackObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCPackObject**)lua_newuserdata(L,sizeof(CCPackObject*)) = new CCPackObject(nValue);
		luaL_getmetatable(L, "CCPackObject"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCPackObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取物品ID
	static int CallGetGoodID(lua_State* L)  
	{ 
		//正确的做法
		CCPackObject** pT = (CCPackObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getGoodID()); 
		return 1;
	}
	//获取物品数量
	static int CallGetGoodCount(lua_State* L)  
	{ 
		CCPackObject** pT = (CCPackObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getGoodCount());
		return 1;  
	}

	//获取物品名称
	static int CallGetGoodName(lua_State* L)  
	{  
		CCPackObject** pT = (CCPackObject**)lua_topointer(L,1);  
		lua_pushstring(L, (*pT)->getGoodName());
		return 1;  
	}
	//获取装备或者使用物品的类型
	static int CallGetMakeGoodType(lua_State* L)  
	{ 
		CCPackObject** pT = (CCPackObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getMakeGoodType());
		return 1;  
	}
	//获取物品的总价格
	static int CallGetGoodAllPrice(lua_State* L)  
	{ 
		CCPackObject** pT = (CCPackObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getGoodAllPrice());
		return 1;  
	}
	//获取卖物句柄
	static int CallGetSellHanle(lua_State* L)  
	{ 
		CCPackObject** pT = (CCPackObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getSellHandle());
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCPackObject::CreateClass); 
		lua_setglobal(L,"CCPackObject");
		luaL_newmetatable(L,"CCPackObject");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCPackObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getGoodID");  
		lua_pushcfunction(L,CallGetGoodID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getGoodCount");  
		lua_pushcfunction(L,CallGetGoodCount);  
		lua_settable(L,-3); 

		lua_pushstring(L,"getGoodName");  
		lua_pushcfunction(L,CallGetGoodName);  
		lua_settable(L,-3); 

		lua_pushstring(L,"getMakeGoodType");  
		lua_pushcfunction(L,CallGetMakeGoodType);  
		lua_settable(L,-3); 

		lua_pushstring(L,"getGoodAllPrice");  
		lua_pushcfunction(L,CallGetGoodAllPrice);  
		lua_settable(L,-3); 

		lua_pushstring(L,"getSellHandle");  
		lua_pushcfunction(L,CallGetSellHanle);  
		lua_settable(L,-3); 

		lua_pop(L,1);
	}
};