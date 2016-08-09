#include "stdafx.h"
// DrawToolDlg.cpp : ʵ���ļ�
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



// CDrawToolDlg �Ի���




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


// CDrawToolDlg ��Ϣ�������

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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);


	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 120;
	m_manager.setDrawCRect(rcClient);
	//m_manager.Strategy(&m_smallStrategy);
	m_manager.OnInitial();
	initBKDC();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDrawToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

		m_manager.OnPaint(*m_g);//��ͼ
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_dcBackgroud, 0, 0, SRCCOPY);
		
		//CDialogEx::OnPaint();
	}
}

//��Ϣ·��
BOOL CDrawToolDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_manager.PreTranslateMessage(pMsg))
	{
		return TRUE;
	}
	
	//���̰���
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
	//��մ��
	GetDlgItem(IDC_CLEAR)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_CLEAR)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);

	//���¼���
	GetDlgItem(IDC_RELOAD)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_RELOAD)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);

	//���С��
	GetDlgItem(IDC_INPUTITEM)->GetWindowRect(itemRect);
	ScreenToClient(&itemRect);
	GetDlgItem(IDC_INPUTITEM)->SetWindowPos(NULL, itemRect.left, drawClient.bottom + 5 , itemRect.Width(), itemRect.Height(), SWP_SHOWWINDOW);
	
	//����
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
//���
void CDrawToolDlg::OnBnClickedClear()
{
	m_manager.clearDrawItem();
	InvalidateRect(m_manager.getDrawCRect());
}
//���¼���
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

	
	//�����ó�����,������ף������
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

	//���ε�ʱ��SIDE1 �� SIDE2��ת �� SIDE3 �� SIDE4��ת
	//���ķ�����һ����⵽�����ΰ壬��PanelFace�ӽڵ��е�Layer="SIDE1 �ĳ� Layer="SIDE2
	//�����վ�

	std::list<IDrawItem*> infos;
// 	<VERTICAL Layer="VERTICAL14.000000" Name="����1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="483" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(248,483,180,15,15,14));
// 	<VERTICAL Layer="SIDE29.000000" Name="����2">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="483" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,483,0,33,8,9));
// 	<VERTICAL Layer="SIDE29.000000" Name="����1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="451" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,451,0,33,8,9));
// 	<VERTICAL Layer="SIDE29.000000" Name="����1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="99" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,99,0,33,8,9));
// 	<VERTICAL Layer="VERTICAL14.000000" Name="����1">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="67" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(248,67,180,15,15,14));
// 	<VERTICAL Layer="SIDE29.000000" Name="����2">
// 		<Param Name="pos_x" Value="248" />
// 		<Param Name="pos_y" Value="67" />
// 		<Param Name="angle" Value="0" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(2,248,67,0,33,8,9));
// 	<VERTICAL Layer="VERTICAL14.000000" Name="����1">
// 		<Param Name="pos_x" Value="48" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(48,33,180,15,15,14));
// 	<VERTICAL Layer="SIDE49.000000" Name="����2">
// 		<Param Name="pos_x" Value="48" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="90" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(4,48,33,90,33,8,9));
// 	<VERTICAL Layer="SIDE49.000000" Name="����1">
// 		<Param Name="pos_x" Value="144" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="90" />
// 		<Param Name="size_x" Value="33" />
// 		<Param Name="size_y" Value="8" />
// 		<Param Name="depth" Value="9" />
// 		<Param Name="dwgFile" Value="SIDE.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawSideVertical(4,144,33,90,33,8,9));
// 	<VERTICAL Layer="VERTICAL14.000000" Name="����1">
// 		<Param Name="pos_x" Value="240" />
// 		<Param Name="pos_y" Value="33" />
// 		<Param Name="angle" Value="180" />
// 		<Param Name="size_x" Value="15" />
// 		<Param Name="size_y" Value="15" />
// 		<Param Name="depth" Value="14" />
// 		<Param Name="dwgFile" Value="VERTICAL.dwg" />
// 	</VERTICAL>
	infos.push_back(new DrawVertical(240,33,180,15,15,14));
// 		<VERTICAL Layer="SIDE49.000000" Name="����2">
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
	//��ܲ���
	ASSERT(TestDrawTools::TestDrawToolsAll());
	ASSERT(TestDrawLine::TestDrawLineAll());
	ASSERT(TestDrawItem::TestDrawItemAll());
	ASSERT(TestDrawItemManagement::TestDrawItemManagementAll());

	//���̴������
	ASSERT(TestSmallPanel::TestSmallPanelAll());


#if TestNew

#endif
	InvalidateRect(m_manager.getDrawCRect());
}

int CDrawToolDlg::initBKDC()
{
	//����bitmap
	CRect rcClient;
	GetClientRect(rcClient);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(GetDC(), rcClient.Width(), rcClient.Height());

	//��������DC
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

