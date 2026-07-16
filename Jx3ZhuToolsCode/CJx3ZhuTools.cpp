// CJx3ZhuTools.cpp : 实现文件
//

#include "stdafx.h"
#include "Jx3ZhuToolsCode.h"
#include "CJx3ZhuTools.h"
#include "afxdialogex.h"
#include <string>
using namespace std;
#include "CUserInfo.h"
#include "CMonsterInformation.h"
#include "CMonsterTree.h"
#include "CGroundInfo.h"
#include "CGroundTree.h"
#include "CTaskHasIDs.h"
#include "CCall.h"

// CCJx3ZhuTools 对话框

IMPLEMENT_DYNAMIC(CCJx3ZhuTools, CDialogEx)

CCJx3ZhuTools::CCJx3ZhuTools(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCJx3ZhuTools::IDD, pParent)
{

}

CCJx3ZhuTools::~CCJx3ZhuTools()
{
}

void CCJx3ZhuTools::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, M_COMBOX_LUA);
}


BEGIN_MESSAGE_MAP(CCJx3ZhuTools, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCJx3ZhuTools::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCJx3ZhuTools::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCJx3ZhuTools::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCJx3ZhuTools::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCJx3ZhuTools::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCJx3ZhuTools::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCJx3ZhuTools::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCJx3ZhuTools::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCJx3ZhuTools::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CCJx3ZhuTools::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CCJx3ZhuTools::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CCJx3ZhuTools::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CCJx3ZhuTools::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CCJx3ZhuTools::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CCJx3ZhuTools::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CCJx3ZhuTools::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CCJx3ZhuTools::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CCJx3ZhuTools::OnBnClickedButton18)
	ON_MESSAGE(WM_HOTKEY,OnHotKey) //(此行为加入的)
//	ON_WM_PAINT()
//	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()
BOOL isHide = FALSE;
BOOL CCJx3ZhuTools::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	RegisterHotKey(m_hWnd,1001,MOD_CONTROL|MOD_ALT,'X');
	RegisterHotKey(m_hWnd,1002,MOD_CONTROL|MOD_ALT,'x');
	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);//从任务栏中去掉.
	LoadLuaScript();
	return TRUE;  // return TRUE unless you set the focus to a control
}

//void CCJx3ZhuTools::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if ((nID & 0xFFF0) == SC_CLOSE)
//	{
//		//this->ShowWindow(SW_HIDE);
//	}
//	CDialogEx::OnSysCommand(nID, lParam);
//}

BOOL CCJx3ZhuTools::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	UnregisterHotKey( m_hWnd, 1001); 
	UnregisterHotKey( m_hWnd, 1002); 
	return CDialogEx::DestroyWindow();
}
CString GetRootPath ()
{
	char szPathTemp[512];
	CString RootPath;

	GetModuleFileName(GetModuleHandle("Jx3ZhuToolsCode.dll"), szPathTemp, 512);//取模块运行路径
	for (int i=strlen(szPathTemp); i>=0; i--)   //////去掉模块名，保存最终路径
	{    if (szPathTemp[i] == '\\')  
	{   
		szPathTemp[i] = '\0'; 
		break;
	}
	}
	RootPath = szPathTemp;
	RootPath = RootPath + "\\Script";
	return RootPath;
}

///热键
LRESULT CCJx3ZhuTools::OnHotKey(WPARAM wParam,LPARAM lParam)

{

	if(wParam == 1001 || wParam == 1002)

	{
		if (isHide==TRUE)
		{
			//显示窗口
			this->ShowWindow(SW_SHOW);
			isHide =FALSE;
		}else if(isHide==FALSE)
		{
			//隐藏窗口
			this->ShowWindow(SW_HIDE);
			isHide = TRUE;
		}
	}

	return true;

}
//////////系统功能区/////////
void FindLuaScript(vector<CString>& sFileNames)

