#include "stdafx.h"
#include "Global.h"

LONG lwndProc = 0;
HWND g_hGameHandle = 0;

int JmpAddr = 0;
int TxtAddr = 0;
int TALK_ID = 0;//对话使用的ID
string HOOKText = "HOOKTEXT";//Hook到的文本

char* GB2312ToBIG5(const char* szGBString)
{
	LCID lcid = MAKELCID(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED),
		SORT_CHINESE_PRC);
	int nLength = LCMapString(lcid,LCMAP_TRADITIONAL_CHINESE,szGBString,-1,NULL,0);
	char* pBuffer=new char[nLength+1];
	LCMapString(lcid,LCMAP_TRADITIONAL_CHINESE,szGBString,-1,pBuffer,nLength);
	pBuffer[nLength]=0;
	wchar_t* pUnicodeBuff = GB2312ToUnicode(pBuffer);
	char* pBIG5Buff = UnicodeToBIG5(pUnicodeBuff);
	delete[] pBuffer;
	delete[] pUnicodeBuff;
	return pBIG5Buff;
}
wchar_t* GB2312ToUnicode(const char* szGBString)
{
	UINT nCodePage = 936; //GB2312
	int nLength=MultiByteToWideChar(nCodePage,0,szGBString,-1,NULL,0);
	wchar_t* pBuffer = new wchar_t[nLength+1];
	MultiByteToWideChar(nCodePage,0,szGBString,-1,pBuffer,nLength);
	pBuffer[nLength]=0;
	return pBuffer;
}
//Unicode 转换成 BIG5：
char* UnicodeToBIG5(const wchar_t* szUnicodeString)
{
	UINT nCodePage = 950; //BIG5
	int nLength=WideCharToMultiByte(nCodePage,0,
		szUnicodeString,-1,NULL,0,NULL,NULL);
	char* pBuffer=new char[nLength+1];
	WideCharToMultiByte(nCodePage,0,szUnicodeString,-1,pBuffer,nLength,NULL,NULL);
	pBuffer[nLength]=0;
	return pBuffer;
}
//繁体中文BIG5 转换成 简体中文 GB2312
char* BIG5ToGB2312(const char* szBIG5String)
{
	LCID lcid = MAKELCID(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED),
		SORT_CHINESE_PRC);
	wchar_t* szUnicodeBuff = BIG5ToUnicode(szBIG5String);
	char* szGB2312Buff = UnicodeToGB2312(szUnicodeBuff);
	int nLength = LCMapString(lcid,LCMAP_SIMPLIFIED_CHINESE, szGB2312Buff,-1,NULL,0);
	char* pBuffer = new char[nLength + 1];
	LCMapString(0x0804,LCMAP_SIMPLIFIED_CHINESE,szGB2312Buff,-1,pBuffer,nLength);
	pBuffer[nLength] = 0;
	delete[] szUnicodeBuff;
	delete[] szGB2312Buff;
	return pBuffer;
}
//BIG5 转换成 Unicode：
wchar_t* BIG5ToUnicode(const char* szBIG5String)
{
	UINT nCodePage = 950; //BIG5
	int nLength=MultiByteToWideChar(nCodePage,0,szBIG5String,-1,NULL,0);
	wchar_t* pBuffer = new wchar_t[nLength+1];
	MultiByteToWideChar(nCodePage,0,szBIG5String,-1,pBuffer,nLength);
	pBuffer[nLength]=0;
	return pBuffer;
}
//Unicode 转换成 GB2312：
char* UnicodeToGB2312(const wchar_t* szUnicodeString)
{
	UINT nCodePage = 936; //GB2312
	int nLength=WideCharToMultiByte(nCodePage,0,szUnicodeString,-1,NULL,0,NULL,NULL);
	char* pBuffer=new char[nLength+1];
	WideCharToMultiByte(nCodePage,0,szUnicodeString,-1,pBuffer,nLength,NULL,NULL);
	pBuffer[nLength]=0;
	return pBuffer;
}
//UTF-8到GB2312的转换
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}


