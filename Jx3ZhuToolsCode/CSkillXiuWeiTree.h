#pragma once
//技能修为偏移枚举
enum SKILL_XIUWEI_OFFSET
{
	XIUWEI_FLAG_OFFSET = 0xD//二叉树判断偏移
};
class CCSkillXiuWeiTree
{
private: 
	int BASE_ADDR;//基地址
	int BASE_ADDR_VALUE;//基地址值
	int SECOND_OFFSET;//二级偏移
	int START_ADDR;//开始地址
	vector<int> SKILL_XIUWEI_ARRAY;//技能修为地址集合
	void LuaSkillXiuWeiTree(int StartAddr);
public:
	CCSkillXiuWeiTree(void);
	~CCSkillXiuWeiTree(void);
	//LUA获取列表数量
	int LuaSize();
	//LUA根据索引获取对象
	int LuaGetSkillXiuWeiAddr(int _index);
};
//lua 封装类
class RgisterCCSkillXiuWeiTree
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCSkillXiuWeiTree**)lua_newuserdata(L,sizeof(CCSkillXiuWeiTree*)) = new CCSkillXiuWeiTree();
		luaL_getmetatable(L, "CCSkillXiuWeiTree"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCSkillXiuWeiTree**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCSkillXiuWeiTree** pT = (CCSkillXiuWeiTree**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->LuaSize()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCSkillXiuWeiTree** pT = (CCSkillXiuWeiTree**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->LuaGetSkillXiuWeiAddr((int)lua_tonumber(L,2)));
		return 1;  
	}

	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCSkillXiuWeiTree::CreateClass); 
		lua_setglobal(L,"CCSkillXiuWeiTree");
		luaL_newmetatable(L,"CCSkillXiuWeiTree");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCSkillXiuWeiTree::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"LuaSize");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"LuaGetSkillXiuWeiAddr");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};
