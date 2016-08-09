#include "StdAfx.h"
#include "DrawItemStrategy.h"
#include <sstream>

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
	m_pressFlag = false;
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
	//��������ƶ�����
	if (m_pressFlag)
	{
		PointF diff(point.X - m_mouseStartPoint.X, point.Y - m_mouseStartPoint.Y);
		
		//����
		auto lasttime = clock(); 
		

		for(auto itter = all.begin();itter != all.end() ; itter++ )
		{
			(*itter)->move(diff);
		}
		
		std::ostringstream os;
		os<<"�ƶ�ʱ��:"<<clock()-lasttime<<"\n";
		TRACE(os.str().c_str());

		m_mouseStartPoint = point;
	}
	else
	{
		//������������ɫ
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
//��Ӧ�������
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
//��Ӧ�������
void DrawItemStrategyBase::OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all)
{
	m_pressFlag = false;
}		
//��Ӧ�Ҽ�����
void DrawItemStrategyBase::OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all){}	
//��Ӧ�Ҽ�����
void DrawItemStrategyBase::OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all){}	
//��Ӧ�������
void DrawItemStrategyBase::OnClear(std::list<IDrawItem*> all){}
#endif
