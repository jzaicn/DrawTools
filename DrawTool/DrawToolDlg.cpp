#include "stdafx.h"
// DrawToolDlg.cpp : 实现文件
//

#include "DrawTool.h"
#include "DrawToolDlg.h"
#include "afxdialogex.h"
#include "DrawItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CDrawToolDlg 对话框




CDrawToolDlg::CDrawToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()

	ON_BN_CLICKED(IDC_RELOAD, &CDrawToolDlg::OnBnClickedReload)
	ON_BN_CLICKED(IDC_INPUTITEM, &CDrawToolDlg::OnBnClickedInputitem)
END_MESSAGE_MAP()


// CDrawToolDlg 消息处理程序

BOOL CDrawToolDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码

	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 120;
	m_manager.setDrawRect(rcClient);

	CreateOutterFrame(rcClient);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrawToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{

	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrawToolDlg::OnPaint()
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
		CRect rcClient;
		GetClientRect(rcClient);

		CRect drawRect = m_manager.getDrawRect();

		CPaintDC dc(this);

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
		dcMem.SelectObject(&bmpMem);
		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);

		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
		
		m_manager.OnPaint(g);//画图

		

		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);

		bmpMem.DeleteObject();
		dcMem.DeleteDC();

		//CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrawToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//消息路由
BOOL CDrawToolDlg::PreTranslateMessage(MSG* pMsg)
{
	//键盘按键
	if (pMsg ->message == WM_KEYDOWN)  // If a keydown message
	{
		CString key;
		key.Format(L"key press 0x%02x\n",pMsg->wParam);
		OutputDebugString(key);

		if (m_manager.PreTranslateMessage(pMsg)){
			InvalidateRect(m_manager.getDrawRect());
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


//按下按键
void CDrawToolDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

BOOL CDrawToolDlg::OnEraseBkgnd(CDC* pDC)
{
	m_manager.OnEraseBkgnd(pDC);
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CDrawToolDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	m_manager.OnMouseMove(nFlags,point);
	InvalidateRect(m_manager.getDrawRect());
	CDialogEx::OnMouseMove(nFlags, point);
}

void CDrawToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_manager.OnLButtonDown(nFlags,point);
	InvalidateRect(m_manager.getDrawRect());
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDrawToolDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_manager.OnLButtonUp(nFlags,point);
	InvalidateRect(m_manager.getDrawRect());
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDrawToolDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_manager.OnRButtonDown(nFlags,point);
	InvalidateRect(m_manager.getDrawRect());
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CDrawToolDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_manager.OnRButtonUp(nFlags,point);
	InvalidateRect(m_manager.getDrawRect());
	CDialogEx::OnRButtonUp(nFlags, point);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void CDrawToolDlg::OnBnClickedReload()
{
	clearDrawMap();
}


void CDrawToolDlg::OnBnClickedInputitem()
{
	//测试用凹型
	std::vector<CPoint> points;
	points.push_back(CPoint(0,0));
	points.push_back(CPoint(50,0));
	points.push_back(CPoint(50,50));
	points.push_back(CPoint(150,50));
	points.push_back(CPoint(150,0));
	points.push_back(CPoint(200,0));
	points.push_back(CPoint(200,100));
	points.push_back(CPoint(0,100));
	DrawItemSmallPanel* panel = new DrawItemSmallPanel(points);
	m_manager.addDrawItem(panel);

	//测试用三角形
// 	std::vector<CPoint> points;
// 	points.push_back(CPoint(0,0));
// 	points.push_back(CPoint(100,100));
// 	points.push_back(CPoint(200,50));
// 	DrawItemSmallPanel* panel = new DrawItemSmallPanel(points);
// 	m_manager.addDrawItem(panel);

	//测试用正方形
// 	DrawItemBase* item = new DrawItemBase();
// 	item->setRect(0,0,100,100);
// 	m_manager.addDrawItem(item);

	InvalidateRect(m_manager.getDrawRect());
}

void CDrawToolDlg::clearDrawMap()
{
	m_manager.clearDrawItem();
}

void CDrawToolDlg::addItemDrawMap(CSkinButton* drawItem)
{

}

void CDrawToolDlg::CreateOutterFrame( CRect &rcClient )
{
	DrawItemBase* leftBorder = new DrawItemBase();
	leftBorder->setRect(rcClient.left,rcClient.top,rcClient.left + 10,rcClient.bottom);
	m_manager.addDrawItem(leftBorder);

	DrawItemBase* rightBorder = new DrawItemBase();
	rightBorder->setRect(rcClient.right - 10 ,rcClient.top,rcClient.right,rcClient.bottom);
	m_manager.addDrawItem(rightBorder);

	DrawItemBase* topBorder = new DrawItemBase();
	topBorder->setRect(rcClient.left,rcClient.top,rcClient.right,rcClient.top + 10);
	m_manager.addDrawItem(topBorder);

	DrawItemBase* bottomBorder = new DrawItemBase();
	bottomBorder->setRect(rcClient.left,rcClient.bottom -10 ,rcClient.right,rcClient.bottom);
	m_manager.addDrawItem(bottomBorder);
}


