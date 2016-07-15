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
	RectF m_drawRect;								//工具的区域定义
	PointF m_mouseStartPoint;						//鼠标的起始点
	std::vector<IDrawItem*> m_allDrawItemList;		//所有的画图元素
	std::vector<IDrawItem*> m_staticDrawItemList;	//所有静止
	std::vector<IDrawItem*> m_activeDrawItemList;	//所有激活数据

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

	//角度转弧度  
	double getRadFromAngle(double angle)  ;
	//根据某点，旋转一个角度   
	void rotateByAngle(PointF pointCenter,  
		PointF &pointNeedRotate,  
		double dAngleDegree)  ;
	void DrawItemManagement::rotateDrawItem(IDrawItem* item);
};

