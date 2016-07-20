#include "StdAfx.h"
#include "DrawItem.h"

/************************************************************************/
/*  绘图接口 IDrawItem                                                  */
/************************************************************************/

/************************************************************************/
/*  绘图基类 DrawItemBase                                               */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// 构造数据
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
	m_myRect = DrawTools::buildRectF(topLeft,bottomRight);
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
//////////////////////////////////////////////////////////////////////////
// 实现接口
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


void DrawItemBase::setRect(RectF rect)
{
	m_myRect = rect;
}
void DrawItemBase::setRect(PointF topLeft,PointF bottomRight)
{
	setRect(DrawTools::buildRectF(topLeft,bottomRight));
}
void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
{
	setRect(RectF(x1,y1,x2,y2));
}

RectF DrawItemBase::getRect()
{
	return m_myRect;
}

Region DrawItemBase::getRegion()
{
	return Region region(getRect());
}


void DrawItemBase::readPoints(std::vector<PointF>& points)
{
	points.push_back(DrawTools::getTopLeft(getRect()));
	points.push_back(DrawTools::getBottomLeft(getRect()));
	points.push_back(DrawTools::getBottomRight(getRect()));
	points.push_back(DrawTools::getTopRight(getRect()));
}
void DrawItemBase::writePoints(std::list<PointF>& points)
{
	std::vector<PointF> tempArr;
	tempArr.push_back(points.front());
	points.pop_front();
	tempArr.push_back(points.front());
	points.pop_front();
	tempArr.push_back(points.front());
	points.pop_front();
	tempArr.push_back(points.front());
	points.pop_front();

	PointF topLeft(numeric_limits<float>::max(),numeric_limits<float>::max());
	PointF bottomRight(numeric_limits<float>::min(),numeric_limits<float>::min());
	for_each(tempArr.begin(),tempArr.end(),
		[&](PointF p)
	{
		topLeft.X = min(topLeft.X,p.X);
		topLeft.Y = min(topLeft.Y,p.Y);
		bottomRight.X = max(topLeft.X,p.X);
		bottomRight.Y = max(topLeft.Y,p.Y);
	});

	m_myRect = DrawTools::buildRectF(topLeft,bottomRight);
}


void DrawItemBase::moveTo(PointF point)
{
	m_myRect.Offset(point.X - m_myRect.GetLeft(),point.Y - m_myRect.GetTop());
}
void DrawItemBase::move(PointF offset)
{
	m_myRect.Offset(offset.X,offset.Y);
}


void DrawItemBase::OnPaint( Graphics &g )
{
	Region* region = getCloneRigon();
	if (StateNormal == m_state)
	{
		g.FillRegion(&SolidBrush(DrawTools::ColorNormal), region);
	}
	else if (StateHovered == m_state)
	{
		g.FillRegion(&SolidBrush(DrawTools::ColorHovered), region);
	}
	else if (StateDisable == m_state)
	{
		g.FillRegion(&SolidBrush(DrawTools::ColorDisable), region);
	}
	else if (StateDown == m_state)
	{
		g.FillRegion(&SolidBrush(DrawTools::ColorDown), region);
	}
	else if (StateError == m_state)
	{
		g.FillRegion(&SolidBrush(DrawTools::ColorError), region);
	}
	else
	{
		//TODO: 记录日志报错
		OutputDebugString("DrawItemBase::OnPaint() maybe error state\n");
		g.FillRegion(&SolidBrush(DrawTools::ColorNormal), region);
	}
	delete region;
}


//////////////////////////////////////////////////////////////////////////
// 公共数据
const int DrawItemBase::StateNormal = 0;
const int DrawItemBase::StateHovered = 1;
const int DrawItemBase::StateDisable = 2;
const int DrawItemBase::StateDown = 3;
const int DrawItemBase::StateError = 4;

#endif

/************************************************************************/
/*  绘图形状 DrawItemShape                                               */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// 构造
DrawItemShape::DrawItemShape(RectF outterRect,std::vector<IDrawLine*> lines)
{
	m_myRect = outterRect;
	m_lines = lines;
}
DrawItemShape::~DrawItemShape()
{
	if (!m_lines.empty())
	{
		for (unsigned int i = 0;i<m_lines.size();i++)
		{
			delete m_lines[i];
		}
		m_lines.clear();
	}
}

//////////////////////////////////////////////////////////////////////////
// 接口实现
Region DrawItemShape::getRegion()
{
	if (m_lines.size()>0)
	{
		GraphicsPath path;
		path.StartFigure();
		for (unsigned int i = 0;i<m_lines.size();i++)
		{
			m_lines[i]->getPath(path);
		}
		path.CloseFigure();
		return region(&path);
	}
	else
	{
		return DrawItemBase::getRegion();
	}
}

void DrawItemShape::readPoints(std::list<PointF>& points)
{
	for (unsigned int i = 0;i<m_lines.size();i++)
	{
		m_lines[i]->loadPoints(points);
	}
	return result;
}
void DrawItemShape::writePoints(std::list<PointF>& points)
{
	for (unsigned int i = 0;i<m_lines.size();i++)
	{
		m_lines[i]->updatePoints(points);
	}
}

void DrawItemShape::moveTo(PointF point)
{
	move(point - DrawTools::getTopLeft(m_myRect));
}
void DrawItemShape::move(PointF offset)
{
	std::vector<PointF> points = getAllPoints();
	for (unsigned int i = 0;i<points.size();i++)
	{
		points[i] = points[i] + offset;
	}
	setAllPoints(points);
	m_myRect.Offset(offset);
}

void DrawItemShape::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);
}

#endif