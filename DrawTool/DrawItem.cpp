#include "StdAfx.h"
#include "DrawItem.h"

#include "L4Cpp.h"

/************************************************************************/
/*  绘图基类                                                            */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// 基础颜色定义
Color DrawItemBase::ColorNormal = Color(228, 238, 249);
Color DrawItemBase::ColorHovered = Color(242, 247, 252);
Color DrawItemBase::ColorDisable = Color(211, 216, 224);
Color DrawItemBase::ColorDown = Color(255, 255 ,255);
Color DrawItemBase::ColorError = Color(230, 12,3);

//////////////////////////////////////////////////////////////////////////
// 基础状态定义
const int DrawItemBase::StateNormal = 0;
const int DrawItemBase::StateHovered = 1;
const int DrawItemBase::StateDisable = 2;
const int DrawItemBase::StateDown = 3;
const int DrawItemBase::StateError = 4;

//////////////////////////////////////////////////////////////////////////
//实际基础类
DrawItemBase::DrawItemBase()
{
	m_type = "";
	m_ID = "";
	m_order = 0;
	m_state = StateNormal;
	m_myRect = CRect(0,0,0,0);
}

DrawItemBase::DrawItemBase(CPoint topLeft,CPoint bottomRight)
{
	m_type = "";
	m_ID = "";
	m_order = 0;
	m_state = StateNormal;
	m_myRect = CRect(topLeft,bottomRight);
}

DrawItemBase::DrawItemBase(CRect rect)
{
	m_type = "";
	m_ID = "";
	m_order = 0;
	m_state = StateNormal;
	m_myRect = rect;
}

DrawItemBase::~DrawItemBase(void)
{
}

void DrawItemBase::setState(int state)
{
	m_state = state;
}
int DrawItemBase::getState()
{
	return m_state;
}

void DrawItemBase::setType(CString type)
{
	m_type = type;
}
CString DrawItemBase::getType()
{
	return m_type;
}

void DrawItemBase::setID(CString id)
{
	m_ID = id;
}
CString DrawItemBase::getID()
{
	return m_ID;
}

void DrawItemBase::setOrder(int order)
{
	m_order = order;
}
int DrawItemBase::getOrder()
{
	return m_order;
}

void DrawItemBase::OnPaint( Graphics &g )
{
	Region* region = getCloneRigon();
	if (StateNormal == m_state)
	{
		g.FillRegion(&SolidBrush(ColorNormal), region);
	}
	else if (StateHovered == m_state)
	{
		g.FillRegion(&SolidBrush(ColorHovered), region);
	}
	else if (StateDisable == m_state)
	{
		g.FillRegion(&SolidBrush(ColorDisable), region);
	}
	else if (StateDown == m_state)
	{
		g.FillRegion(&SolidBrush(ColorDown), region);
	}
	else if (StateError == m_state)
	{
		g.FillRegion(&SolidBrush(ColorError), region);
	}
	else
	{
		//TODO: 记录日志报错
		g.FillRegion(&SolidBrush(ColorNormal), region);
	}
	delete region;
}

void DrawItemBase::moveTo(CPoint point)
{
	m_myRect.MoveToXY(point.x,point.y);
}

void DrawItemBase::move(CPoint offset)
{
	m_myRect.OffsetRect(offset.x,offset.y);
}

void DrawItemBase::setRect(CRect rect)
{
	m_myRect = rect;
}
void DrawItemBase::setRect(CPoint topLeft,CPoint bottomRight)
{
	setRect(CRect(topLeft,bottomRight));
}
void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
{
	setRect(CRect(x1,y1,x2,y2));
}

CRect DrawItemBase::getRect()
{
	return m_myRect;
}

std::vector<CPoint> DrawItemBase::getPoints()
{
	std::vector<CPoint> points;
	points.push_back(getRect().TopLeft());
	points.push_back(getRect().BottomRight());
	return points;
}
Region* DrawItemBase::getCloneRigon()
{
	CRect rect = getRect();
	Region region(Rect(rect.left,rect.top,rect.Width(),rect.Height()));
	return region.Clone();  
}

