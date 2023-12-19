
// dllhostDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "dllhost.h"
#include "dllhostDlg.h"
#include "afxdialogex.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdllhostDlg 对话框



CdllhostDlg::CdllhostDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLLHOST_DIALOG, pParent)
	, m_bunker_num(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CdllhostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BUNKER_NUM, m_bunker_num);
	DDV_MinMaxInt(pDX, m_bunker_num, 0, 999999);
	DDX_Control(pDX, IDC_STATUS_GODMOD, m_sGodMod);
}

BOOL CdllhostDlg::PreTranslateMessage(MSG * pMsg)
{
	//屏蔽ESC关闭窗体/
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	//屏蔽回车关闭窗体,但会导致回车在窗体上失效.
	//if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN && pMsg->wParam) return TRUE;
	else
		return CDialog::PreTranslateMessage(pMsg);
	return 0;
}

BEGIN_MESSAGE_MAP(CdllhostDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CdllhostDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CdllhostDlg 消息处理程序

BOOL CdllhostDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	// TODO: 在此添加额外的初始化代码
	//RegisterHotKey(this->m_hWnd, HOTKEY_BUNKER_PROFIT, MOD_CONTROL, VK_F1);
	//RegisterHotKey(this->m_hWnd, HOTKEY_GOD_MOD, MOD_CONTROL, VK_F3);
	//RegisterHotKey(this->m_hWnd, HOTKEY_TRANSFER, MOD_CONTROL, VK_F4);

	RegisterHotKey(this->m_hWnd, HOTKEY_BUNKER_PROFIT, MOD_SHIFT, VK_F1);
	RegisterHotKey(this->m_hWnd, HOTKEY_GOD_MOD, MOD_SHIFT, VK_F3);
	RegisterHotKey(this->m_hWnd, HOTKEY_TRANSFER, MOD_SHIFT, VK_F4);

	//m_hack->getInstance()->open(GAME_PROC_NAME);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdllhostDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdllhostDlg::OnPaint()
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
HCURSOR CdllhostDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CdllhostDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
#if  __release__
	VMProtectBegin("CdllhostDlg::OnHotKey");
#endif //  __release__

	CString cs;
	BSTR bstr;
	bool bSel = false;

	switch (nHotKeyId)
	{
	case HOTKEY_BUNKER_PROFIT:
		UpdateData(true);
		// !0 失败
		cs.Append("地堡出货倍数设置...");
		if (m_hack->getInstance()->set_bunker_profit(this->m_bunker_num))
		{
			cs += "失败";
			this->m_bunker_num = 0;
			UpdateData(false);
		}
		else
		{
			cs += "成功";
		}
		bSel = TRUE;
		break;
	case HOTKEY_GOD_MOD:

		cs.Append("无敌模式...");
		if (m_hack->getInstance()->god_mod())
		{
			cs += "开启";
			m_sGodMod.SetWindowText("[开启]");
		}
		else
		{
			cs += "关闭";
			m_sGodMod.SetWindowText("[关闭]");
		}
		bSel = TRUE;
		break;
	case HOTKEY_TRANSFER:

		cs.Append("传送...");
		m_hack->getInstance()->transfer_addr();
		bSel = TRUE;
		break;
	}

	if (bSel)
	{
		bstr = cs.AllocSysString();
		string2voc(bstr);
		SysFreeString(bstr);

/*		
		auto voc_func = [&bstr](){
			string2voc(bstr);
			SysFreeString(bstr);
		};
		std::thread t(voc_func);
		t.detach();
*/	
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
#if  __release__
	VMProtectEnd();
#endif //  __release__
}

void CdllhostDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	UnregisterHotKey(this->m_hWnd, HOTKEY_BUNKER_PROFIT);
	UnregisterHotKey(this->m_hWnd, HOTKEY_GOD_MOD);
	UnregisterHotKey(this->m_hWnd, HOTKEY_TRANSFER);

	m_hack->getInstance()->close();
	m_hack->getInstance()->destroyIntance();

}


void CdllhostDlg::OnBnClickedButton1()
{
#if __release__
	VMProtectBegin("CdllhostDlg::OnBnClickedButton1");
#endif
	// TODO: 在此添加控件通知处理程序代码
	if (! m_hack->getInstance()->open(GAME_PROC_NAME))
	{
		//MessageBeep(MB_ICONEXCLAMATION);
		CWnd* w = nullptr;
		
		w = GetDlgItem(IDC_BUTTON1);
		w->SetWindowTextA("已启动");
		w->EnableWindow(FALSE);
		
		auto voc_func = []() {
			string2voc(L"欢迎你使用BackWater...");
		};
		std::thread t(voc_func);
		t.detach();
	}
	else
	{
		MessageBoxA("请先启动游戏","[提示]",MB_OK);
		//string2voc(L"请先启动以后");
	}
#if __release__
	VMProtectEnd();
#endif
}