/************************************************************************/
/* 全局标识                                                             */
/************************************************************************/

//定义基址和偏移Const

/************************************************************************/
/* 人物信息相关                                                         */
/************************************************************************/
//001c0000+29D6B8

const int ROLE_BASE_OFFSET = 0x29D710;//模块地址+偏移就是基址(偏移变了，自己CE手动更新)++
const int ROLE_CURRENT_BLOOD_OFFSET = 0x2D8;//人物当前血偏移(怪物也可以用)
const int ROLE_CURRENT_MAGIC_OFFSET = 0x300;//人物当前蓝偏移(怪物也可以用)
const int ROLE_SELECT_ID_OFFSET = 0x8B8;//人物选中怪物ID偏移
const int ROLE_XIUWEI_OFFSET = 0x1D278;//人物修为偏移
const int USER_ACTION_STATUS_OFFSET = 0x37C;//战斗状态
const int USER_GLOD_OFFSET = 0x77C8;//人物金币偏移
/************************************************************************/
/* 寻路                                                                 */
/************************************************************************/
//JX3UI.dll 5DB80000

const int MOUSE_MOVETO_CALL_ECX = 0x120ECC;//鼠标寻路CALL ECX 计算
const int MOUSE_MOVETO_CALL = 0x3FF70;//鼠标寻路CALL 计算

/************************************************************************/
/* 怪物                                                                 */
/************************************************************************/
const int MONSTER_TERR_BASE_OFFSET = 0x0029D768;//怪物二叉树基址的计算偏移
const int MONSTER_TERR_OFFSET = 0x004782D8;//二叉树大偏移，不用模块计算

/************************************************************************/
/* 地面(跟怪物的一样)                                                   */
/************************************************************************/
const int DOOD_TERR_BASE_OFFSET = 0x0029D768;//地面二叉树基址的计算偏移
const int DOOD_TERR_OFFSET =  0x004782D8;//地面二叉树大偏移，不用模块计算


/************************************************************************/
/* 技能                                                                  */
/************************************************************************/
const int SKILL_CALL_OFFSET = 0x0010F3D0;//技能CALL偏移

/************************************************************************/
/* 选怪                                                                 */
/************************************************************************/
const int SELECT_MONSTER_CALL_OFFSET = 0x00118B10;//选怪CALL偏移
/************************************************************************/
/*采集(跟地面相关)                                                      */
/************************************************************************/
const int ACQUIST_CALL_ECX_OFFSET = 0x00282490;//采集CALL ECX 偏移
const int ACQUIST_CALL_OFFSET = 0x000494F0;//采集CALL 偏移

/************************************************************************/
/* 拾取相关                                                              */
/************************************************************************/
const int PICKUP_GOOD_ECX_OFFSET = 0x00282490; //拾取物品 CALL ECX偏移
const int PICKUP_GOOD_CALL_OFFSET = 0x0004BBA0; //拾取物品CALL偏移

//拾取金币
const int PICKUP_GLOD_CALL_ECX_OFFSET = 0x00282490; //拾取金币CALL ECX 偏移
const int PICKUP_GLOD_CALL_OFFSET = 0x0004BBE0; //拾取金币CALL 偏移

/************************************************************************/
/* 任务                                                                 */
/************************************************************************/
const int CURRENT_TASK_ID_OFFSET_1 = 0x903C;//当前已接任务ID数字偏移——1
const int CURRENT_TASK_ID_OFFSET_2 = 0x514;//当前已接任务ID数字偏移——2(需手动更新)