{

	WIN32_FIND_DATAA file;
	HANDLE hFile;
	CString filePath, cc;
	BOOL fileCunzai = true;
	CString RootPath =  GetRootPath ();
	filePath = RootPath + "\\*.*";
	hFile = FindFirstFile (filePath, &file);

	while(INVALID_HANDLE_VALUE != hFile && fileCunzai == TRUE)  ////取目录内所有脚本名称

	{
		sFileNames.push_back(file.cFileName);
		fileCunzai = FindNextFile(hFile, &file);
	}
}
// CCJx3ZhuTools 消息处理程序
//加载lua脚本
void CCJx3ZhuTools::LoadLuaScript()
{
	int pathShu, pathXia;
	vector<CString > filePath;
	FindLuaScript (filePath); /////寻找运行目录内的所有脚本文件
	pathShu = filePath.size ();
	M_COMBOX_LUA.ResetContent();
	for (pathXia = 2; pathXia < pathShu; pathXia++)
	{
		M_COMBOX_LUA.AddString (filePath[pathXia]);   /////脚本列表框内增加脚本名
	}
	M_COMBOX_LUA.SetCurSel (0);
	filePath.clear ();
}
HANDLE ScriptThreadID = NULL;
CCLua __CCLua;
DWORD WINAPI LuaRunScript (PVOID pParam)
{
	CCJx3ZhuTools *p = (CCJx3ZhuTools*)pParam;
	CString ScriptName;
	int ScriptIndex = p->M_COMBOX_LUA.GetCurSel ();  //取脚本列表当前选中项索引
	p->M_COMBOX_LUA.GetLBText (ScriptIndex, ScriptName);  //取脚本列表内选中脚本名
	CString RootPath =  GetRootPath ();
	RootPath = RootPath + "\\";
	RootPath = RootPath + ScriptName;
	__CCLua.Lua_DoFile(RootPath);
	return TRUE;
}
//执行LUA
void CCJx3ZhuTools::OnBnClickedButton1()
{
	if (ScriptThreadID)
	{
		TerminateThread(ScriptThreadID, 0);
	}
	__CCLua = _Clua;
	ScriptThreadID = ::CreateThread(NULL,0,LuaRunScript,this,0,0);
}

void CCJx3ZhuTools::OnBnClickedButton11()
{
	if (ScriptThreadID)
	{
		TerminateThread(ScriptThreadID,0);
		WaitForSingleObject(ScriptThreadID,INFINITE);
		//至此，线程本身和线程ID消失
		CloseHandle(ScriptThreadID);
		//至此，线程句柄消失
	}
}


//刷新脚本列表
void CCJx3ZhuTools::OnBnClickedButton2()
{
	LoadLuaScript();
}

/************************************************************************/
/* 测试信息                                                             */
/************************************************************************/
void CCJx3ZhuTools::OnBnClickedButton3()
{
	CCUserInfo _CCUserInfo;
	CString strAddrName;
	strAddrName.Format("人物名称:%s,%s ,坐标：%d,%d,%d 血:%d/%d 等级：%d\r\n",_CCUserInfo.getObjectName().c_str(),_CCUserInfo.getObjectNameEx(),_CCUserInfo.getObjectPointX(),_CCUserInfo.getObjectPointY(),_CCUserInfo.getObjectPointZ(),_CCUserInfo.getObjectCurrentBlood(),_CCUserInfo.getObjectMaxBlood(),_CCUserInfo.getObjectLevel());
	SetDlgItemText(IDC_EDIT_MESSAGE,strAddrName);
}

