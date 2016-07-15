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
	m_myRect = RectF(0,0,0,0);
}

DrawItemBase::DrawItemBase(PointF topLeft,PointF bottomRight)
{
	m_type = "";
	m_ID = "";
	m_order = 0;
	m_state = StateNormal;
	m_myRect = buildRectF(topLeft,bottomRight);
}

DrawItemBase::DrawItemBase(RectF rect)
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

void DrawItemBase::moveTo(PointF point)
{
	m_myRect.Offset(point.X - m_myRect.GetLeft(),point.Y - m_myRect.GetTop());
}

void DrawItemBase::move(PointF offset)
{
	m_myRect.Offset(offset.X,offset.Y);
}

void DrawItemBase::setRect(RectF rect)
{
	m_myRect = rect;
}
void DrawItemBase::setRect(PointF topLeft,PointF bottomRight)
{
	setRect(buildRectF(topLeft,bottomRight));
}
void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
{
	setRect(RectF(x1,y1,x2,y2));
}

RectF DrawItemBase::getRect()
{
	return m_myRect;
}

std::vector<PointF> DrawItemBase::getPoints()
{
	std::vector<PointF> points;
	points.push_back(getTopLeft(getRect()));
	points.push_back(getBottomRight(getRect()));
	return points;
}
Region* DrawItemBase::getCloneRigon()
{
	Region region(getRect());
	return region.Clone();  
}

bool DrawItemBase::IsVisible(PointF point)
{
	Region region(getRect());
	return region.IsVisible(point.X,point.Y);
}
RectF DrawItemBase::buildRectF(PointF topLeft,PointF bottomRight)
{
	return RectF(topLeft.X ,
		topLeft.Y ,
		bottomRight.X - topLeft.X ,
		bottomRight.Y - topLeft.Y
		);
}

PointF DrawItemBase::getTopLeft(RectF rect)
{
	return PointF(rect.GetLeft(),rect.GetTop());
}
PointF DrawItemBase::getBottomRight(RectF rect)
{
	return PointF(rect.GetRight(),rect.GetBottom());
}
PointF DrawItemBase::getTopRight(RectF rect)
{
	return PointF(rect.GetRight(),rect.GetTop());
}
PointF DrawItemBase::getBottomLeft(RectF rect)
{
	return PointF(rect.GetLeft(),rect.GetBottom());
}
#endif
/************************************************************************/
/*  直线多边形                                                            */
/************************************************************************/
#if 1
DrawItemPolygon::DrawItemPolygon()
{
	m_type = "companel";
}
DrawItemPolygon::DrawItemPolygon(PointF topLeft,PointF bottomRight)
{
	m_type = "companel";
	
	RectF rect = buildRectF(topLeft,bottomRight);
	std::vector<PointF> points;
	points.push_back(getTopLeft(rect));
	points.push_back(getTopRight(rect));
	points.push_back(getBottomRight(rect));
	points.push_back(getBottomLeft(rect));
	setOutline(points);
}
DrawItemPolygon::DrawItemPolygon(RectF rect)
{
	m_type = "companel";

	std::vector<PointF> points;
	points.push_back(getTopLeft(rect));
	points.push_back(getTopRight(rect));
	points.push_back(getBottomRight(rect));
	points.push_back(getBottomLeft(rect));
	setOutline(points);
}
DrawItemPolygon::DrawItemPolygon(const std::vector<PointF>& outlines)
{
	m_type = "companel";

	setOutline(outlines);
}
DrawItemPolygon::~DrawItemPolygon()
{

}

void DrawItemPolygon::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);
}

void DrawItemPolygon::setOutline(std::vector<PointF> outlines)
{
	PointF topLeft(MAXINT,MAXINT);
	PointF bottomRight(MININT,MININT);
	m_outlines.clear();
	for(unsigned int i = 0; i < outlines.size() ; i++)
	{
		//x最小的值保持在
		if (outlines[i].X < topLeft.X)
		{
			topLeft.X = outlines[i].X;
		}
		//x最大的值保持在
		if (outlines[i].X > bottomRight.X)
		{
			bottomRight.X = outlines[i].X;
		}
		//y最小的值保持在
		if (outlines[i].Y < topLeft.Y)
		{
			topLeft.Y = outlines[i].Y;
		}
		//y最大的值保持在
		if (outlines[i].Y > bottomRight.Y)
		{
			bottomRight.Y = outlines[i].Y;
		}
		m_outlines.push_back(outlines[i]);
	}

	setRect(buildRectF(topLeft,bottomRight));
	
}

std::vector<PointF> DrawItemPolygon::getOutline()
{
	return m_outlines;
}

void DrawItemPolygon::moveTo(PointF point)
{
	PointF topLeft = getTopLeft(getRect());
	move(PointF(point.X - topLeft.X,point.Y - topLeft.Y));
}
void DrawItemPolygon::move(PointF offset)
{
	for (unsigned int i = 0;i<m_outlines.size();i++)
	{
		m_outlines[i] = m_outlines[i] + offset;
	}
	m_myRect.Offset(offset.X,offset.Y);
}

void DrawItemPolygon::setRect(RectF rect)
{
	m_myRect = rect;
}
RectF DrawItemPolygon::getRect()
{
	return m_myRect;
}

Gdiplus::Region* DrawItemPolygon::getCloneRigon()
{
	if (m_outlines.size()>0)
	{
// 		GraphicsPath path;
// 		Point* outlineArr = getOutlineArrClone();
// 		path.AddPolygon(outlineArr,m_outlines.size());
// 		Region region(&path);
// 		delete outlineArr;
// 		return region.Clone(); 

		GraphicsPath path;
		path.StartFigure();
		//Point* outlineArr = getOutlineArrClone();
		path.AddArc(0,0,100,100,00.0,360.0);
		path.CloseFigure();
		//path.AddPolygon(outlineArr,m_outlines.size());
		Region region(&path);
		return region.Clone(); 
		//delete outlineArr;
	}
	else
	{
		Region region;
		return region.Clone();
	}
}
bool DrawItemPolygon::IsVisible(PointF point)
{
	if (m_outlines.size()>0)
	{
// 		GraphicsPath path;
// 		Point* outlineArr = getOutlineArrClone();
// 		path.AddPolygon(outlineArr,m_outlines.size());
// 		Region region(&path);
// 		delete outlineArr;
// 		return region.IsVisible(point.X,point.Y);

		GraphicsPath path;
		path.StartFigure();
		//Point* outlineArr = getOutlineArrClone();
		path.AddArc(0,0,100,100,00.0,360.0);
		path.CloseFigure();
		//path.AddPolygon(outlineArr,m_outlines.size());
		Region region(&path);
		return region.IsVisible(point.X,point.Y);
		//delete outlineArr;

	}
	else
	{
		return false;
	}
}

Point* DrawItemPolygon::getOutlineArrClone()
{
	Point* outlineArr = new Point[m_outlines.size()];
	for (int i = 0;i<m_outlines.size();i++)
	{
		outlineArr[i].X = m_outlines[i].X;
		outlineArr[i].Y = m_outlines[i].Y;
	}
	return outlineArr;
}
#endif

/************************************************************************/
/*  直线拼圆弧多边形                                                            */
/************************************************************************/
#if 1
#endif