#pragma once

#define  TREE_SHOP_FALG_OFFSET 0xD // 二叉树Flag
#define  TREE_SHOP_SMALL_OFFSET 0x10 //二叉树小偏移

class CCShopTree
{
private:
	int BASE_VALUE;
	int BASE_OFFSET;
	int START_ADDR;
	vector<int> vecAllShopAddr;
	//遍历二叉树
	void TreeList(int StartAddr);
public:
	CCShopTree(void);
	~CCShopTree(void);
	//获取数量
	int getAllShopCount()
	{
		return vecAllShopAddr.size();
	}
	//获取单个值
	int getAddrByIndex(int _index)
	{
		return vecAllShopAddr.at(_index);
	}
};

//lua 封装类
class RgisterCCShopTree
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCShopTree**)lua_newuserdata(L,sizeof(CCShopTree*)) = new CCShopTree();
		luaL_getmetatable(L, "CCShopTree"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCShopTree**)lua_topointer(L,1);  
		return 0;  
	}
	//获取数量
	static int CallGetSize(lua_State* L)  
	{ 
		//正确的做法
		CCShopTree** pT = (CCShopTree**)lua_topointer(L,1);  
		//打印成员变量的值  
		lua_pushnumber(L,(*pT)->getAllShopCount()); 
		return 1;
	}
	//获取单个对象
	static int CallGetObject(lua_State* L)  
	{ 
		CCShopTree** pT = (CCShopTree**)lua_topointer(L,1);
		lua_pushnumber(L,(*pT)->getAddrByIndex((int)lua_tonumber(L,2)));
		return 1;  
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterCCShopTree::CreateClass); 
		lua_setglobal(L,"CCShopTree");
		luaL_newmetatable(L,"CCShopTree");

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterCCShopTree::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  
		lua_pushstring(L,"getAllShopCount");  
		lua_pushcfunction(L,CallGetSize);  
		lua_settable(L,-3);

		lua_pushstring(L,"getAddrByIndex");  
		lua_pushcfunction(L,CallGetObject);  
		lua_settable(L,-3);  


		lua_pop(L,1);
	}
};