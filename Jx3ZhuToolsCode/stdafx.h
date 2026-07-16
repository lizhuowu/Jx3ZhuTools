// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>

#include "include\\luah.h"

#include <Psapi.h>
#include <Userenv.h>
#include <DbgHelp.h>
#include <tlhelp32.h>
#include <string>
using namespace std;

#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Dbghelp.lib")
#include "Global.h"
#include "GameStruct.h"
#include "CGameWndProc.h"
#include "CLua.h"
#include "CObjectBase.h"//对象基本
#include "HOOK.h"
#include "CCommon.h"
#include "CUserConfig.h"
#include "CSocketCmd.h"


static CCGameWndProc *_CCGameWndProc = CCGameWndProc::Instantialize();
static CCLua _Clua;//全局使用的LUA类对象
static HOOK _HOOK;//全局使用的HOOK类对象
static CCCommon _CCCommon;//全局使用的CCCommon类对象
static CCSocketCmd _CCSocketCmd;//通讯

//自定义消息
//鼠标寻路
#define MOVETO					WM_USER + 201
//选择怪物
#define SELECT_MONSTER			WM_USER + 202
//使用技能
#define SKILL					WM_USER + 203
//采集
#define ACQUITST					WM_USER + 204
//拾取物品
#define PICKUPGOOD					WM_USER + 205
//封包接任务
#define ACCPET_TASK_BUFFER					WM_USER + 206
//封包交任务
#define FINSH_TASK_BUFFER					WM_USER + 207
//NPC对话
#define OPEN_NPC					WM_USER + 208
//买东西
#define BUY_GOOD					WM_USER + 209
//打开商店CALL
#define OPEN_SHOP					WM_USER + 210
//NPC二级对话
#define NPC_TASK_TALK_SUB			WM_USER + 211
//使用物品
#define USE_GOOD					WM_USER + 212
//穿戴物品
#define WEAR_GOOD					WM_USER + 213
//拾取金币
#define PICKUPGLOD					WM_USER + 214
//跳CALL
#define ROLEJMP					WM_USER + 215
//轻功CALL
#define ROLEDODGE				WM_USER + 216
//取消打坐CALL
#define CANCEL_SET_DOWN				WM_USER + 217
//按键CALL(F UP)
#define KEY_ACTION_F_UP				WM_USER + 218
//转向CALL
#define TRAN_ACTION				WM_USER + 219
//销毁物品CALL
#define DISTORY_GOOD			WM_USER + 220
//退出组队
#define QUIT_TEAM_MESSAGE			WM_USER + 221
//发起组队
#define REQUEST_TEAM_MESSAGE		WM_USER + 222
//接受组队
#define RESPONSE_TEAM_MESSAGE		WM_USER + 223
//按键CALL(F DOWN)
#define KEY_ACTION_F_DOWN				WM_USER + 224
//按键CALL(ESC UP)
#define KEY_ACTION_ESC_UP				WM_USER + 225
//按键CALL(ESC DOWN)
#define KEY_ACTION_ESC_DOWN				WM_USER + 226
//图内寻路
#define MAP_IN_RUN_TO					WM_USER + 227
//按键CALL（SPACE DOWN）
#define KEY_ACTION_SPACE_DOWN			WM_USER + 228
//按键CALL（SPACE UP）
#define KEY_ACTION_SPACE_UP			WM_USER + 229
//切换内功
#define CHANGE_KUNG_FU				WM_USER + 230
//交互
#define  INTERAVTIVE				WM_USER + 231
//获取修理价格
#define  GET_REPAIR_PRICE			WM_USER + 232
//修理全部装备
#define  REPAIR_WEAR				WM_USER + 233
//升级技能
#define  SKILL_UP_LEVEL				WM_USER + 234
//定点使用技能
#define  SKILL_MAKE_POINT			WM_USER + 235
//奇穴设置
#define  SPECIL_SET					WM_USER + 236
//机关任务移动
#define  ORGAN_RUN_MOVE				WM_USER + 237
//怪物视野
#define  MONSTER_VIEW				WM_USER + 238
//对象类型
#define	 OBJECT_TYPE_RET			WM_USER + 239
//装备千机
#define	 WEAR_THOUSANDS				WM_USER + 240
//放弃任务
#define	 DELETE_TASK_BUFFER			WM_USER + 241
//神行千里
#define	 SHEN_XING_QIN_LI			WM_USER + 242
//装备马匹
#define	 WEAR_HORSE					WM_USER + 243
//装备马匹
#define	 USE_PACKET					WM_USER + 244
//获取物品价格
#define	 GET_GOOD_PRICE				WM_USER + 245
//卖物品
#define	 SELL_GOOD					WM_USER + 246
//封包交任务，选物品
#define FINSH_TASK_BUFFER_EX		WM_USER + 247
//刷木童
#define INTERAVTIVE_SHUA_MUTONG		WM_USER + 248
//登高
#define INTERAVTIVE_DENGGAO			WM_USER + 249
//过图CALL
#define MAP_CHANGE_MOVE			WM_USER + 251