bool DrawItemBase::IsVisible(CPoint point)
{
	CRect rect = getRect();
	Region region(Rect(rect.left,rect.top,rect.Width(),rect.Height()));
	return region.IsVisible(point.x,point.y);
}
#endif
/************************************************************************/
/*  绘图小板类                                                            */
/************************************************************************/
#if 1
DrawItemSmallPanel::DrawItemSmallPanel()
{

}
DrawItemSmallPanel::DrawItemSmallPanel(CPoint topLeft,CPoint bottomRight)
{
	m_myRect = CRect(topLeft,bottomRight);
}
DrawItemSmallPanel::DrawItemSmallPanel(CRect rect)
{
	m_myRect = rect;
}
DrawItemSmallPanel::DrawItemSmallPanel(const std::vector<CPoint>& outlines)
{
	setOutline(outlines);
}
DrawItemSmallPanel::~DrawItemSmallPanel()
{

}

void DrawItemSmallPanel::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);
}

void DrawItemSmallPanel::setOutline(std::vector<CPoint> outlines)
{
	CPoint topLeft(MAXINT,MAXINT);
	CPoint bottomRight(MININT,MININT);
	for(int i = 0; i < outlines.size() ; i++)
	{
		//x最小的值保持在
		if (outlines[i].x < topLeft.x)
		{
			topLeft.x = outlines[i].x;
		}
		//x最大的值保持在
		if (outlines[i].x > bottomRight.x)
		{
			bottomRight.x = outlines[i].x;
		}
		//y最小的值保持在
		if (outlines[i].y < topLeft.y)
		{
			topLeft.y = outlines[i].y;
		}
		//y最大的值保持在
		if (outlines[i].y > bottomRight.y)
		{
			bottomRight.y = outlines[i].y;
		}
		m_outlines.push_back(outlines[i]);
	}

	setRect(CRect(topLeft,bottomRight));
	
}

std::vector<CPoint> DrawItemSmallPanel::getOutline()
{
	return m_outlines;
}

void DrawItemSmallPanel::moveTo(CPoint point)
{
	CPoint topLeft = getRect().TopLeft();
	move(CPoint(point.x - topLeft.x,point.y - topLeft.y));
}
void DrawItemSmallPanel::move(CPoint offset)
{
	for (int i = 0;i<m_outlines.size();i++)
	{
		m_outlines[i].Offset(offset);
	}
}

void DrawItemSmallPanel::setRect(CRect rect)
{
	//TODO: 待商议的移动方法
	moveTo(rect.TopLeft());
}
CRect DrawItemSmallPanel::getRect()
{
	return m_myRect;
}

Gdiplus::Region* DrawItemSmallPanel::getCloneRigon()
{
	if (m_outlines.size()>0)
	{
		GraphicsPath path;
		Point* outlineArr = getOutlineArr();
		path.AddPolygon(outlineArr,m_outlines.size());
		Region region(&path);
		delete outlineArr;
		return region.Clone(); 
	}
	else
	{
		Region region;
		return region.Clone();
	}
}
bool DrawItemSmallPanel::IsVisible(CPoint point)
{
	if (m_outlines.size()>0)
	{
		GraphicsPath path;
		Point* outlineArr = getOutlineArr();
		path.AddPolygon(outlineArr,m_outlines.size());
		Region region(&path);
		delete outlineArr;
		return region.IsVisible(point.x,point.y);
	}
	else
	{
		return false;
	}
}

Point* DrawItemSmallPanel::getOutlineArr()
{
	Point* outlineArr = new Point[m_outlines.size()];
	for (int i = 0;i<m_outlines.size();i++)
	{
		outlineArr[i].X = m_outlines[i].x;
		outlineArr[i].Y = m_outlines[i].y;
	}
	return outlineArr;
}

#endif