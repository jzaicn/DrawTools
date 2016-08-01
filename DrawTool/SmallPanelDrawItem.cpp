#include "StdAfx.h"
#include "SmallPanelDrawItem.h"
#include <algorithm> 
#include "DrawTools.h"

/************************************************************************/
/* ��ֱ�� DrawVertical                                                  */
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
/* ����� DrawSideVertical                                              */
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
	m_myRect = rect;									//���๹�캯��û���ü�����
	m_lines = DrawTools::buildDrawStraightLine(rect);	//���๹�캯��û���ü�����
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
/* ����� DrawSaw                                                       */
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
/* С����Ϣ SmallPanel                                                  */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// ����
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
// �ӿ�ʵ��
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
	//DrawItemBase::OnPaint(g);	//������
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
/* �༭������� PanelEditionStrategy                                    */
/************************************************************************/
#if 1
//////////////////////////////////////////////////////////////////////////
// �ӿ�
void SmallPanelStrategy::OnInitial( std::list<IDrawItem*> all )
{
	m_pressFlag = false;
}
void SmallPanelStrategy::OnPaint( Graphics& g, std::list<IDrawItem*> all )
{
	DrawItemStrategyBase::OnPaint(g,all);
	//IsActiveCraseWithStatic(g);
}
bool SmallPanelStrategy::PreTranslateMessage( MSG* pMsg, std::list<IDrawItem*> all )
{
	//���̰���
	if (pMsg ->message == WM_KEYDOWN)  // If a keydown message
	{
		//���¿ո�
		if (pMsg ->wParam == _T('\x020'))
		{
			for(auto itter = m_active.begin();itter != m_active.end() ; itter++ )
			{
				RotateItem((*itter));
			}
			return true;
		}
	}
	return false;
}
bool SmallPanelStrategy::OnEraseBkgnd( CDC* pDC, std::list<IDrawItem*> all )
{
	return true;
}
void SmallPanelStrategy::OnMouseMove( UINT nFlags, PointF point, std::list<IDrawItem*> all )
{
	if (m_pressFlag)
	{
		PointF diff(point.X - m_mouseStartPoint.X, point.Y - m_mouseStartPoint.Y);
		MoveAllActive(diff);
		m_mouseStartPoint = point;

		//if (IsActiveCraseWithStatic())
		if (0)
		{
			SetActiveState(DrawItemBase::StateError);

			PointF rediff(m_mouseStartPoint.X - point.X, m_mouseStartPoint.Y - point.Y);
			MoveAllActive(rediff);
		}
		else
		{
			SetActiveState(DrawItemBase::StateDown);
		}
	}
	else
	{
		SetStaticHoveredByPoint(point);

	}



}
void SmallPanelStrategy::OnLButtonDown( UINT nFlags, PointF point, std::list<IDrawItem*> all )
{
	//�л���ʱ�򣬵����ζ�Ų���Ԫ�����
	if (m_pressFlag)
	{
		m_pressFlag = false;
		m_active.clear();
		m_static.clear();
		m_static = all;
	}
	//û�л���ʱ�򣬵����ζ��ʰ��Ԫ��
	else
	{
		bool isPicked = false;
		m_active.clear();
		m_static.clear();

		for(auto itter = all.rbegin();itter != all.rend() ; itter++ )
		{
			if(!isPicked && (*itter)->getRegion()->IsVisible(point))
			{
				isPicked = true;
				m_pressFlag = true;
				(*itter) ->setState(DrawItemBase::StateDown);
				m_active.push_back((*itter) );
			}
			else
			{
				m_static.push_back((*itter) );
			}
		}
		m_mouseStartPoint = point;
	}
}
void SmallPanelStrategy::OnLButtonUp( UINT nFlags, PointF point, std::list<IDrawItem*> all )
{
	//�л���ʱ�򣬵����ζ�Ų���Ԫ�����
	if (m_pressFlag)
	{
		m_pressFlag = false;
		m_active.clear();
		m_static.clear();
		m_static = all;
	}
}
void SmallPanelStrategy::OnRButtonDown( UINT nFlags, PointF point, std::list<IDrawItem*> all )
{

}
void SmallPanelStrategy::OnRButtonUp( UINT nFlags, PointF point, std::list<IDrawItem*> all )
{

}

