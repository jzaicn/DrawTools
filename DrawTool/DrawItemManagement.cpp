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

/************************************************************************/
/*                                                                      */
/************************************************************************/

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


bool DrawItemManagement::PreTranslateMessage(MSG* pMsg)
{
	//按下空格
	if (pMsg ->wParam == _T('\x020'))
	{
		for (int i = 0;i<m_activeDrawItemList.size();i++)
		{
			rotateDrawItem(m_activeDrawItemList[i]);
		}
		return true;
	}

	return false;
    
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
		if (IsCrashArea())
		{
			SetActiveState(DrawItemBase::StateError);
		}
		else
		{
			SetActiveState(DrawItemBase::StateDown);
		}

		for(int i = 0; i < m_staticDrawItemList.size(); i++)
		{
			if (m_staticDrawItemList[i]->IsVisible(point))
			{
				m_staticDrawItemList[i]->setState(DrawItemBase::StateHovered);
			}
			else
			{
				m_staticDrawItemList[i]->setState(DrawItemBase::StateNormal);
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

// 		//处理活动组件跟静态部分碰撞问题
// 		if (IsCrashArea())
// 		{
// 			for(int i = 0; i < m_activeDrawItemList.size(); i++)
// 			{
// 				m_activeDrawItemList[i]->move(rediff);
// 			}
// 		}

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

/************************************************************************/
/*                                                                      */
/************************************************************************/


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

#include <math.h>  
#define MY_PI 3.14159265358979323846  
//角度转弧度  
double DrawItemManagement::getRadFromAngle(double angle)  
{  
	return (angle / 180 * MY_PI);  
}  
//根据某点，旋转一个角度   
void DrawItemManagement::rotateByAngle(PointF pointCenter,  
	PointF &pointNeedRotate,  
	double dAngleDegree)  
{  
	//通过移动把旋转中心放到坐标原点  
	//旋转矩阵，公式如下（以原点旋转θ度）  
	//(x',y') = ( x*cosθ-y*sinθ , x*sinθ+y*cosθ )  
	PointF pointshifting = pointCenter-PointF(0,0);//旋转中心到坐标原点的距离  
	PointF point0 = pointCenter - pointshifting;  
	PointF point1 = pointNeedRotate - pointshifting;  
	double dAngle2Rad = getRadFromAngle(dAngleDegree);    
	PointF point2(point1.X*cos(dAngle2Rad) - point1.Y*sin(dAngle2Rad),  
		point1.X*sin(dAngle2Rad) + point1.Y*cos(dAngle2Rad));  
	pointNeedRotate = point2 + pointshifting;  
} 


void DrawItemManagement::rotateDrawItem(IDrawItem* item)
{
	if (item->getType().Compare(L"companel") == 0)
	{
		DrawItemSmallPanel* companel = (DrawItemSmallPanel*)item;
		std::vector<CPoint> outlines = companel->getOutline();
		CRect rect = companel->getRect();

		//用于旋转后偏移
		PointF offset(rect.Height(),0);

		std::vector<CPoint> outResult;
		for(int i = 0; i < outlines.size(); i++)
		{
			//旋转点
			PointF tempPoint(outlines[i].x,outlines[i].y);
			rotateByAngle(PointF(rect.left,rect.top),tempPoint,90);

			//偏移点
			tempPoint = tempPoint + offset;

			//保存
			outResult.push_back(CPoint(tempPoint.X,tempPoint.Y));
		}
		companel->setOutline(outResult);
	}
}