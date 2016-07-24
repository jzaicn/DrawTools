#pragma once
#include "DrawFrameHeader.h"

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
	virtual void OnLButtonDown(UINT nFlags, PointF poin, std::list<IDrawItem*> allt) = 0;	//��Ӧ�������
	virtual void OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//��Ӧ�������
	virtual void OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;	//��Ӧ�Ҽ�����
	virtual void OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//��Ӧ�Ҽ�����

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
	DrawItemStrategyBase(void);
	~DrawItemStrategyBase();

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

public:
	//////////////////////////////////////////////////////////////////////////
	// ���
	bool IsCrash_ActiveWithStatic();							//�Ƿ�����;�̬������ײ
	void SetAll_ActiveState(int state);							//ͳһ���û����Ԫ��״̬

public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	static bool MoveDrawItem(IDrawItem* item , PointF point);	//����Ƿ����ƶ�
	static void RotateDrawItem(IDrawItem* item);				//Ԫ����ת
	static void scaleDrawItemDown(IDrawItem* item);				//Ԫ����С



protected:
	std::list<IDrawItem*> m_static;	//���о�ֹ
	std::list<IDrawItem*> m_active;	//���м�������
	PointF m_mouseStartPoint;						//������ʼ��
	
};
#endif
