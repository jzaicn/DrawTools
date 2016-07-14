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
	CRect m_drawRect;								//工具的区域定义
	CPoint m_mouseStartPoint;						//鼠标的起始点
	std::vector<IDrawItem*> m_allDrawItemList;		//所有的画图元素
	std::vector<IDrawItem*> m_staticDrawItemList;	//所有静止
	std::vector<IDrawItem*> m_activeDrawItemList;	//所有激活数据

public:
	void OnPaint(Graphics& g);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
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
};

