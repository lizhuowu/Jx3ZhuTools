
// Jx3ZhuToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Jx3ZhuTools.h"
#include "Jx3ZhuToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//---------------------------------------------------------
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



//---------------------------------------------------------
// CJx3ZhuToolsDlg 对话框

CJx3ZhuToolsDlg::CJx3ZhuToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJx3ZhuToolsDlg::IDD, pParent)
	, hideXspyWhenCapture_(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJx3ZhuToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJx3ZhuToolsDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CJx3ZhuToolsDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_SPY_START, &CJx3ZhuToolsDlg::OnSpyStart)
	ON_MESSAGE(WM_SPY, &CJx3ZhuToolsDlg::OnSpy)

END_MESSAGE_MAP()


// CJx3ZhuToolsDlg 消息处理程序

BOOL CJx3ZhuToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// init
	ui_capture_.SubclassDlgItem(IDC_STATIC1, this);

	ui_capture_.AddRecvWnd(m_hWnd); // 由主界面统一处理

	hideXspyWhenCapture_ = true;


	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJx3ZhuToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJx3ZhuToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJx3ZhuToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HWND hwndPointNow = NULL; 



/************************************************************************/
/* 提权                                                                  */
/************************************************************************/
int EnableDebugPriv(const char * name)
{
	HANDLE hToken;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken);    //获得进程本地唯一ID
	LUID luid;
	LookupPrivilegeValueA(NULL, name, &luid); // 打开进程令牌环
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;                            
	AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL); // 调整权限
	return 0;
}


void CJx3ZhuToolsDlg::OnBnClickedButton1()
{
	DWORD procssID = 0;
	GetWindowThreadProcessId(hwndPointNow, &procssID);
	if (procssID <= 0)
	{
		SetDlgItemText(IDC_STATIC_TITLE, _T("错误: 获取进程ID失败!"));
		SetDlgItemText(IDC_STATIC_HWND, _T(""));
		return;
	}
	//提权
	EnableDebugPriv((const char*)SE_DEBUG_NAME);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE, procssID);
	if (hProcess == NULL)
	{
		SetDlgItemText(IDC_STATIC_TITLE, _T("错误: 打开进程失败!"));
		SetDlgItemText(IDC_STATIC_HWND, _T(""));
		return;
	}

	//申请内存
	LPVOID lpDwordAlloc = VirtualAllocEx(hProcess, NULL, 256, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (lpDwordAlloc == 0)
	{
		SetDlgItemText(IDC_STATIC_TITLE, _T("错误: 申请内存失败!"));
		SetDlgItemText(IDC_STATIC_HWND, _T(""));
		CloseHandle(hProcess);
		return;
	}
	//dll 全局路径
	TCHAR szBuf[MAX_PATH];
	ZeroMemory(szBuf, MAX_PATH);
	GetCurrentDirectory(MAX_PATH, szBuf);
	CString path;
	path.Format("%s\\Jx3ZhuToolsCode.dll", szBuf);
	DWORD flags = 0;
	//写入内存
	WriteProcessMemory(hProcess, lpDwordAlloc, path.GetBuffer(), strlen(path.GetBuffer())+1, &flags);
	if(flags < strlen(path.GetBuffer()))
	{
		SetDlgItemText(IDC_STATIC_TITLE, _T("错误: 写入内存失败!"));
		SetDlgItemText(IDC_STATIC_HWND, _T(""));
		VirtualFreeEx(hProcess, lpDwordAlloc, 256, MEM_COMMIT);
		CloseHandle(hProcess);
		return;
	}

	HANDLE hCreateRemoteThread = CreateRemoteThread(hProcess,NULL,NULL,(LPTHREAD_START_ROUTINE)LoadLibraryA,lpDwordAlloc,NULL,NULL);
	WaitForSingleObject(hCreateRemoteThread,0xFFFFFF);
	VirtualFreeEx(hProcess, lpDwordAlloc, 256, MEM_COMMIT);
	CloseHandle(hCreateRemoteThread);
	CloseHandle(hProcess);

	return;
}


// 获取真实的顶层窗口
HWND CJx3ZhuToolsDlg::GetRealTopWindow(HWND hWnd)
{
	// 使用 GetAncestor 获取最顶层的拥有者窗口(GA_ROOT), 这比手动循环 GetParent 更准确，能正确处理弹出式窗口和子窗口.
	HWND hTop = ::GetAncestor(hWnd, GA_ROOT);
	return (hTop != NULL) ? hTop : hWnd;
}

LRESULT CJx3ZhuToolsDlg::OnSpyStart(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	if (hideXspyWhenCapture_)
		ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CJx3ZhuToolsDlg::OnSpy(WPARAM wParam, LPARAM /*lParam*/)
{
	// 拖拽结束后恢复窗口显示
	if (hideXspyWhenCapture_)
		ShowWindow(SW_SHOW);

	// 获取用户选中的目标窗口
	HWND hWnd = (HWND)wParam;
	if (hWnd == NULL || !::IsWindow(hWnd)) { MessageBeep(0); return 0; }
	if (hWnd == GetDlgItem(IDC_STATIC1)->GetSafeHwnd()) return 0;

	hwndPointNow = hWnd;

	// 获取窗口信息
	TCHAR szClass[256] = { 0 };
	TCHAR szTitle[256] = { 0 };
	::GetClassName(hWnd, szClass, 255);
	::GetWindowText(hWnd, szTitle, 255);

	CString strTitle;
	strTitle.Format(_T("标题: %s\r\n类名: %s"), szTitle, szClass);
	SetDlgItemText(IDC_STATIC_TITLE, strTitle);

	CString strHwnd;
	int id = ::GetDlgCtrlID(hWnd);
	if (id != 0)
	{
		strHwnd.Format(_T("窗口句柄: 0x%p\r\nID: %d (0x%X)"), hWnd, id, id);
	}
	else
	{
		strHwnd.Format(_T("窗口句柄: 0x%p\r\nID: N/A"), hWnd);
	}
	SetDlgItemText(IDC_STATIC_HWND, strHwnd);
	return 0;
}