DWORD GetMissonNameAdderss()
{
	MEMORY_BASIC_INFORMATION AdderssInfo;
	CString MissonName;
	DWORD MissonNameAdderss = 0;
	int a;
	DWORD StartAdderss = 0x20DD0000;
	a = VirtualQuery ((LPCVOID)StartAdderss,&AdderssInfo,sizeof(AdderssInfo));
	if(a != 0)
	{
		while(AdderssInfo.RegionSize != 0x14b000)
		{
			StartAdderss = StartAdderss + 0x10000;
			VirtualQuery ((LPCVOID)StartAdderss,&AdderssInfo,sizeof(AdderssInfo));
			if(AdderssInfo.RegionSize == 0x14B000)
			{
				break;
			}
		}
		MissonNameAdderss = (DWORD)AdderssInfo.BaseAddress + 0x12c;
	}else{}
	return MissonNameAdderss;
}
//获取任务名称地址
void CCJx3ZhuTools::OnBnClickedButton4()
{
	DWORD sss = GetMissonNameAdderss();
	CString strAddrName;
	strAddrName.Format("任务名称地址：%08X",sss);
	SetDlgItemText(IDC_EDIT_MESSAGE,strAddrName);
}


void CCJx3ZhuTools::OnBnClickedButton5()
{
	CCMonsterTree _CMonsterTree;
	int size = _CMonsterTree.Size();
	if(size > 0)
	{
		CString allMsg;
		CString strMsg;
		for(int i = 0;i< size;i++)
		{
			CCMonsterInformation _CCMonsterInformation = _CMonsterTree.GetMonsterInformation(i);
			strMsg.Format("地址：0x%08X,对象地址:%08X,名称：%s,称号：%s,ID:%d(0x%04X) 血量：%d/%d ,坐标:[%d,%d] ,距离：%d\r\n",_CCMonsterInformation.getTreeAddr(),_CCMonsterInformation.getObjectAddr(),_CCMonsterInformation.getMonsterName(),_CCMonsterInformation.getMonsterTitle(),_CCMonsterInformation.getMonsterID(),_CCMonsterInformation.getMonsterID(),_CCMonsterInformation.getMonsterCurrentBlood(),_CCMonsterInformation.getMonsterMaxBlood(),_CCMonsterInformation.getMonsterX(),_CCMonsterInformation.getMonsterY(),_CCMonsterInformation.getMonsterDsc());
			allMsg = allMsg + strMsg; 
		}
		SetDlgItemText(IDC_EDIT_MESSAGE,allMsg);
	}
}


void CCJx3ZhuTools::OnBnClickedButton6()
{
	CCGroundTree _CCGroundTree;
	int size = _CCGroundTree.Size();
	if(size > 0)
	{
		CString allMsg;
		CString strMsg;
		for(int i = 0;i< size;i++)
		{
			CCGroundInfo _CCGroundInfo = _CCGroundTree.GetGroundInformation(i);
			strMsg.Format("Tree:0x%08X,ID:0x%08X名称：%s,ID:%d ,坐标:[%d,%d] ,距离：%d\r\n",_CCGroundInfo.getTreeAddr(),_CCGroundInfo.getObjectAddr(),_CCGroundInfo.getGroundName(),_CCGroundInfo.getGroundGoodID(),_CCGroundInfo.getGroundGoodX(),_CCGroundInfo.getGroundGoodY(),_CCGroundInfo.getGroundDsc());
			allMsg = allMsg + strMsg; 
		}
		SetDlgItemText(IDC_EDIT_MESSAGE,allMsg);
	}else
	{
		SetDlgItemText(IDC_EDIT_MESSAGE,"无信息");
	}
}


void CCJx3ZhuTools::OnBnClickedButton7()
{
	CCTaskHasIDs _CCTaskHasIDs;
	int size = _CCTaskHasIDs.getCount();
	if(size > 0)
	{
		CString allMsg;
		CString strMsg;
		for(int i = 0;i< size;i++)
		{
			int TaskID = _CCTaskHasIDs.getAddrByIndex(i);
			strMsg.Format("任务ID：%d - 0x%08X\r\n",TaskID,TaskID);
			allMsg = allMsg + strMsg; 
		}
		SetDlgItemText(IDC_EDIT_MESSAGE,allMsg);
	}
}


