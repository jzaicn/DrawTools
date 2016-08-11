#include "StdAfx.h"
#include "DrawItem.h"

#include "DrawTools.h"

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
	m_isDrawPath = false;
	m_isFillPath = true;
	m_drawColor = DrawTools::ColorBorder;
	m_fillColor = DrawTools::ColorNormal;
}
DrawItemBase::DrawItemBase(PointF topLeft,PointF bottomRight)
{
	m_type = "";
	m_ID = "";
	m_order = 0;
	m_state = StateNormal;
	m_myRect = DrawTools::buildRectF(topLeft,bottomRight);
	m_isDrawPath = false;
	m_isFillPath = true;
	m_drawColor = DrawTools::ColorBorder;
	m_fillColor = DrawTools::ColorNormal;
}
DrawItemBase::DrawItemBase(RectF rect)
{
	m_type = "";
	m_ID = "";
	m_order = 0;
	m_state = StateNormal;
	m_myRect = rect;
	m_isDrawPath = false;
	m_isFillPath = true;
	m_drawColor = DrawTools::ColorBorder;
	m_fillColor = DrawTools::ColorNormal;
}
DrawItemBase::~DrawItemBase(void)
{
}
//////////////////////////////////////////////////////////////////////////
// 实现接口
void DrawItemBase::setState(const int& state)
{
	m_state = state;
}
const int& DrawItemBase::getState()const
{
	return m_state;
}

void DrawItemBase::setType(const CString& type)
{
	m_type = type;
}
const CString& DrawItemBase::getType()const
{
	return m_type;
}

void DrawItemBase::setID(const CString& id)
{
	m_ID = id;
}
const CString& DrawItemBase::getID()const
{
	return m_ID;
}

void DrawItemBase::setOrder(const int& order)
{
	m_order = order;
}
const int& DrawItemBase::getOrder()const
{
	return m_order;
}


void DrawItemBase::setRect(RectF rect)
{
	m_myRect = rect;
	m_region = std::shared_ptr<Region>(new Region(getRect()));	
}
RectF DrawItemBase::getRect()const
{
	return m_myRect;
}

void DrawItemBase::setDrawPath(bool isDrawPath)
{
	m_isDrawPath = isDrawPath;
}
void DrawItemBase::setFillPath(bool isFillPath)
{
	m_isFillPath = isFillPath;
}

const std::shared_ptr<Region>& DrawItemBase::getRegion()
{
	if(isChangeRegion()) ResetRegion();
	return m_region;
}

//
//const std::shared_ptr<Region>& DrawItemBase::getRegion() const
//{	
//	return m_region;
//}
//
//
//void DrawItemBase::readPoints(std::list<PointF>& points) const
//{
//	points.push_back(DrawTools::getTopLeft(getRect()));
//	points.push_back(DrawTools::getBottomLeft(getRect()));
//	points.push_back(DrawTools::getBottomRight(getRect()));
//	points.push_back(DrawTools::getTopRight(getRect()));
//}
//void DrawItemBase::writePoints(std::list<PointF>& points)
//{
//	auto begin = points.begin();
//	auto end = begin;
//	std::advance(end,4);
//
//	std::list<PointF> tempArr(begin,end);
//	points.erase(begin,end);
//	
//	PointF topLeft(FLT_MAX,FLT_MAX);
//	PointF bottomRight(FLT_MIN,FLT_MIN);
//	for(auto itter = tempArr.begin();itter != tempArr.end() ; itter++ )
//	{
//		topLeft.X = (topLeft.X < (*itter).X ? topLeft.X : (*itter).X);
//		topLeft.Y = (topLeft.Y < (*itter).Y ? topLeft.Y : (*itter).Y);
//		bottomRight.X = (bottomRight.X > (*itter).X ? bottomRight.X :(*itter).X);
//		bottomRight.Y = (bottomRight.Y > (*itter).Y ? bottomRight.Y :(*itter).Y);
//	}
//	m_myRect = DrawTools::buildRectF(topLeft,bottomRight);
//}
//

// void DrawItemBase::moveTo(PointF point)
// {
// 	PointF temp = point - DrawTools::getTopLeft(getRect());
// 	move(point);
// }
// void DrawItemBase::move(PointF offset)
// {
// 	std::list<PointF> points;
// 	readPoints(points);
// 	for(auto itter = points.begin();itter != points.end() ; itter++ )
// 	{
// 		(*itter) = (*itter) + offset;
// 	}
// 	writePoints(points);
// }

// 
// void DrawItemBase::OnPaint( Graphics &g )
// {
// 	auto region = getRegion();
// 	static SolidBrush brush(DrawTools::ColorNormal);
// 	if (m_isFillPath)
// 	{
// 		if (StateNormal == m_state)
// 		{
// 			brush.SetColor(DrawTools::ColorNormal);
// 		}
// 		else if (StateHovered == m_state)
// 		{
// 			brush.SetColor(DrawTools::ColorHovered);
// 			//g.FillRegion(&SolidBrush(DrawTools::ColorHovered), region.get());
// 		}
// 		else if (StateDisable == m_state)
// 		{
// 			brush.SetColor(DrawTools::ColorDisable);
// 			//g.FillRegion(&SolidBrush(DrawTools::ColorDisable), region.get());
// 		}
// 		else if (StateDown == m_state)
// 		{
// 			brush.SetColor(DrawTools::ColorDown);
// 			//g.FillRegion(&SolidBrush(DrawTools::ColorDown), region.get());
// 		}
// 		else if (StateError == m_state)
// 		{
// 			brush.SetColor(DrawTools::ColorError);
// 			//g.FillRegion(&SolidBrush(DrawTools::ColorError), region.get());
// 		}
// 		else
// 		{
// 			brush.SetColor(m_fillColor);
// 		}
// 		g.FillRegion(&brush, region.get());
// 	}
// 	if (m_isDrawPath)
// 	{
// 		g.DrawRectangle(&Pen(m_drawColor),getRect());
// 	}
// }


