#include "StdAfx.h"
#include "SmallPanelDrawItem.h"


Color SmallPanelDrawItem::ColorBorder = Color::Black;
Color SmallPanelDrawItem::ColorShapeBorder = Color::Yellow;
Color SmallPanelDrawItem::ColorVertical = Color::Blue;
Color SmallPanelDrawItem::ColorSaw = Color::Blue;

SmallPanelDrawItem::SmallPanelDrawItem(void):
 DrawItemShape(RectF(0,0,0,0),std::vector<IDrawLine*>())
{
	m_scale = 1.0;
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
/*                                                                      */
/************************************************************************/


void SmallPanelDrawItem::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);
	//TODO: »­±ßÔµ
	OnPaintBorder(g);
	//TODO: »­ÒìÐÎÊý¾Ý
	OnPaintOtherShape(g);
	//TODO: ¿×
	OnPaintVertical(g);
	//TODO: ²Û
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
/*                                                                      */
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
/*                                                                      */
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