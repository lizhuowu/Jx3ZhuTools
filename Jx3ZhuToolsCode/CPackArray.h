#pragma once
class CCPackArray
{
private:
	int BASE_ADDR;//根地址
	int PACKET_COUNT;//背包格子数量
	vector<int> PACK_VECT_ARRAY; 
public:
	CCPackArray(void);
	CCPackArray(int BaseAddr);
	~CCPackArray(void);
	//获取数量
	int getCount()
	{
		return PACK_VECT_ARRAY.size();
	}
	//获取单个值
	int getAddrByIndex(int _index)
	{
		return PACK_VECT_ARRAY.at(_index);
	} 
};


//lua 封装类
class RgisterCCPackArray
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCPackArray**)lua_newuserdata(L,sizeof(CCPackArray*)) = new CCPackArray(nValue);
		luaL_getmetatable(L, "CCPackArray"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCPackArray**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetCount(lua_State* L)  
	{ 
		//正确的做法
		CCPackArray** pT = (CCPackArray**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getCount()); 
		return 1;
	}
	//获取单个对象
	static int CallGetAddrByIndext(lua_State* L)  
	{ 
		CCPackArray** pT = (CCPackArray**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getAddrByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCPackArray::CreateClass); 
		lua_setglobal(L,"CCPackArray");
		luaL_newmetatable(L,"CCPackArray");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCPackArray::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getCount");  
		lua_pushcfunction(L,CallGetCount);  
		lua_settable(L,-3);

		lua_pushstring(L,"getAddrByIndex");  
		lua_pushcfunction(L,CallGetAddrByIndext);  
		lua_settable(L,-3); 

		lua_pop(L,1);
	}
};