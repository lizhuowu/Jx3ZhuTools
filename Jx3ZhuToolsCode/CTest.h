#pragma once


class CCTest
{

public:
	CCTest(void);
	~CCTest(void);
	char * CCTest::getStr(char * content);
	int CCTest::retInt(int X,int Y);
};
 class RegisterCCTest{
 public:
	//导出一个函数到Lua,用于创建C++类  
	static int CreateCCTest(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);  

		//创建一个CTest对象并把它的指针通过用户数据方式传递给lua  
		//这是对userdata的说明:  
		//A full userdata represents a block of memory.   
		//It is an object (like a table): you must create it, it can have its own metatable  
		*(CCTest**)lua_newuserdata(L,sizeof(CCTest*)) = new CCTest();  
		//从注册表中找到CTest元表并压入栈顶  
		luaL_getmetatable(L, "CCTest");  
		//将CTest元表作为用户数据的元表(由于对函数还不熟悉,开始理解成把userdata赋给CTest呢，哈哈)  
		lua_setmetatable(L,-2);  
		//该函数调用后栈里就是一个userdata了。  
		return 1;  
	}
	static int DestoryCCTest(lua_State* L)  
	{  
		//释放对象  
		delete *(CCTest**)lua_topointer(L,1);  
		return 0;  
	}
	static int CallgetStr(lua_State* L)  
	{  
		//调用C++类方法的跳板函数,此处其实有个陷阱  
		//lua_topointer返回的其实是CTest**，由于此处不涉及到  
		//类的数据成员操作,无所谓我就没有改了  
		CCTest* pT = (CCTest*)lua_topointer(L,1);  
		lua_pushstring(L, pT->getStr((char *)lua_tostring(L,2)));  
		return 1;  
	}
	static int CallInt(lua_State* L)  
	{  
		//这样才能给找到真正的对象  
		CCTest** pT = (CCTest**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->retInt((int)lua_tonumber(L,2),(int)lua_tonumber(L,3)));
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RegisterCCTest::CreateCCTest); 
		lua_setglobal(L,"CCTest");
		luaL_newmetatable(L,"CCTest"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RegisterCCTest::DestoryCCTest);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getStr");  
		lua_pushcfunction(L,CallgetStr);  
		lua_settable(L,-3);  

		lua_pushstring(L,"retInt");  
		lua_pushcfunction(L,CallInt);  
		lua_settable(L,-3);  
		//lua_pop(L,1);
	}
 };