//任务判断条件
const int TASK_JUDJMENT_ARRAY_OFFSET_1 = 0x4000;//任务判断条件数组偏移一
const int TASK_JUDJMENT_ARRAY_OFFSET_2 = 0xAD4;//任务判断条件数组偏移二
//所有任务二叉(暂时不用)
const int TASK_ALL_BASE_OFFSET = 0x29D768;//获取所有任务的二叉基址偏移
const int TASK_ALL_BASE_FIRST_OFFSET = 0x844;//获取所有任务的第一级偏移
//接任务封包CALL
const int ACCPET_TASK_BUFFER_CALL_ECX_OFFSET = 0x00282490; //接任务CALL ECX 偏移
const int ACCPET_TASK_BUFFER_CALL_OFFSET = 0x000693C0; //接任务CALL 偏移

/************************************************************************/
/* NPC 操作相关                                                         */
/************************************************************************/
//打开NPC
const int OPEN_NPC_CALL_ECX_OFFSET = 0x00282490; //打开NPC ECX 偏移
const int OPEN_NPC_CALL_OFFSET = 0x000493F0; //打开NPC CALL偏移

/************************************************************************/
/* 商店相关                                                             */
/************************************************************************/
//根据商店ID获取商店地址
const int GET_SHOP_ADDR_BY_SHOPID_TREE_ECX_OFFSET = 0x29D768;//根据商店ID获取商店地址CALL ECX 偏移
const int GET_SHOP_ADDR_BY_SHOPID_TREE_BIG_OFFSET = 0x301A8;//根据商店ID获取商店地址大偏移
const int SHOP_LIST_OFFSET = 0xA4;//商店列表遍历偏移 - 上面2个的特征码定位到后，再往下面的就是
const int SHOP_LIST_COUNT_OFFSET = 0x8c;//商店列表数量偏移

//打开商店CALL
const int OPEN_SHOP_BY_INDEX_CALL_ECX_OFFSET = 0x00282490; //打开商店CALL ECX 偏移
const int OPEN_SHOP_BY_INDEX_CALL_OFFSET = 0x0004C050; //打开商店CALL 偏移

/************************************************************************/
/* 商店单价相关                                                         */
/************************************************************************/
const int GOOD_PRICE_IMUL = 0x74;//商店物品单价 计算索引下标
const int GOOD_PRICE_ADDR_OFFSET = 0x8c;//商店物品单价 单价数组地址偏移

//买物品CALL 相关
const int BUY_GOOD_CALL_ECX_OFFSET = 0x00282490; //商店买物品CALL ECX 偏移
const int BUY_GOOD_CALL_OFFSET = 0x0004DC20; //商店买物品CALL 偏移

/************************************************************************/
/* HOOK 打开商店和任务对话ID地址(注入立刻HOOK)                          */
/************************************************************************/
const int HOOK_SHOP_TALK_ADDR_OFFSET = 0x0005830F; //HOOK地址
/************************************************************************/
/* NPC 任务对话（二级）                                                 */
/************************************************************************/
const int NPC_TALK_SUB_CALL_ECX_OFFSET = 0x00282490; //任务二级对话CALL ECX偏移
const int NPC_TALK_SUB_CALL_OFFSET = 0x0004FD60; //任务二级对话CALL偏移

/************************************************************************/
/* 背包相关                                                             */
/************************************************************************/
const int PACK_PERCEL_ARRAY_BASE_OFFSET = 0x29D710; //背包包裹数组基址(人物基址)
const int PACL_PERCEL_ARRAY_BIG_OFFSET = 0x6950;//背包包裹数组大偏移

/************************************************************************/
/* 使用物品CALL                                                         */
/************************************************************************/
const int USE_GOOD_CALL_ECX_OFFSET = 0x00282490; //使用物品CALL ECX偏移
const int USE_GOOD_CALL_OFFSET = 0x00048680; //使用物品CALL 偏移
const int USE_GOOD_CALL_STRUCT_CONST_OFFSET = 0x2759D4;//存放使用物品CALL 结构 第二个常量的值++

/************************************************************************/
/* 穿戴物品CALL                                                         */
/************************************************************************/
const int WEAR_GOOD_CALL_ECX_OFFSET = 0x00282490; //穿戴物品CALL ECX 偏移
const int WEAR_GOOD_CALL_OFFSET = 0x00047810; //穿戴物品CALL 偏移

