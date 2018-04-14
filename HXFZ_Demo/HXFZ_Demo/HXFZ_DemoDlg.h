
// HXFZ_DemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CHXFZ_DemoDlg 对话框
class CHXFZ_DemoDlg : public CDialogEx
{
// 构造
public:
	CHXFZ_DemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HXFZ_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtAPDU;
	CEdit m_edtProtocol;
	afx_msg void OnBnClickedButtonGenProtocol();
};