void CCJx3ZhuTools::OnBnClickedButton8()
{
	/*struct AL_STRUCT _AL_STRUCT;
	_AL_STRUCT.Param1 = 2;
	CCCall _CCCall;
	_CCCall.CALL_GET_SHOP_ADDRA_BY_ID(&_AL_STRUCT);
	CString strMsg;
	strMsg.Format("地址:0x%08X\r\n",_AL_STRUCT.Param2);
	SetDlgItemText(IDC_EDIT_MESSAGE,strMsg);*/
}


void CCJx3ZhuTools::OnBnClickedButton9()
{
	CCPlayerTree _CCPlayerTree;
	int size = _CCPlayerTree.Size();
	if(size > 0)
	{
		CString allMsg;
		CString strMsg;
		for(int i = 0;i< size;i++)
		{
			CCPlayerInfomation _CCPlayerInfomation = _CCPlayerTree.GetPlayerInformation(i);
			strMsg.Format("地址：0x%08X,名称：%s,ID:%d(0x%04X),坐标:[%d,%d] ,距离：%d\r\n",_CCPlayerInfomation.getTreeAddr(),_CCPlayerInfomation.getPlayerName(),_CCPlayerInfomation.getPlayerALLID(),_CCPlayerInfomation.getPlayerALLID(),_CCPlayerInfomation.getPlayerX(),_CCPlayerInfomation.getPlayerY(),_CCPlayerInfomation.getPlayerDsc());
			allMsg = allMsg + strMsg; 
		}
		SetDlgItemText(IDC_EDIT_MESSAGE,allMsg);
	}
}

CString messageAll;

