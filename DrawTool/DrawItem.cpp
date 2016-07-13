#include "StdAfx.h"
#include "DrawItem.h"

#include "L4Cpp.h"

/************************************************************************/
/*  ��ͼ����                                                            */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// ������ɫ����
Color DrawItemBase::ColorNormal = Color(228, 238, 249);
Color DrawItemBase::ColorHovered = Color(242, 247, 252);
Color DrawItemBase::ColorDisable = Color(211, 216, 224);
Color DrawItemBase::ColorDown = Color(0, 0 ,0);
Color DrawItemBase::ColorError = Color(230, 12,3);

//////////////////////////////////////////////////////////////////////////
// ����״̬����
int DrawItemBase::StateNormal = 0;
int DrawItemBase::StateHovered = 1;
int DrawItemBase::StateDisable = 2;
int DrawItemBase::StateDown = 3;
int DrawItemBase::StateError = 4;

//////////////////////////////////////////////////////////////////////////
//ʵ�ʻ�����
DrawItemBase::DrawItemBase()
{
	m_state = StateNormal;
	m_myRect = CRect(0,0,0,0);
}

DrawItemBase::DrawItemBase(CPoint topLeft,CPoint bottomRight)
{
	m_state = StateNormal;
	m_myRect = CRect(topLeft,bottomRight);
}

DrawItemBase::DrawItemBase(CRect rect)
{
	m_state = StateNormal;
	m_myRect = rect;
}

DrawItemBase::~DrawItemBase(void)
{
}

void DrawItemBase::setType(CString type)
{
	m_type = type;
}
CString DrawItemBase::getType()
{
	return m_type;
}

void DrawItemBase::setID(CString id)
{
	m_ID = id;
}
CString DrawItemBase::getID()
{
	return m_ID;
}

void DrawItemBase::setOrder(int order)
{
	m_order = order;
}
int DrawItemBase::getOrder()
{
	return m_order;
}

void DrawItemBase::OnPaint( Graphics &g )
{
	switch(m_state)
	{
	case StateNormal:
		g.FillRectangle(&SolidBrush(ColorNormal), getRigon());
		break;
	case StateHovered:
		g.FillRectangle(&SolidBrush(ColorHovered), getRigon());
		break;
	case StateDisable:
		g.FillRectangle(&SolidBrush(ColorDisable), getRigon());
		break;
	case StateDown:
		g.FillRectangle(&SolidBrush(ColorDown), getRigon());
		break;
	case StateError:
		g.FillRectangle(&SolidBrush(ColorError), getRigon());
		break;
	case default:
		g.FillRectangle(&SolidBrush(ColorNormal), getRigon());
		break;
	}
}

void DrawItemBase::moveTo(CPoint point)
{
	moveTo(point.x,point.y);
}
void DrawItemBase::moveTo(LONG x,LONG y)
{
	m_myRect.SetRect(x, y, 
		m_myRect.right - m_myRect.left,
		m_myRect.bottom - m_myRect.top );
}

void DrawItemBase::move(CPoint offset)
{
	m_myRect.OffsetRect(offset.x,offset.y);
}
void DrawItemBase::move(LONG x,LONG y)
{
	m_myRect.OffsetRect(x,y);
}

void DrawItemBase::setRect(CRect rect)
{
	m_myRect.SetRect(rect);
}
void DrawItemBase::setRect(CPoint topLeft,CPoint bottomRight)
{
	m_myRect.SetRect(topLeft,bottomRight);
}
void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
{
	m_myRect.SetRect(x1,y1,x2,y2);
}
CRect DrawItemBase::getRect()
{
	return m_myRect;
}

std::vector<CPoint> DrawItemBase::getPoints()
{
	std::vector<CPoint> points;
	points.push_back(m_myRect.TopLeft());
	points.push_back(m_myRect.BottomRight());
}
Region DrawItemBase::getRigon()
{
	Region region(getRect());
	return region;
}

