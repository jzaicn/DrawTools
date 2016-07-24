#include "StdAfx.h"
#include "DrawItemStrategy.h"

/************************************************************************/
/* ��ͼ���Խӿ� IDrawItemStrategy                                       */
/************************************************************************/


/************************************************************************/
/* ��ͼ���Ի��� DrawItemStrategyBase                                     */
/************************************************************************/
#if 1

//////////////////////////////////////////////////////////////////////////
// �¼�
//��Ӧ��ʼ��
void DrawItemStrategyBase::OnInitial( std::list<IDrawItem*> all )
{

}
//��Ӧ��ͼ
void DrawItemStrategyBase::OnPaint( Graphics& g, std::list<IDrawItem*> all )
{
	for(auto itter = all.begin();itter != all.end() ; itter++ )
	{
		(*itter)->OnPaint(g);
	}
}
//��Ӧ��Ϣ
bool DrawItemStrategyBase::PreTranslateMessage(MSG* pMsg, std::list<IDrawItem*> all)
{
	if(pMsg->message == WM_MOUSEWHEEL)
	{
		if(GET_WHEEL_DELTA_WPARAM(pMsg->wParam) < 0)
		{
			//���¹�
			OutputDebugString(L"down\n");
		}
		else
		{
			//���Ϲ�
			OutputDebugString(L"up\n");
		}
	}


// 	//���¿ո�
// 	if (pMsg ->wParam == _T('\x020'))
// 	{
// 		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
// 		{
// 			rotateDrawItem((*itter));
// 		}
// 		return true;
// 	}
// 	//����+
// 	if (pMsg ->wParam == _T('\x06B'))
// 	{
// 		for(auto itter = m_activeDrawItemList.begin();itter != m_activeDrawItemList.end() ; itter++ )
// 		{
// 			//scaleDrawItemUp((*itter));
// 		}
// 		return true;
// 	}
// 	//����-
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
//��Ӧ��������
bool DrawItemStrategyBase::OnEraseBkgnd(CDC* pDC, std::list<IDrawItem*> all)
{
	return true;
}						
//��Ӧ����ƶ�
void DrawItemStrategyBase::OnMouseMove(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
// 	//������������ɫ
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
// 	//��������ƶ�����
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
// 		//�����������̬������ײ����
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
//��Ӧ�������
void DrawItemStrategyBase::OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
// 	//�л���ʱ�򣬵����ζ�Ų���Ԫ�����
// 	if (m_activeDrawItemList.size()>0)
// 	{
// 		m_activeDrawItemList.clear();
// 		m_staticDrawItemList.clear();
// 		m_staticDrawItemList = m_allDrawItemList;
// 	}
// 	//û�л���ʱ�򣬵����ζ��ʰ��Ԫ��
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
//��Ӧ�������
void DrawItemStrategyBase::OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
// 	//�л���ʱ�򣬵����ζ�Ų���Ԫ�����
// 	if (m_activeDrawItemList.size()>0)
// 	{
// 		m_activeDrawItemList.clear();
// 		m_staticDrawItemList.clear();
// 		m_staticDrawItemList = m_allDrawItemList;
// 	}
}		
//��Ӧ�Ҽ�����
void DrawItemStrategyBase::OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all){}	
//��Ӧ�Ҽ�����
void DrawItemStrategyBase::OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all){}		
//////////////////////////////////////////////////////////////////////////
// ���
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
// ����
#endif
