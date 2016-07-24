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
	std::list<IDrawItem*> m_allDrawItemList;		//所有的画图元素
	std::list<IDrawItem*> m_staticDrawItemList;	//所有静止
	std::list<IDrawItem*> m_activeDrawItemList;	//所有激活数据

public:
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
	std::list<IDrawItem*>& getDrawItemList();		//取回元素列表
	void clearDrawItem();							//清空元素列表

	void setDrawRectF(RectF drawRect);				//设置绘图区域
	void setDrawCRect(CRect drawRect);				//设置绘图区域
	RectF getDrawRectF();							//得到绘图区域
	CRect getDrawCRect();							//得到绘图区域

public:
	bool IsCrashArea();								//是否活动区域和静态区域碰撞
	void SetActiveState(int state);					//统一设置活动区域元素状态
	bool checkMoveable(IDrawItem* item , PointF point);	//检测是否能移动
	void rotateDrawItem(IDrawItem* item);			//元素旋转
	void scaleDrawItemDown(IDrawItem* item);		//元素缩小
};

