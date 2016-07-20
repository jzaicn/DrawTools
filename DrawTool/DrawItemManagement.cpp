#include "StdAfx.h"
#include "afxwin.h"
#include "DrawTools.h"
#include <algorithm>
#include "DrawItemManagement.h"

DrawItemManagement::DrawItemManagement(void)
{
}
DrawItemManagement::~DrawItemManagement(void)
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void DrawItemManagement::OnPaint(Graphics& g)
{
	//画背景色
	g.FillRectangle(&SolidBrush(Color::Black),getDrawRectF());

	//画每个子元素
	for(auto itter = m_allDrawItemList.begin();itter != m_allDrawItemList.end() ; itter++ )
	{
		(*itter)->OnPaint(g);
	}
}


bool DrawItemManagement::PreTranslateMessage(MSG* pMsg)
{
	//按下空格
	if (pMsg ->wParam == _T('\x020'))
	{
		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
		{
			rotateDrawItem((*itter));
		}
		return true;
	}

	return false;
    
}

BOOL DrawItemManagement::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void DrawItemManagement::OnMouseMove(UINT nFlags, PointF point)
{
	//处理组件鼠标着色
	if (1)
	{
		if (IsCrashArea())
		{
			SetActiveState(DrawItemBase::StateError);
		}
		else
		{
			SetActiveState(DrawItemBase::StateDown);
		}

		for(auto itter = m_staticDrawItemList.begin();itter != m_staticDrawItemList.end() ; itter++ )
		{
			if ((*itter)->getRegion().IsVisible(point))
			{
				(*itter)->setState(DrawItemBase::StateHovered);
			}
			else
			{
				(*itter)->setState(DrawItemBase::StateNormal);
			}
		}
	}

	//处理活动组件移动部分
	if (1)
	{
		PointF diff(point.X - m_mouseStartPoint.X, point.Y - m_mouseStartPoint.Y);
		PointF rediff(m_mouseStartPoint.X - point.X, m_mouseStartPoint.Y - point.Y);

		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
		{
			(*itter)->move(diff);
		}

		//处理活动组件跟静态部分碰撞问题
		if (IsCrashArea())
		{
			for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
			{
				(*itter)->move(rediff);
			}
		}

		m_mouseStartPoint = point;
	}
}

void DrawItemManagement::OnLButtonDown(UINT nFlags, PointF point)
{
	//有活动点的时候，点击意味着布置元素完成
	if (m_activeDrawItemList.size()>0)
	{
		m_activeDrawItemList.clear();
		m_staticDrawItemList.clear();
		m_staticDrawItemList = m_allDrawItemList;
	}
	//没有活动点的时候，点击意味着拾起元素
	else
	{
		bool isPicked = false;
		m_activeDrawItemList.clear();
		m_staticDrawItemList.clear();

		for(auto itter = m_allDrawItemList.begin();itter != m_allDrawItemList.end() ; itter++ )
		{
			if(!isPicked && (*itter)->getRegion().IsVisible(point))
			{
				isPicked = true;
				(*itter) ->setState(DrawItemBase::StateDown);
				m_activeDrawItemList.push_back((*itter) );
			}
			else
			{
				m_staticDrawItemList.push_back((*itter) );
			}
		}
		m_mouseStartPoint = point;
	}
}

void DrawItemManagement::OnLButtonUp(UINT nFlags, PointF point)
{
	//有活动点的时候，点击意味着布置元素完成
	if (m_activeDrawItemList.size()>0)
	{
		m_activeDrawItemList.clear();
		m_staticDrawItemList.clear();
		m_staticDrawItemList = m_allDrawItemList;
	}
}

void DrawItemManagement::OnRButtonDown(UINT nFlags, PointF point)
{

}

void DrawItemManagement::OnRButtonUp(UINT nFlags, PointF point)
{

}

/************************************************************************/
/*                                                                      */
/************************************************************************/


void DrawItemManagement::addDrawItem(IDrawItem* drawItem)
{
	m_allDrawItemList.push_back(drawItem);
}

