#include "StdAfx.h"
#include "SmallPanelDrawItem.h"


Color SmallPanelDrawItem::ColorBorder = Color(0, 0, 0);

SmallPanelDrawItem::SmallPanelDrawItem(void):
 DrawItemShape(RectF(0,0,0,0),std::vector<IDrawLine*>())
{
	m_scale = 1.0;
}


SmallPanelDrawItem::~SmallPanelDrawItem(void)
{
}

void SmallPanelDrawItem::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);
	//TODO: »­±ßÔµ
	//TODO: »­ÒìÐÎÊý¾Ý
	//TODO: ¿×
	//TODO: ²Û
	//TODO: Ð´×Ö
}

void SmallPanelDrawItem::OnPaintBorder( Graphics &g )
{
	RectF rect = getRect();
	//g.DrawRectangle(&CPen(PS_SOLID,1,ColorBorder),rect);
}

void SmallPanelDrawItem::moveTo( PointF point )
{
	DrawItemBase::moveTo(point);
}

void SmallPanelDrawItem::move( PointF offset )
{
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
