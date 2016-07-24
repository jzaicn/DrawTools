#include "StdAfx.h"
#include "DrawItemStrategy.h"

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
	if(pMsg->message == WM_MOUSEWHEEL)
	{
		if(GET_WHEEL_DELTA_WPARAM(pMsg->wParam) < 0)
		{
			//向下滚
			OutputDebugString(L"down\n");
		}
		else
		{
			//向上滚
			OutputDebugString(L"up\n");
		}
	}


// 	//按下空格
// 	if (pMsg ->wParam == _T('\x020'))
// 	{
// 		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
// 		{
// 			rotateDrawItem((*itter));
// 		}
// 		return true;
// 	}
// 	//按下+
// 	if (pMsg ->wParam == _T('\x06B'))
// 	{
// 		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
// 		{
// 			//scaleDrawItemUp((*itter));
// 		}
// 		return true;
// 	}
// 	//按下-
// 	if (pMsg ->wParam == _T('\x06D'))
// 	{
// 		for(auto itter = m_allDrawItemList.begin();itter != m_allDrawItemList.end() ; itter++ )
// 		{
// 			scaleDrawItemDown((*itter));
// 		}
// 		return true;
// 	}
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
// 	//处理组件鼠标着色
// 	if (1)
// 	{
// 		if (IsCrashArea())
// 		{
// 			SetActiveState(DrawItemBase::StateError);
// 		}
// 		else
// 		{
// 			SetActiveState(DrawItemBase::StateDown);
// 		}
// 
// 		for(auto itter = m_staticDrawItemList.begin();itter != m_staticDrawItemList.end() ; itter++ )
// 		{
// 			if ((*itter)->getRegion()->IsVisible(point))
// 			{
// 				(*itter)->setState(DrawItemBase::StateHovered);
// 			}
// 			else
// 			{
// 				(*itter)->setState(DrawItemBase::StateNormal);
// 			}
// 		}
// 	}
// 
// 	//处理活动组件移动部分
// 	if (1)
// 	{
// 		PointF diff(point.X - m_mouseStartPoint.X, point.Y - m_mouseStartPoint.Y);
// 		PointF rediff(m_mouseStartPoint.X - point.X, m_mouseStartPoint.Y - point.Y);
// 
// 		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
// 		{
// 			(*itter)->move(diff);
// 		}
// 
// 		//处理活动组件跟静态部分碰撞问题
// 		if (IsCrashArea())
// 		{
// 			for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
// 			{
// 				(*itter)->move(rediff);
// 			}
// 		}
// 
// 		m_mouseStartPoint = point;
// 	}
}		
//响应左键按下
void DrawItemStrategyBase::OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
// 	//有活动点的时候，点击意味着布置元素完成
// 	if (m_activeDrawItemList.size()>0)
// 	{
// 		m_activeDrawItemList.clear();
// 		m_staticDrawItemList.clear();
// 		m_staticDrawItemList = m_allDrawItemList;
// 	}
// 	//没有活动点的时候，点击意味着拾起元素
// 	else
// 	{
// 		bool isPicked = false;
// 		m_activeDrawItemList.clear();
// 		m_staticDrawItemList.clear();
// 
// 		for(auto itter = m_allDrawItemList.begin();itter != m_allDrawItemList.end() ; itter++ )
// 		{
// 			if(!isPicked && (*itter)->getRegion()->IsVisible(point))
// 			{
// 				isPicked = true;
// 				(*itter) ->setState(DrawItemBase::StateDown);
// 				m_activeDrawItemList.push_back((*itter) );
// 			}
// 			else
// 			{
// 				m_staticDrawItemList.push_back((*itter) );
// 			}
// 		}
// 		m_mouseStartPoint = point;
// 	}
}	
//响应左键弹起
void DrawItemStrategyBase::OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
// 	//有活动点的时候，点击意味着布置元素完成
// 	if (m_activeDrawItemList.size()>0)
// 	{
// 		m_activeDrawItemList.clear();
// 		m_staticDrawItemList.clear();
// 		m_staticDrawItemList = m_allDrawItemList;
// 	}
}		
//响应右键按下
void DrawItemStrategyBase::OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all){}	
//响应右键弹起
void DrawItemStrategyBase::OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all){}		
//////////////////////////////////////////////////////////////////////////
// 检测
// bool DrawItemStrategyBaseB::IsCrash_ActiveWithStatic()
// {
// 
// }
// 
// void DrawItemStrategyBaseB::SetAll_ActiveState( int state )
// {
// 
// }
// 
// bool DrawItemStrategyBaseB::MoveDrawItem( IDrawItem* item , PointF point )
// {
// 
// }
// 
// void DrawItemStrategyBaseB::RotateDrawItem( IDrawItem* item )
// {
// 
// }
// 
// void DrawItemStrategyBaseB::scaleDrawItemDown( IDrawItem* item )
// {
// 
// }

//////////////////////////////////////////////////////////////////////////
// 操作
#endif
