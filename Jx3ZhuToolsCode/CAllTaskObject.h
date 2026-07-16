#pragma once

enum AllTaskObjectOffset
{
	ID_OFFSET = 0x10,//任务ID偏移
	ID_OBJECT_OFFSET = 0x14//任务对象偏移
};

class CCAllTaskObject
{
private:
	int BASE_TREE_ADDR;
	int BASE_OBJECT_ADDR;//用来判断任务是否已接的地址
	int TASK_ID;
public:
	CCAllTaskObject(void);
	~CCAllTaskObject(void);
	CCAllTaskObject(int BASE_START);
	//获取任务ID
	int getTaskID()
	{
		return TASK_ID;
	}
	//获取任务判断的地址
	int getObjectAddr()
	{
		return BASE_OBJECT_ADDR;
	}
};

//lua 封装类
class RgisterCCAllTaskObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCAllTaskObject**)lua_newuserdata(L,sizeof(CCAllTaskObject*)) = new CCAllTaskObject(nValue);
		luaL_getmetatable(L, "CCAllTaskObject"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCAllTaskObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取任务ID
	static int CallGetTaskID(lua_State* L)  
	{ 
		//正确的做法
		CCAllTaskObject** pT = (CCAllTaskObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getTaskID()); 
		return 1;
	}
	//获取判断用的对象地址
	static int CallGetObjectAddr(lua_State* L)  
	{ 
		CCAllTaskObject** pT = (CCAllTaskObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getObjectAddr());
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCAllTaskObject::CreateClass); 
		lua_setglobal(L,"CCAllTaskObject");
		luaL_newmetatable(L,"CCAllTaskObject");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCAllTaskObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getTaskID");  
		lua_pushcfunction(L,CallGetTaskID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getObjectAddr");  
		lua_pushcfunction(L,CallGetObjectAddr);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};
