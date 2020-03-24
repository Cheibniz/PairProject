#pragma once


// DrawDlg 对话框

class DrawDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DrawDlg)

public:
	DrawDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DrawDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnDraw();
	DECLARE_MESSAGE_MAP()
public:
	
	
	
	
	afx_msg void OnBnClickedOk();
};
