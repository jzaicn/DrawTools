#pragma once

#include "atltypes.h"
#include "DrawItem.h"
#include <vector>

class DrawItemManagement
{
public:
	DrawItemManagement(void);
	~DrawItemManagement(void);

private:
	RectF m_drawRect;								//���ߵ�������
	PointF m_mouseStartPoint;						//������ʼ��
	std::list<IDrawItem*> m_allDrawItemList;		//���еĻ�ͼԪ��
	std::list<IDrawItem*> m_staticDrawItemList;	//���о�ֹ
	std::list<IDrawItem*> m_activeDrawItemList;	//���м�������

public:
	void OnPaint(Graphics& g);						//��Ӧ��ͼ
	bool PreTranslateMessage(MSG* pMsg);			//��Ӧ��Ϣ
	BOOL OnEraseBkgnd(CDC* pDC);					//��Ӧ��������
	void OnMouseMove(UINT nFlags, PointF point);	//��Ӧ����ƶ�



	void OnLButtonDown(UINT nFlags, PointF point);	//��Ӧ�������
	void OnLButtonUp(UINT nFlags, PointF point);	//��Ӧ�������
	void OnRButtonDown(UINT nFlags, PointF point);	//��Ӧ�Ҽ�����
	void OnRButtonUp(UINT nFlags, PointF point);	//��Ӧ�Ҽ�����

public:
	void addDrawItem(IDrawItem* drawItem);			//���Ԫ��
	std::list<IDrawItem*>& getDrawItemList();		//ȡ��Ԫ���б�
	void clearDrawItem();							//���Ԫ���б�

	void setDrawRectF(RectF drawRect);				//���û�ͼ����
	void setDrawCRect(CRect drawRect);				//���û�ͼ����
	RectF getDrawRectF();							//�õ���ͼ����
	CRect getDrawCRect();							//�õ���ͼ����

public:
	bool IsCrashArea();								//�Ƿ�����;�̬������ײ
	void SetActiveState(int state);					//ͳһ���û����Ԫ��״̬
	bool checkMoveable(IDrawItem* item , PointF point);	//����Ƿ����ƶ�
	void rotateDrawItem(IDrawItem* item);			//Ԫ����ת
	void scaleDrawItemDown(IDrawItem* item);		//Ԫ����С
};

