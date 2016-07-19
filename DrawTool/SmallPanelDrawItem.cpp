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

	RectF rect;
	rect.X = m_pos_x - (m_size_x/2);
	rect.Y = m_pos_y - (m_size_y/2);
	rect.Width = m_size_x;
	rect.Height = m_size_y;
	m_rect = rect;
}

void DrawInfoBase::loadPoints( std::vector<PointF>& points )
{
	points.push_back(PointF(m_pos_x,m_pos_y));
}

void DrawInfoBase::updatePoints( std::vector<PointF>& points )
{
	PointF point = points.front();
	points.erase(points.begin());
	m_pos_x = point.X;
	m_pos_y = point.Y;
}

void DrawInfoBase::drawLineToGraphic( Graphics &g )
{
	g.DrawRectangle(&Pen(DrawTools::ColorVertical),m_rect);
}

////////////////////////////////////////////////////////////////////////////
DrawVertical::DrawVertical( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth ) :DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
void DrawVertical::drawLineToGraphic( Graphics &g )
{
	RectF rect;
	rect.X = m_pos_x - (m_size_x/2);
	rect.Y = m_pos_y - (m_size_y/2);
	rect.Width = m_size_x;
	rect.Height = m_size_y;
	m_rect = rect;

	g.DrawEllipse(&Pen(DrawTools::ColorVertical),m_rect);
	g.FillEllipse(&SolidBrush(DrawTools::ColorVertical),m_rect);
}

//////////////////////////////////////////////////////////////////////////
DrawSideVertical::DrawSideVertical(int side, float pos_x,float pos_y,float angle,float size_x,float size_y,float depth ) :DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth)
{
	switch (side)
	{
	case 1:	//左面
		{
			RectF rect;
			rect.X = m_pos_x - m_size_x;
			rect.Y = m_pos_y - (m_size_y/2);
			rect.Width = m_size_x;
			rect.Height = m_size_y;
			m_rect = rect;
		}
		break;
	case 2:	//右面
		{
			RectF rect;
			rect.X = m_pos_x;
			rect.Y = m_pos_y - (m_size_y/2);
			rect.Width = m_size_x;
			rect.Height = m_size_y;
			m_rect = rect;
		}
		break;
	case 3:	//下面
		{
			RectF rect;
			rect.X = m_pos_x - (m_size_y/2);
			rect.Y = m_pos_y;
			rect.Width = m_size_y;
			rect.Height = m_size_x;
		}
		break;
	case 4:	//上面
		{
			RectF rect;
			rect.X = m_pos_x - (m_size_y/2);
			rect.Y = m_pos_y - m_size_x;
			rect.Width = m_size_y;
			rect.Height = m_size_x;
			m_rect = rect;
		}
		break;
	default: //中心点矩形
		{
			RectF rect;
			rect.X = m_pos_x - (m_size_x/2);
			rect.Y = m_pos_y - (m_size_y/2);
			rect.Width = m_size_x;
			rect.Height = m_size_y;
			m_rect = rect;
		}
	}
	m_infos = InfosByRect(m_rect);
}
void DrawSideVertical::loadPoints( std::vector<PointF>& points )
{
	for (unsigned int i = 0; i < m_infos.size() ; i++)
	{
		m_infos[i]->loadPoints(points);
	}
}

void DrawSideVertical::updatePoints( std::vector<PointF>& points )
{
	for (unsigned int i = 0; i < m_infos.size() ; i++)
	{
		m_infos[i]->updatePoints(points);
	}
}

void DrawSideVertical::drawLineToGraphic( Graphics &g )
{
	GraphicsPath path;
	path.StartFigure();
	for (unsigned int i = 0; i < m_infos.size() ; i++)
	{
		m_infos[i]->getLineToPath(path);
	}
	path.CloseFigure();
	g.DrawPath(&Pen(DrawTools::ColorVertical),&path);
}

std::vector<IDrawLine*> DrawSideVertical::InfosByRect( RectF rect )
{
	std::vector<IDrawLine* > infos;
	infos.push_back(new DrawStraightLine(DrawTools::getTopLeft(rect),DrawTools::getBottomLeft(rect)));
	infos.push_back(new DrawStraightLine(DrawTools::getBottomLeft(rect),DrawTools::getBottomRight(rect)));
	infos.push_back(new DrawStraightLine(DrawTools::getBottomRight(rect),DrawTools::getTopRight(rect)));
	infos.push_back(new DrawStraightLine(DrawTools::getTopRight(rect),DrawTools::getTopLeft(rect)));
	return infos;
}



////////////////////////////////////////////////////////////////////////////

void DrawSaw::drawLineToGraphic( Graphics &g )
{
	g.DrawRectangle(&Pen(DrawTools::ColorSaw),m_rect);
	g.FillRectangle(&SolidBrush(DrawTools::ColorSaw),m_rect);
}

#endif
/************************************************************************/
/*  板件初始化                                                           */
/************************************************************************/
#if 1
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

#endif
/************************************************************************/
/* 板件绘制                                                             */
/************************************************************************/
#if 1

void SmallPanelDrawItem::OnPaint( Graphics &g )
{
	DrawItemBase::OnPaint(g);	//画区域
	OnPaintBorder(g);			//画边缘
	OnPaintOtherShape(g);		//画异形数据
	OnPaintInfo(g);				//孔、槽
}

void SmallPanelDrawItem::OnPaintBorder( Graphics &g )
{
	RectF rect = getRect();
	g.DrawRectangle(&Pen(DrawTools::ColorBorder),rect);
}

void SmallPanelDrawItem::OnPaintOtherShape( Graphics &g )
{
	GraphicsPath path;
	buildPath(path);
	Region region(&path);
	g.FillRegion(&SolidBrush(DrawTools::ColorShapeBorder), &region);
	g.DrawPath(&Pen(DrawTools::ColorVertical),&path);
}

void SmallPanelDrawItem::OnPaintInfo( Graphics &g )
{
	for (unsigned int i = 0;i<m_infos.size();i++)
	{
		m_infos[i]->drawLineToGraphic(g);
	}
}

#endif
/************************************************************************/
/* 移动信息                                                             */
/************************************************************************/
#if 1
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
#endif
/************************************************************************/
/* 点坐标转换                                                            */
/************************************************************************/
#if 1
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

void SmallPanelDrawItem::setVertical( std::vector<IDrawInfo*> infos )
{
	m_infos = infos;
}

void SmallPanelDrawItem::setAllPoints( std::vector<PointF>& points )
{
	DrawItemShape::setAllPoints(points);

	for (unsigned int i = 0;i < m_infos.size();i++)
	{
		m_infos[i]->updatePoints(points);
	}
}
std::vector<PointF> SmallPanelDrawItem::getAllPoints()
{
	std::vector<PointF> points = DrawItemShape::getAllPoints();

	for (unsigned int i = 0;i < m_infos.size();i++)
	{
		m_infos[i]->loadPoints(points);
	}

	return points;
}


#endif

