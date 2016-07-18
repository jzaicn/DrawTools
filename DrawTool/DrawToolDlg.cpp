#include "stdafx.h"
// DrawToolDlg.cpp : 实现文件
//

#include "DrawTool.h"
#include "DrawToolDlg.h"
#include "afxdialogex.h"
#include "DrawItem.h"
//#include "SmallPanelDrawItem.h"

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
	ON_BN_CLICKED(IDC_TEST, &CDrawToolDlg::OnBnClickedTest)
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


	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 120;
	m_manager.setDrawCRect(rcClient);

	CreateOutterFrame(m_manager.getDrawRectF());



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

		RectF drawRect = m_manager.getDrawRectF();

		CPaintDC dc(this);

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
		dcMem.SelectObject(&bmpMem);
		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);

		
		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), RectF(rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height()));
		
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
			InvalidateRect(m_manager.getDrawCRect());
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

void CDrawToolDlg::OnBnClickedReload()
{
	clearDrawMap();
}


void CDrawToolDlg::OnBnClickedInputitem()
{
	//// 	<Vector X="1998.0000" Y="10.0000" R="0.0000" Sign="0" Dir="0" />
	//// 	<Vector X="370.0000" Y="10.0000" R="360.0000" Sign="1" Dir="1" />
	//// 	<Vector X="10.0000" Y="370.0000" R="360.0000" Sign="2" Dir="1" />
	//// 	<Vector X="1998.0000" Y="370.0000" R="0.0000" Sign="0" Dir="0" />
	////
	////  lines.push_back(new DrawStraightLine(PointF(,),PointF(,)));
	////  lines.push_back(new DrawArcLine(PointF(,),PointF(,),0,0));
	////测试用圆角长方形
	//RectF rect(10,10,390,360);
	//std::vector<IDrawLine*> lines;
	//lines.push_back(new DrawStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
	//lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
	//lines.push_back(new DrawStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
	//lines.push_back(new DrawStraightLine(PointF(400,370.0000),PointF(400,10.0000)));

	//SmallPanelDrawItem* shape = SmallPanelDrawItem::SmallPanelFactory(rect);
	//shape->setOutterLine(lines);
	//m_manager.addDrawItem(shape);


 	// 	<Vector X="1998.0000" Y="10.0000" R="0.0000" Sign="0" Dir="0" />
 	// 	<Vector X="370.0000" Y="10.0000" R="360.0000" Sign="1" Dir="1" />
 	// 	<Vector X="10.0000" Y="370.0000" R="360.0000" Sign="2" Dir="1" />
 	// 	<Vector X="1998.0000" Y="370.0000" R="0.0000" Sign="0" Dir="0" />
 	//
 	//  lines.push_back(new DrawStraightLine(PointF(,),PointF(,)));
 	//  lines.push_back(new DrawArcLine(PointF(,),PointF(,),0,0));
 	//测试用圆角长方形
 	RectF rect(10,10,390,360);
 	std::vector<IDrawLine*> lines;
 	lines.push_back(new DrawStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
 	lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
 	lines.push_back(new DrawStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
 	lines.push_back(new DrawStraightLine(PointF(400,370.0000),PointF(400,10.0000)));
 
 	DrawItemShape* shape = new DrawItemShape(rect,lines);
 	shape->setType(L"companel");
 	m_manager.addDrawItem(shape);




	//测试用凹型
// 	std::vector<PointF> points;
// 	points.push_back(PointF(0,0));
// 	points.push_back(PointF(50,0));
// 	points.push_back(PointF(50,50));
// 	points.push_back(PointF(150,50));
// 	points.push_back(PointF(150,0));
// 	points.push_back(PointF(200,0));
// 	points.push_back(PointF(200,100));
// 	points.push_back(PointF(0,100));
// 	DrawItemPolygon* panel = new DrawItemPolygon(points);
// 	m_manager.addDrawItem(panel);

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

	InvalidateRect(m_manager.getDrawCRect());
}

void CDrawToolDlg::clearDrawMap()
{
	m_manager.clearDrawItem();
	InvalidateRect(m_manager.getDrawCRect());
}

void CDrawToolDlg::CreateOutterFrame( RectF &rcClient )
{
// 	DrawItemBase* leftBorder = new DrawItemBase();
// 	leftBorder->setRect(rcClient.left,rcClient.top,rcClient.left + 10,rcClient.bottom);
// 	m_manager.addDrawItem(leftBorder);
// 
// 	DrawItemBase* rightBorder = new DrawItemBase();
// 	rightBorder->setRect(rcClient.right - 10 ,rcClient.top,rcClient.right,rcClient.bottom);
// 	m_manager.addDrawItem(rightBorder);
// 
// 	DrawItemBase* topBorder = new DrawItemBase();
// 	topBorder->setRect(rcClient.left,rcClient.top,rcClient.right,rcClient.top + 10);
// 	m_manager.addDrawItem(topBorder);
// 
// 	DrawItemBase* bottomBorder = new DrawItemBase();
// 	bottomBorder->setRect(rcClient.left,rcClient.bottom -10 ,rcClient.right,rcClient.bottom);
// 	m_manager.addDrawItem(bottomBorder);
}

bool pfe(PointF& p1,PointF& p2)
{
	return (fabs(p1.X - p2.X)<0.00001) && (fabs(p1.Y - p2.Y)<0.00001);
}

#define TestOnce 1
#define TestNew 1
void CDrawToolDlg::OnBnClickedTest()
{
	//测试画图形的点移动是否恰当
#if TestOnce
	{
		ASSERT(DrawTools::ArcSignLeft == 1);

		RectF rect(10,10,390,360);
		std::vector<IDrawLine*> lines;
		lines.push_back(new DrawStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
		lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
		lines.push_back(new DrawStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
		lines.push_back(new DrawStraightLine(PointF(400,370.0000),PointF(400,10.0000)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);

		shape->move(PointF(0,0));
		std::vector<PointF> points = shape->getAllPoints();
		ASSERT(points[0].Equals(PointF(400,10)));

		delete shape;
	}
#endif

	//DrawTools点坐标转换是否得当
#if TestOnce
	//点角度计算
	{
	 	PointF center(50,50);
	 
	 	//正轴
	 	PointF point1(100,50);
	 	double angle1 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point1));
	 	ASSERT(angle1 == 0.0);
	 
	 	//正半轴
	 	PointF point2(100,0);
	 	double angle2 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point2));
	 	ASSERT(angle2 == 45.0);
	 
	 	//正半轴
	 	PointF point3(50,00);
	 	double angle3 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point3));
	 	ASSERT(angle3 == 90.0);
	 
	 	//正半轴
	 	PointF point4(00,00);
	 	double angle4 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point4));
	 	ASSERT(angle4 == 135.0);
	 
	 	//正轴
	 	PointF point5(0,50);
	 	double angle5 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point5));
	 	ASSERT(angle5 == 180.0);
	 
	 	//正半轴
	 	PointF point6(0,100);
	 	double angle6 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point6));
	 	ASSERT(angle6 == 225.0);
	 
	 	//正半轴
	 	PointF point7(50,100);
	 	double angle7 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point7));
	 	ASSERT(angle7 == 270.0);
	 
	 	//正半轴
	 	PointF point8(100,100);
	 	double angle8 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point8));
	 	ASSERT(angle8 == 315.0);
	 
	}
	//角坐标计算测试
	{
		PointF center(50.0,50.0);
		double beginAngle = 0.0 ,sweepAngle = 0.0;

		//正向4个象限
		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50),PointF(50.0,0.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 0.0);
		ASSERT(sweepAngle == 90.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,0.0),PointF(0.0,50.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 90.0);
		ASSERT(sweepAngle == 90.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50),PointF(50.0,100.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 180.0);
		ASSERT(sweepAngle == 90.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,100),PointF(100,50.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 270.0);
		ASSERT(sweepAngle == 90.0);



		//再追一圈4个象限
		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,0.0),PointF(100,50),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 90.0);
		ASSERT(sweepAngle == 270.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50.0),PointF(50,0.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 180.0);
		ASSERT(sweepAngle == 270.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,100.0),PointF(0.0,50),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 270.0);
		ASSERT(sweepAngle == 270.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50.0),PointF(50,100),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 0.0);
		ASSERT(sweepAngle == 270.0);
	}

	//最短追及
	{
		PointF center(50.0,50.0);
		double beginAngle = 0.0 ,sweepAngle = 0.0;

		//正向4个象限
		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50),PointF(50.0,0.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 0.0);
		ASSERT(sweepAngle == 90.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,0.0),PointF(0.0,50.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 90.0);
		ASSERT(sweepAngle == 90.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50),PointF(50.0,100.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 180.0);
		ASSERT(sweepAngle == 90.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,100),PointF(100,50.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 270.0);
		ASSERT(sweepAngle == 90.0);



		//再追一圈4个象限
		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,0.0),PointF(100,50),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 90.0);
		ASSERT(sweepAngle == 270.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50.0),PointF(50,0.0),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 180.0);
		ASSERT(sweepAngle == 270.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,100.0),PointF(0.0,50),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 270.0);
		ASSERT(sweepAngle == 270.0);

		DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50.0),PointF(50,100),50,beginAngle,sweepAngle);
		ASSERT(beginAngle == 0.0);
		ASSERT(sweepAngle == 270.0);
	}
	//正式角坐标到显示用角坐标转换
	{
		ASSERT(DrawTools::getAngularCoordinate_Mirror(60.0) == 300.0);
		ASSERT(DrawTools::getAngularCoordinate_Mirror(270.0) == 90.0);

		double begin1 = 90.0;
		double sweep1 = 90;
		DrawTools::getDrawArcAngularCoordinate(begin1,sweep1);
		ASSERT(begin1 == 180);
		ASSERT(sweep1 == 90);
	}