//////////////////////////////////////////////////////////////////////////
// 公共数据
const int DrawItemBase::StateSelfDefine = 0;
const int DrawItemBase::StateNormal = 1;
const int DrawItemBase::StateHovered = 2;
const int DrawItemBase::StateDisable = 3;
const int DrawItemBase::StateDown = 4;
const int DrawItemBase::StateError = 5;

#endif

/************************************************************************/
/*  绘图形状 DrawItemShape                                               */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// 构造
DrawItemShape::DrawItemShape(RectF rect,const std::list<IDataLine*>& lines)
{
	m_myRect = rect;
	m_lines = lines;
	setRegion(lines);
}
DrawItemShape::~DrawItemShape()
{
	if (!m_lines.empty())
	{
		for(auto itter = m_lines.begin();itter != m_lines.end() ; itter++ )
		{
			delete (*itter);
		}
		m_lines.clear();
	}
}

//////////////////////////////////////////////////////////////////////////
// 接口实现
// const std::shared_ptr<Region>& DrawItemShape::getRegion() const
// {
// 	return DrawItemBase::getRegion();	
// }

void DrawItemShape::readPoints(std::list<PointF>& points) const
{
	for(auto itter = m_lines.begin();itter != m_lines.end() ; itter++ )
	{
		(*itter)->loadPoints(points);
	}
}
void DrawItemShape::writePoints(std::list<PointF>& points)
{
	for(auto itter = m_lines.begin();itter != m_lines.end() ; itter++ )
	{
		(*itter)->updatePoints(points);
	}
}

void DrawItemShape::move(PointF offset)
{
	foreachPoint([&offset](PointF& p){
		p = p+offset;
	});
}

void DrawItemShape::OnPaint( Graphics &g )
{
	if(isChangeRegion())
	{
		ResetRegion();
	}
	std::shared_ptr<Region> region = getRegion();
	static SolidBrush brush(DrawTools::ColorNormal);
	if (m_isFillPath)
	{
		if (StateNormal == m_state)
		{
			g.FillRegion(&brush, region.get());
		}
		else if (StateHovered == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorHovered), region.get());
		}
		else if (StateDisable == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorDisable), region.get());
		}
		else if (StateDown == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorDown), region.get());
		}
		else if (StateError == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorError), region.get());
		}
		else
		{
			g.FillRegion(&SolidBrush(m_fillColor), region.get());
		}
	}
	if (m_isDrawPath)
	{
		GraphicsPath path;
		path.StartFigure();
		for(auto itter = m_lines.begin();itter != m_lines.end() ; itter++ )
		{
			(*itter)->getPath(path);
		}
		path.CloseFigure();

		g.DrawPath(&Pen(m_drawColor),&path);
	}
}

void DrawItemShape::setRegion(const std::list<IDataLine*>& lines)
{
	GraphicsPath path;
	path.StartFigure();
	for(auto itter = m_lines.begin();itter != m_lines.end() ; itter++ )
	{
		(*itter)->getPath(path);
	}
	path.CloseFigure();
	m_region = std::shared_ptr<Region>(new Region(&path));
}

void DrawItemShape::foreachPoint(void (*func) (PointF&))
{
	foreachPoint(std::ptr_fun(func));
}

void DrawItemShape::foreachPoint(void (*func) (const PointF&)) const
{
	foreachPoint(std::ptr_fun(func));
}

bool DrawItemShape::isChangeRegion() const
{
	auto it = std::find_if(m_lines.begin(),m_lines.end(),std::mem_fun(&IDataLine::isChange));
	return it != m_lines.end();
}

void DrawItemShape::ResetRegion()
{
	setRegion(m_lines);
}

#endif

/************************************************************************/
/*  绘图形状 DrawItemCircle                                             */
/************************************************************************/
#if 1
DrawItemCircle::DrawItemCircle( RectF rect,float pos_x,float pos_y,float radius )
	:DrawItemShape(rect,std::list<IDataLine*>())
{
	initCircle(rect,pos_x,pos_y,radius);
}
void DrawItemCircle::initCircle(RectF rect,float pos_x,float pos_y,float radius)
{
	setRect(rect);
	RectF rectCircle = RectF(pos_x - radius,pos_y - radius,radius*2.0,radius*2.0);
	//获得圆弧上下左右各点
	PointF top( (rectCircle.GetRight() + rectCircle.GetLeft())/2 , rectCircle.GetTop() );
	PointF left( rectCircle.GetLeft() , (rectCircle.GetBottom() + rectCircle.GetTop())/2 );
	PointF bottom((rectCircle.GetRight() + rectCircle.GetLeft())/2,rectCircle.GetBottom());
	PointF right(rectCircle.GetRight(),(rectCircle.GetBottom() + rectCircle.GetTop())/2);

	m_lines.clear();
	m_lines.push_back(new DrawArcLine(top,left,radius,DrawTools::ArcSignLeft));
	m_lines.push_back(new DrawArcLine(left,bottom,radius,DrawTools::ArcSignLeft));
	m_lines.push_back(new DrawArcLine(bottom,right,radius,DrawTools::ArcSignLeft));
	m_lines.push_back(new DrawArcLine(right,top,radius,DrawTools::ArcSignLeft));
}
#endif
/************************************************************************/
/*  绘图形状 DrawItemRectangle                                          */
/************************************************************************/
#if 1
DrawItemRectangle::DrawItemRectangle( RectF rect,std::list<IDataLine*> lines )
	:DrawItemShape(rect,lines)
{
	
}
#endif
