
// dllhostDlg.h: 头文件
//

#pragma once


#include "hack.h"


// CdllhostDlg 对话框
class CdllhostDlg : public CDialogEx
{
// 构造
public:
	CdllhostDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLLHOST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);


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
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();

private:
	hack* m_hack;
public:
	int m_bunker_num;
	CStatic m_sGodMod;
};
