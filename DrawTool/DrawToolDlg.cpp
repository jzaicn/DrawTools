
// DrawToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawTool.h"
#include "DrawToolDlg.h"
#include "afxdialogex.h"
#include "DrawItem.h"

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
//	ON_WM_MOUSEWHEEL()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONDOWN()
ON_WM_RBUTTONUP()
ON_BN_CLICKED(IDC_RELOAD, &CDrawToolDlg::OnBnClickedReload)
ON_BN_CLICKED(IDC_INPUTITEM, &CDrawToolDlg::OnBnClickedInputitem)
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_rcDragArea.SetRect(0, 0, 300, 300);


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
		CPaintDC dc(this);

		CRect rcClient;
		GetClientRect(rcClient);

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
		dcMem.SelectObject(&bmpMem);

		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);//GetBkColor(dc.m_hDC);

		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
		g.FillRectangle(&SolidBrush(Color::Black), m_rcDragArea.left, m_rcDragArea.top, m_rcDragArea.Width(), m_rcDragArea.Height());


		for(int i = 0; i < m_vpDragableRect.size(); i++)
		{
			m_vpDragableRect[i]->Draw(g);
		}

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

//���°���
void CDrawToolDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CDrawToolDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CDrawToolDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(m_nSelectedDragRect != -1 && m_nSelectedDragRect < m_vpDragableRect.size())
	{
		CRect rc = (CRect)(*(m_vpDragableRect[m_nSelectedDragRect]));
		rc.OffsetRect(point.x - m_ptDragStartPos.x, point.y - m_ptDragStartPos.y);
		m_vpDragableRect[m_nSelectedDragRect]->SetRect(rc.left, rc.top, rc.right, rc.bottom);
		m_ptDragStartPos = point;
		InvalidateRect(m_rcDragArea);
	}
	else
	{
		for(int i = 0; i < m_vpDragableRect.size(); i++)
		{
			if (m_vpDragableRect[i]->PtInRect(point) &&  m_vpDragableRect[i]->GetButtonState() != CSkinButton::bs_Down)
				m_vpDragableRect[i]->SetButtonState(CSkinButton::bs_Hovered);
			else if(!m_vpDragableRect[i]->PtInRect(point))
				m_vpDragableRect[i]->SetButtonState(CSkinButton::bs_Normal);

		}
	}


	CDialogEx::OnMouseMove(nFlags, point);
}

void CDrawToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for(int i = 0; i < m_vpDragableRect.size(); i++)
	{
		if (m_vpDragableRect[i]->PtInRect(point))
		{
			m_vpDragableRect[i]->SetButtonState(CSkinButton::bs_Down);
			m_nSelectedDragRect = i;
			m_ptDragStartPos = point;
			break;
		}
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDrawToolDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	if(m_nSelectedDragRect != -1 && m_nSelectedDragRect < m_vpDragableRect.size())
	{
		m_vpDragableRect[m_nSelectedDragRect]->SetButtonState(CSkinButton::bs_Hovered);
		m_nSelectedDragRect = -1;
		InvalidateRect(m_rcDragArea);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDrawToolDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnRButtonDown(nFlags, point);
}

void CDrawToolDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSkinButton* pNewBtn = new CSkinButton(L"", 0, 0, 0, this);
	int nPanelWidth = 50;
	int nPanelHeight = 50;
	pNewBtn->SetRect(m_rcDragArea.left, m_rcDragArea.top, m_rcDragArea.left+nPanelWidth, m_rcDragArea.top+nPanelHeight);

	addItemDrawMap(pNewBtn);

	InvalidateRect(m_rcDragArea);
}

void CDrawToolDlg::clearDrawMap()
{
	for (int i = 0;i<m_vpDragableRect.size();i++)
	{
		delete m_vpDragableRect[i];
	}
	m_vpDragableRect.clear();
}

void CDrawToolDlg::addItemDrawMap(CSkinButton* drawItem)
{
	m_vpDragableRect.push_back(drawItem);
}