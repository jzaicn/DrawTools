#include "StdAfx.h"
#include "DrawItemStrategy.h"
#include <sstream>

/************************************************************************/
/* 画图策略接口 IDrawItemStrategy                                       */
/************************************************************************/


/************************************************************************/
/* 画图策略基类 DrawItemStrategyBase                                     */
/************************************************************************/
#if 1

//////////////////////////////////////////////////////////////////////////
// 事件
//响应初始化
void DrawItemStrategyBase::OnInitial( std::list<IDrawItem*> all )
{
	m_pressFlag = false;
}
//响应绘图
void DrawItemStrategyBase::OnPaint( Graphics& g, std::list<IDrawItem*> all )
{
	for(auto itter = all.begin();itter != all.end() ; itter++ )
	{
		(*itter)->OnPaint(g);
	}
}
//响应消息
bool DrawItemStrategyBase::PreTranslateMessage(MSG* pMsg, std::list<IDrawItem*> all)
{
	return false;
}				
//响应擦除背景
bool DrawItemStrategyBase::OnEraseBkgnd(CDC* pDC, std::list<IDrawItem*> all)
{
	return true;
}						
//响应鼠标移动
void DrawItemStrategyBase::OnMouseMove(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
	//所有组件移动部分
	if (m_pressFlag)
	{
		PointF diff(point.X - m_mouseStartPoint.X, point.Y - m_mouseStartPoint.Y);
		
		//测试
		auto lasttime = clock(); 
		

		for(auto itter = all.begin();itter != all.end() ; itter++ )
		{
			(*itter)->move(diff);
		}
		
		std::ostringstream os;
		os<<"移动时间:"<<clock()-lasttime<<"\n";
		TRACE(os.str().c_str());

		m_mouseStartPoint = point;
	}
	else
	{
		//处理组件鼠标着色
		for(auto itter = all.begin();itter != all.end() ; itter++ )
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
}		
//响应左键按下
void DrawItemStrategyBase::OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
	m_pressFlag = true;
	 
	for(auto itter = all.begin();itter != all.end() ; itter++ )
	{
	 	if((*itter)->getRegion()->IsVisible(point))
	 	{
	 		(*itter) ->setState(DrawItemBase::StateDown);
	 	}
	}
	m_mouseStartPoint = point;
}	
//响应左键弹起
void DrawItemStrategyBase::OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
	m_pressFlag = false;
}		
//响应右键按下
void DrawItemStrategyBase::OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all){}	
//响应右键弹起
void DrawItemStrategyBase::OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all){}	
//响应清除数据
void DrawItemStrategyBase::OnClear(std::list<IDrawItem*> all){}
#endif
