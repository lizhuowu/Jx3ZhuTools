#include "stdafx.h"
#include "CControlResponseTeam.h"


CCControlResponseTeam::CCControlResponseTeam(void)
{
	//初始化基址数据
	BASE_VALUE = 0;
	BASE_ADDR = 0;
	int BaseControl = (int)_CCGameWndProc->GetGameModuleAddr();

	BASE_ADDR = BaseControl + CONTROL_BASE_OFFSET;
	if (BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR) && IsReadAddrInt((PVOID)BASE_ADDR))
	{
		BASE_VALUE = *(int *)BASE_ADDR;
		if (BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR) && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_VALUE = *(int *)(BASE_ADDR + CONTROL_BASE_BIG_OFFSET);
		}else
		{
			OutputDebugString("初始化控件基址数据出错!");
		}
	}else
	{
		OutputDebugString("初始化控件基址数据出错!");
	}
}

CCControlResponseTeam::~CCControlResponseTeam(void)
{

}
//获取最后一个发起组队消息，并组队
void CCControlResponseTeam::GetLastTeamerAndResponse()
{
	if (IsReadAddrInt((PVOID)(BASE_VALUE + 0x4)))
	{
		int FirstEcx = *(int *)(BASE_VALUE + 0x4);
		FirstEcx = FirstEcx + CONTROL_BIG_OFFSET;
		int FirstEdi = FirstEcx + 0x60;
		int Count = 0xA;
		int CurrnetEdi = 0;
		for (int i = 0;i < Count ; i++)
		{
			CurrnetEdi = FirstEdi + i * CONTROL_TOP_ARRAY_PER;
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
							char ControlTxt[255] = {0};
							strcpy_s(ControlTxt,(char *)(ObjectEsi+0x20));
							string strControlTxt = ControlTxt;
							std::size_t found = strControlTxt.find("MB_IMTP_");
							if (found!=std::string::npos)
							{
								string FindStgr = "MB_IMTP_";
								//发起组队
								string PlayerName = strControlTxt.substr(FindStgr.length(),strControlTxt.length() - FindStgr.length());
								struct RESPONE_TETHER_TEAM __RESPONE_TETHER_TEAM = {0};
								strcpy_s(__RESPONE_TETHER_TEAM.PlayName,PlayerName.c_str());
								SendMessageA (g_hGameHandle,RESPONSE_TEAM_MESSAGE, 0, (LPARAM)&__RESPONE_TETHER_TEAM);
								break;
							}
						}
					}
				}
			}
		}
	}else
	{
		OutputDebugString("接受组队失败!");
	}	
}