/************************************************************************/
/* 轻功/跳CALL                                                          */
/************************************************************************/
const int ROLE_JMP_CALL_OFFSET = 0x00176810; //跳CALL
const int ROLE_DODGE_CALL_ECX_OFFSET = 0x00282490; //轻功CALL ECX 偏移
const int ROLE_DODGE_CALL_OFFSET = 0x00049760; //轻功CALL 偏移

/************************************************************************/
/* 取消打坐                                                             */
/************************************************************************/
const int CANCEL_SETDOWN_CALL_OFFSET = 0x00119A00; //取消打坐坐
/************************************************************************/
/* 按键CALL                                                             */
/************************************************************************/
const int KEY_CALL_ECX_BASE_OFFSET = 0x001A4F30; //按键CALL ECX 基址
const int KEY_CALL_ECX_BASE_BIG_OFFSET = 0x00000D68; //按键CALL 大偏移
const int KEY_CALL_OFFSET = 0x0005E330; //按键CALL 偏移

/************************************************************************/
/* 转向CALL                                                             */
/************************************************************************/
const int TRAN_CALL_ECX_BASE_OFFSET = 0x0018E9F0; //转向CALL ECX 计算偏移
const int TRAN_CALL_ECX_BIG_OFFSET = 0x0000D048; //转向CALL ECX 大偏移
const int TRAN_CALL_OFFSET = 0x0000389B; //转向CALL 偏移

/************************************************************************/
/* 销毁物品                                                             */
/************************************************************************/
const int DELETE_GOOD_CALL_ECX_OFFSET = 0x00282490; //销毁物品CALL ECX 计算偏移
const int DELETE_GOOD_CALL_OFFSET = 0x00047810; //销毁物品CALL 计算偏移

/************************************************************************/
/* 控件                                                                 */
/************************************************************************/
const int CONTROL_BASE_OFFSET = 0x275998;//控件基址偏移
const int CONTROL_BASE_BIG_OFFSET = 0x4E0;//控件基址大偏移
const int CONTROL_BIG_OFFSET = 0xDAC;//控件遍历的大偏移
const int CONTROL_TOP_ARRAY_PER = 0x160;//最外部的10个长度的数组每个数组的间隔大小


/************************************************************************/
/*轻功CALL HOOK地址                                                     */
/************************************************************************/
const int DODGE_HOOK_1 = 0x00178D00; //轻功修改地址1(0x55 改为 0C2 0x4 0x00)
const int DODGE_HOOK_2 = 0x001176C3; //轻功修改地址2(0x75 改为 0xEB)

/************************************************************************/
/* 二级对话CALL第一参数计算                                             */
/************************************************************************/
const int TASK_SUB_TALK_PRARTM_BASE_OFFSET = 0x001A4F30; //二级对话CALL第一参数计算 基址偏移
const int TASK_SUB_TALK_PRARTM_OFFSET_1 = 0x000008F8; //二级对话CALL第一参数计算 第一级偏移
const int TASK_SUB_TALK_PRARTM_OFFSET_2 = 0x0000003C; //二级对话CALL第一参数计算 第二级偏移

/************************************************************************/
/* 图内寻路CALL                                                         */
/************************************************************************/
const int MAP_IN_RUN_TO_CALL_ECX_OFFSET = 0x00282490; //图内寻路CALL ECX 偏移
const int MAP_IN_RUN_TO_CALL_OFFSET = 0x0004CFE0; //图内寻路CALL 偏移

/************************************************************************/
/* 切换内功                                                             */
/************************************************************************/
const int CHANGE_KUNG_FU_CALL_ECX_OFFSET = 0x00282490; //切换内功CALL ECX 偏移
const int CHANGE_KUNG_FU_CALL_OFFSET = 0x0004BEA0; //切换内功CALL 偏移

