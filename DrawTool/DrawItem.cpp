#include "StdAfx.h"
#include "DrawItem.h"

#include "L4Cpp.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

DrawItemBase::DrawItemBase()
{
	m_isActive = false;
	m_posStart = CPoint(0,0);
	m_myRect = CRect(0,0,0,0);
}

DrawItemBase::~DrawItemBase(void)
{
}

//获得包围矩形
CRect DrawItemBase::getRect()
{
	return m_myRect;
}

//获得类型
CString DrawItemBase::getType()
{
	return CString();
}

//获得ID
CString DrawItemBase::getID()
{
	return CString();
}

//获得顺序
int DrawItemBase::getZIndex()
{
	return 0;
}

//画图
void DrawItemBase::OnPaint( Graphics &g )
{
	g.FillRectangle(&SolidBrush(Color::Blue), m_myRect.left,m_myRect.top,m_myRect.Width(),m_myRect.Height());
}

//是否可用
bool DrawItemBase::isActive()
{
	return m_isActive;
}

//是否选中，//TODO: 应该抽取到策略中
bool DrawItemBase::checkSelected( CPoint point )
{
	return (bool)(m_myRect.PtInRect(point));
}

void DrawItemBase::OnCommand( CString command,CString param )
{
}

void DrawItemBase::OnMouseMove( CPoint point )
{
	if (isActive())
	{
		CRect rc = m_myRect;
		rc.OffsetRect(point.x - m_posStart.x, point.y - m_posStart.y);
		m_myRect.SetRect(rc.left, rc.top, rc.right, rc.bottom);
		m_posStart = point;
	}
}

void DrawItemBase::OnLButtonDown(CPoint point)
{
	if (checkSelected(point))
	{
		//有效的时候，譬如布置的时候，点击意味着确认摆放
		if (isActive())
		{
			endActive(point);
		}
		//无效的时候，譬如静止，点击意味着受到点选
		else
		{
			beginActive(point);
		}
	}
}

void DrawItemBase::OnLButtonUp(CPoint point)
{
	if (checkSelected(point))
	{
		//有效的时候，譬如布置的时候，释放意味着确认摆放
		if (isActive())
		{
			endActive(point);
		}
	}
}

void DrawItemBase::OnRButtonDown(CPoint point)
{

}

void DrawItemBase::OnRButtonUp(CPoint point)
{

}

//开始启动
void DrawItemBase::beginActive(CPoint point)
{
	m_isActive = true;

	m_posStart = point;

	L4Cpp::Log()->debug("beginActive");
}
//结束启动
void DrawItemBase::endActive(CPoint point)
{
	m_isActive = false;

	m_posStart = point;

	L4Cpp::Log()->debug("endActive");
}
//设置矩形位置，矩形必须而接口非必须
void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
{
	m_myRect.SetRect(x1,y1,x2,y2);
}
//设置矩形位置，矩形必须而接口非必须
void DrawItemBase::setRect(CPoint topLeft,CPoint bottomRight)
{
	m_myRect.SetRect(topLeft.x,topLeft.y,bottomRight.x,bottomRight.y);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
