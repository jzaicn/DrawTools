#include "stdafx.h"
// DrawToolDlg.cpp : ʵ���ļ�
//

#include "DrawTool.h"
#include "DrawToolDlg.h"
#include "afxdialogex.h"
#include "DrawItem.h"
#include "SmallPanelDrawItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CDrawToolDlg �Ի���




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


// CDrawToolDlg ��Ϣ�������

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

	//ShowWindow(SW_MAXIMIZE);


	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 120;
	m_manager.setDrawCRect(rcClient);

	CreateOutterFrame(m_manager.getDrawRectF());



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

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

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
		dcMem.SelectObject(&bmpMem);
		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);

		
		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), RectF(rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height()));
		
		m_manager.OnPaint(g);//��ͼ

		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);

		bmpMem.DeleteObject();
		dcMem.DeleteDC();

		//CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDrawToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//��Ϣ·��
BOOL CDrawToolDlg::PreTranslateMessage(MSG* pMsg)
{
	//���̰���
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
//���°���
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
#if 0	//Բ�ǳ����� + ��
	/*
	<ComPanel Barcode="160425-1005" Name="�װ�">
	<ComInfomation>
		<Info Name="���Ǻ�" Value="" />
		<Info Name="������" Value="160425" />
		<Info Name="���" Value="1" />
		<Info Name="������" Value="160425-1005" />
		<Info Name="��Ʒ����" Value="A1���¹�" />
		<Info Name="��Ʒ����" Value="�װ�" />
		<Info Name="��������" Value="������/R5681" />
		<Info Name="���ϳ���" Value="449" />
		<Info Name="���Ͽ��" Value="498" />
		<Info Name="���Ϻ��" Value="18" />
		<Info Name="��������" Value="1" />
		<Info Name="��·����" Value="����" />
		<Info Name="�����" Value="1.5 0.5 0.5 0.5" />
		<Info Name="��Ʒ����" Value="450" />
		<Info Name="��Ʒ���" Value="500" />
		<Info Name="��Ʒ���" Value="18" />
		<Info Name="����" Value="ID:1;gapWidth:310;gapDepth:128;" />
		<Info Name="��ת" Value="0" />
		<Info Name="�����" Value="" />
		<Info Name="�Ƿ񿪲�" Value="" />
		<Info Name="�����" Value="" />
		<Info Name="�����" Value="" />
		<Info Name="�Ƿ���" Value="" />
		<Info Name="�����" Value="" />
		<Info Name="�ͻ���Ϣ" Value="" />
		<Info Name="���˵�" Value="����������" />
		<Info Name="���۱�ʶ" Value="��24" />
		<Info Name="�����ʶ" Value="��" />
		<Info Name="���" Value="˫" />
		<Info Name="��������" Value="" />
		<Info Name="��������" Value="160425-2005" />
		<Info Name="����ID" Value="��01" />
		<Info Name="�ͻ���ַ" Value="" />
		<Info Name="��۱�ʶ" Value="A��24#B��" />
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
		<SAW Layer="ROUTER6.00T6.00" Name="�װ忪��">
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
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
			<Param Name="pos_x" Value="416.5" />
			<Param Name="pos_y" Value="175.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
			<Param Name="pos_x" Value="416.5" />
			<Param Name="pos_y" Value="431.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
			<Param Name="pos_x" Value="32.5" />
			<Param Name="pos_y" Value="47.5" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
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
	//������Բ�ǳ�����
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
#endif	//Բ�ǳ����� + ��

#if 0	//���Բ������ʾ
	/*
	<OutLine>
		<Vector X="0" Y="0" R="0" Sign="0" Dir="0" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="0" Y="-531" R="0" Sign="0" Dir="0" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="131" Y="-531" R="150" Sign="1" Dir="1" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="281" Y="-381" R="150" Sign="2" Dir="1" Cut="0" OutDir="0" type="0" A="" />
		<Vector X="281" Y="0" R="0" Sign="0" Dir="0" Cut="0" OutDir="0" type="0" A="" />
	</OutLine>
	<PanelFace Index="5" Barcode="20160713153251B002">
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
			<Param Name="pos_x" Value="248" />
			<Param Name="pos_y" Value="483" />
			<Param Name="angle" Value="180" />
			<Param Name="size_x" Value="15" />
			<Param Name="size_y" Value="15" />
			<Param Name="depth" Value="14" />
			<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="����2">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="483" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="����1">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="451" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="����1">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="99" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="67" />
		<Param Name="angle" Value="180" />
		<Param Name="size_x" Value="15" />
		<Param Name="size_y" Value="15" />
		<Param Name="depth" Value="14" />
		<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE19.000000" Name="����2">
		<Param Name="pos_x" Value="248" />
		<Param Name="pos_y" Value="67" />
		<Param Name="angle" Value="0" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
		<Param Name="pos_x" Value="48" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="180" />
		<Param Name="size_x" Value="15" />
		<Param Name="size_y" Value="15" />
		<Param Name="depth" Value="14" />
		<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE39.000000" Name="����2">
		<Param Name="pos_x" Value="48" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="90" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE39.000000" Name="����1">
		<Param Name="pos_x" Value="144" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="90" />
		<Param Name="size_x" Value="33" />
		<Param Name="size_y" Value="8" />
		<Param Name="depth" Value="9" />
		<Param Name="dwgFile" Value="SIDE.dwg" />
		</VERTICAL>
		<VERTICAL Layer="VERTICAL14.000000" Name="����1">
		<Param Name="pos_x" Value="240" />
		<Param Name="pos_y" Value="33" />
		<Param Name="angle" Value="180" />
		<Param Name="size_x" Value="15" />
		<Param Name="size_y" Value="15" />
		<Param Name="depth" Value="14" />
		<Param Name="dwgFile" Value="VERTICAL.dwg" />
		</VERTICAL>
		<VERTICAL Layer="SIDE39.000000" Name="����2">
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
	//�����ó�����,������ף������
	RectF rect(0,0,281,531);
	SmallPanelDrawItem* shape = SmallPanelDrawItem::SmallPanelFactory(rect);
	
	std::list<IDrawLine*> lines;
	lines.push_back(new DrawStraightLine(PointF(0,0),PointF(0,381)));
	lines.push_back(new DrawArcLine(PointF(0,381),PointF(150,531),150,1));
	lines.push_back(new DrawStraightLine(PointF(150,531),PointF(281,531)));
	lines.push_back(new DrawStraightLine(PointF(281,531),PointF(281,0)));
	lines.push_back(new DrawStraightLine(PointF(281,0),PointF(0,0)));

	shape->setOutterLine(lines);

	//���ε�ʱ��SIDE1 �� SIDE2��ת �� SIDE3 �� SIDE4��ת
	//���ķ�����һ����⵽�����ΰ壬��PanelFace�ӽڵ��е�Layer="SIDE1 �ĳ� Layer="SIDE2
	//�����վ�

	std::list<IDrawInfo*> infos;
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
	shape->setVertical(infos);

	m_manager.addDrawItem(shape);

#endif	//���Բ������ʾ

#if 0	//Բ�ǳ����� + ��
	// 	<Vector X="1998.0000" Y="10.0000" R="0.0000" Sign="0" Dir="0" />
	// 	<Vector X="370.0000" Y="10.0000" R="360.0000" Sign="1" Dir="1" />
	// 	<Vector X="10.0000" Y="370.0000" R="360.0000" Sign="2" Dir="1" />
	// 	<Vector X="1998.0000" Y="370.0000" R="0.0000" Sign="0" Dir="0" />
	//
	//  lines.push_back(new DrawStraightLine(PointF(,),PointF(,)));
	//  lines.push_back(new DrawArcLine(PointF(,),PointF(,),0,0));
	//������Բ�ǳ�����
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
#endif	//Բ�ǳ����� + ��


	
#if 0	//Բ������
//��һ��Բ��������
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
#endif // Բ������
	
#if 0 //�����ð���
	//�����ð���
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
#endif //�����ð���

#if 0 //������������
	//������������
	std::list<PointF> points;
	points.push_back(PointF(0,0));
	points.push_back(PointF(100,100));
	points.push_back(PointF(200,50));
	DrawItemPolygon* panel = new DrawItemPolygon(points);
	m_manager.addDrawItem(panel);
#endif //������������

#if 0 //������
	//������������
	DrawItemBase* item = new DrawItemBase();
	item->setRect(0,0,100,100);
	m_manager.addDrawItem(item);
#endif // ������

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
	//���Ի�ͼ�εĵ��ƶ��Ƿ�ǡ��
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

	//DrawTools������ת���Ƿ�õ�
#if TestOnce
	//��Ƕȼ���
	{
	 	PointF center(50,50);
	 
	 	//����
	 	PointF point1(100,50);
	 	double angle1 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point1));
	 	ASSERT(angle1 == 0.0);
	 
	 	//������
	 	PointF point2(100,0);
	 	double angle2 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point2));
	 	ASSERT(angle2 == 45.0);
	 
	 	//������
	 	PointF point3(50,00);
	 	double angle3 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point3));
	 	ASSERT(angle3 == 90.0);
	 
	 	//������
	 	PointF point4(00,00);
	 	double angle4 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point4));
	 	ASSERT(angle4 == 135.0);
	 
	 	//����
	 	PointF point5(0,50);
	 	double angle5 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point5));
	 	ASSERT(angle5 == 180.0);
	 
	 	//������
	 	PointF point6(0,100);
	 	double angle6 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point6));
	 	ASSERT(angle6 == 225.0);
	 
	 	//������
	 	PointF point7(50,100);
	 	double angle7 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point7));
	 	ASSERT(angle7 == 270.0);
	 
	 	//������
	 	PointF point8(100,100);
	 	double angle8 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point8));
	 	ASSERT(angle8 == 315.0);
	 
	}
	//������������
	{
		PointF center(50.0,50.0);
		double beginAngle = 0.0 ,sweepAngle = 0.0;

		//����4������
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



		//��׷һȦ4������
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

	//���׷��
	{
		PointF center(50.0,50.0);
		double beginAngle = 0.0 ,sweepAngle = 0.0;

		//����4������
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



		//��׷һȦ4������
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
	//��ʽ�����굽��ʾ�ý�����ת��
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

	//��Բ��
#if TestOnce
	//��Բ�� * 4 = һ��Բ
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
	//��Բ��
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
	//��������
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
	//��б����Բ��ֱ��������
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

	//�����������ת
#if TestOnce
	{
		//����������
		RectF rect(0,0,100,100);
		std::list<IDrawLine*> lines;
		lines.push_back(new DrawStraightLine(PointF(100.0,0.0000),PointF(0.0,100.0)));
		lines.push_back(new DrawStraightLine(PointF(0.0,100.0000),PointF(100.0000,100.0)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,0.0)));
		DrawItemShape* shape = new DrawItemShape(rect,lines);
		shape->setType(L"companel");
		m_manager.addDrawItem(shape);

		//�õ����е�
		std::list<PointF> origin1 = shape->getAllPoints();

		//��תͼ��4�Σ��ص�ԭλ�ã�
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);
		m_manager.rotateDrawItem(shape);

		//��������µĵ㣬�Ƚ���ת�����е��Ƿ���ԭλ��
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

		//��ȡ���Χ�߿����ڵ�ǰͼ���������ε��ڽ�ֱ�������Σ�
		//������ÿ����ת���жϵ�һ���㶼�Ƕ��㡣
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
	//���з�
	{
		RectF rect(0,0,100,100);
		std::list<IDrawLine*> lines;

		//��߿�
		lines.push_back(new DrawStraightLine(PointF(100.0,0.0000),PointF(0.0,00.0)));
		lines.push_back(new DrawStraightLine(PointF(00.0,0.0000),PointF(0.0,100.0)));
		lines.push_back(new DrawStraightLine(PointF(0.0,100.0000),PointF(100.0000,100.0)));
		lines.push_back(new DrawStraightLine(PointF(100.0000,100.0000),PointF(100.0000,0.0)));

		//��С��1
		lines.push_back(new DrawStraightLine(PointF(40,10),PointF(10,10)));
		lines.push_back(new DrawStraightLine(PointF(10,10),PointF(10,90)));
		lines.push_back(new DrawStraightLine(PointF(10,90),PointF(40,90)));
		lines.push_back(new DrawStraightLine(PointF(40,90),PointF(40,10)));

// 		//��С��2
// 		lines.push_back(new DrawStraightLine(PointF(50,90),PointF(80,90)));
// 		lines.push_back(new DrawStraightLine(PointF(80,90),PointF(80,10)));
// 		lines.push_back(new DrawStraightLine(PointF(80,10),PointF(50,10)));
// 		lines.push_back(new DrawStraightLine(PointF(50,10),PointF(50,90)));


		DrawItemShape* shape = new DrawItemShape(rect,lines);
		shape->setType(L"companel");
		m_manager.addDrawItem(shape);

		std::list<IDrawLine*> lines2;

		//��С��
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
//TODO: ����Բ
//TODO: ���ϵ�ͼ�����ײۣ�
//TODO: ���������
//TODO: �Ŵ���С��ʾ
//TODO: ��������������С����
//TODO: �������ݱ�������
//TODO: ������Ϣ������־��Ϣ����


