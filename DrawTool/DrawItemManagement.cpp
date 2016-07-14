#include "StdAfx.h"
#include "afxwin.h"
#include "DrawItemManagement.h"
#include <algorithm>

DrawItemManagement::DrawItemManagement(void)
{
}


DrawItemManagement::~DrawItemManagement(void)
{
}


void DrawItemManagement::OnPaint(Graphics& g)
{
	//画背景色
	g.FillRectangle(&SolidBrush(Color::Black), m_drawRect.left, m_drawRect.top, m_drawRect.Width(), m_drawRect.Height());

	//画每个子元素
	for(int i = 0; i < m_allDrawItemList.size(); i++)
	{
		m_allDrawItemList[i]->OnPaint(g);
	}
}


void DrawItemManagement::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

BOOL DrawItemManagement::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void DrawItemManagement::OnMouseMove(UINT nFlags, CPoint point)
{
	//处理组件鼠标着色
	if (1)
	{
		//SetActiveState(DrawItemBase::StateDown);


		for(int i = 0; i < m_staticDrawItemList.size(); i++)
		{
			if (m_staticDrawItemList[i]->IsVisible(point))
			{
				//m_staticDrawItemList[i]->setState(DrawItemBase::StateHovered);
			}
			else
			{
				//m_staticDrawItemList[i]->setState(DrawItemBase::StateNormal);
			}
		}
	}

	//处理活动组件移动部分
	if (1)
	{
		CPoint diff(point.x - m_mouseStartPoint.x, point.y - m_mouseStartPoint.y);
		CPoint rediff(m_mouseStartPoint.x - point.x, m_mouseStartPoint.y - point.y);

		for(int i = 0; i < m_activeDrawItemList.size(); i++)
		{
			m_activeDrawItemList[i]->move(diff);
		}

		//处理活动组件跟静态部分碰撞问题
		if (IsCrashArea())
		{
			for(int i = 0; i < m_activeDrawItemList.size(); i++)
			{
				m_activeDrawItemList[i]->move(rediff);
			}
		}

		m_mouseStartPoint = point;
	}
}

void DrawItemManagement::OnLButtonDown(UINT nFlags, CPoint point)
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

		for(int i = 0; i < m_allDrawItemList.size(); i++)
		{
			if(!isPicked && m_allDrawItemList[i]->IsVisible(point))
			{
				isPicked = true;
				m_allDrawItemList[i]->setState(DrawItemBase::StateDown);
				m_activeDrawItemList.push_back(m_allDrawItemList[i]);
			}
			else
			{
				m_staticDrawItemList.push_back(m_allDrawItemList[i]);
			}
		}
		m_mouseStartPoint = point;
	}
}

void DrawItemManagement::OnLButtonUp(UINT nFlags, CPoint point)
{
	//有活动点的时候，点击意味着布置元素完成
	if (m_activeDrawItemList.size()>0)
	{
		m_activeDrawItemList.clear();
		m_staticDrawItemList.clear();
		m_staticDrawItemList = m_allDrawItemList;
	}
}

void DrawItemManagement::OnRButtonDown(UINT nFlags, CPoint point)
{

}

void DrawItemManagement::OnRButtonUp(UINT nFlags, CPoint point)
{

}



















void DrawItemManagement::addDrawItem(IDrawItem* drawItem)
{
	m_allDrawItemList.push_back(drawItem);
}

std::vector<IDrawItem*>& DrawItemManagement::getDrawItemList()
{
	return m_allDrawItemList;
}

void DrawItemManagement::clearDrawItem()
{
	for (int i = 0;i<m_allDrawItemList.size();i++)
	{
		delete m_allDrawItemList[i];
	}
	m_allDrawItemList.clear();
	m_activeDrawItemList.clear();
	m_staticDrawItemList.clear();
}

void DrawItemManagement::setDrawRect(CRect drawRect)
{
	m_drawRect = drawRect;
}

CRect DrawItemManagement::getDrawRect()
{
	return m_drawRect;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
bool DrawItemManagement::checkMoveable(IDrawItem* item , CPoint point)
{

	return m_drawRect.PtInRect(point);
}

void DrawItemManagement::SetActiveState(int state)
{
	for(int i = 0; i < m_activeDrawItemList.size(); i++)
	{
		m_activeDrawItemList[i]->setState(state);	
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
		for(int i = 0; i < m_staticDrawItemList.size(); i++)
		{
			Gdiplus::Region* region = m_staticDrawItemList[i]->getCloneRigon();
			HRGN regionHgrn = region->GetHRGN(&g);
			int combineResult = CombineRgn( staticRegion,staticRegion,regionHgrn,RGN_OR ); 
			DeleteObject(regionHgrn);
		}
		OffsetRgn(staticRegion,300,0);
		Region staticRegionRgn(staticRegion);
		//g1.FillRegion(&SolidBrush(Color::Red),&staticRegionRgn);

		//判断活动物品是否和原来有重合
		HRGN activeRegion = CreateRectRgn( 0,0,0,0 ); 
		for(int i = 0; i < m_activeDrawItemList.size(); i++)
		{
			Gdiplus::Region* region = m_activeDrawItemList[i]->getCloneRigon();
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

