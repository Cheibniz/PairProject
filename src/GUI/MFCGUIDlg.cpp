
// MFCGUIDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCGUI.h"
#include "MFCGUIDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DrawDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>
#include "Interface.h"
#include "DrawDlg.h"
#include <graphics.h>
#include <sstream>

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


// CMFCGUIDlg 对话框



CMFCGUIDlg::CMFCGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGUI_DIALOG, pParent)
	, m_FILEPATH(_T(""))
	, m_LineValue(_T(""))
	, m_CiecleValue(_T(""))
	, m_ResultValue(0)
	, m_EXCEPTMESSAGE(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_FILEPATH);
	DDX_Text(pDX, IDC_LineInput, m_LineValue);
	DDX_Text(pDX, IDC_CiecleInput, m_CiecleValue);
	DDX_Text(pDX, IDC_EDIT1, m_ResultValue);
	DDX_Text(pDX, IDC_EXCEPT, m_EXCEPTMESSAGE);
}

BEGIN_MESSAGE_MAP(CMFCGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IMPORT_BUTTON, &CMFCGUIDlg::OnBnClickedImportButton)
	ON_BN_CLICKED(IDC_LINEADD, &CMFCGUIDlg::OnBnClickedLineadd)
	ON_BN_CLICKED(IDC_ADDCIRCLE, &CMFCGUIDlg::OnBnClickedAddcircle)
	ON_BN_CLICKED(IDC_GET, &CMFCGUIDlg::OnBnClickedGet)
	ON_BN_CLICKED(IDC_Draw, &CMFCGUIDlg::OnBnClickedDraw)
	ON_BN_CLICKED(IDC_LINEDEL, &CMFCGUIDlg::OnBnClickedLinedel)
	ON_BN_CLICKED(IDC_CIRCLEDEL, &CMFCGUIDlg::OnBnClickedCircledel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCGUIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCGUIDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCGUIDlg 消息处理程序

BOOL CMFCGUIDlg::OnInitDialog()
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
	m_EXCEPTMESSAGE = CString(_T("异常处理程序会在出现异常时终止计算，请在出现异常操作后重启程序"));
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCGUIDlg::OnPaint()
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
HCURSOR CMFCGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCGUIDlg::OnBnClickedImportButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::string path;
	path = CT2A(m_FILEPATH.GetString());
	try
	{
		readFile(path);
	}
	catch (const std::exception&)
	{
		m_EXCEPTMESSAGE = CString(_T("读取文件出现错误,请重启程序"));
		UpdateData(FALSE);
		return;
	}
	m_EXCEPTMESSAGE = CString(_T("读取文件成功"));
	UpdateData(FALSE);
}


void CMFCGUIDlg::OnBnClickedLineadd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::string line;
	line = CT2A(m_LineValue.GetString());
	try
	{
		addGeometryObject(line);
	}
	catch (const std::exception&)
	{
		m_EXCEPTMESSAGE = CString(_T("添加图形时出现错误,请重启程序"));
		UpdateData(FALSE);
		//exit(0);
	}
}


void CMFCGUIDlg::OnBnClickedAddcircle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::string line;
	line = CT2A(m_CiecleValue.GetString());
	try
	{
		addGeometryObject(line);
	}
	catch (const std::exception&)
	{
		m_EXCEPTMESSAGE = CString(_T("添加圆时出现错误,请重启程序"));
		UpdateData(FALSE);
	}
	
}


void CMFCGUIDlg::OnBnClickedGet()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pair<vector<string>, vector<Point>> result;
	result = getResult();
	
	m_ResultValue = result.second.size();
	UpdateData(FALSE);
}


void CMFCGUIDlg::OnBnClickedDraw()
{
	// TODO: 在此添加控件通知处理程序代码
	pair<vector<string>, vector<Point>> result;
	result = getResult();
	
	initgraph(640, 480);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(2);
	for (int x = 0; x <= 640; x += 40)
	{
		line(0, x, 640, x);
	}
	for (int y = 0; y <= 640; y += 40)
	{
		line(y, 0, y, 640);
	}
	setorigin(320, 240);
	//坐标轴
	setlinestyle(0);
	line(0, 999, 0, - 999);
	line(-999, 1, 999, 1);
	line(1, 999, 1, -999);
	line(-999, 0, 999, 0);
	line(-1, 999, -1, -999);
	line(-999, -1, 999, -1);

	setlinecolor(RED);
	
	
	stringstream ss("");
	for (int i = 0; i < result.first.size(); i++)
	{
		string str = result.first[i];
		ss.clear();
		ss << str;
		char type;
		ss >> type;
		switch (type)
		{
		case 'C': {
			setcolor(BLUE);
			double xc, yc, r1;
			ss >> xc >> yc >> r1;
			circle(xc * resize, yc * -resize, r1 * resize);
			break;
		}
		case 'L': {
			moveto(0, 0);
			double x0, y0, x1, y1;
			ss >> x0 >> y0 >> x1 >> y1;
			y0 = -y0; y1 = -y1;
			line(x0 * resize, y0 * resize, x1 * resize, y1 * resize);
			moveto(x0 * resize, y0 * resize);
			linerel((x1 - x0) * 999, (y1 - y0) * 999);
			moveto(x0 * resize, y0 * resize);
			linerel((x1 - x0) * -999, (y1 - y0) * -999);
			break;
		}
		case 'R': {
			moveto(0, 0);
			double x0, y0, x1, y1;
			ss >> x0 >> y0 >> x1 >> y1;
			y0 = -y0; y1 = -y1;
			line(x0 * resize, y0 * resize, x1 * resize, y1 * resize);
			moveto(x0 * resize, y0 * resize);
			linerel((x1 - x0) * 999, (y1 - y0) * 999);
			break;
		}
		case 'S': {
			moveto(0, 0);
			double x0, y0, x1, y1;
			ss >> x0 >> y0 >> x1 >> y1;
			y0 = -y0; y1 = -y1;
			line(x0 * resize, y0 * resize, x1 * resize, y1 * resize);
			break;
		}
		default:
			break;
		}
	}
	for (int i = 0; i < result.second.size(); i++)
	{
		//putpixel(10, 20, RED);
		putpixel(result.second[i].first * resize, result.second[i].second * -resize, YELLOW);
		setcolor(YELLOW);
		circle(result.second[i].first * resize, result.second[i].second * -resize, 1);
		circle(result.second[i].first * resize, result.second[i].second * -resize, 2);
	}

	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	DrawDlg drawDlg;           // 构造对话框类CTipDlg的实例   
	nRes = drawDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;

	// 将各控件中的数据保存到相应的变量   

}

void CMFCGUIDlg::mydraw()
{
}


void CMFCGUIDlg::OnBnClickedLinedel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string line;
	line = CT2A(m_LineValue.GetString());
	try
	{
		removeGeometryObject(line);
	}
	catch (const std::exception&)
	{
		m_EXCEPTMESSAGE = CString(_T("删除直线时出现错误,请重启程序"));
		UpdateData(FALSE);
	}
	UpdateData(FALSE);
}


void CMFCGUIDlg::OnBnClickedCircledel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string line;
	line = CT2A(m_CiecleValue.GetString());
	try
	{
		removeGeometryObject(line);
	}
	catch (const std::exception&)
	{
		m_EXCEPTMESSAGE = CString(_T("删除圆时出现错误,请重启程序"));
		UpdateData(FALSE);
	}
	UpdateData(FALSE);
}


void CMFCGUIDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (resize > 10)
	{

		resize -= 10;
	}
}


void CMFCGUIDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	resize += 10;
}
