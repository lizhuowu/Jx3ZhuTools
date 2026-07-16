#pragma once

#include "CUserInfo.h"
#include "CCall.h"
#include "CCommon.h"
#include "CTest.h"
#include "CMonsterInformation.h"
#include "CMonsterTree.h"
#include "CGroundInfo.h"
#include "CGroundTree.h"
#include "CPickupInfo.h"
#include "CDoodPickups.h"
#include "CTaskHasIDs.h"
#include "CTaskJujmentObject.h"
#include "CTaskJujimentArray.h"
#include "CAllTaskTree.h"
#include "CAllTaskObject.h"
#include "CShopTreeObject.h"
#include "CShopTree.h"
#include "CShopGoodObject.h"
#include "CShopGoodArray.h"
#include "CShopGoodPriceObject.h"
#include "CShopGoodPriceTree.h"
#include "CPackPercelArray.h"
#include "CPackArray.h"
#include "CPackObject.h"
#include "CPlayerInfomation.h"
#include "CPlayerTree.h"
#include "CControlResponseTeam.h"
#include "CRoleWear.h"
#include "CSkillObject.h"
#include "CSkillTree.h"
#include "CSkillXiuWeiTree.h"
#include "CSkillXiuWeiObject.h"
#include "CThousands.h"


class CCLua
{
public:
	lua_State *_lua_Status;//指针改全局
	CCLua(void);
	~CCLua(void);
	void LuaInit();
	void Lua_RegisterFun();
	void LuaRegisterClass();
	void Lua_DoFile(CString luaScriptPath);
	//注册函数
	//日志消息
	static int CCLua::LuaPrint(lua_State *L);
	//延时
	static int CCLua::LuaSleep(lua_State *L);
	//获取人物血
	static int CCLua::LuaGetUserBlood(lua_State *L);
	//获取人物血百分比
	static int CCLua::LuaGetUserBloodPercent(lua_State *L);
	//获取人物等级
	static int CCLua::LuaGetUserLevel(lua_State *L);
	//取人物X坐标
	static int CCLua::LuaGetUserX(lua_State *L);
	//取人物Y坐标
	static int CCLua::LuaGetUserY(lua_State *L);
	//取运行根目录
	static int CCLua::LuaGetRootPath(lua_State *L);
	//堵塞寻路
	static int CCLua::LuaMoveTo(lua_State *L);
	//非堵塞寻路
	static int CCLua::LuaMove(lua_State *L);
	//选怪
	static int LuaSelectMonster(lua_State *L);
	//使用技能
	static int LuaSkill(lua_State *L);
	//采集
	static int LuaAcquitst(lua_State *L);
	//拾取物品
	static int LuaPickUpGood(lua_State *L);
	//封包接任务
	static int LuaAccpetTask(lua_State *L);
	//封包交任务
	static int LuaFinshTask(lua_State *L);
	//打开NPC
	static int LuaOpenNPC(lua_State *L);
	//买物品
	static int LuaBuyGood(lua_State *L);
	//打开商店
	static int LuaOpenShop(lua_State *L);
	//获取HOOK到的商店编号
	static int LuaGetShopIndex(lua_State *L);
	//任务二级对话
	static int LuaNpcTaskSubTalk(lua_State *L);
	//使用物品
	static int LuaUseGood(lua_State *L);
	//穿戴物品
	static int LuaWearGood(lua_State *L);
	//穿戴马匹
	static int LuaWearHorse(lua_State *L);
	//拾取金币
	static int LuaPickGlod(lua_State *L);
	//跳CALL
	static int LuaRoleJmp(lua_State *L);
	//轻功
	static int LuaRoleDodge(lua_State *L);
	//取消打坐
	static int LuaCancelSetDwon(lua_State *L);
	//按键CALL
	static int LuaKey_F_DownCall(lua_State *L);
	//按键CALL
	static int LuaKey_F_UpCall(lua_State *L);
	//按键CALL
	static int LuaKey_ESC_DownCall(lua_State *L);
	//按键CALL
	static int LuaKey_ESC_UpCall(lua_State *L);
	//按键CALL
	static int LuaKey_SPACE_DownCall(lua_State *L);
	//按键CALL
	static int LuaKey_SPACE_UpCall(lua_State *L);
	//获取转向角度
	static int LuaGetTran(lua_State *L);
	//转向CALL
	static int LuaTranCall(lua_State *L);
	//销毁物品
	static int LuDistoryCall(lua_State *L);
	//退出组队
	static int LuaQuitTeam(lua_State *L);
	//发起组队
	static int LuaRequsetTeam(lua_State *L);
	//接受组队
	static int LuaRsponseTeam(lua_State *L);
	//接受最新组队
	static int LuaRsponseNewTeam(lua_State *L);
	//图内寻路
	static int LuaMapInRunTo(lua_State *L);
	//切换内功
	static int LuaChangeKungFu(lua_State *L);
	//交互
	static int LuaInterActive(lua_State *L);
	//修理装备
	static int LuaRepairWear(lua_State *L);
	//技能升级
	static int LuaSkillLevelUp(lua_State *L);
	//定点释放技能
	static int LuaSkillMakePoint(lua_State *L);
	//奇穴设置
	static int LuaSpecilSet(lua_State *L);
	//机关任务
	static int LuaOrganMove(lua_State *L);
	//获取HOOK到的文本
	static int LuaGetHookTxt(lua_State *L);
	//怪物视野
	static int LuaMonsterView(lua_State *L);
	//对象类型
	static int LuaObjectType(lua_State *L);
	//取千机地址
	static int LuaGetThousands(lua_State *L);
	//装备千机装备
	static int LuaWearThousands(lua_State *L);
	//放弃任务
	static int LuaDelTask(lua_State *L);
	//对象类型
	static int LuaShenXingQianLi(lua_State *L);
	//使用礼包
	static int LuaUsePacket(lua_State *L);
	//取商店地址
	static int LuaGetShopAddr(lua_State *L);
	//取物品价格
	static int LuaGetGoodPrice(lua_State *L);
	//卖物品
	static int LuaSellGood(lua_State *L);
	//选择奖励交任务
	static int LuaFinshTaskEx(lua_State *L);
	//刷木童
	static int LuaShuMuTong(lua_State *L);
	//登高
	static int LuaDengGao(lua_State *L);
	//过图CALL
	static int LuaPassMap(lua_State *L);
};

