#include "StdAfx.h"
#include "DrawLine.h"

/************************************************************************/
/*  I线段 IDrawLine                                                     */
/************************************************************************/
#if 1
#endif
/************************************************************************/
/* 线段基类 DrawLineBase                                                */
/************************************************************************/
#if 1
DrawLineBase::DrawLineBase(PointF first,PointF last)
{
	m_first = first;
	m_last = last;
	m_pen = Pen(DrawTools::ColorBorder);
}
void DrawLineBase::loadPoints(std::vector<PointF>& points)
{
	points.push_back(m_first);
	points.push_back(m_last);
}
void DrawLineBase::updatePoints(std::vector<PointF>& points)
{
	m_first = points.front();
	points.erase(points.begin());

	m_last = points.front();
	points.erase(points.begin());
}
void DrawLineBase::getPath(GraphicsPath& path)
{
	path.AddLine(m_first,m_last);
}
void DrawLineBase::getPaint(Graphics &g)
{
	g.DrawLine(&m_pen,m_first,m_last);
}


void DrawLineBase::setPen(Pen pen)
{
	m_pen = pen;
}
Pen DrawLineBase::getPen()
{
	return m_pen;
}
#endif
/************************************************************************/
/* 直线 DrawStraightLine                                                */
/************************************************************************/
#if 1

#endif
/************************************************************************/
/* 曲线 DrawArcLine                                                     */
/************************************************************************/
#if 1
DrawArcLine::DrawArcLine(PointF first, PointF last, float radius, int sign)
	:DrawLineBase(first,last)
{
	m_radius = radius;
	m_sign = sign;
}

void DrawArcLine::getPath(GraphicsPath& path)
{
	RectF rect;
	double beginAngle;
	double endAngle;
	DrawTools::getArc(m_first,m_last,m_radius,m_sign,
		rect,beginAngle,endAngle);
	path.AddArc(rect,beginAngle,endAngle);

}
void DrawArcLine::getPaint(Graphics &g)
{
	RectF rect;
	double beginAngle;
	double endAngle;
	DrawTools::getArc(m_first,m_last,m_radius,m_sign,
		rect,beginAngle,endAngle);
	g.DrawArc(m_pen,rect,beginAngle,endAngle);
}
#endif