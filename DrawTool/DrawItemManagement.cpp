#include "StdAfx.h"
#include "afxwin.h"
#include "DrawItemManagement.h"


DrawItemManagement::DrawItemManagement(void)
{
}


DrawItemManagement::~DrawItemManagement(void)
{
}
// 
// void DrawItemManagement::OnPaint(CPaintDC& dc)
// {
// 	CDC dcMem;
// 	dcMem.CreateCompatibleDC(&dc);
// 	CBitmap bmpMem;
// 	bmpMem.CreateCompatibleBitmap(&dc, m_drawRect.Width(), m_drawRect.Height());
// 	dcMem.SelectObject(&bmpMem);
// 	Graphics g(dcMem.m_hDC);
// 
// 	OnPaintWithoutPrework(g);	//��ͼ
// 
// 	dc.BitBlt(0, 0, m_drawRect.Width(), m_drawRect.Height(), &dcMem, 0, 0, SRCCOPY);
// 
// 	bmpMem.DeleteObject();
// 	dcMem.DeleteDC();
// }

void DrawItemManagement::OnPaintWithoutPrework(Graphics& g)
{
	//������ɫ
	g.FillRectangle(&SolidBrush(Color::Black), m_drawRect.left, m_drawRect.top, m_drawRect.Width(), m_drawRect.Height());

	//��ÿ����Ԫ��
	for(int i = 0; i < m_DrawItemList.size(); i++)
	{
		m_staticDrawItemList[i]->OnPaint(g);
	}

	//��ÿ����Ԫ��
	for(int i = 0; i < m_DrawItemList.size(); i++)
	{
		m_activeDrawItemList[i]->OnPaint(g);
	}
}


void DrawItemManagement::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

BOOL DrawItemManagement::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void DrawItemManagement::OnMouseMove(UINT nFlags, CPoint point)
{
	

	for (int i = 0;i<m_activeDrawItemList.size();i++)
	{
		CRect itemRect = m_activeDrawItemList[i]->getRect();


		HRGN itemRgn=CreateRectRgn(itemRect.left,itemRect.top,itemRect.right,itemRect.bottom);
		CombineRgn(crashRgn,itemRgn,crashRgn,RGN_OR);
		Region rgn(RectF(10,10,100,200));  


		if (checkMoveable(m_DrawItemList[i],point))
		{
			m_DrawItemList[i]->OnMouseMove(point);
		}
	}
}

void DrawItemManagement::OnLButtonDown(UINT nFlags, CPoint point)
{
	for (int i = 0;i<m_DrawItemList.size();i++)
	{
		m_DrawItemList[i]->OnLButtonDown(point);
	}
}

void DrawItemManagement::OnLButtonUp(UINT nFlags, CPoint point)
{
	for (int i = 0;i<m_DrawItemList.size();i++)
	{
		m_DrawItemList[i]->OnLButtonUp(point);
	}
}

void DrawItemManagement::OnRButtonDown(UINT nFlags, CPoint point)
{
	for (int i = 0;i<m_DrawItemList.size();i++)
	{
		m_DrawItemList[i]->OnRButtonDown(point);
	}
}

void DrawItemManagement::OnRButtonUp(UINT nFlags, CPoint point)
{
	for (int i = 0;i<m_DrawItemList.size();i++)
	{
		m_DrawItemList[i]->OnRButtonUp(point);
	}
}



















void DrawItemManagement::addDrawItem(IDrawItem* drawItem)
{
	m_DrawItemList.push_back(drawItem);
}

std::vector<IDrawItem*>& DrawItemManagement::getDrawItemList()
{
	return m_DrawItemList;
}

void DrawItemManagement::clearDrawItem()
{
	for (int i = 0;i<m_DrawItemList.size();i++)
	{
		delete m_DrawItemList[i];
	}
	m_DrawItemList.clear();
}

void DrawItemManagement::setDrawRect(CRect drawRect)
{
	m_drawRect = drawRect;
}

CRect DrawItemManagement::getDrawRect()
{
	return m_drawRect;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
bool DrawItemManagement::checkMoveable(IDrawItem* item , CPoint point)
{

	return m_drawRect.PtInRect(point);
}

