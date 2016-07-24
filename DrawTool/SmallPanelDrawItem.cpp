#include "StdAfx.h"
#include "SmallPanelDrawItem.h"
#include <algorithm> 
#include "DrawTools.h"

/************************************************************************/
/* 垂直孔 DrawVertical                                                  */
/************************************************************************/
#if 1
DrawVertical::DrawVertical( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
	:DrawItemCircle(RectF(pos_x - (size_x/2),pos_y - (size_y/2),size_x,size_y),pos_x,pos_y,size_x/2)
{
	setState(DrawItemBase::StateSelfDefine);
	m_isFillPath = true;
	m_isDrawPath = true;
	m_drawColor = DrawTools::ColorVertical;;
	m_fillColor = DrawTools::ColorVertical;
}
#endif
/************************************************************************/
/* 侧面孔 DrawSideVertical                                              */
/************************************************************************/
#if 1
DrawSideVertical::DrawSideVertical( int side,float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
	:DrawItemRectangle(RectF(),std::list<IDrawLine* >())
{
	RectF rect;
	switch(side)
	{
	case 1 : rect = buildRect_1_Left( pos_x, pos_y, angle, size_x, size_y, depth); break;
	case 2 : rect = buildRect_2_Right( pos_x, pos_y, angle, size_x, size_y, depth); break;
	case 3 : rect = buildRect_3_Bottom( pos_x, pos_y, angle, size_x, size_y, depth); break;
	case 4 : rect = buildRect_4_Top( pos_x, pos_y, angle, size_x, size_y, depth); break;
	default: rect = buildRect_0_Face( pos_x, pos_y, angle, size_x, size_y, depth); break;
	}
	m_myRect = rect;									//父类构造函数没来得及调用
	m_lines = DrawTools::buildDrawStraightLine(rect);	//父类构造函数没来得及调用
	m_isFillPath = false;
	m_isDrawPath = true;
	m_drawColor = DrawTools::ColorVertical;
}
RectF DrawSideVertical::buildRect_1_Left( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
{
	RectF rect;
	rect.X = pos_x - size_x;
	rect.Y = pos_y - (size_y/2);
	rect.Width = size_x;
	rect.Height = size_y;
	return rect;
}
RectF DrawSideVertical::buildRect_2_Right( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
{
	RectF rect;
	rect.X = pos_x;
	rect.Y = pos_y - (size_y/2);
	rect.Width = size_x;
	rect.Height = size_y;
	return rect;
}
RectF DrawSideVertical::buildRect_3_Bottom( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
{
	RectF rect;
	rect.X = pos_x - (size_y/2);
	rect.Y = pos_y;
	rect.Width = size_y;
	rect.Height = size_x;
	return rect;
}
RectF DrawSideVertical::buildRect_4_Top( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
{
	RectF rect;
	rect.X = pos_x - (size_y/2);
	rect.Y = pos_y - size_x;
	rect.Width = size_y;
	rect.Height = size_x;
	return rect;
}
RectF DrawSideVertical::buildRect_0_Face( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
{
	RectF rect;
	rect.X = pos_x - (size_x/2);
	rect.Y = pos_y - (size_y/2);
	rect.Width = size_x;
	rect.Height = size_y;
	return rect;
}
#endif
/************************************************************************/
/* 侧面孔 DrawSaw                                                       */
/************************************************************************/
#if 1
DrawSaw::DrawSaw( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth )
	:DrawItemRectangle(RectF(),std::list<IDrawLine* >())
{
	RectF rect = DrawSideVertical::buildRect_0_Face( pos_x, pos_y, angle, size_x, size_y, depth);
	DrawItemRectangle &base = *this;
	base = DrawItemRectangle(rect,DrawTools::buildDrawStraightLine(rect));
	m_isFillPath = true;
	m_isDrawPath = true;
	m_drawColor = DrawTools::ColorSaw;
	m_fillColor = DrawTools::ColorSaw;
	setState(DrawItemBase::StateSelfDefine);
}
#endif
/************************************************************************/
/* 小板信息 SmallPanel                                                  */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// 构造
SmallPanel::SmallPanel( RectF rect ):DrawItemBase(rect)
{
	setType(L"SmallPanel");
}

SmallPanel::~SmallPanel( void )
{
	std::for_each(m_outterFrame.begin(),m_outterFrame.end(),[&](IDrawItem* item){delete item;});
	std::for_each(m_innerFrame.begin(),m_innerFrame.end(),[&](IDrawItem* item){delete item;});
	std::for_each(m_innerShape.begin(),m_innerShape.end(),[&](IDrawItem* item){delete item;});
	std::for_each(m_outterShape.begin(),m_outterShape.end(),[&](IDrawItem* item){delete item;});
	std::for_each(m_infoSide.begin(),m_infoSide.end(),[&](IDrawItem* item){delete item;});
	std::for_each(m_infoVertical.begin(),m_infoVertical.end(),[&](IDrawItem* item){delete item;});
	std::for_each(m_infoSaw.begin(),m_infoSaw.end(),[&](IDrawItem* item){delete item;});
}

//////////////////////////////////////////////////////////////////////////
// 接口实现
void SmallPanel::setState( int state )
{
	std::for_each(m_innerFrame.begin(),m_innerFrame.end(),[=](IDrawItem* item){item->setState(state);});
	std::for_each(m_innerShape.begin(),m_innerShape.end(),[=](IDrawItem* item){item->setState(state);});
	DrawItemBase::setState(state);
}


std::shared_ptr<Region> SmallPanel::getRegion()
{
	if (m_innerFrame.size()>0)
	{
		return m_innerShape.front()->getRegion();
	}
	else
	{
		return DrawItemBase::getRegion();
	}
}

void SmallPanel::readPoints( std::list<PointF>& points )
{
	DrawItemBase::readPoints(points);
	std::for_each(m_outterFrame.begin(),m_outterFrame.end(),[&](IDrawItem* item){item->readPoints(points);});
	std::for_each(m_innerFrame.begin(),m_innerFrame.end(),[&](IDrawItem* item){item->readPoints(points);});
	std::for_each(m_innerShape.begin(),m_innerShape.end(),[&](IDrawItem* item){item->readPoints(points);});
	std::for_each(m_outterShape.begin(),m_outterShape.end(),[&](IDrawItem* item){item->readPoints(points);});

	std::for_each(m_infoSide.begin(),m_infoSide.end(),[&](IDrawItem* item){item->readPoints(points);});
	std::for_each(m_infoVertical.begin(),m_infoVertical.end(),[&](IDrawItem* item){item->readPoints(points);});
	std::for_each(m_infoSaw.begin(),m_infoSaw.end(),[&](IDrawItem* item){item->readPoints(points);});
}

void SmallPanel::writePoints( std::list<PointF>& points )
{
	DrawItemBase::writePoints(points);
	std::for_each(m_outterFrame.begin(),m_outterFrame.end(),[&](IDrawItem* item){item->writePoints(points);});
	std::for_each(m_innerFrame.begin(),m_innerFrame.end(),[&](IDrawItem* item){item->writePoints(points);});
	std::for_each(m_innerShape.begin(),m_innerShape.end(),[&](IDrawItem* item){item->writePoints(points);});
	std::for_each(m_outterShape.begin(),m_outterShape.end(),[&](IDrawItem* item){item->writePoints(points);});

	std::for_each(m_infoSide.begin(),m_infoSide.end(),[&](IDrawItem* item){item->writePoints(points);});
	std::for_each(m_infoVertical.begin(),m_infoVertical.end(),[&](IDrawItem* item){item->writePoints(points);});
	std::for_each(m_infoSaw.begin(),m_infoSaw.end(),[&](IDrawItem* item){item->writePoints(points);});
}

void SmallPanel::OnPaint( Graphics &g )
{
	//DrawItemBase::OnPaint(g);	//画区域
	//std::for_each(m_outterFrame.begin(),m_outterFrame.end(),[&](IDrawItem* item){item->OnPaint(g);});
	std::for_each(m_innerFrame.begin(),m_innerFrame.end(),[&](IDrawItem* item){item->OnPaint(g);});
	std::for_each(m_innerShape.begin(),m_innerShape.end(),[&](IDrawItem* item){item->OnPaint(g);});
	//std::for_each(m_outterShape.begin(),m_outterShape.end(),[&](IDrawItem* item){item->OnPaint(g);});

	std::for_each(m_infoSide.begin(),m_infoSide.end(),[&](IDrawItem* item){item->OnPaint(g);});
	std::for_each(m_infoVertical.begin(),m_infoVertical.end(),[&](IDrawItem* item){item->OnPaint(g);});
	std::for_each(m_infoSaw.begin(),m_infoSaw.end(),[&](IDrawItem* item){item->OnPaint(g);});
}

#endif
/************************************************************************/
/* 编辑板件策略 PanelEditionStrategy                                    */
/************************************************************************/
#if 1
#endif