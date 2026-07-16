#include "stdafx.h"
#include "HOOK.h"

void __declspec( naked ) callback()
{
	_asm 
	{
			pushad
			push ebx
			mov ebx, [edx+0x04]
			mov TALK_ID, ebx
			pop ebx
			push eax
			lea eax, [edx+0x10]
			mov TxtAddr, eax
			pop eax
	}
		HOOKText = (char*)TxtAddr;
	_asm 
	{
			popad
			push esi
			mov esi, [edx+0x8]
			push edi
			jmp [JmpAddr]
	}
}

HOOK::HOOK(void)
{

}
//HOOK方法
void HOOK::HOOKCall()
{
	int HookAddr = (int)_CCGameWndProc->GetGameModuleAddr() + HOOK_SHOP_TALK_ADDR_OFFSET;
	int HOOKLength = 5;
	DWORD old; 
	VirtualProtect((LPVOID)HookAddr,HOOKLength,PAGE_READWRITE,&old);
	int New = (int)callback-HookAddr-5;
	_try
	{
		*((byte*)(HookAddr)) = 0xE9;
		*((DWORD*)(HookAddr+1)) = New;
		JmpAddr = HookAddr + 5;
	}
	_except(1)
	{
		TRACE("HOOK商店任务对话失败!\r\n");
		return;
	}
	VirtualProtect((LPVOID)HookAddr,HOOKLength,old,&old);
	OutputDebugString("HOOK商店任务对话成功!\r\n");
}

HOOK::~HOOK(void)
{
}
