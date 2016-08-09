#include "StdAfx.h"
#include "DrawLine.h"
#include "DrawTools.h"

/************************************************************************/
/*  I线段 IDataLine                                                     */
/************************************************************************/
#if 1
#endif
/************************************************************************/
/* 线段基类 DrawLineBase                                                */
/************************************************************************/
#if 1
DataLineBase::DataLineBase(PointF first,PointF last)
{
	m_first = first;
	m_last = last;
}
void DataLineBase::loadPoints(std::list<PointF>& points) const
{
	points.push_back(m_first);
	points.push_back(m_last);
}
void DataLineBase::updatePoints(std::list<PointF>& points)
{
	auto begin = points.cbegin();
	auto end = ++points.cbegin();
	m_first = *begin;
	m_last = *end;
	points.erase(begin,++end);
}
void DataLineBase::getPath(GraphicsPath& path) const
{
	path.AddLine(m_first,m_last);
}
void DataLineBase::getPaint(Graphics &g)
{
	g.DrawLine(&Pen(DrawTools::ColorBorder),m_first,m_last);
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
	:DataLineBase(first,last)
{
	m_radius = radius;
	m_sign = sign;
}

void DrawArcLine::getPath(GraphicsPath& path) const
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
	g.DrawArc(&Pen(DrawTools::ColorBorder),rect,beginAngle,endAngle);
}
#endif