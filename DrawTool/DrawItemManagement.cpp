#include "StdAfx.h"
#include "afxwin.h"
#include "DrawTools.h"
#include <algorithm>
#include "DrawItemManagement.h"

DrawItemStrategyBase DrawItemManagement::DefaultStrategy;

DrawItemManagement::DrawItemManagement(void)
{
	m_backgroundColor = Color::Black;
	m_strategy = &DefaultStrategy;
}
DrawItemManagement::~DrawItemManagement(void)
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//响应初始化
void DrawItemManagement::OnInitial()
{
	m_strategy->OnInitial(m_allDrawItemList);
}

void DrawItemManagement::OnPaint(Graphics& g)
{
	//画背景色
	g.FillRectangle(&SolidBrush(m_backgroundColor),getDrawRectF());

	m_strategy->OnPaint(g,m_allDrawItemList);
}

bool DrawItemManagement::PreTranslateMessage(MSG* pMsg)
{

	return m_strategy->PreTranslateMessage(pMsg,m_allDrawItemList);
    
}

BOOL DrawItemManagement::OnEraseBkgnd(CDC* pDC)
{
	return m_strategy->OnEraseBkgnd(pDC,m_allDrawItemList);
}

void DrawItemManagement::OnMouseMove(UINT nFlags, PointF point)
{
	m_strategy->OnMouseMove(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnLButtonDown(UINT nFlags, PointF point)
{
	m_strategy->OnLButtonDown(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnLButtonUp(UINT nFlags, PointF point)
{
	m_strategy->OnLButtonUp(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnRButtonDown(UINT nFlags, PointF point)
{
	m_strategy->OnRButtonDown(nFlags,point,m_allDrawItemList);
}

void DrawItemManagement::OnRButtonUp(UINT nFlags, PointF point)
{
	m_strategy->OnRButtonUp(nFlags,point,m_allDrawItemList);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/


void DrawItemManagement::addDrawItem(IDrawItem* drawItem)
{
	m_allDrawItemList.push_back(drawItem);
}

void DrawItemManagement::setDrawItemList( std::list<IDrawItem*> list )
{
	m_allDrawItemList = list;
}

std::list<IDrawItem*> DrawItemManagement::getDrawItemList()
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
//bool DrawItemManagement::checkMoveable(IDrawItem* item , PointF point)
//{
//	return getDrawCRect().PtInRect(DrawTools::buildCPoint(point));
//}
//
//void DrawItemManagement::SetActiveState(int state)
//{
//	for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
//	{
//		(*itter)->setState(state);	
//	}
//}
//
//bool DrawItemManagement::IsCrashArea()
//{
//	bool isActiveCrashStatic = false;
//	try
//	{
//		Bitmap img(200,300); 
//		Graphics g((Image*)&img);
//		//原来的墙
//		HRGN staticRegion = CreateRectRgn( 0,0,0,0 ); 
//		for(auto itter = m_staticDrawItemList.begin();itter != m_staticDrawItemList.end() ; itter++ )
//		{
//			std::shared_ptr<Region> region = (*itter)->getRegion();
//			HRGN regionHgrn = region->GetHRGN(&g);
//			int combineResult = CombineRgn( staticRegion,staticRegion,regionHgrn,RGN_OR ); 
//			DeleteObject(regionHgrn);
//		}
//		OffsetRgn(staticRegion,300,0);
//		Region staticRegionRgn(staticRegion);
//		//g1.FillRegion(&SolidBrush(Color::Red),&staticRegionRgn);
//
//		//判断活动物品是否和原来有重合
//		HRGN activeRegion = CreateRectRgn( 0,0,0,0 ); 
//		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
//		{
//			std::shared_ptr<Region> region = (*itter)->getRegion();
//			HRGN regionHgrn = region->GetHRGN(&g);
//			int combineResult = CombineRgn( activeRegion,activeRegion,regionHgrn,RGN_OR ); 
//			DeleteObject(regionHgrn);
//		}
//		OffsetRgn(activeRegion,300,0);
//		Region activeRegionRgn(activeRegion);
//		//g1.FillRegion(&SolidBrush(Color::Yellow),&activeRegionRgn);
//
//		
//		HRGN crashRegion = CreateRectRgn( 0,0,0,0 ); 
//		int combineResult = CombineRgn( crashRegion,staticRegion,activeRegion,RGN_AND );
//		//g1.FillRegion(&SolidBrush(Color::Blue),&crashRegionRgn);
//
//		if(combineResult != NULLREGION)
//		{
//			isActiveCrashStatic = true;
//		}
//		DeleteObject(crashRegion);
//		DeleteObject(staticRegion);
//		DeleteObject(activeRegion);
//		
//	}
//	catch (...)
//	{
//		isActiveCrashStatic = false;
//	}
//
//	return isActiveCrashStatic;
//}
//
//void DrawItemManagement::rotateDrawItem(IDrawItem* item)
//{
//	//if (item->getType().Compare(L"DrawItemShape") == 0 || item->getType().Compare(L"SmallPanel") == 0)
//	{
//		DrawItemShape* companel = (DrawItemShape*)item;
//		std::list<PointF> outlines;
//		companel->readPoints(outlines);
//		RectF rect = companel->getRect();
//		
//		//用于旋转后偏移
//		PointF offset(rect.Height,0);
//
//		std::list<PointF> outResult;
//
//		for(auto itter = outlines.begin();itter != outlines.end() ; itter++ )
//		{
//			//旋转点
//			PointF tempPoint((*itter).X,(*itter).Y);
//			DrawTools::rotateByAngle(DrawTools::getTopLeft(rect),tempPoint,90);
//
//			//偏移点
//			tempPoint = tempPoint + offset;
//
//			//保存
//			outResult.push_back(PointF(tempPoint.X,tempPoint.Y));
//		}
//
//		companel->writePoints(outResult);
//		companel->setRect(RectF(rect.X,rect.Y,rect.Height,rect.Width));
//
//	}
//}
//
//
//void DrawItemManagement::scaleDrawItemDown(IDrawItem* item)
//{
//	{
//		std::list<PointF> points;
//		std::list<PointF> outResult;
//		item->readPoints(points);
//
//		for(auto itter = points.begin();itter != points.end() ; itter++ )
//		{
//			//旋转点
//			PointF tempPoint((*itter).X,(*itter).Y);
//			tempPoint.X = tempPoint.X * 0.99;
//			tempPoint.Y = tempPoint.Y * 0.99;
//
//			//保存
//			outResult.push_back(PointF(tempPoint.X,tempPoint.Y));
//		}
//		item->writePoints(outResult);
//
//	}
//}