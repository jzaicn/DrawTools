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
	std::vector<IDrawItem*> m_allDrawItemList;		//���еĻ�ͼԪ��
	std::vector<IDrawItem*> m_staticDrawItemList;	//���о�ֹ
	std::vector<IDrawItem*> m_activeDrawItemList;	//���м�������

public:
	void OnPaint(Graphics& g);
	bool PreTranslateMessage(MSG* pMsg);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnMouseMove(UINT nFlags, PointF point);

	bool IsCrashArea();


	void OnLButtonDown(UINT nFlags, PointF point);
	void OnLButtonUp(UINT nFlags, PointF point);
	void OnRButtonDown(UINT nFlags, PointF point);
	void OnRButtonUp(UINT nFlags, PointF point);

public:
	void addDrawItem(IDrawItem* drawItem);
	std::vector<IDrawItem*>& getDrawItemList();
	void clearDrawItem();
	void setDrawRectF(RectF drawRect);
	void setDrawCRect(CRect drawRect);
	RectF getDrawRectF();
	CRect getDrawCRect();

public:


	void SetActiveState(int state);

	bool checkMoveable(IDrawItem* item , PointF point);

	//�Ƕ�ת����  
	double getRadFromAngle(double angle)  ;
	//����ĳ�㣬��תһ���Ƕ�   
	void rotateByAngle(PointF pointCenter,  
		PointF &pointNeedRotate,  
		double dAngleDegree)  ;
	void DrawItemManagement::rotateDrawItem(IDrawItem* item);
};

