#include "stdafx.h"
// DrawToolDlg.cpp : 实现文件
//

#include "DrawTool.h"
#include "DrawToolDlg.h"
#include "afxdialogex.h"


#include "DrawLine.h"
#include "DrawItem.h"
#include "DrawItemStrategy.h"
#include "SmallPanelDrawItem.h"

#include "TestBase.h"
#include "TestDrawTools.h"
#include "TestDrawLine.h"
#include "TestDrawItem.h"
#include "TestDrawItemManagement.h"
#include "TestSmallPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CDrawToolDlg 对话框




CDrawToolDlg::CDrawToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dcBackgroudBitmap = nullptr;
	m_g= nullptr;
}

void CDrawToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()

	ON_BN_CLICKED(IDC_RELOAD, &CDrawToolDlg::OnBnClickedReload)
	ON_BN_CLICKED(IDC_INPUTITEM, &CDrawToolDlg::OnBnClickedInputitem)
	ON_BN_CLICKED(IDC_TEST, &CDrawToolDlg::OnBnClickedTest)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CLEAR, &CDrawToolDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CDrawToolDlg 消息处理程序

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

HCURSOR CDrawToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




/************************************************************************/
/*                                                                      */
/************************************************************************/
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

	ShowWindow(SW_MAXIMIZE);


	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 120;
	m_manager.setDrawCRect(rcClient);
	//m_manager.Strategy(&m_smallStrategy);
	m_manager.OnInitial();
	initBKDC();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

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

		RectF drawRect = m_manager.getDrawRectF();

		CPaintDC dc(this);		
		
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);
		m_g->FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), RectF(rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height()));

		m_manager.OnPaint(*m_g);//画图
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_dcBackgroud, 0, 0, SRCCOPY);
		
		//CDialogEx::OnPaint();
	}
}

//消息路由
BOOL CDrawToolDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_manager.PreTranslateMessage(pMsg))
	{
		return TRUE;
	}
	
	//键盘按键
	if (pMsg ->message == WM_KEYDOWN)  // If a keydown message
	{
		CString key;
		key.Format(L"key press 0x%02x\n",pMsg->wParam);
		OutputDebugString(key);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDrawToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rcClient;
	GetClientRect(rcClient);

	CRect drawClient = rcClient;
	drawClient.bottom -= 60;
	m_manager.setDrawCRect(drawClient);

	CRect itemRect;
	//清空大板
	GetDlgItem(IDC_CLEAR)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_CLEAR)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);

	//重新加载
	GetDlgItem(IDC_RELOAD)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_RELOAD)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);

	//添加小板
	GetDlgItem(IDC_INPUTITEM)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_INPUTITEM)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);
	
	//测试
	GetDlgItem(IDC_TEST)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_TEST)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);


}

BOOL CDrawToolDlg::OnEraseBkgnd(CDC* pDC)
{
	m_manager.OnEraseBkgnd(pDC);
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CDrawToolDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	PointF _pointF(point.x,point.y);
	m_manager.OnMouseMove(nFlags,_pointF);
	InvalidateRect(m_manager.getDrawCRect());
	CDialogEx::OnMouseMove(nFlags, point);
}

void CDrawToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PointF _pointF(point.x,point.y);
	m_manager.OnLButtonDown(nFlags,_pointF);
	InvalidateRect(m_manager.getDrawCRect());
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDrawToolDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	PointF _pointF(point.x,point.y);
	m_manager.OnLButtonUp(nFlags,_pointF);
	InvalidateRect(m_manager.getDrawCRect());
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDrawToolDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	PointF _pointF(point.x,point.y);
	m_manager.OnRButtonDown(nFlags,_pointF);
	InvalidateRect(m_manager.getDrawCRect());
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CDrawToolDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	PointF _pointF(point.x,point.y);
	m_manager.OnRButtonUp(nFlags,_pointF);
	InvalidateRect(m_manager.getDrawCRect());
	CDialogEx::OnRButtonUp(nFlags, point);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//清空
void CDrawToolDlg::OnBnClickedClear()
{
	m_manager.clearDrawItem();
	InvalidateRect(m_manager.getDrawCRect());
}
//重新加载
void CDrawToolDlg::OnBnClickedReload()
{
	m_manager.clearDrawItem();
	InvalidateRect(m_manager.getDrawCRect());
}

#define TestOnce 0
#define TestNew 1

