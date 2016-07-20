#include "stdafx.h"
// DrawToolDlg.cpp : 实现文件
//

#include "DrawTool.h"
#include "DrawToolDlg.h"
#include "afxdialogex.h"
#include "DrawItem.h"
#include "SmallPanelDrawItem.h"

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
	ON_WM_SIZE()
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

void CDrawToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 120;
	m_manager.setDrawCRect(rcClient);
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
#if 0	//圆角长方形 + 槽
	/*
	<ComPanel Barcode="160425-1005" Name="底板">
	<ComInfomation>
		<Info Name="助记号" Value="" />
		<Info Name="订单号" Value="160425" />
		<Info Name="柜号" Value="1" />
		<Info Name="条码编号" Value="160425-1005" />
		<Info Name="产品名称" Value="A1型衣柜" />
		<Info Name="成品名称" Value="底板" />
		<Info Name="材质名称" Value="颗粒板/R5681" />
		<Info Name="开料长度" Value="449" />
		<Info Name="开料宽度" Value="498" />
		<Info Name="开料厚度" Value="18" />
		<Info Name="需切数量" Value="1" />
		<Info Name="纹路方向" Value="横纹" />
		<Info Name="封边量" Value="1.5 0.5 0.5 0.5" />
		<Info Name="成品长度" Value="450" />
		<Info Name="成品宽度" Value="500" />
		<Info Name="成品厚度" Value="18" />
		<Info Name="异型" Value="ID:1;gapWidth:310;gapDepth:128;" />
		<Info Name="旋转" Value="0" />
		<Info Name="正面槽" Value="" />
		<Info Name="是否开槽" Value="" />
		<Info Name="反面槽" Value="" />
		<Info Name="正面孔" Value="" />
		<Info Name="是否打孔" Value="" />
		<Info Name="反面孔" Value="" />
		<Info Name="客户信息" Value="" />
		<Info Name="加盟店" Value="广西南宁店" />
		<Info Name="拉槽标识" Value="槽24" />
		<Info Name="排钻标识" Value="钻" />
		<Info Name="钻孔" Value="双" />
		<Info Name="订单类型" Value="" />
		<Info Name="反面条码" Value="160425-2005" />
		<Info Name="异型ID" Value="异01" />
		<Info Name="客户地址" Value="" />
		<Info Name="钻槽标识" Value="A槽24#B钻" />
	</ComInfomation>
	<OutLine>
		<Vector X="10.0000" Y="646.0000" R="0.0000" Sign="0" Dir="0" />
		<Vector X="10.0000" Y="1016.0000" R="0.0000" Sign="0" Dir="0" />
		<Vector X="459.0000" Y="1016.0000" R="0.0000" Sign="0" Dir="0" />
		<Vector X="459.0000" Y="518.0000" R="0.0000" Sign="0" Dir="0" />
		<Vector X="320.0000" Y="518.0000" R="0.0000" Sign="0" Dir="0" />
		<Vector X="320.0000" Y="646.0000" R="0.0000" Sign="0" Dir="0" />
	</OutLine>
	<PanelFace Index="0" Barcode="160425-1005">
		<SAW Layer="ROUTER6.00T6.00" Name="底板开槽">
			<Param Name="pos_x" Value="379.5" />
			<Param Name="pos_y" Value="18.5" />
			<Param Name="angle" Value="0" />
			<Param Name="size_x" Value="140" />
			<Param Name="size_y" Value="10" />
			<Param Name="depth" Value="6" />
			<Param Name="dwgFile" Value="ROUTER_T6.00.dwg" />
		</SAW>
	</PanelFace>
	<PanelFace Index="5" Barcode="160425-2005">
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
			<Param Name="pos_x" Value="416.5" />
			<Param Name="pos_y" Value="175.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
			<Param Name="pos_x" Value="416.5" />
			<Param Name="pos_y" Value="431.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
			<Param Name="pos_x" Value="32.5" />
			<Param Name="pos_y" Value="47.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
			<Param Name="pos_x" Value="32.5" />
			<Param Name="pos_y" Value="431.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
	</PanelFace>
	</ComPanel>
	*/
	//测试用圆角长方形
	RectF rect(0,0,449,498);
	SmallPanelDrawItem* shape = SmallPanelDrawItem::SmallPanelFactory(rect);

	std::list<IDrawLine*> lines;
	lines.push_back(new DrawStraightLine(PointF(0.0000 ,128.0000 ),PointF(0.0000,498.0000)));
	lines.push_back(new DrawStraightLine(PointF(0.0000 ,498.0000),PointF(449.0000,498.0000)));
	lines.push_back(new DrawStraightLine(PointF(449.0000,498.0000),PointF(449.0000,0.0000)));
	lines.push_back(new DrawStraightLine(PointF(449.0000,0.0000 ),PointF(310.0000,0.0000)));
	lines.push_back(new DrawStraightLine(PointF(310.0000,0.0000 ),PointF(310.0000,128.0000)));
	lines.push_back(new DrawStraightLine(PointF(310.0000,128.0000 ),PointF(0.0000,128.0000)));
	lines.push_back(new DrawStraightLine(PointF(310.0000,128.0000 ),PointF(0.0000,128.0000)));
	shape->setOutterLine(lines);

	std::list<IDrawInfo*> infos;
	infos.push_back(new DrawSaw(379.5,18.5,0,140,10,6));
	shape->setVertical(infos);

	m_manager.addDrawItem(shape);
