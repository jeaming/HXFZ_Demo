
// HXFZ_DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HXFZ_Demo.h"
#include "HXFZ_DemoDlg.h"
#include "afxdialogex.h"

#include "HEX2BIN.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHXFZ_DemoDlg �Ի���



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


// CHXFZ_DemoDlg ��Ϣ�������

BOOL CHXFZ_DemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_edtAPDU.SetWindowTextA("0084000008");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHXFZ_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHXFZ_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHXFZ_DemoDlg::OnBnClickedButtonGenProtocol()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