void CDrawToolDlg::OnBnClickedInputitem()
{

#if 1

	
	//测试用长方形,带侧面孔，正面孔
	RectF rect = RectF(0,0,281,531);
	SmallPanel* shape = new SmallPanel(rect);
	
	

	std::list<IDataLine*> lines;
	lines.push_back(new DataStraightLine(PointF(0,0),PointF(0,381)));
	lines.push_back(new DrawArcLine(PointF(0,381),PointF(150,531),150,1));
	lines.push_back(new DataStraightLine(PointF(150,531),PointF(281,531)));
	lines.push_back(new DataStraightLine(PointF(281,531),PointF(281,0)));
	lines.push_back(new DataStraightLine(PointF(281,0),PointF(0,0)));

	//DrawItemShape* shape = new DrawItemShape(rect,lines);
	shape->setInnerShape(new DrawItemShape(rect,lines));

	//异形的时候，SIDE1 和 SIDE2翻转 ， SIDE3 和 SIDE4翻转
	//更改方法：一旦检测到是异形板，将PanelFace子节点中的Layer="SIDE1 改成 Layer="SIDE2
	//其他照旧

	std::list<IDrawItem*> infos;
// 	<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="483" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(248,483,180,15,15,14));
// 	<VERTICAL Layer="SIDE29.000000" Name="开孔2">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="483" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,483,0,33,8,9));
// 	<VERTICAL Layer="SIDE29.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="451" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,451,0,33,8,9));
// 	<VERTICAL Layer="SIDE29.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="99" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,99,0,33,8,9));
// 	<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="67" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(248,67,180,15,15,14));
// 	<VERTICAL Layer="SIDE29.000000" Name="开孔2">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="67" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,67,0,33,8,9));
// 	<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="48" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(48,33,180,15,15,14));
// 	<VERTICAL Layer="SIDE49.000000" Name="开孔2">
// 		<Param Name="pos_x" Value="48" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="90" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(4,48,33,90,33,8,9));
// 	<VERTICAL Layer="SIDE49.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="144" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="90" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(4,144,33,90,33,8,9));
// 	<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
// 		<Param Name="pos_x" Value="240" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(240,33,180,15,15,14));
// 		<VERTICAL Layer="SIDE49.000000" Name="开孔2">
// 			<Param Name="pos_x" Value="240" />
// 			<Param Name="pos_y" Value="33" />
// 			<Param Name="angle" Value="90" />
// 			<Param Name="size_x" Value="33" />
// 			<Param Name="size_y" Value="8" />
// 			<Param Name="depth" Value="9" />
// 			<Param Name="dwgFile" Value="SIDE.dwg" />
// 		</VERTICAL>
	infos.push_back(new DrawSideVertical(4,240,33,90,33,8,9));
//		</PanelFace>
	shape->InfoVertical(infos);

	m_manager.addDrawItem(shape);
	m_smallStrategy.addNewActiveItem(shape);

#endif	

	InvalidateRect(m_manager.getDrawCRect());
}



void CDrawToolDlg::OnBnClickedTest()
{
	//框架测试
	ASSERT(TestDrawTools::TestDrawToolsAll());
	ASSERT(TestDrawLine::TestDrawLineAll());
	ASSERT(TestDrawItem::TestDrawItemAll());
	ASSERT(TestDrawItemManagement::TestDrawItemManagementAll());

	//工程代码测试
	ASSERT(TestSmallPanel::TestSmallPanelAll());


#if TestNew

#endif
	InvalidateRect(m_manager.getDrawCRect());
}

int CDrawToolDlg::initBKDC()
{
	//创建bitmap
	CRect rcClient;
	GetClientRect(rcClient);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(GetDC(), rcClient.Width(), rcClient.Height());

	//创建缓冲DC
	m_dcBackgroud.CreateCompatibleDC(GetDC());
	m_dcBackgroudBitmap = m_dcBackgroud.SelectObject(&bmpMem);
	m_g = Graphics::FromHDC(m_dcBackgroud.GetSafeHdc());
	return !!m_dcBackgroud.GetSafeHdc();
}

int CDrawToolDlg::releaseBKDC()
{
	auto curbitmap = m_dcBackgroud.GetCurrentBitmap();
	 if(curbitmap && curbitmap != m_dcBackgroudBitmap)
	 {
		 auto lastbitmap = m_dcBackgroud.SelectObject(m_dcBackgroudBitmap);
	 }
	 m_dcBackgroud.DeleteDC();
	 return !m_dcBackgroud.GetSafeHdc();
}

CDrawToolDlg::~CDrawToolDlg()
{
	auto re = releaseBKDC();
	delete m_g;
}

