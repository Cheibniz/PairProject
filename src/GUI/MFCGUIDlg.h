
// MFCGUIDlg.h: 头文件
//

#pragma once


// CMFCGUIDlg 对话框
class CMFCGUIDlg : public CDialogEx
{
// 构造
public:
	CMFCGUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGUI_DIALOG };
#endif

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
	CString m_FILEPATH;
	CString m_LineValue;
	CString m_CiecleValue;
	afx_msg void OnBnClickedImportButton();
	afx_msg void OnBnClickedLineadd();
	afx_msg void OnBnClickedAddcircle();
	afx_msg void OnBnClickedGet();
	int m_ResultValue;
	afx_msg void OnBnClickedDraw();
	void mydraw();
	afx_msg void OnBnClickedLinedel();
	afx_msg void OnBnClickedCircledel();
	CString m_EXCEPTMESSAGE;
	int resize = 30;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
