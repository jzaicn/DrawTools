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
	CRect m_drawRect;
	std::vector<IDrawItem*> m_staticDrawItemList;
	std::vector<IDrawItem*> m_activeDrawItemList;

public:
	void OnPaint(CPaintDC& dc);
	void OnPaintWithoutPrework(Graphics& g);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnMouseMove(UINT nFlags, CPoint point);
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
	bool checkMoveable(IDrawItem* item , CPoint point);
};