std::list<IDrawItem*>& DrawItemManagement::getDrawItemList()
{
	return m_allDrawItemList;
}

void DrawItemManagement::clearDrawItem()
{
	for(auto itter = m_allDrawItemList.begin();itter != m_allDrawItemList.end() ; itter++ )
	{
		delete (*itter);
	}
	m_allDrawItemList.clear();
	m_activeDrawItemList.clear();
	m_staticDrawItemList.clear();
}

void DrawItemManagement::setDrawRectF(RectF drawRect)
{
	m_drawRect = drawRect;
}

void DrawItemManagement::setDrawCRect(CRect drawRect)
{
	setDrawRectF(DrawTools::buildRectF(drawRect));
}

RectF DrawItemManagement::getDrawRectF()
{
	return m_drawRect;
}

CRect DrawItemManagement::getDrawCRect()
{
	return DrawTools::buildCRect(m_drawRect);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
bool DrawItemManagement::checkMoveable(IDrawItem* item , PointF point)
{
	return getDrawCRect().PtInRect(DrawTools::buildCPoint(point));
}

void DrawItemManagement::SetActiveState(int state)
{
	for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
	{
		(*itter)->setState(state);	
	}
}

bool DrawItemManagement::IsCrashArea()
{
	bool isActiveCrashStatic = false;
	try
	{
		Bitmap img(200,300); 
		Graphics g((Image*)&img);
		//原来的墙
		HRGN staticRegion = CreateRectRgn( 0,0,0,0 ); 
		for(auto itter = m_staticDrawItemList.begin();itter != m_staticDrawItemList.end() ; itter++ )
		{
			Gdiplus::Region* region = (*itter)->getRegion();
			HRGN regionHgrn = region->GetHRGN(&g);
			int combineResult = CombineRgn( staticRegion,staticRegion,regionHgrn,RGN_OR ); 
			DeleteObject(regionHgrn);
		}
		OffsetRgn(staticRegion,300,0);
		Region staticRegionRgn(staticRegion);
		//g1.FillRegion(&SolidBrush(Color::Red),&staticRegionRgn);

		//判断活动物品是否和原来有重合
		HRGN activeRegion = CreateRectRgn( 0,0,0,0 ); 
		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
		{
			Gdiplus::Region* region = (*itter)->getRegion();
			HRGN regionHgrn = region->GetHRGN(&g);
			int combineResult = CombineRgn( activeRegion,activeRegion,regionHgrn,RGN_OR ); 
			DeleteObject(regionHgrn);
		}
		OffsetRgn(activeRegion,300,0);
		Region activeRegionRgn(activeRegion);
		//g1.FillRegion(&SolidBrush(Color::Yellow),&activeRegionRgn);

		
		HRGN crashRegion = CreateRectRgn( 0,0,0,0 ); 
		int combineResult = CombineRgn( crashRegion,staticRegion,activeRegion,RGN_AND );
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

void DrawItemManagement::rotateDrawItem(IDrawItem* item)
{
	if (item->getType().Compare(L"DrawItemShape") == 0 || item->getType().Compare(L"SmallPanel") == 0)
	{
		DrawItemShape* companel = (DrawItemShape*)item;
		std::list<PointF> outlines;
		companel->readPoints(outlines);
		RectF rect = companel->getRect();

		//用于旋转后偏移
		PointF offset(rect.Height,0);

		std::list<PointF> outResult;
		for(auto itter = outlines.begin();itter != outlines.end() ; itter++ )
		{
			//旋转点
			PointF tempPoint((*itter).X,(*itter).Y);
			DrawTools::rotateByAngle(DrawTools::getTopLeft(rect),tempPoint,90);

			//偏移点
			tempPoint = tempPoint + offset;

			//保存
			outResult.push_back(PointF(tempPoint.X,tempPoint.Y));
		}
		companel->writePoints(outResult);
		companel->setRect(RectF(rect.X,rect.Y,rect.Height,rect.Width));
	}
}