/************************************************************************/
/* 控件测试                                                             */
/************************************************************************/
void CCJx3ZhuTools::OnBnClickedButton10()
{
	messageAll = "";
	int ClientBase = (int)_CCGameWndProc->GetGameModuleAddr();
	int BaseControl = ClientBase + CONTROL_BASE_OFFSET;
	BaseControl = *(int *)BaseControl;
	BaseControl = *(int *)(BaseControl + CONTROL_BASE_BIG_OFFSET);
	if (IsReadAddrInt((PVOID)(BaseControl + 0x4)))
	{
		int FirstEcx = *(int *)(BaseControl + 0x4);
		FirstEcx = FirstEcx + 0xDAC;
		int FirstEdi = FirstEcx + 0x60;
		int Count = 0xA;
		int CurrnetEdi = 0;
		for (int i = 0;i < Count ; i++)
		{
			CurrnetEdi = FirstEdi + i *0x160;
			if (IsReadAddrInt((PVOID)CurrnetEdi))
			{
				unsigned int _Eax = *(unsigned int *)(CurrnetEdi);
				if (!(_Eax & 0x4000000) && _Eax & 0x80008000)
				{
					int ObjectEsi = 0;
					if (IsReadAddrInt((PVOID)(CurrnetEdi +0x10)))
					{
						ObjectEsi = *(int *)(CurrnetEdi +0x10);
						if (IsReadAddrInt((PVOID)ObjectEsi))
						{
							float F_P_F_1 = *(float *)(ObjectEsi + 0x4);
							float F_P_F_2 = *(float *)(ObjectEsi + 0x8);
							float F_P_S_1 = *(float *)(ObjectEsi + 0xC);
							float F_P_S_2 = *(float *)(ObjectEsi + 0x10);
							float F_P_T_1 = *(float *)(ObjectEsi + 0x14);
							float F_P_T_2 = *(float *)(ObjectEsi + 0x18);
							int _ControlType = *(int *)(ObjectEsi + 0x1C);
							char ControlTxt[255] = {0};
							strcpy_s(ControlTxt,(char *)(ObjectEsi+0x20));
							CString currentStr;
							currentStr.Format("地址：%08X,坐标1:[%0.1f,%0.1f],坐标2:[%0.1f,%0.1f],坐标3:[%0.1f,%0.1f] 类型：【%d】,Txt:%s\r\n",
								ObjectEsi,F_P_F_1,F_P_F_2,F_P_S_1,F_P_S_2,F_P_T_1,F_P_T_2,_ControlType,ControlTxt);
							messageAll = messageAll + currentStr;
							SubControl(ObjectEsi,1);
							//自循环
							int CmpEcx = *(int *)(ObjectEsi + 0x64);
							while (CmpEcx > 0)
							{
								SubControl(CmpEcx,1);
								CmpEcx = *(int *)(CmpEcx + 0x64);
							}
						}
					}
				}
			}else
			{
				CString addr;
				addr.Format("address = %08X 错误地址1\r\n",CurrnetEdi);
				messageAll = messageAll + addr;
			}
		}
	}else
	{
		AfxMessageBox("(BaseControl + 0x4) Error Address");
	}	
	SetDlgItemText(IDC_EDIT_MESSAGE,messageAll);
}
//递归遍历子控件
void CCJx3ZhuTools::SubControl(int BaseAddr,int Level)
{
	if (IsReadAddrInt((PVOID)BaseAddr))
	{
		unsigned int _Eax = *(unsigned int *)(BaseAddr +0x60);
		if (!(_Eax & 0x4000000) && _Eax & 0x80008000)
		{
			//遍历信息
			float F_P_F_1 = *(float *)(BaseAddr + 0x4);
			float F_P_F_2 = *(float *)(BaseAddr + 0x8);
			float F_P_S_1 = *(float *)(BaseAddr + 0xC);
			float F_P_S_2 = *(float *)(BaseAddr + 0x10);
			float F_P_T_1 = *(float *)(BaseAddr + 0x14);
			float F_P_T_2 = *(float *)(BaseAddr + 0x18);
			int _ControlType = *(int *)(BaseAddr + 0x1C);
			char ControlTxt[255] = {0};
			strcpy_s(ControlTxt,(char *)(BaseAddr+0x20));
			CString currentStr;
			CString space_count;
			if (Level==2)
			{
				space_count = "     [Sub_Details]";
			}else
			{
				space_count="";
			}
			currentStr.Format("        %sSub - 地址：%08X,坐标1:[%0.1f,%0.1f],坐标2:[%0.1f,%0.1f],坐标3:[%0.1f,%0.1f] 类型：【%d】,Txt:%s\r\n",
				space_count.GetBuffer(),BaseAddr,F_P_F_1,F_P_F_2,F_P_S_1,F_P_S_2,F_P_T_1,F_P_T_2,_ControlType,ControlTxt);
			messageAll = messageAll + currentStr;
			ShowDetails(BaseAddr);
			int CmpAddr = *(int *)(BaseAddr + 0x70);
			if (CmpAddr > 0)
			{
				ShowDetails(CmpAddr);
				SubControl(CmpAddr,2);
				//自循环
				int CmpEcx = *(int *)(CmpAddr + 0x64);
				while (CmpEcx > 0)
				{
					//ShowDetails(CmpAddr);
					SubControl(CmpEcx,2);
					CmpEcx = *(int *)(CmpEcx + 0x64);
				}
			}
		}
	}
}
//获取详细控件信息
void CCJx3ZhuTools::ShowDetails(int	BaseAddr)
{
	if (IsReadAddrInt((PVOID)BaseAddr))
	{
		int StartAddr = *(int *)(BaseAddr + 0x80);
		int EndAddr = *(int *)(BaseAddr + 0x84);
		if (StartAddr > 0 && EndAddr > 0 && StartAddr < EndAddr)
		{
			while (StartAddr < EndAddr)
			{
				int NameStart = *(int *)StartAddr;
				char ControlTxt[255] = {0};
				strcpy_s(ControlTxt,(char *)(NameStart+0x70));
				int ShowNameAddr1 = *(int *)(NameStart + 0xFC);
				ShowNameAddr1 = ShowNameAddr1 << 6;//左移6位
				int ShowNameAddr2 = *(int *)(NameStart + 0x128);
				ShowNameAddr1 = ShowNameAddr1 + ShowNameAddr2;
				wchar_t ControlNameTxt[255] = {0};
				if (IsReadAddrInt((PVOID)ShowNameAddr1))
				{
					if (IsReadAddrInt((PVOID)(ShowNameAddr1+0x38)))
					{
						int AddrName = *(int *)(ShowNameAddr1+0x38);
						if (IsReadAddrInt((PVOID)AddrName))
						{
							wcsncpy_s(ControlNameTxt,(wchar_t *)(AddrName),250);
							char *CharNameTxt = UnicodeToGB2312(ControlNameTxt);
							CString currentStr;
							currentStr.Format("                     地址:%08X, Txt: %s ,NameAddr = %08X, NameTxt: %s\r\n",NameStart,ControlTxt,ShowNameAddr1,CharNameTxt);
							messageAll = messageAll + currentStr;
						}else
						{
							CString currentStr;
							currentStr.Format("                     地址:%08X, Txt: %s \r\n",NameStart,ControlTxt);
							messageAll = messageAll + currentStr;
						}
					}else
					{
						CString currentStr;
						currentStr.Format("                     地址:%08X, Txt: %s \r\n",NameStart,ControlTxt);
						messageAll = messageAll + currentStr;
					}
					
				}else
				{
					CString currentStr;
					currentStr.Format("                     地址:%08X, Txt: %s \r\n",NameStart,ControlTxt);
					messageAll = messageAll + currentStr;
				}
				StartAddr = StartAddr + 0x4;//递增4
			}
		}
	}
}




