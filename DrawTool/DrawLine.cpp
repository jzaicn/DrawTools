#include "StdAfx.h"
#include "DrawLine.h"
#include "DrawTools.h"

/************************************************************************/
/*  I�߶� IDrawLine                                                     */
/************************************************************************/
#if 1
#endif
/************************************************************************/
/* �߶λ��� DrawLineBase                                                */
/************************************************************************/
#if 1
DrawLineBase::DrawLineBase(PointF first,PointF last)
{
	m_first = first;
	m_last = last;
}
void DrawLineBase::loadPoints(std::list<PointF>& points)
{
	points.push_back(m_first);
	points.push_back(m_last);
}
void DrawLineBase::updatePoints(std::list<PointF>& points)
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
	g.DrawLine(&Pen(DrawTools::ColorBorder),m_first,m_last);
}
#endif
/************************************************************************/
/* ֱ�� DrawStraightLine                                                */
/************************************************************************/
#if 1

#endif
/************************************************************************/
/* ���� DrawArcLine                                                     */
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
	g.DrawArc(&Pen(DrawTools::ColorBorder),rect,beginAngle,endAngle);
}
#endif