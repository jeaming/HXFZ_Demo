
// HXFZ_DemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CHXFZ_DemoDlg �Ի���
class CHXFZ_DemoDlg : public CDialogEx
{
// ����
public:
	CHXFZ_DemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HXFZ_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