void CCJx3ZhuTools::OnBnClickedButton12()
{
	CString aaa;
	GetDlgItemTextA(IDC_EDIT_i,aaa);
	 CCCall _CCCall;
	 _CCCall.CALL_ACQUIST( _ttoi(aaa.GetBuffer()));
}


void CCJx3ZhuTools::OnBnClickedButton13()
{
	CCRoleWear _CCRoleWear;
	CCPackArray _CCPackArray(_CCRoleWear.getAddr());
	int Count = _CCPackArray.getCount();
	CString all;
	CString strMsg;
	strMsg.Format("Addr = %08X\r\n",_CCRoleWear.getAddr());
	all = all + strMsg;
	for (int i = 0;i<Count;i++)
	{
		int Addr = _CCPackArray.getAddrByIndex(i);
		if (Addr > 0)
		{
			CCPackObject _CCPackObject(Addr);
			strMsg.Format("Addr = %08X ,索引：%d,名称：%s,ID:%d,类别：%d \r\n",Addr,i,_CCPackObject.getGoodName(),_CCPackObject.getGoodID(),_CCPackObject.getMakeGoodType());
			all = all + strMsg;
		}
	}
	/*int AllPrice = _CCCommon.GetAllPrice();
	CString price;
	price.Format("修理总价格：%d \r\n",AllPrice);
	all = all + price;*/
	SetDlgItemText(IDC_EDIT_MESSAGE,all);
}


void CCJx3ZhuTools::OnBnClickedButton14()
{
	CString HookTextStr ="";
	HookTextStr.Format("Handle = %08X , str = %s",TALK_ID,HOOKText.c_str());
	SetDlgItemText(IDC_EDIT_MESSAGE,HookTextStr);
}


void CCJx3ZhuTools::OnBnClickedButton15()
{
	CString aaa;
	GetDlgItemTextA(IDC_EDIT_i,aaa);
	CCCall _CCCall;
	_CCCall.CALL_ORGAN_MOVE( _ttoi(aaa.GetBuffer()));
}


