
#include "DataLine.h"
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
	m_points.push_back(first);
	m_points.push_back(last);
}
void DataLineBase::loadPoints(std::list<PointF>& points) const
{
	foreachPoint([&points](const PointF& p){
		points.push_back(p);
	});

}
void DataLineBase::updatePoints(std::list<PointF>& points)
{
	foreachPoint([&points](PointF& p){
		p = points.front();
		points.pop_back();
	});

	m_isChange = true;
}
void DataLineBase::getPath(GraphicsPath& path) const
{	
	auto count = m_points.size();
	auto begin = m_points.cbegin();
	for (int i = 0;i<count-1;++i,++begin)
	{
		auto end = begin;
		advance(end,1);
		path.AddLine(*begin,*end);
	}
}
void DataLineBase::onPaint(Graphics &g)
{
	auto count = m_points.size();
	auto begin = m_points.cbegin();
	for (int i = 0;i<count-1;++i,++begin)
	{
		auto end = begin;
		advance(end,1);
		g.DrawLine(&Pen(DrawTools::ColorBorder),*begin,*end);
	}
}

void DataLineBase::foreachPoint(void (*func)(PointF&))
{
	if(isChange()) m_points_last = m_points;
	foreachPoint(std::ptr_fun(func));
}

void DataLineBase::foreachPoint(void (*func)(const PointF&)) const
{
	foreachPoint(std::ptr_fun(func));
}

bool operator ==(const PointF& lhs,const PointF& rhs)
{
	return lhs.X == rhs.X && lhs.Y== rhs.Y;
}

bool DataLineBase::isChange() const
{
	assert(m_points.size()==m_points_last.size() || m_points_last.size() == 0);
	auto begin = m_points.cbegin(),end = m_points.cend();
	auto begin_last = m_points_last.cbegin(),end_last = m_points_last.cend();
	while (begin != end && begin_last!=end_last 
		&& *(begin++) == *(begin_last++))
	{}

	//若没有遍历到最后一个，则为改变
	return begin != end;
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
	assert(m_points.size() == 2);
	m_radius = radius;
	m_sign = sign;
	m_center = DrawTools::getCircleCenter(first,last,radius,sign);
	m_points.push_back(m_center);
}

DrawArcLine::DrawArcLine(PointF first, PointF last,PointF center)
	:DataLineBase(first,last)
{
	assert(m_points.size() == 2);
	m_points.push_back(m_center);

	//计算sign,radius
	m_radius = DrawTools::getDistance(first,center);
	m_sign = -1;
}

void DrawArcLine::getPath(GraphicsPath& path) const
{
	double beginAngle = 0,sweepAngle = 0;
	RectF rect(getcenter().X-m_radius,getcenter().Y-m_radius,m_radius*2,m_radius*2);
	DrawTools::getAngularCoordinate_DegreeCatchShort(getcenter() , getFrist(), getLast(), 0, beginAngle, sweepAngle);
	DrawTools::getDrawArcAngularCoordinate(beginAngle,sweepAngle);
	path.AddArc(rect,beginAngle,sweepAngle);
}
void DrawArcLine::onPaint(Graphics &g)
{
	double beginAngle = 0,sweepAngle = 0;
	RectF rect(getcenter().X-m_radius,getcenter().Y-m_radius,m_radius*2,m_radius*2);
	DrawTools::getAngularCoordinate_DegreeCatchShort(getcenter() , getFrist(), getLast(), 0, beginAngle, sweepAngle);
	DrawTools::getDrawArcAngularCoordinate(beginAngle,sweepAngle);
	g.DrawArc(&Pen(DrawTools::ColorBorder),rect,beginAngle,sweepAngle);
}

const PointF& DrawArcLine::getcenter()const
{
	auto begin = m_points.begin();
	std::advance(begin,2);
	return *begin;
}

#endif

void DrawLineList::loadPoints(std::list<PointF>& points) const
{
	foreachPoint([&points](const PointF& p){
		points.push_back(p);
	});
}

void DrawLineList::updatePoints(std::list<PointF>& points)
{
	foreachPoint([&points](PointF& p){
		assert(points.empty() == false);
		p = points.front();
		points.pop_front();
	});
}

void DrawLineList::foreachPoint(void (*func) (PointF&))
{
	foreachPoint(std::ptr_fun(func));
}

void DrawLineList::foreachPoint(void (*func) (const PointF&)) const
{
	foreachPoint(std::ptr_fun(func));
}
