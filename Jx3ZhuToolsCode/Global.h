#pragma once
#define  IsReadAddrInt(addr) !IsBadReadPtr(addr,sizeof(unsigned int))//四字节判断
#define  IsReadAddrByte(addr) !IsBadReadPtr(addr,sizeof(byte))//一字节判断
#define	 __TRY try {
#define  __CATCH(MESSAGE)  } catch (...) { OutputDebugString(MESSAGE); }

extern LONG lwndProc;
extern HWND g_hGameHandle;

extern int JmpAddr;
extern int TxtAddr;
extern int TALK_ID;//对话使用的ID
extern string HOOKText;//Hook到的文本

char* GB2312ToBIG5(const char* szGBString);
wchar_t* GB2312ToUnicode(const char* szGBString);
char* UnicodeToBIG5(const wchar_t* szUnicodeString);
char* BIG5ToGB2312(const char* szBIG5String);
wchar_t* BIG5ToUnicode(const char* szBIG5String);
char* UnicodeToGB2312(const wchar_t* szUnicodeString);
char* U2G(const char* utf8);
/************************************************************************/
/*                                                                      */
/************************************************************************/
extern const int ROLE_BASE_OFFSET;
extern const int ROLE_CURRENT_BLOOD_OFFSET;
extern const int ROLE_CURRENT_MAGIC_OFFSET;
extern const int ROLE_SELECT_ID_OFFSET;
extern const int ROLE_XIUWEI_OFFSET;//人物修为偏移
extern const int USER_ACTION_STATUS_OFFSET;//战斗状态
extern const int USER_GLOD_OFFSET;//人物金币偏移
/************************************************************************/
/*                                                                      */
/************************************************************************/
extern const int MOUSE_MOVETO_CALL_ECX;//鼠标寻路CALL ECX 计算
extern const int MOUSE_MOVETO_CALL;//鼠标寻路CALL 计算

/************************************************************************/
/*                                                                      */
/************************************************************************/

extern const int MONSTER_TERR_BASE_OFFSET;//怪物二叉树基址的计算偏移
extern const int MONSTER_TERR_OFFSET;//二叉树大偏移，不用模块计算
/************************************************************************/
/*                                                                      */
/************************************************************************/
extern const int SKILL_CALL_OFFSET;//技能CALL偏移
/************************************************************************/
/*                                                                      */
/************************************************************************/

extern const int SELECT_MONSTER_CALL_OFFSET;//选怪CALL偏移
/************************************************************************/
/* 地面                                                               */
/************************************************************************/
extern const int DOOD_TERR_BASE_OFFSET;//地面二叉树基址的计算偏移
extern const int DOOD_TERR_OFFSET;//地面二叉树大偏移，不用模块计算

/************************************************************************/
/*采集(跟地面相关)                                                      */
/************************************************************************/
extern const int ACQUIST_CALL_ECX_OFFSET;//采集CALL ECX 偏移
extern const int ACQUIST_CALL_OFFSET;//采集CALL 偏移

/************************************************************************/
/* 拾取相关                                                              */
/************************************************************************/
extern const int PICKUP_GOOD_ECX_OFFSET;//拾取物品 CALL ECX偏移
extern const int PICKUP_GOOD_CALL_OFFSET;//拾取物品CALL偏移
//拾取金币
extern const int PICKUP_GLOD_CALL_ECX_OFFSET;//拾取金币CALL ECX 偏移
extern const int PICKUP_GLOD_CALL_OFFSET;//拾取金币CALL 偏移

/************************************************************************/
/* 任务                                                                 */
/************************************************************************/
//任务基址用人物基址
extern const int CURRENT_TASK_ID_OFFSET_1;//当前已接任务ID数字偏移——1
extern const int CURRENT_TASK_ID_OFFSET_2;//当前已接任务ID数字偏移——2(需手动更新)
//任务判断条件
extern const int TASK_JUDJMENT_ARRAY_OFFSET_1;//任务判断条件数组偏移一
extern const int TASK_JUDJMENT_ARRAY_OFFSET_2;//任务判断条件数组偏移二
//所有任务二叉
extern const int TASK_ALL_BASE_OFFSET;//获取所有任务的二叉基址偏移
extern const int TASK_ALL_BASE_FIRST_OFFSET;//获取所有任务的第一级偏移
//接任务封包CALL
extern const int ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;//接任务CALL ECX 偏移
extern const int ACCPET_TASK_BUFFER_CALL_OFFSET;//接任务CALL 偏移