void DrawItemBase::setState(int state)
{
	m_state = state;
}
int DrawItemBase::getState()
{
	return m_state;
}

// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// //��ð�Χ����
// CRect DrawItemBase::getRect()
// {
// 	return m_myRect;
// }
// 
// //�������
// CString DrawItemBase::getType()
// {
// 	return CString();
// }
// 
// //���ID
// CString DrawItemBase::getID()
// {
// 	return CString();
// }
// 
// //���˳��
// int DrawItemBase::getZIndex()
// {
// 	return 0;
// }
// 
// //��ͼ
// void DrawItemBase::OnPaint( Graphics &g )
// {

// 	
// }
// 
// //�Ƿ����
// bool DrawItemBase::isActive()
// {
// 	return m_isActive;
// }
// 
// //�Ƿ�ѡ�У�//TODO: Ӧ�ó�ȡ��������
// bool DrawItemBase::checkSelected( CPoint point )
// {
// 	return (bool)(m_myRect.PtInRect(point));
// }
// 
// void DrawItemBase::OnCommand( CString command,CString param )
// {
// }
// 
// void DrawItemBase::OnMouseMove( CPoint point )
// {
// 	if (checkSelected(point))
// 	{
// 		m_isMouseHover = true;
// 	}
// 	else
// 	{
// 		m_isMouseHover = false;
// 	}
// 
// 	if (isActive())
// 	{
// 		move(point.x - m_posStart.x, point.y - m_posStart.y);
// 		m_posStart = point;
// 	}
// }
// 
// void DrawItemBase::OnLButtonDown(CPoint point)
// {
// 	if (checkSelected(point))
// 	{
// 		//��Ч��ʱ��Ʃ�粼�õ�ʱ�򣬵����ζ��ȷ�ϰڷ�
// 		if (isActive())
// 		{
// 			endActive(point);
// 		}
// 		//��Ч��ʱ��Ʃ�羲ֹ�������ζ���ܵ���ѡ
// 		else
// 		{
// 			beginActive(point);
// 		}
// 	}
// }
// 
// void DrawItemBase::OnLButtonUp(CPoint point)
// {
// 	if (checkSelected(point))
// 	{
// 		//��Ч��ʱ��Ʃ�粼�õ�ʱ���ͷ���ζ��ȷ�ϰڷ�
// 		if (isActive())
// 		{
// 			endActive(point);
// 		}
// 	}
// }
// 
// void DrawItemBase::OnRButtonDown(CPoint point)
// {
// 
// }
// 
// void DrawItemBase::OnRButtonUp(CPoint point)
// {
// 
// }
// 
// //��ʼ����
// void DrawItemBase::beginActive(CPoint point)
// {
// 	m_isActive = true;
// 
// 	m_posStart = point;
// 
// 	L4Cpp::Log()->debug("beginActive");
// }
// //��������
// void DrawItemBase::endActive(CPoint point)
// {
// 	m_isActive = false;
// 
// 	m_posStart = point;
// 
// 	L4Cpp::Log()->debug("endActive");
// }
// 
// void DrawItemBase::moveTo(LONG x,LONG y)
// {

// }
// 
// void DrawItemBase::moveTo(CPoint point)
// {

// }
// 
// 
// void DrawItemBase::move(LONG x,LONG y)
// {
// 	
// }
// 
// void DrawItemBase::move(CPoint point)
// {
// 	
// }
// 
// //���þ���λ�ã����α�����ӿڷǱ���
// void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
// {
// 	m_myRect.SetRect(x1,y1,x2,y2);
// }
// //���þ���λ�ã����α�����ӿڷǱ���
// void DrawItemBase::setRect(CPoint topLeft,CPoint bottomRight)
// {
// 	m_myRect.SetRect(topLeft.x,topLeft.y,bottomRight.x,bottomRight.y);
// }
// 