/************************************************************************/
/* 交互CALL                                                             */
/************************************************************************/
const int INTERACTIVE_CALL_ECX_OFFSET = 0x00282490; //交互CALL ECX 偏移
const int INTERACTIVE_CALL_OFFSET = 0x0004CA60; //交互CALL 偏移
const int INTERAVTIVE_CONST_BASE_OFFSET = 0x0029D768; //交互CALL 常量基址
const int INTERACTIVE_CONST_OFFSET_1 = 0x000011A0; //交互CALL常量偏移1
const int INTERACTIVE_CONST_OFFSET_2 = 0x0000F004; //交互CALL常量偏移2
/************************************************************************/
/* 获取全部修理价格CALL                                                 */
/************************************************************************/
const int REPAIR_PRICE_CALL_OFFSET = 0x00107B00; //获取全部修理价格CALL 偏移
/************************************************************************/
/* 修理全部装备                                                         */
/************************************************************************/
const int REPAIR_WEAR_CALL_ECX_OFFSET = 0x00282490; //修理全部装备CALL ECX 偏移
const int REPAIR_WEAR_CALL_OFFSET = 0x0004DE50; //修理全部装备CALL 偏移
/************************************************************************/
/* 技能二叉/技能升级/获取技能升级修为                                   */
/************************************************************************/
const int SKILL_TERR_OFFSET = 0x00005318; //技能二叉树大偏移
const int SKILL_UP_CALL_ECX_OFFSET = 0x00282490; //升级技能CALL ECX偏移
const int SKILL_UP_CALL_OFFSET = 0x00046F80; //升级技能CALL 偏移
/************************************************************************/
/* 定点释放技能                                                         */
/************************************************************************/
const int SKILL_MAKE_POINT_CALL_OFFSET = 0x0010F880;//定点释放技能CALL 偏移
/************************************************************************/
/* 奇穴设置                                                             */
/************************************************************************/
const int SPECIL_SET_CALL_ECX_OFFSET = 0x00282490;//奇穴设置CALL ECX 偏移
const int SPECIL_SET_CALL_OFFSET = 0x0004D250; //奇穴设置CALL 偏移
/************************************************************************/
/* 机关任务CALL                                                         */
/************************************************************************/
const int CALL_ORGAN_CALL_ECX_OFFSET = 0x00282490; //机关任务CALL ECX偏移
const int CALL_ORGAN_CALL_OFFSET = 0x0004FD60; //机关任务CALL偏移
/************************************************************************/
/* 判断怪物视野                                                         */
/************************************************************************/
const int CALL_MONSTER_VIEW = 0x000CFAE0; //判断怪物是否在视野内
/************************************************************************/
/* 对象类型CALL                                                         */
/************************************************************************/
const int CALL_TYPE_RET = 0x0011C1E0; //判断对象类型CALL 偏移
/************************************************************************/
/* 使用礼包                                                             */
/************************************************************************/
const int CALL_USE_PACKET_CALL_ECX_OFFSET = 0x00282490; //使用礼包CALL ECX 偏移
const int CALL_USE_PACKET_CALL_OFFSET = 0x0004C000; //使用礼包CALL 偏移
/************************************************************************/
/* 获取物品价格CALL                                                     */
/************************************************************************/
const int GOOD_PRICE_CALL_OFFSET = 0x00107CF0; //获取价格CALL 偏移
/************************************************************************/
/* 卖物品CALL                                                           */
/************************************************************************/
const int SELL_GOOD_CALL_ECX_OFFSET = 0x00282490; //卖物品CALL ECX 偏移
const int SELL_GOOD_CALL_OFFSET = 0x0004DEA0; //卖物品CALL 偏移
/************************************************************************/
/* 过图CALL																*/
/************************************************************************/
const int PASS_MAP_CALL_ECX_OFFSET = 0x00282490; //过图CALL ECX 偏移
const int PASS_MAP_CALL_OFFSET = 0x0004D1F0; //过图CALL 偏移