//打开NPC
extern const int OPEN_NPC_CALL_ECX_OFFSET;//打开NPC ECX 偏移
extern const int OPEN_NPC_CALL_OFFSET;//打开NPC CALL偏移
/************************************************************************/
/* 商店相关                                                             */
/************************************************************************/
//根据商店ID获取商店地址
extern const int GET_SHOP_ADDR_BY_SHOPID_TREE_ECX_OFFSET;//根据商店ID获取商店地址CALL ECX 偏移
extern const int GET_SHOP_ADDR_BY_SHOPID_TREE_BIG_OFFSET;//根据商店ID获取商店地址大偏移
extern const int SHOP_LIST_OFFSET;//商店列表遍历偏移 - 上面三个的特征码定位到下面的就是
extern const int SHOP_LIST_COUNT_OFFSET;//商店列表数量偏移

//打开商店CALL
extern const int OPEN_SHOP_BY_INDEX_CALL_ECX_OFFSET;//打开商店CALL ECX 偏移
extern const int OPEN_SHOP_BY_INDEX_CALL_OFFSET;//打开商店CALL 偏移

/************************************************************************/
/* 商店单价相关                                                         */
/************************************************************************/
extern const int GOOD_PRICE_IMUL;//计算索引下标
extern const int GOOD_PRICE_ADDR_OFFSET;//单价数组地址
//买物品CALL 相关
extern const int BUY_GOOD_CALL_ECX_OFFSET;//商店买物品CALL ECX 偏移
extern const int BUY_GOOD_CALL_OFFSET;//商店买物品CALL 偏移

/************************************************************************/
/* HOOK 打开商店和任务对话ID地址(注入立刻HOOK)                          */
/************************************************************************/
extern const int HOOK_SHOP_TALK_ADDR_OFFSET;//HOOK地址
/************************************************************************/
/* NPC 任务对话（二级）                                                 */
/************************************************************************/
extern const int NPC_TALK_SUB_CALL_ECX_OFFSET;//任务二级对话CALL ECX偏移
extern const int NPC_TALK_SUB_CALL_OFFSET;//任务二级对话CALL偏移

/************************************************************************/
/* 背包相关                                                             */
/************************************************************************/
extern const int PACK_PERCEL_ARRAY_BASE_OFFSET;//背包包裹数组基址
extern const int PACL_PERCEL_ARRAY_BIG_OFFSET;//背包包裹数组大偏移
/************************************************************************/
/* 使用物品CALL                                                         */
/************************************************************************/
extern const int USE_GOOD_CALL_ECX_OFFSET;//使用物品CALL ECX偏移
extern const int USE_GOOD_CALL_OFFSET;//使用物品CALL 偏移
extern const int USE_GOOD_CALL_STRUCT_CONST_OFFSET;//存放使用物品CALL 结构 第二个产量的值
/************************************************************************/
/* 穿戴物品CALL                                                         */
/************************************************************************/
extern const int WEAR_GOOD_CALL_ECX_OFFSET;//穿戴物品CALL ECX 偏移
extern const int WEAR_GOOD_CALL_OFFSET;//穿戴物品CALL 偏移
/************************************************************************/
/* 跳CALL                                                               */
/************************************************************************/
extern const int ROLE_JMP_CALL_OFFSET;//跳CALL
extern const int ROLE_DODGE_CALL_ECX_OFFSET;//轻功CALL ECX 偏移
extern const int ROLE_DODGE_CALL_OFFSET;//轻功CALL 偏移
/************************************************************************/
/* 取消打坐                                                             */
/************************************************************************/
extern const int CANCEL_SETDOWN_CALL_OFFSET;//取消打坐
/************************************************************************/
/* 按键CALL                                                             */
/************************************************************************/
extern const int KEY_CALL_ECX_BASE_OFFSET;//按键CALL ECX 基址
extern const int KEY_CALL_ECX_BASE_BIG_OFFSET;//按键CALL 大偏移
extern const int KEY_CALL_OFFSET;//按键CALL 偏移
/************************************************************************/
/* 转向CALL                                                             */
/************************************************************************/
extern const int TRAN_CALL_ECX_BASE_OFFSET;//转向CALL ECX 计算偏移
extern const int TRAN_CALL_ECX_BIG_OFFSET;//转向CALL ECX 大偏移
extern const int TRAN_CALL_OFFSET;//转向CALL 偏移
/************************************************************************/
/* 销毁物品                                                             */
/************************************************************************/
extern const int DELETE_GOOD_CALL_ECX_OFFSET;//销毁物品CALL ECX 计算偏移
extern const int DELETE_GOOD_CALL_OFFSET;//销毁物品CALL 计算偏移

/************************************************************************/
/* 控件                                                                 */
/************************************************************************/
extern const int CONTROL_BASE_OFFSET;//控件基址偏移
extern const int CONTROL_BASE_BIG_OFFSET;//控件基址大偏移
extern const int CONTROL_BIG_OFFSET;//控件遍历的大偏移
extern const int CONTROL_TOP_ARRAY_PER;//最外部的10个长度的数组每个数组的间隔大小

