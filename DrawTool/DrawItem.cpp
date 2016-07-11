#include "StdAfx.h"
#include "DrawItem.h"

#include "L4Cpp.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

DrawItemBase::DrawItemBase()
{
	m_isActive = false;
	m_posStart = CPoint(0,0);
	m_myRect = CRect(0,0,0,0);
}


DrawItemBase::~DrawItemBase(void)
{
}

CRect DrawItemBase::getRect()
{
	return m_myRect;
}

CString DrawItemBase::getType()
{
	return CString();
}

CString DrawItemBase::getID()
{
	return CString();
}

int DrawItemBase::getZIndex()
{
	return 0;
}

void DrawItemBase::OnPaint( Graphics &g )
{
	g.FillRectangle(&SolidBrush(Color::Blue), m_myRect.left,m_myRect.top,m_myRect.Width(),m_myRect.Height());
}

bool DrawItemBase::isActive()
{
	return m_isActive;
}

bool DrawItemBase::checkSelected( CPoint point )
{
	return (bool)(m_myRect.PtInRect(point));
}

bool DrawItemBase::checkMovable( const std::vector<IDrawItem>& allItem,CPoint dstPoint )
{
	//TODO: ������
	return true;
}

void DrawItemBase::OnCommand( CString command,CString param )
{
}

void DrawItemBase::OnMouseMove( CPoint point )
{
	if (isActive())
	{
		CRect rc = m_myRect;
		rc.OffsetRect(point.x - m_posStart.x, point.y - m_posStart.y);
		m_myRect.SetRect(rc.left, rc.top, rc.right, rc.bottom);
		m_posStart = point;
	}
}

void DrawItemBase::OnLButtonDown(CPoint point)
{
	if (checkSelected(point))
	{
		//��Ч��ʱ��Ʃ�粼�õ�ʱ�򣬵����ζ��ȷ�ϰڷ�
		if (isActive())
		{
			endActive(point);
		}
		//��Ч��ʱ��Ʃ�羲ֹ�������ζ���ܵ���ѡ
		else
		{
			beginActive(point);
		}
	}
}

void DrawItemBase::OnLButtonUp(CPoint point)
{
	if (checkSelected(point))
	{
		//��Ч��ʱ��Ʃ�粼�õ�ʱ���ͷ���ζ��ȷ�ϰڷ�
		if (isActive())
		{
			endActive(point);
		}
	}
}

void DrawItemBase::OnRButtonDown(CPoint point)
{

}

void DrawItemBase::OnRButtonUp(CPoint point)
{

}

void DrawItemBase::beginActive(CPoint point)
{
	m_isActive = true;

	m_posStart = point;

	L4Cpp::Log()->debug("beginActive");
}

void DrawItemBase::endActive(CPoint point)
{
	m_isActive = false;

	m_posStart = point;

	L4Cpp::Log()->debug("endActive");
}

void DrawItemBase::setRect(int x1,int y1,int x2,int y2)
{
	m_myRect.SetRect(x1,y1,x2,y2);
}
void DrawItemBase::setRect(CPoint topLeft,CPoint bottomRight)
{
	m_myRect.SetRect(topLeft.x,topLeft.y,bottomRight.x,bottomRight.y);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