#endif

	//画圆弧
#if TestOnce
	//画圆弧 * 4 = 一个圆
	{
		RectF rect(0,0,100,100);
		std::vector<IDrawLine*> lines;
		lines.push_back(new DrawArcLine(PointF(100.0000,50.0000),PointF(50.0000,0.00),50,1));
		lines.push_back(new DrawArcLine(PointF(50.0000,00.0000),PointF(00.0000,50.0),50,1));
		lines.push_back(new DrawArcLine(PointF(00.0000,50.0000),PointF(50.0000,100),50,1));
		lines.push_back(new DrawArcLine(PointF(50.0000,100.0000),PointF(100.0000,50.0),50,1));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		m_manager.addDrawItem(shape);

		m_manager.clearDrawItem();
	}
	//画圆弧
	{
		RectF rect(0,0,100,100);
		std::vector<IDrawLine*> lines;
		lines.push_back(new DrawArcLine(PointF(100.0000,00.0000),PointF(0.0000,100),100,1));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		m_manager.addDrawItem(shape);

		DrawItemShape* item = (DrawItemShape*)m_manager.getDrawItemList()[0];
		std::vector<PointF> points = item->getAllPoints();

		ASSERT(points[0].X == 100);
		ASSERT(points[0].Y == 0.0);
		ASSERT(points[1].X == 0.0);
		ASSERT(points[1].Y == 100);
		//m_manager.clearDrawItem();
	}
	//画三角形
	{	
		RectF rect(0,0,100,100);
		std::vector<IDrawLine*> lines;
		lines.push_back(new DrawStraightLine(PointF(100,0.0000),PointF(0,100)));
		lines.push_back(new DrawStraightLine(PointF(0,100.0000),PointF(100.0000,100)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,00)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		m_manager.addDrawItem(shape);
		m_manager.clearDrawItem();
	}
	//画斜边是圆的直角三角形
	{
		RectF rect(0,0,100,100);
		std::vector<IDrawLine*> lines;
		lines.push_back(new DrawArcLine(PointF(100.0000,00.0000),PointF(0.0000,100),110,1));
		lines.push_back(new DrawStraightLine(PointF(0,100.0000),PointF(100.0000,100)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,00)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		m_manager.addDrawItem(shape);
		m_manager.clearDrawItem();
	}
#endif

	//测试坐标点旋转
#if TestOnce
	{
		//构造三角形
		RectF rect(0,0,100,100);
		std::vector<IDrawLine*> lines;
		lines.push_back(new DrawStraightLine(PointF(100.0,0.0000),PointF(0.0,100.0)));
		lines.push_back(new DrawStraightLine(PointF(0.0,100.0000),PointF(100.0000,100.0)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,0.0)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		shape->setType(L"companel");
		m_manager.addDrawItem(shape);

		//得到所有点
		std::vector<PointF> origin1 = shape->getAllPoints();

		//旋转图形4次（回到原位置）
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);

		//获得所有新的点，比较旋转后所有点是否还在原位置
		std::vector<PointF> result1 = shape->getAllPoints();
		ASSERT(origin1.size() == result1.size());
		for (unsigned int i = 0;i<result1.size() ; i++)
		{
			bool a = result1[i].Equals(origin1[i]);

			//CString mm;
			//mm.Format(L"%d (%f, %f) (%f, %f)\n",a,result1[i].X,result1[i].Y,origin1[i].X,origin1[i].Y);
			//OutputDebugString(mm);


			ASSERT(fabs(result1[i].X - origin1[i].X) <0.0000001);
			ASSERT(fabs(result1[i].Y - origin1[i].Y) <0.0000001);
			//ASSERT(result1[i].Equals(origin1[i]));
		}

		//获取外包围边框，由于当前图形是正方形的内接直角三角形，
		//所以在每次旋转后判断第一个点都是顶点。
		RectF originRect1 = shape->getRect();


		ASSERT(pfe(DrawTools::getTopRight(originRect1),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getBottomRight(originRect1),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getBottomLeft(originRect1),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getTopLeft(originRect1),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getTopRight(originRect1),shape->getAllPoints()[0]));


		shape->move(PointF(200,100));

		std::vector<PointF> origin2 = shape->getAllPoints();

		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);

		std::vector<PointF> result2 = shape->getAllPoints();
		ASSERT(origin2.size() == result2.size());
		for (unsigned int i = 0;i<result2.size() ; i++)
		{
			//CString mm;
			//mm.Format(L"(%f, %f) (%f, %f)\n",result2[i].X,result2[i].Y,origin2[i].X,origin2[i].Y);
			//OutputDebugString(mm);

			ASSERT(result2[i].Equals(origin2[i]));
		}

		RectF originRect2 = shape->getRect();


		ASSERT(pfe(DrawTools::getTopRight(originRect2),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getBottomRight(originRect2),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getBottomLeft(originRect2),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getTopLeft(originRect2),shape->getAllPoints()[0]));
		m_manager.rotateDrawItem(shape);
		ASSERT(pfe(DrawTools::getTopRight(originRect2),shape->getAllPoints()[0]));

		m_manager.clearDrawItem();
	}

#endif

#if TestNew
	//方中方
	{
		RectF rect(0,0,100,100);
		std::vector<IDrawLine*> lines;

		//外边框
		lines.push_back(new DrawStraightLine(PointF(100.0,0.0000),PointF(0.0,00.0)));
		lines.push_back(new DrawStraightLine(PointF(00.0,0.0000),PointF(0.0,100.0)));
		lines.push_back(new DrawStraightLine(PointF(0.0,100.0000),PointF(100.0000,100.0)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,0.0)));

		//内小方1
		lines.push_back(new DrawStraightLine(PointF(40,10),PointF(10,10)));
		lines.push_back(new DrawStraightLine(PointF(10,10),PointF(10,90)));
		lines.push_back(new DrawStraightLine(PointF(10,90),PointF(40,90)));
		lines.push_back(new DrawStraightLine(PointF(40,90),PointF(40,10)));

// 		//内小方2
// 		lines.push_back(new DrawStraightLine(PointF(50,90),PointF(80,90)));
// 		lines.push_back(new DrawStraightLine(PointF(80,90),PointF(80,10)));
// 		lines.push_back(new DrawStraightLine(PointF(80,10),PointF(50,10)));
// 		lines.push_back(new DrawStraightLine(PointF(50,10),PointF(50,90)));


		DrawItemShape* shape = new DrawItemShape(rect,lines);
		shape->setType(L"companel");
		m_manager.addDrawItem(shape);

		std::vector<IDrawLine*> lines2;

		//内小方
		RectF rect2(15,15,10,10);
		lines2.push_back(new DrawStraightLine(PointF(15,15),PointF(15,10)));
		lines2.push_back(new DrawStraightLine(PointF(15,10),PointF(10,10)));
		lines2.push_back(new DrawStraightLine(PointF(10,10),PointF(10,15)));
		lines2.push_back(new DrawStraightLine(PointF(10,15),PointF(15,15)));

		DrawItemShape* shape2 = new DrawItemShape(rect2,lines2);
		shape2->setType(L"companel");
		m_manager.addDrawItem(shape2);

	}












#endif
	InvalidateRect(m_manager.getDrawCRect());
}

/************************************************************************/
/* TODO LIST                                                            */
/************************************************************************/
//TODO: 方中圆
//TODO: 板上的图案（孔槽）
//TODO: 板件外轮廓
//TODO: 放大缩小显示
//TODO: 界面大板栏，界面小板栏
//TODO: 加载数据保存数据
//TODO: 错误信息管理，日志信息管理