/************************************************************************/
/*轻功CALL HOOK地址                                                     */
/************************************************************************/
extern const int DODGE_HOOK_1;//轻功修改地址1(0x55 改为 0C2 0x4 0x00)
extern const int DODGE_HOOK_2;//轻功修改地址2(0x75 改为 0xEB)

/************************************************************************/
/* 二级对话CALL第一参数计算                                             */
/************************************************************************/
extern const int TASK_SUB_TALK_PRARTM_BASE_OFFSET;//二级对话CALL第一参数计算 基址偏移
extern const int TASK_SUB_TALK_PRARTM_OFFSET_1;//二级对话CALL第一参数计算 第一级偏移
extern const int TASK_SUB_TALK_PRARTM_OFFSET_2;//二级对话CALL第一参数计算 第二级偏移

/************************************************************************/
/* 图内寻路CALL                                                         */
/************************************************************************/
extern const int MAP_IN_RUN_TO_CALL_ECX_OFFSET;//图内寻路CALL ECX 偏移
extern const int MAP_IN_RUN_TO_CALL_OFFSET;//图内寻路CALL 偏移

/************************************************************************/
/* 切换内功                                                             */
/************************************************************************/
extern const int CHANGE_KUNG_FU_CALL_ECX_OFFSET;  //切换内功CALL ECX 偏移
extern const int CHANGE_KUNG_FU_CALL_OFFSET;//切换内功CALL 偏移

/************************************************************************/
/* 交互CALL                                                             */
/************************************************************************/
extern const int INTERACTIVE_CALL_ECX_OFFSET;//交互CALL ECX 偏移
extern const int INTERACTIVE_CALL_OFFSET;//交互CALL 偏移
extern const int INTERAVTIVE_CONST_BASE_OFFSET;//交互CALL 常量基址
extern const int INTERACTIVE_CONST_OFFSET_1;//交互CALL常量偏移1
extern const int INTERACTIVE_CONST_OFFSET_2;//交互CALL常量偏移2
/************************************************************************/
/* 获取全部修理价格CALL                                                 */
/************************************************************************/
extern const int REPAIR_PRICE_CALL_OFFSET;//获取全部修理价格CALL 偏移
/************************************************************************/
/* 修理全部装备                                                         */
/************************************************************************/
extern const int REPAIR_WEAR_CALL_ECX_OFFSET;//修理全部装备CALL ECX 偏移
extern const int REPAIR_WEAR_CALL_OFFSET;//修理全部装备CALL 偏移
/************************************************************************/
/* 技能二叉/技能升级/获取技能升级修为                                   */
/************************************************************************/
extern const int SKILL_TERR_OFFSET;//技能二叉树大偏移
extern const int SKILL_UP_CALL_ECX_OFFSET;//升级技能CALL ECX偏移
extern const int SKILL_UP_CALL_OFFSET;//升级技能CALL 偏移
/************************************************************************/
/* 定点释放技能                                                         */
/************************************************************************/
extern const int SKILL_MAKE_POINT_CALL_OFFSET;//定点释放技能CALL 偏移
/************************************************************************/
/* 奇穴设置                                                             */
/************************************************************************/
extern const int SPECIL_SET_CALL_ECX_OFFSET;//奇穴设置CALL ECX 偏移
extern const int SPECIL_SET_CALL_OFFSET;//奇穴设置CALL 偏移

/************************************************************************/
/* 机关任务CALL                                                         */
/************************************************************************/
extern const int CALL_ORGAN_CALL_ECX_OFFSET;//机关任务CALL ECX偏移
extern const int CALL_ORGAN_CALL_OFFSET;//机关任务CALL偏移
/************************************************************************/
/* 判断怪物视野                                                         */
/************************************************************************/
extern const int CALL_MONSTER_VIEW;//判断怪物是否在视野内
/************************************************************************/
/* 对象类型CALL                                                         */
/************************************************************************/
extern const int CALL_TYPE_RET;//判断对象类型CALL 偏移
/************************************************************************/
/* 使用礼包                                                             */
/************************************************************************/
extern const int CALL_USE_PACKET_CALL_ECX_OFFSET;//使用礼包CALL ECX 偏移
extern const int CALL_USE_PACKET_CALL_OFFSET;//使用礼包CALL 偏移
/************************************************************************/
/* 获取物品价格CALL                                                     */
/************************************************************************/
extern const int GOOD_PRICE_CALL_OFFSET;//获取价格CALL 偏移
/************************************************************************/
/* 买物品CALL                                                           */
/************************************************************************/
extern const int SELL_GOOD_CALL_ECX_OFFSET;//卖物品CALL ECX 偏移
extern const int SELL_GOOD_CALL_OFFSET;//卖物品CALL 偏移

/************************************************************************/
/* 过图CALL                                                             */
/************************************************************************/
extern const int PASS_MAP_CALL_ECX_OFFSET;//过图CALL ECX 偏移
extern const int PASS_MAP_CALL_OFFSET;//过图CALL 偏移

