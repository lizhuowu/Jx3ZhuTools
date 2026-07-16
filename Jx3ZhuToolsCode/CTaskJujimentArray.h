#pragma once



class CCTaskJujimentArray
{
private:
	int BASE_VALUE;//基址值
	int BASE_OFFSET_1_VALUE;//第一偏移值
	int BASE_OFFSET_2_VALUE;//第二偏移值
	vector<int> vecJujmentObjects;
public:
	CCTaskJujimentArray(void);
	~CCTaskJujimentArray(void);
	//获取任务条件判断数量
	int getVectCount()
	{
		return vecJujmentObjects.size();
	}
	//获取单个值
	int getAddrByIndex(int _index)
	{
		return vecJujmentObjects.at(_index);
	}
};
//lua 封装类
class RgisterCCTaskJujimentArray
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCTaskJujimentArray**)lua_newuserdata(L,sizeof(CCTaskJujimentArray*)) = new CCTaskJujimentArray();
		luaL_getmetatable(L, "CCTaskJujimentArray"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCTaskJujimentArray**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCTaskJujimentArray** pT = (CCTaskJujimentArray**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getVectCount()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCTaskJujimentArray** pT = (CCTaskJujimentArray**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getAddrByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCTaskJujimentArray::CreateClass); 
		lua_setglobal(L,"CCTaskJujimentArray");
		luaL_newmetatable(L,"CCTaskJujimentArray");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCTaskJujimentArray::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getVectCount");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"getAddrByIndex");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};
