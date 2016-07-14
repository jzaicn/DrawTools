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
	CRect m_drawRect;								//���ߵ�������
	CPoint m_mouseStartPoint;						//������ʼ��
	std::vector<IDrawItem*> m_allDrawItemList;		//���еĻ�ͼԪ��
	std::vector<IDrawItem*> m_staticDrawItemList;	//���о�ֹ
	std::vector<IDrawItem*> m_activeDrawItemList;	//���м�������

public:
	void OnPaint(Graphics& g);
	bool PreTranslateMessage(MSG* pMsg);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnMouseMove(UINT nFlags, CPoint point);

	bool IsCrashArea();


	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);

public:
	void addDrawItem(IDrawItem* drawItem);
	std::vector<IDrawItem*>& getDrawItemList();
	void clearDrawItem();
	void setDrawRect(CRect drawRect);
	CRect getDrawRect();

public:


	void SetActiveState(int state);

	bool checkMoveable(IDrawItem* item , CPoint point);

	//�Ƕ�ת����  
	double DrawItemManagement::getRadFromAngle(double angle)  ;
	//����ĳ�㣬��תһ���Ƕ�   
	void DrawItemManagement::rotateByAngle(PointF pointCenter,  
		PointF &pointNeedRotate,  
		double dAngleDegree)  ;
	void DrawItemManagement::rotateDrawItem(IDrawItem* item);
};

