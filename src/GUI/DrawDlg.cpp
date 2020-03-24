// DrawDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCGUI.h"
#include "DrawDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <graphics.h>
// DrawDlg 对话框

IMPLEMENT_DYNAMIC(DrawDlg, CDialogEx)

DrawDlg::DrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW, pParent)
{
	OnDraw();
}

DrawDlg::~DrawDlg()
{
}

void DrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	
}

void DrawDlg::OnDraw()
{
	
}


BEGIN_MESSAGE_MAP(DrawDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &DrawDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// DrawDlg 消息处理程序


void DrawDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	closegraph();
}
