#pragma once
//怪物对象信息
enum SKILL_OFFSET
{
	SKILL_LEVEL_OFFSET = 0x10,//技能等级
	SKILL_ID_OFFSET = 0x14,//技能ID
	SKILL_OBJECT_OFFSET = 0x1C,//技能对象
	SKILL_NAME_TO_OBJECT_OFFSET = 0x4,//相对于技能对象的技能名称偏移
	SKILL_CURRENT_XIUWEI_TO_OBJECT_OFFSET = 0x10//技能当前修为
};
class CCSkillObject
{
private:
	int BASE_START;//技能开始地址
	int SKILL_LEVEL;//技能等级
	int SKILL_ID;//技能ID
	int OBJECT_ADDR;//对象地址
	string SKILL_NAME;//怪物名称
	int CURRENT_XIUWEI;//当前修为
public:
	CCSkillObject(void);
	CCSkillObject(int Addr);
	~CCSkillObject(void);
	//获取Tree地址
	int getTreeAddr()
	{
		return BASE_START;
	}

	//获取对象地址
	int getObjecteAddr()
	{
		return OBJECT_ADDR;
	}

	//获取技能等级
	int getSkillLevel()
	{
		SKILL_LEVEL = 0;
		__TRY
			if (BASE_START && IsReadAddrInt((PVOID)BASE_START) && IsReadAddrInt((PVOID)(BASE_START + SKILL_LEVEL_OFFSET)))
			{
				SKILL_LEVEL = *(int *)(BASE_START + SKILL_LEVEL_OFFSET);
			}
		__CATCH("获取技能等级出错!")
		return SKILL_LEVEL;
	}
	//获取数据ID
	int getSkillID()
	{
		SKILL_ID = 0;
		__TRY
			if (BASE_START && IsReadAddrInt((PVOID)BASE_START) && IsReadAddrInt((PVOID)(BASE_START + SKILL_ID_OFFSET)))
			{
				SKILL_ID = *(int *)(BASE_START + SKILL_ID_OFFSET);
			}
			__CATCH("获取技能ID出错!")
		return SKILL_ID;
	}
	//获取技能名称
	const char * getSkillName()
	{
		SKILL_NAME = "";
		__TRY
			if (OBJECT_ADDR && IsReadAddrInt((PVOID)OBJECT_ADDR) && IsReadAddrInt((PVOID)(OBJECT_ADDR + SKILL_NAME_TO_OBJECT_OFFSET)))
			{
				int TempAddr = *(int *)(OBJECT_ADDR + SKILL_NAME_TO_OBJECT_OFFSET);
				char SkillName[255] = {0};
				strcpy_s(SkillName,(char *)(TempAddr));
				SKILL_NAME = SkillName;
			}
			__CATCH("获取技能名称出错!")
		return SKILL_NAME.c_str();;
	}
	//获取当前修为
	int	getCurrentXiuWei()
	{
		CURRENT_XIUWEI = 0;
		__TRY
			if (OBJECT_ADDR && IsReadAddrInt((PVOID)OBJECT_ADDR) && IsReadAddrInt((PVOID)(OBJECT_ADDR + SKILL_CURRENT_XIUWEI_TO_OBJECT_OFFSET)))
			{
				CURRENT_XIUWEI = *(int *)(OBJECT_ADDR + SKILL_CURRENT_XIUWEI_TO_OBJECT_OFFSET);
			}
			__CATCH("获取技能当前修为出错!")
		return CURRENT_XIUWEI;
	}
};

//lua 封装类
class RgisterCCSkillObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCSkillObject**)lua_newuserdata(L,sizeof(CCSkillObject*)) = new CCSkillObject(nValue);
		luaL_getmetatable(L, "CCSkillObject"); 
		lua_setmetatable(L,-2);
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCSkillObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取地址
	static int CallGetTreeAddr(lua_State* L)  
	{ 
		CCSkillObject** pT = (CCSkillObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getTreeAddr());
		return 1;  
	}
	//获取地址
	static int CallGetObjecteAddr(lua_State* L)  
	{ 
		CCSkillObject** pT = (CCSkillObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjecteAddr());
		return 1;  
	}
	//获取技能等级
	static int CallGetSkillLevel(lua_State* L)  
	{ 
		CCSkillObject** pT = (CCSkillObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getSkillLevel());
		return 1;  
	}
	//获取技能ID
	static int CallGetSkillID(lua_State* L)  
	{ 
		CCSkillObject** pT = (CCSkillObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getSkillID());
		return 1;  
	}
	//获取技能当前修为
	static int CallGetCurrentXiuWei(lua_State* L)  
	{ 
		CCSkillObject** pT = (CCSkillObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getCurrentXiuWei());
		return 1;  
	}
	//获取技能名称
	static int CallGetSkillName(lua_State* L)  
	{  
		CCSkillObject** pT = (CCSkillObject**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getSkillName());  
		return 1;
	}

	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCSkillObject::CreateClass); 
		lua_setglobal(L,"CCSkillObject");
		luaL_newmetatable(L,"CCSkillObject"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCSkillObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getTreeAddr");  
		lua_pushcfunction(L,CallGetTreeAddr);  
		lua_settable(L,-3);

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getObjecteAddr");  
		lua_pushcfunction(L,CallGetObjecteAddr);  
		lua_settable(L,-3);

		lua_pushstring(L,"getSkillLevel");  
		lua_pushcfunction(L,CallGetSkillLevel);  
		lua_settable(L,-3);

		lua_pushstring(L,"getSkillID");  
		lua_pushcfunction(L,CallGetSkillID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getCurrentXiuWei");  
		lua_pushcfunction(L,CallGetCurrentXiuWei);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getSkillName");  
		lua_pushcfunction(L,CallGetSkillName);  
		lua_settable(L,-3);  
		
		lua_pop(L,1);
	}
};