void CCJx3ZhuTools::OnBnClickedButton16()
{
	if (HOOKText == "HOOKTEXT")
	{
		OutputDebugString("机关任务失败，请先打开NPC对话!");
		return;
	}
	int weizhi1 = 0, weizhi2 = 0;
	int a[3] = {0, 0, 0}, b[3] = {0, 0, 0}, c[3] = {0, 0, 0}, d[4] = {0, 0, 0}, i = 0;
	string tmp_Str = "";
	if (HOOKText != "HOOKTEXT") 
	{
		for (i = 0; i < 9; i++)
		{
			weizhi1 = HOOKText.find ("T ", weizhi1);
			weizhi2 = HOOKText.find (">", weizhi1 + 2);
			tmp_Str = HOOKText.substr (weizhi1 + 2, weizhi2 - weizhi1 - 2);
			weizhi1++;
			if (tmp_Str == "")
			{
				break;
			}
			switch (i)
			{
			case 0:{
				a[0] = _ttoi (tmp_Str.c_str());
				break;
				   }

			case 1: {
				a[1] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 2: {
				a[2] = _ttoi (tmp_Str.c_str());
				break;
					}
			case 3: {
				b[0] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 4: {
				b[1] = _ttoi (tmp_Str.c_str());
				break;
					}
			case 5: {
				b[2] = _ttoi (tmp_Str.c_str());
				break;
					}
			case 6: {
				c[0] = _ttoi (tmp_Str.c_str());
				break;
					 }
			case 7: {
				c[1] = _ttoi (tmp_Str.c_str());
				break;
					}
			case 8: {
				c[2] = _ttoi (tmp_Str.c_str());
				break;
					}
			default: break;
			}

		}

		CString allaa;


		CString aaa;
		aaa.Format ("a：%d,%d,%d \r\n", a[0], a[1], a[2]);
		allaa = allaa + aaa;


		CString bbb;
		bbb.Format ("b：%d,%d,%d\r\n", b[0], b[1], b[2]);
		allaa = allaa + bbb;


		CString ccc;
		ccc.Format ("c：%d,%d,%d\r\n", c[0], c[1], c[2]);
		allaa = allaa + ccc;

		SetDlgItemText(IDC_EDIT_MESSAGE,allaa);
	}
}


void CCJx3ZhuTools::OnBnClickedButton17()
{
	CString all;
	CString strMsg;
	CCPackPercelArray _CCPackPercelArray;
	int count = _CCPackPercelArray.getCount();
	for (int i = 0;i<count;i++)
	{
		int Addr = _CCPackPercelArray.getAddrByIndex(i);
		if (Addr > 0)
		{
			CCPackArray _CCPackArray(Addr);
			int ArrayCount = _CCPackArray.getCount();
			for (int j = 0;j < ArrayCount;j++)
			{
				int  currentAddrPack = _CCPackArray.getAddrByIndex(j);
				if (currentAddrPack > 0)
				{
					CCPackObject _CCPackObject(currentAddrPack);
					strMsg.Format("currentAddrPack = %08X ,索引：%d,名称：%s,ID:%d,类别：%d ,总价：%d \r\n",currentAddrPack,i,_CCPackObject.getGoodName(),_CCPackObject.getGoodID(),_CCPackObject.getMakeGoodType(),_CCPackObject.getGoodAllPrice());
					all = all + strMsg;
				}
			}
		}
	}
	SetDlgItemText(IDC_EDIT_MESSAGE,all);
}

void CCJx3ZhuTools::OnBnClickedButton18()
{
	CString all;
	CString strMsg;
	CCSkillTree _CCSkillTree;
	int count = _CCSkillTree.LuaSize();
	for (int i = 0;i< count;i++)
	{
		int CurrentSkillAddr = _CCSkillTree.LuaGetSkillAddr(i);
		if (CurrentSkillAddr>0)
		{
			CCSkillObject _CCSkillObject(CurrentSkillAddr);
			strMsg.Format("树地址：%08X,对象地址:%08X ,名称：%s,技能ID:%08X,技能等级：%d \r\n",_CCSkillObject.getTreeAddr(),_CCSkillObject.getObjecteAddr(),_CCSkillObject.getSkillName(),_CCSkillObject.getSkillID(),_CCSkillObject.getSkillLevel());
			all = all + strMsg;
		}
	}
	SetDlgItemText(IDC_EDIT_MESSAGE,all);
}


//void CCJx3ZhuTools::OnSetFont(CFont* pFont)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	CDialogEx::OnSetFont(pFont);
//}

