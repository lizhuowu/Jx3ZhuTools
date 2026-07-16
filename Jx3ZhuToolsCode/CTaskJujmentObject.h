#pragma once

enum TASK_JUJMENT_OFFSET
{
	TASK_OBJECT_OFFSET = 0x8,//任务属性偏移
	TASK_MONSTER_COUNT_START_OFFSET = 0xC,//任务打怪数量开始偏移，每个条件+4
	TASK_MAX_MONSTER_COUNT_START_OFFSET = 0x1F0,//任务需打怪数量开始偏移，每个条件+2
	TASK_MAX_STEP_COUNT_START_OFFSET = 0x1C,//任务步骤开始偏移,暂时是每个条件+4
	TASK_MAX_ACQUIST_COUNT_START_OFFSET = 0x7E,//任务需采集数量开始偏移,暂时是每个条件+2
	TASK_STEP_COUNT_START_OFFSET = 0x1F8//任步骤任务获取打怪数量,每次加4
};

class CCTaskJujmentObject
{

private:
	int BASE_OBJECT;//根地址
	int TASK_OBJECT;//任务对象地址
	int TASK_ID;//任务ID
public:
	CCTaskJujmentObject(void);
	CCTaskJujmentObject(int Base_Start_Addr);
	~CCTaskJujmentObject(void);
	//获取任务ID
	int getTaskID();
	//根据索引获取已打怪数量
	int getTaskCurrentMonstByIndex(int _index);
	//根据索引获取最大打怪数量
	int getTaskMaxMonstByIndex(int _index);
	//根据索引获取步骤完成情况
	int getTaskStepByIndex(int _index);
	//根据索引获取步骤打怪最大数量
	//参数1.步骤索引
	int getTaskStepMaxByIndex(int _index);
	//根据索引获取采集最大数量
	int getTaskAcquistMaxCountByIndex(int _index);
};

//lua 封装类
class RgisterCCTaskJujmentObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数 
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCTaskJujmentObject**)lua_newuserdata(L,sizeof(CCTaskJujmentObject*)) = new CCTaskJujmentObject(nValue);
		luaL_getmetatable(L, "CCTaskJujmentObject"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCTaskJujmentObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetTaskID(lua_State* L)  
	{ 
		//正确的做法
		CCTaskJujmentObject** pT = (CCTaskJujmentObject**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getTaskID()); 
		return 1;
	}
	//根据索引获取已打怪数量
	static int CallGetTaskCurrentMonstByIndex(lua_State* L)  
	{ 
		CCTaskJujmentObject** pT = (CCTaskJujmentObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getTaskCurrentMonstByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	//根据索引获取最大打怪数量
	static int CallGetTaskMaxMonstByIndex(lua_State* L)  
	{ 
		CCTaskJujmentObject** pT = (CCTaskJujmentObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getTaskMaxMonstByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	//根据索引获取步骤当前数量
	static int CallGetTaskStepByIndex(lua_State* L)  
	{ 
		CCTaskJujmentObject** pT = (CCTaskJujmentObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getTaskStepByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	//根据索引获取步骤最大数量
	static int CallGetTaskStepMaxByIndex(lua_State* L)  
	{ 
		CCTaskJujmentObject** pT = (CCTaskJujmentObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getTaskStepMaxByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	//根据索引获取采集最大数量
	static int CallGetTaskAcquistMaxCountByIndex(lua_State* L)  
	{ 
		CCTaskJujmentObject** pT = (CCTaskJujmentObject**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getTaskAcquistMaxCountByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCTaskJujmentObject::CreateClass); 
		lua_setglobal(L,"CCTaskJujmentObject");
		luaL_newmetatable(L,"CCTaskJujmentObject");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCTaskJujmentObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getTaskID");  
		lua_pushcfunction(L,CallGetTaskID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getTaskCurrentMonstByIndex");  
		lua_pushcfunction(L,CallGetTaskCurrentMonstByIndex);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getTaskMaxMonstByIndex");  
		lua_pushcfunction(L,CallGetTaskMaxMonstByIndex);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getTaskStepByIndex");  
		lua_pushcfunction(L,CallGetTaskStepByIndex);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getTaskStepMaxByIndex");  
		lua_pushcfunction(L,CallGetTaskStepMaxByIndex);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getTaskAcquistMaxCountByIndex");
		lua_pushcfunction(L,CallGetTaskAcquistMaxCountByIndex);  
		lua_settable(L,-3);  

		lua_pop(L,1);
	}
};
