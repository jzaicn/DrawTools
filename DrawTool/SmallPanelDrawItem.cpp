#include "StdAfx.h"
#include "SmallPanelDrawItem.h"

/************************************************************************/
/* 板件额外信息                                                          */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
DrawInfoBase::DrawInfoBase(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
{
	m_pos_x = pos_x;
	m_pos_y = pos_y;
	m_angle = angle;
	m_size_x = size_x;
	m_size_y = size_y;
	m_depth = depth;
}

void DrawInfoBase::loadPoints( std::vector<PointF>& points )
{
	points.push_back(PointF(m_pos_x,m_pos_y));
}

void DrawInfoBase::updatePoints( std::vector<PointF>& points )
{
	PointF point = points.front();
	points.erase(points.begin());
}

void DrawInfoBase::drawLineToGraphic( Graphics &g )
{
	RectF rect;
	rect.X = m_pos_x - (m_size_x/2);
	rect.Y = m_pos_y - (m_size_y/2);
	rect.Width = m_size_x;
	rect.Height = m_size_y;
	g.DrawRectangle(&Pen(DrawTools::ColorVertical),rect);
}
//
////////////////////////////////////////////////////////////////////////////
//
//void DrawSaw::loadPoints( std::vector<PointF>& points )
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//void DrawSaw::updatePoints( std::vector<PointF>& points )
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//void DrawSaw::drawLineToGraphic( Graphics &g )
//{
//	throw std::exception("The method or operation is not implemented.");
//}

#endif
/************************************************************************/
/*  板件初始化                                                           */
/************************************************************************/
Color SmallPanelDrawItem::ColorBorder = Color::Black;
Color SmallPanelDrawItem::ColorShapeBorder = Color::Yellow;
Color SmallPanelDrawItem::ColorVertical = Color::Blue;
Color SmallPanelDrawItem::ColorSaw = Color::Blue;

SmallPanelDrawItem::SmallPanelDrawItem(void):
 DrawItemShape(RectF(0,0,0,0),std::vector<IDrawLine*>())
{
}


SmallPanelDrawItem::~SmallPanelDrawItem(void)
{
}

SmallPanelDrawItem* SmallPanelDrawItem::SmallPanelFactory(RectF rect)
{
	SmallPanelDrawItem* smallPanel = new SmallPanelDrawItem();
	smallPanel->setType(L"SmallPanel");
	smallPanel->setRect(rect);
	return smallPanel;
}

/************************************************************************/
/* 板件绘制                                                             */
/************************************************************************/


void SmallPanelDrawItem::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);	//画区域
	OnPaintBorder(g);			//画边缘
	OnPaintOtherShape(g);		//画异形数据
	//TODO: 孔
	OnPaintVertical(g);
	//TODO: 槽
	OnPaintSaw(g);
}

void SmallPanelDrawItem::OnPaintBorder( Graphics &g )
{
	RectF rect = getRect();
	g.DrawRectangle(&Pen(ColorBorder),rect);
}

void SmallPanelDrawItem::OnPaintOtherShape( Graphics &g )
{
	GraphicsPath path;
	buildPath(path);
	Region region(&path);
	g.FillRegion(&SolidBrush(ColorShapeBorder), &region);
	g.DrawPath(&Pen(ColorVertical),&path);
}

void SmallPanelDrawItem::OnPaintVertical( Graphics &g )
{
	RectF rect = getRect();
	g.DrawRectangle(&Pen(ColorBorder),rect);
}

void SmallPanelDrawItem::OnPaintSaw( Graphics &g )
{
	RectF rect = getRect();
	g.DrawRectangle(&Pen(ColorBorder),rect);
}


/************************************************************************/
/* 移动信息                                                             */
/************************************************************************/

void SmallPanelDrawItem::moveTo( PointF point )
{
	DrawItemBase::moveTo(point);
}

void SmallPanelDrawItem::move( PointF offset )
{
	std::vector<PointF> points = getAllPoints();
	for (unsigned int i = 0;i<points.size();i++)
	{
		points[i] = points[i] + offset;
	}
	setAllPoints(points);
	DrawItemBase::move(offset);
}

void SmallPanelDrawItem::setRect( RectF rect )
{
	DrawItemBase::setRect(rect);
}

RectF SmallPanelDrawItem::getRect()
{
	return DrawItemBase::getRect();
}

Gdiplus::Region* SmallPanelDrawItem::getCloneRigon()
{
	return DrawItemBase::getCloneRigon();
}

bool SmallPanelDrawItem::IsVisible( PointF point )
{
	return DrawItemBase::IsVisible(point);
}


/************************************************************************/
/* 点坐标转换                                                            */
/************************************************************************/
void SmallPanelDrawItem::setOutterLine(std::vector<IDrawLine*> outterline)
{
	m_lines = outterline;
}

void SmallPanelDrawItem::addInnerLine(std::vector<IDrawLine*> outterline)
{

}
void SmallPanelDrawItem::setInnerLine(std::vector<std::vector<IDrawLine*>> outterline)
{

}
std::vector<std::vector<IDrawLine*>> SmallPanelDrawItem::getInnerLine()
{
	return std::vector<std::vector<IDrawLine*>>();
}

void SmallPanelDrawItem::setAllPoints( std::vector<PointF> outlines )
{
	DrawItemShape::setAllPoints(outlines);
}
std::vector<PointF> SmallPanelDrawItem::getAllPoints()
{
	return DrawItemShape::getAllPoints();
}

