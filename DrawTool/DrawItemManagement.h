#pragma once

#include "atltypes.h"
#include <vector>
#include <list>
#include "DrawCommon.h"

#include "DrawItem.h"
#include "DrawItemStrategy.h"

class DrawItemManagement
{
public:
	DrawItemManagement(void);
	~DrawItemManagement(void);

private:
	RectF m_drawRect;								//���ߵ�������
	Color m_backgroundColor;						//��������ı���ɫ
	IDrawItemStrategy* m_strategy;					//��������
	std::list<IDrawItem*> m_allDrawItemList;		//���еĻ�ͼԪ��

public:
	void OnInitial();								//��Ӧ��ʼ��
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
	void setDrawItemList(std::list<IDrawItem*> list);	//����Ԫ���б�
	std::list<IDrawItem*> getDrawItemList();		//ȡ��Ԫ���б�
	void clearDrawItem();							//���Ԫ���б�

	Color BackgroundColor() const { return m_backgroundColor; }
	void BackgroundColor(Color val) { m_backgroundColor = val; }

	IDrawItemStrategy* Strategy() const { return m_strategy; }
	void Strategy(IDrawItemStrategy* val) {delete m_strategy; m_strategy = val; }

	void setDrawRectF(RectF drawRect);				//���û�ͼ����
	void setDrawCRect(CRect drawRect);				//���û�ͼ����
	RectF getDrawRectF();							//�õ���ͼ����
	CRect getDrawCRect();							//�õ���ͼ����


};