#endif	//圆角长方形 + 槽

#if 0	//测试侧面孔显示
	/*
	<OutLine>
		<Vector X="0" Y="0" R="0" Sign="0" Dir="0" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="0" Y="-531" R="0" Sign="0" Dir="0" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="131" Y="-531" R="150" Sign="1" Dir="1" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="281" Y="-381" R="150" Sign="2" Dir="1" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="281" Y="0" R="0" Sign="0" Dir="0" Cut="0" OutDir="0" type="0" A="" />
	</OutLine>
	<PanelFace Index="5" Barcode="20160713153251B002">
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
			<Param Name="pos_x" Value="248" />
			<Param Name="pos_y" Value="483" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="开孔2">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="483" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="开孔1">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="451" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="开孔1">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="99" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="67" />
		<Param Name="angle" Value="180" />
		<Param Name="size_x" Value="15" />
		<Param Name="size_y" Value="15" />
		<Param Name="depth" Value="14" />
		<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="开孔2">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="67" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
		<Param Name="pos_x" Value="48" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="180" />
		<Param Name="size_x" Value="15" />
		<Param Name="size_y" Value="15" />
		<Param Name="depth" Value="14" />
		<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE39.000000" Name="开孔2">
		<Param Name="pos_x" Value="48" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="90" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE39.000000" Name="开孔1">
		<Param Name="pos_x" Value="144" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="90" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="开孔1">
		<Param Name="pos_x" Value="240" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="180" />
		<Param Name="size_x" Value="15" />
		<Param Name="size_y" Value="15" />
		<Param Name="depth" Value="14" />
		<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE39.000000" Name="开孔2">
		<Param Name="pos_x" Value="240" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="90" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
	</PanelFace>
	*/

	//
	//  lines.push_back(new DrawStraightLine(PointF(,),PointF(,)));
	//  lines.push_back(new DrawArcLine(PointF(,),PointF(,),0,0));
	//测试用长方形,带侧面孔，正面孔
	RectF rect(0,0,281,531);
	SmallPanelDrawItem* shape = SmallPanelDrawItem::SmallPanelFactory(rect);
	
	std::list<IDrawLine*> lines;
	lines.push_back(new DrawStraightLine(PointF(0,0),PointF(0,381)));
	lines.push_back(new DrawArcLine(PointF(0,381),PointF(150,531),150,1));
	lines.push_back(new DrawStraightLine(PointF(150,531),PointF(281,531)));
	lines.push_back(new DrawStraightLine(PointF(281,531),PointF(281,0)));
	lines.push_back(new DrawStraightLine(PointF(281,0),PointF(0,0)));

	shape->setOutterLine(lines);

	//异形的时候，SIDE1 和 SIDE2翻转 ， SIDE3 和 SIDE4翻转
	//更改方法：一旦检测到是异形板，将PanelFace子节点中的Layer="SIDE1 改成 Layer="SIDE2
	//其他照旧

	std::list<IDrawInfo*> infos;
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
	shape->setVertical(infos);

	m_manager.addDrawItem(shape);

