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
	RectF m_drawRect;								//工具的区域定义
	Color m_backgroundColor;						//工作区间的背景色
	IDrawItemStrategy* m_strategy;					//工作策略
	std::list<IDrawItem*> m_allDrawItemList;		//所有的画图元素

public:
	void OnInitial();								//响应初始化
	void OnPaint(Graphics& g);						//响应绘图
	bool PreTranslateMessage(MSG* pMsg);			//响应消息
	BOOL OnEraseBkgnd(CDC* pDC);					//响应擦除背景
	void OnMouseMove(UINT nFlags, PointF point);	//响应鼠标移动
	void OnLButtonDown(UINT nFlags, PointF point);	//响应左键按下
	void OnLButtonUp(UINT nFlags, PointF point);	//响应左键弹起
	void OnRButtonDown(UINT nFlags, PointF point);	//响应右键按下
	void OnRButtonUp(UINT nFlags, PointF point);	//响应右键弹起

public:
	void addDrawItem(IDrawItem* drawItem);			//添加元素
	void setDrawItemList(std::list<IDrawItem*> list);	//设置元素列表
	std::list<IDrawItem*> getDrawItemList();		//取回元素列表
	void clearDrawItem();							//清空元素列表

	Color BackgroundColor() const { return m_backgroundColor; }
	void BackgroundColor(Color val) { m_backgroundColor = val; }

	IDrawItemStrategy* Strategy() const { return m_strategy; }
	void Strategy(IDrawItemStrategy* val) {delete m_strategy; m_strategy = val; }

	void setDrawRectF(RectF drawRect);				//设置绘图区域
	void setDrawCRect(CRect drawRect);				//设置绘图区域
	RectF getDrawRectF();							//得到绘图区域
	CRect getDrawCRect();							//得到绘图区域


};

