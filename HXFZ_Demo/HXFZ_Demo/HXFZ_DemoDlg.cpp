
// HXFZ_DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HXFZ_Demo.h"
#include "HXFZ_DemoDlg.h"
#include "afxdialogex.h"

#include "HEX2BIN.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CHXFZ_DemoDlg 对话框



CHXFZ_DemoDlg::CHXFZ_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHXFZ_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHXFZ_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_APDU, m_edtAPDU);
	DDX_Control(pDX, IDC_EDIT_PROTOCOL, m_edtProtocol);
}

BEGIN_MESSAGE_MAP(CHXFZ_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GEN_PROTOCOL, &CHXFZ_DemoDlg::OnBnClickedButtonGenProtocol)
END_MESSAGE_MAP()


// CHXFZ_DemoDlg 消息处理程序

BOOL CHXFZ_DemoDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_edtAPDU.SetWindowTextA("0084000008");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHXFZ_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHXFZ_DemoDlg::OnPaint()
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
HCURSOR CHXFZ_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHXFZ_DemoDlg::OnBnClickedButtonGenProtocol()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strAPDU;
	CString strProtocol;
	unsigned char szProtocol[512];
	//char szLength[5];

	m_edtAPDU.GetWindowTextA(strAPDU);

	int iApdu = strAPDU.GetLength()/2;
	memset(szProtocol, 0, sizeof(szProtocol));
	szProtocol[0] = 0x02;

	iApdu += 3;

	szProtocol[1] = (unsigned char)(iApdu / 255);
	szProtocol[2] = (unsigned char)(iApdu % 255);

	//sprintf_s(szLength, 5, "%.04x", iApdu);
	//Hex2Bin(szProtocol + 1, (unsigned char*)szLength, 4);

	szProtocol[3] = 0xC0;
	szProtocol[4] = 0x31;
	szProtocol[5] = 0x00;

	Hex2Bin(szProtocol + 6, (unsigned char*)strAPDU.GetBuffer(), (iApdu - 3) * 2);

	//include 0x02 0x00 0x08  begin byte + lenght bytes
	iApdu += 3;

	for (int i = 3; i != iApdu; ++i)
		szProtocol[iApdu] ^= szProtocol[i];

	iApdu++;
	szProtocol[iApdu] = 0x03;
	
	iApdu++; 
	SwitchDataMode(szProtocol, &iApdu, BIN2HEX);

	m_edtProtocol.SetWindowTextA((LPCTSTR)szProtocol);

}
