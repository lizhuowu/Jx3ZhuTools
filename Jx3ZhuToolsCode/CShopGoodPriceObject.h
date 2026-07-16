#pragma once

#define  PRICE_OFFSET  0x18 //单价偏移
#define  PRICE_OBJECT_OFFSET_LEA 0x14//价格对象数组小偏移
#define  PRICE_TREE_ID_SHOP_TREE 0x10 //商店价格ID偏移
class CCShopGoodPriceObject
{
private:
	int BASE_ADDR;
	int PRICE_ADDR;
	int SHOP_ID;
public:
	CCShopGoodPriceObject(void);
	CCShopGoodPriceObject(int addr);
	~CCShopGoodPriceObject(void);
	
	//获取单价
	int getGoodPrice(int GoodIndex)
	{
		__TRY
		if(PRICE_ADDR && IsReadAddrInt((PVOID)PRICE_ADDR))
		{
			int _Index = GoodIndex * GOOD_PRICE_IMUL;
			if((PRICE_ADDR + _Index + PRICE_OFFSET) && IsReadAddrInt((PVOID)(PRICE_ADDR + _Index + PRICE_OFFSET)))
			{
				int ret = *(int*)(PRICE_ADDR + _Index + PRICE_OFFSET);
				return ret;
			}
		}
		__CATCH("获取单价出错")
		return 0;
	}
	//获取购买物品时判断ID
	int getShopIDBuy()
	{
		SHOP_ID = -1;
		__TRY
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			SHOP_ID = *(int *)(BASE_ADDR + PRICE_TREE_ID_SHOP_TREE);
		}
		__CATCH("获取商店单价ID出错")
		return SHOP_ID;
	}
};
//lua 封装类
class RgisterCCShopGoodPriceObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCShopGoodPriceObject**)lua_newuserdata(L,sizeof(CCShopGoodPriceObject*)) = new CCShopGoodPriceObject(nValue);
		luaL_getmetatable(L, "CCShopGoodPriceObject"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCShopGoodPriceObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetPrice(lua_State* L)  
	{ 
		//正确的做法
		CCShopGoodPriceObject** pT = (CCShopGoodPriceObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getGoodPrice((int)lua_tonumber(L,2))); 
		return 1;
	}
	//获取商店价格ID
	static int CallGetShopIDBuy(lua_State* L)  
	{ 
		//正确的做法
		CCShopGoodPriceObject** pT = (CCShopGoodPriceObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getShopIDBuy()); 
		return 1;
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCShopGoodPriceObject::CreateClass); 
		lua_setglobal(L,"CCShopGoodPriceObject");
		luaL_newmetatable(L,"CCShopGoodPriceObject");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCShopGoodPriceObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getGoodPrice");  
		lua_pushcfunction(L,CallGetPrice);  
		lua_settable(L,-3);

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getShopIDBuy");  
		lua_pushcfunction(L,CallGetShopIDBuy);  
		lua_settable(L,-3);

		lua_pop(L,1);
	}
};