#endif	//测试侧面孔显示

#if 0	//圆角长方形 + 槽
	// 	<Vector X="1998.0000" Y="10.0000" R="0.0000" Sign="0" Dir="0" />
	// 	<Vector X="370.0000" Y="10.0000" R="360.0000" Sign="1" Dir="1" />
	// 	<Vector X="10.0000" Y="370.0000" R="360.0000" Sign="2" Dir="1" />
	// 	<Vector X="1998.0000" Y="370.0000" R="0.0000" Sign="0" Dir="0" />
	//
	//  lines.push_back(new DrawStraightLine(PointF(,),PointF(,)));
	//  lines.push_back(new DrawArcLine(PointF(,),PointF(,),0,0));
	//测试用圆角长方形
	RectF rect(5,5,400,370);
	SmallPanelDrawItem* shape = SmallPanelDrawItem::SmallPanelFactory(rect);

	std::list<IDrawLine*> lines;
	lines.push_back(new DrawStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
	lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
	lines.push_back(new DrawStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
	lines.push_back(new DrawStraightLine(PointF(400,370.0000),PointF(400,10.0000)));
	shape->setOutterLine(lines);

	std::list<IDrawInfo*> infos;
	infos.push_back(new DrawSaw(370.0,20,0,18,18,1));
	shape->setVertical(infos);

	m_manager.addDrawItem(shape);
#endif	//圆角长方形 + 槽


	
#if 0	//圆弧三角
//画一个圆角三角形
 		// 	<Vector X="1998.0000" Y="10.0000" R="0.0000" Sign="0" Dir="0" />
 		// 	<Vector X="370.0000" Y="10.0000" R="360.0000" Sign="1" Dir="1" />
 		// 	<Vector X="10.0000" Y="370.0000" R="360.0000" Sign="2" Dir="1" />
 		// 	<Vector X="1998.0000" Y="370.0000" R="0.0000" Sign="0" Dir="0" />
 		//
 		//  lines.push_back(new DrawStraightLine(PointF(,),PointF(,)));
 		//  lines.push_back(new DrawArcLine(PointF(,),PointF(,),0,0));
 		//
 		RectF rect(10,10,390,360);
 		std::list<IDrawLine*> lines;
 		lines.push_back(new DrawStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
 		lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
 		lines.push_back(new DrawStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
 		lines.push_back(new DrawStraightLine(PointF(400,370.0000),PointF(400,10.0000)));
 
 		DrawItemShape* shape = new DrawItemShape(rect,lines);
 		shape->setType(L"companel");
		m_manager.addDrawItem(shape);
#endif // 圆弧三角
	
#if 0 //测试用凹型
	//测试用凹型
	std::list<PointF> points;
	points.push_back(PointF(0,0));
	points.push_back(PointF(50,0));
	points.push_back(PointF(50,50));
	points.push_back(PointF(150,50));
	points.push_back(PointF(150,0));
	points.push_back(PointF(200,0));
	points.push_back(PointF(200,100));
	points.push_back(PointF(0,100));
	DrawItemPolygon* panel = new DrawItemPolygon(points);
	m_manager.addDrawItem(panel);
#endif //测试用凹型

#if 0 //测试用三角形
	//测试用三角形
	std::list<PointF> points;
	points.push_back(PointF(0,0));
	points.push_back(PointF(100,100));
	points.push_back(PointF(200,50));
	DrawItemPolygon* panel = new DrawItemPolygon(points);
	m_manager.addDrawItem(panel);
#endif //测试用三角形

#if 0 //正方形
	//测试用正方形
	DrawItemBase* item = new DrawItemBase();
	item->setRect(0,0,100,100);
	m_manager.addDrawItem(item);
#endif // 正方形

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

#define TestOnce 0
#define TestNew 0
void CDrawToolDlg::OnBnClickedTest()
{
	//测试画图形的点移动是否恰当
#if TestOnce
	{
		ASSERT(DrawTools::ArcSignLeft == 1);

		RectF rect(10,10,390,360);
		std::list<IDrawLine*> lines;
		lines.push_back(new DrawStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
		lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
		lines.push_back(new DrawStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
		lines.push_back(new DrawStraightLine(PointF(400,370.0000),PointF(400,10.0000)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);

		shape->move(PointF(0,0));
		std::list<PointF> points = shape->getAllPoints();
		ASSERT(points.front().Equals(PointF(400,10)));

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
		ASSERT(begin1 == 270);
		ASSERT(sweep1 == -90);
	}
#endif

	//画圆弧
#if TestOnce
	//画圆弧 * 4 = 一个圆
	{
		RectF rect(0,0,100,100);
		std::list<IDrawLine*> lines;
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
		std::list<IDrawLine*> lines;
		lines.push_back(new DrawArcLine(PointF(100.0000,00.0000),PointF(0.0000,100),100,1));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		m_manager.addDrawItem(shape);

		DrawItemShape* item = (DrawItemShape*)m_manager.getDrawItemList().front();
		std::list<PointF> points = item->getAllPoints();

		ASSERT(points.front().X == 100);
		ASSERT(points.front().Y == 0.0);
		points.pop_front();
		ASSERT(points.front().X == 0.0);
		ASSERT(points.front().Y == 100);
		//m_manager.clearDrawItem();
	}
	//画三角形
	{	
		RectF rect(0,0,100,100);
		std::list<IDrawLine*> lines;
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
		std::list<IDrawLine*> lines;
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
		std::list<IDrawLine*> lines;
		lines.push_back(new DrawStraightLine(PointF(100.0,0.0000),PointF(0.0,100.0)));
		lines.push_back(new DrawStraightLine(PointF(0.0,100.0000),PointF(100.0000,100.0)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,0.0)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		shape->setType(L"companel");
		m_manager.addDrawItem(shape);

		//得到所有点
		std::list<PointF> origin1 = shape->getAllPoints();

		//旋转图形4次（回到原位置）
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);

		//获得所有新的点，比较旋转后所有点是否还在原位置
		std::list<PointF> result1 = shape->getAllPoints();
		ASSERT(origin1.size() == result1.size());
		auto itterOrigin = origin1.begin();
		for(auto itterMLine = m_lines.begin();itterMLine < result1.end() ; itterMLine++,itterOrigin++ )
		for (unsigned int i = 0;i<result1.size() ; i++)
		{
			bool a = (*itterMLine).Equals((*itterOrigin));

			//CString mm;
			//mm.Format(L"%d (%f, %f) (%f, %f)\n",a,(*itterMLine).X,(*itterMLine).Y,(*itterOrigin).X,(*itterOrigin).Y);
			//OutputDebugString(mm);


			ASSERT(fabs((*itterMLine).X - (*itterOrigin).X) <0.0000001);
			ASSERT(fabs((*itterMLine).Y - (*itterOrigin).Y) <0.0000001);
			//ASSERT((*itterMLine).Equals((*itterOrigin)));
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

		std::list<PointF> origin2 = shape->getAllPoints();

		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);

		std::list<PointF> result2 = shape->getAllPoints();
		ASSERT(origin2.size() == result2.size());
		for(auto itterMLine = m_lines.begin();itterMLine < m_lines.end() ; itterMLine++ )
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
		std::list<IDrawLine*> lines;

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

		std::list<IDrawLine*> lines2;

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


