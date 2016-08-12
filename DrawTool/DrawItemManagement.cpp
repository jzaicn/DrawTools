#include "afxwin.h"
#include "DrawTools.h"
#include <algorithm>
#include "DrawItemManagement.h"


DrawItemManagement::DrawItemManagement(void)
{
	m_strategy= nullptr;
	m_backgroundColor = Color::Black;

	m_strategy = new DrawItemStrategyBase();
}
DrawItemManagement::~DrawItemManagement(void)
{
	delete m_strategy;
	clearDrawItem();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//响应初始化
void DrawItemManagement::OnInitial()
{
	m_strategy->OnInitial(m_allDrawItemList);
}

void DrawItemManagement::OnPaint(Graphics& g)
{
	//画背景色
	g.FillRectangle(&SolidBrush(m_backgroundColor),getDrawRectF());

	m_strategy->OnPaint(g,m_allDrawItemList);
}

bool DrawItemManagement::PreTranslateMessage(MSG* pMsg)
{

	return m_strategy->PreTranslateMessage(pMsg,m_allDrawItemList);
    
}

BOOL DrawItemManagement::OnEraseBkgnd(CDC* pDC)
{
	return m_strategy->OnEraseBkgnd(pDC,m_allDrawItemList);
}

void DrawItemManagement::OnMouseMove(UINT nFlags, PointF point)
{
	m_strategy->OnMouseMove(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnLButtonDown(UINT nFlags, PointF point)
{
	m_strategy->OnLButtonDown(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnLButtonUp(UINT nFlags, PointF point)
{
	m_strategy->OnLButtonUp(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnRButtonDown(UINT nFlags, PointF point)
{
	m_strategy->OnRButtonDown(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnRButtonUp(UINT nFlags, PointF point)
{
	m_strategy->OnRButtonUp(nFlags,point,m_allDrawItemList);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/


void DrawItemManagement::addDrawItem(IDrawItem* drawItem)
{
	m_allDrawItemList.push_back(drawItem);
}

void DrawItemManagement::setDrawItemList( std::list<IDrawItem*> list )
{
	m_allDrawItemList = list;
}

std::list<IDrawItem*> DrawItemManagement::getDrawItemList()
{
	return m_allDrawItemList;
}

void DrawItemManagement::clearDrawItem()
{
	for(auto itter = m_allDrawItemList.begin();itter != m_allDrawItemList.end() ; itter++ )
	{
		delete (*itter);
	}
	m_allDrawItemList.clear();
	//m_strategy->OnClear(m_allDrawItemList);
}


void DrawItemManagement::setDrawRectF(RectF drawRect)
{
	m_drawRect = drawRect;
}

void DrawItemManagement::setDrawCRect(CRect drawRect)
{
	setDrawRectF(DrawTools::buildRectF(drawRect));
}

RectF DrawItemManagement::getDrawRectF()
{
	return m_drawRect;
}

CRect DrawItemManagement::getDrawCRect()
{
	return DrawTools::buildCRect(m_drawRect);
}