void SmallPanelStrategy::OnClear(std::list<IDrawItem*> all)
{
	m_active.clear();
	m_static.clear();
}
//////////////////////////////////////////////////////////////////////////
// �ӿ�
void SmallPanelStrategy::addNewActiveItem(IDrawItem* item)
{
	m_pressFlag = true;
	m_active.push_back(item);
}

//bool SmallPanelStrategy::IsActiveCraseWithStatic(Graphics &g1)
bool SmallPanelStrategy::IsActiveCraseWithStatic()
{
	bool isActiveCrashStatic = false;
	try
	{
		Bitmap img(200,300); 
		Graphics g((Image*)&img);
		//ԭ����ǽ
		HRGN staticRegion = CreateRectRgn( 0,0,0,0 ); 
		for(auto itter = m_static.begin();itter != m_static.end() ; itter++ )
		{
			std::shared_ptr<Region> region = (*itter)->getRegion();
			HRGN regionHgrn = region->GetHRGN(&g);
			int combineResult = CombineRgn( staticRegion,staticRegion,regionHgrn,RGN_OR ); 
			DeleteObject(regionHgrn);
		}
		OffsetRgn(staticRegion,300,0);
		Region staticRegionRgn(staticRegion);
		//g1.FillRegion(&SolidBrush(Color::Red),&staticRegionRgn);

		//�жϻ��Ʒ�Ƿ��ԭ�����غ�
		HRGN activeRegion = CreateRectRgn( 0,0,0,0 ); 
		for(auto itter = m_active.begin();itter != m_active.end() ; itter++ )
		{
			std::shared_ptr<Region> region = (*itter)->getRegion();
			HRGN regionHgrn = region->GetHRGN(&g);
			int combineResult = CombineRgn( activeRegion,activeRegion,regionHgrn,RGN_OR ); 
			DeleteObject(regionHgrn);
		}
		OffsetRgn(activeRegion,300,0);
		Region activeRegionRgn(activeRegion);
		//g1.FillRegion(&SolidBrush(Color::Yellow),&activeRegionRgn);


		HRGN crashRegion = CreateRectRgn( 0,0,0,0 ); 
		int combineResult = CombineRgn( crashRegion,staticRegion,activeRegion,RGN_AND );
		Region crashRegionRgn(crashRegion);
		//g1.FillRegion(&SolidBrush(Color::Blue),&crashRegionRgn);

		if(combineResult != NULLREGION)
		{
			isActiveCrashStatic = true;
		}
		DeleteObject(crashRegion);
		DeleteObject(staticRegion);
		DeleteObject(activeRegion);

	}
	catch (...)
	{
		isActiveCrashStatic = false;
	}

	return isActiveCrashStatic;
}

void SmallPanelStrategy::SetStaticHoveredByPoint( PointF point )
{
	for(auto itter = m_static.begin();itter != m_static.end() ; itter++ )
	{
		if ((*itter)->getRegion()->IsVisible(point))
		{
			(*itter)->setState(DrawItemBase::StateHovered);
		}
		else
		{
			(*itter)->setState(DrawItemBase::StateNormal);
		}
	}
}

void SmallPanelStrategy::SetActiveState( int state )
{
	for(auto itter = m_active.begin();itter != m_active.end() ; itter++ )
	{
		(*itter)->setState(state);
	}
}
void SmallPanelStrategy::MoveAllActive( PointF diff )
{
	for(auto itter = m_active.begin();itter != m_active.end() ; itter++ )
	{
		(*itter)->move(diff);
	}
}

void SmallPanelStrategy::RotateItem(IDrawItem* item)
{
	DrawItemShape* companel = (DrawItemShape*)item;
	std::list<PointF> outlines;
	companel->readPoints(outlines);
	RectF rect = companel->getRect();

	//������ת��ƫ��
	PointF offset(rect.Height,0);

	std::list<PointF> outResult;

	for(auto itter = outlines.begin();itter != outlines.end() ; itter++ )
	{
		//��ת��
		PointF tempPoint((*itter).X,(*itter).Y);
		DrawTools::rotateByAngle(DrawTools::getTopLeft(rect),tempPoint,90);

		//ƫ�Ƶ�
		tempPoint = tempPoint + offset;

		//����
		outResult.push_back(PointF(tempPoint.X,tempPoint.Y));
	}

	companel->writePoints(outResult);
	companel->setRect(RectF(rect.X,rect.Y,rect.Height,rect.Width));

}





#endif