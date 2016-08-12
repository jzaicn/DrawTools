#pragma once
#include <list>
#include "DrawCommon.h"

#include "DrawItem.h"

/************************************************************************/
/* ��ͼ���Խӿ� IDrawItemStrategy                                       */
/************************************************************************/
#if 1
class IDrawItemStrategy
{
public:
	virtual void OnInitial(std::list<IDrawItem*> all) = 0;									//��Ӧ��ʼ��
	virtual void OnPaint(Graphics& g, std::list<IDrawItem*> all) = 0;						//��Ӧ��ͼ
	virtual bool PreTranslateMessage(MSG* pMsg, std::list<IDrawItem*> all) = 0;				//��Ӧ��Ϣ
	virtual bool OnEraseBkgnd(CDC* pDC, std::list<IDrawItem*> all) = 0;						//��Ӧ��������
	virtual void OnMouseMove(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//��Ӧ����ƶ�
	virtual void OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;	//��Ӧ�������
	virtual void OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//��Ӧ�������
	virtual void OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;	//��Ӧ�Ҽ�����
	virtual void OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//��Ӧ�Ҽ�����
	virtual void OnClear(std::list<IDrawItem*> all) = 0;									//��Ӧ�������
	virtual ~IDrawItemStrategy(){};
};
#endif

/************************************************************************/
/* ��ͼ���Ի��� DrawItemStrategyBase                                     */
/************************************************************************/
#if 1
class DrawItemStrategyBase : public IDrawItemStrategy
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemStrategyBase():m_pressFlag(false){};
	virtual ~DrawItemStrategyBase(){};

public:
	//////////////////////////////////////////////////////////////////////////
	// �¼�
	virtual void OnInitial(std::list<IDrawItem*> all);									//��Ӧ��ʼ��
	virtual void OnPaint(Graphics& g, std::list<IDrawItem*> all);						//��Ӧ��ͼ
	virtual bool PreTranslateMessage(MSG* pMsg, std::list<IDrawItem*> all);				//��Ӧ��Ϣ
	virtual bool OnEraseBkgnd(CDC* pDC, std::list<IDrawItem*> all);						//��Ӧ��������
	virtual void OnMouseMove(UINT nFlags, PointF point, std::list<IDrawItem*> all);		//��Ӧ����ƶ�
	virtual void OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all);	//��Ӧ�������
	virtual void OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all);		//��Ӧ�������
	virtual void OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all);	//��Ӧ�Ҽ�����
	virtual void OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all);		//��Ӧ�Ҽ�����
	virtual void OnClear(std::list<IDrawItem*> all);									//��Ӧ�������
	
protected:
	PointF m_mouseStartPoint;						//������ʼ��
	bool m_pressFlag;								//��갴��
	
};
#endif
