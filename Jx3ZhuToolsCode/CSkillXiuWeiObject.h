#pragma once
enum SKILL_XIUWEI_OBJECTOFFSET
{
	SKILL_XIUWEI_ID_OFFSET = 0x10,//技能ID
	SKILL_XIUWEI_XIUWEI_OFFSET = 0x18//技能升级修为
};
class CCSkillXiuWeiObject
{
private:
private:
	int BASE_START;//技能开始地址
	int SKILL_ID;//技能ID
	int SKILL_XIUWEI;//技能升级需要修为
public:
	CCSkillXiuWeiObject(void);
	CCSkillXiuWeiObject(int Addr);
	~CCSkillXiuWeiObject(void);
	//获取Tree地址
	int getTreeAddr()
	{
		return BASE_START;
	}
	//获取技能修为
	int getSkillXiuWei()
	{
		SKILL_XIUWEI = 0;
		__TRY
			if (BASE_START && IsReadAddrInt((PVOID)BASE_START) && IsReadAddrInt((PVOID)(BASE_START + SKILL_XIUWEI_XIUWEI_OFFSET)))
			{
				SKILL_XIUWEI = *(int *)(BASE_START + SKILL_XIUWEI_XIUWEI_OFFSET);
			}
			__CATCH("获取技能修为出错!")
				return SKILL_XIUWEI;
	}
	//获取数据ID
	int getSkillID()
	{
		SKILL_ID = 0;
		__TRY
			if (BASE_START && IsReadAddrInt((PVOID)BASE_START) && IsReadAddrInt((PVOID)(BASE_START + SKILL_XIUWEI_ID_OFFSET)))
			{
				SKILL_ID = *(int *)(BASE_START + SKILL_XIUWEI_ID_OFFSET);
			}
			__CATCH("获取技能ID出错!")
		return SKILL_ID;
	}
};
//lua 封装类
class RgisterCCSkillXiuWeiObject
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCSkillXiuWeiObject**)lua_newuserdata(L,sizeof(CCSkillXiuWeiObject*)) = new CCSkillXiuWeiObject(nValue);
		luaL_getmetatable(L, "CCSkillXiuWeiObject"); 
		lua_setmetatable(L,-2);
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCSkillXiuWeiObject**)lua_topointer(L,1);  
		return 0;  
	}
	//获取地址
	static int CallGetTreeAddr(lua_State* L)  
	{ 
		CCSkillXiuWeiObject** pT = (CCSkillXiuWeiObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getTreeAddr());
		return 1;  
	}
	//获取技能升级修为
	static int CallGetSkillXiuWei(lua_State* L)  
	{ 
		CCSkillXiuWeiObject** pT = (CCSkillXiuWeiObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getSkillXiuWei());
		return 1;  
	}
	//获取技能ID
	static int CallGetSkillID(lua_State* L)  
	{ 
		CCSkillXiuWeiObject** pT = (CCSkillXiuWeiObject**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getSkillID());
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCSkillXiuWeiObject::CreateClass); 
		lua_setglobal(L,"CCSkillXiuWeiObject");
		luaL_newmetatable(L,"CCSkillXiuWeiObject"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCSkillXiuWeiObject::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getTreeAddr");  
		lua_pushcfunction(L,CallGetTreeAddr);  
		lua_settable(L,-3);

		lua_pushstring(L,"getSkillXiuWei");  
		lua_pushcfunction(L,CallGetSkillXiuWei);  
		lua_settable(L,-3);

		lua_pushstring(L,"getSkillID");
		lua_pushcfunction(L,CallGetSkillID);  
		lua_settable(L,-3);

		lua_pop(L,1);
	}
};