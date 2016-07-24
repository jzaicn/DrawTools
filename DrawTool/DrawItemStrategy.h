#pragma once
#include "DrawFrameHeader.h"

/************************************************************************/
/* 画图策略接口 IDrawItemStrategy                                       */
/************************************************************************/
#if 1
class IDrawItemStrategy
{
public:
	virtual void OnInitial(std::list<IDrawItem*> all) = 0;									//响应初始化
	virtual void OnPaint(Graphics& g, std::list<IDrawItem*> all) = 0;						//响应绘图
	virtual bool PreTranslateMessage(MSG* pMsg, std::list<IDrawItem*> all) = 0;				//响应消息
	virtual bool OnEraseBkgnd(CDC* pDC, std::list<IDrawItem*> all) = 0;						//响应擦除背景
	virtual void OnMouseMove(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//响应鼠标移动
	virtual void OnLButtonDown(UINT nFlags, PointF poin, std::list<IDrawItem*> allt) = 0;	//响应左键按下
	virtual void OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//响应左键弹起
	virtual void OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;	//响应右键按下
	virtual void OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//响应右键弹起

};
#endif

/************************************************************************/
/* 画图策略基类 DrawItemStrategyBase                                     */
/************************************************************************/
#if 1
class DrawItemStrategyBase : public IDrawItemStrategy
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemStrategyBase(void);
	~DrawItemStrategyBase();

public:
	//////////////////////////////////////////////////////////////////////////
	// 事件
	virtual void OnInitial(std::list<IDrawItem*> all);									//响应初始化
	virtual void OnPaint(Graphics& g, std::list<IDrawItem*> all);						//响应绘图
	virtual bool PreTranslateMessage(MSG* pMsg, std::list<IDrawItem*> all);				//响应消息
	virtual bool OnEraseBkgnd(CDC* pDC, std::list<IDrawItem*> all);						//响应擦除背景
	virtual void OnMouseMove(UINT nFlags, PointF point, std::list<IDrawItem*> all);		//响应鼠标移动
	virtual void OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all);	//响应左键按下
	virtual void OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all);		//响应左键弹起
	virtual void OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all);	//响应右键按下
	virtual void OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all);		//响应右键弹起

public:
	//////////////////////////////////////////////////////////////////////////
	// 检测
	bool IsCrash_ActiveWithStatic();							//是否活动区域和静态区域碰撞
	void SetAll_ActiveState(int state);							//统一设置活动区域元素状态

public:
	//////////////////////////////////////////////////////////////////////////
	// 操作
	static bool MoveDrawItem(IDrawItem* item , PointF point);	//检测是否能移动
	static void RotateDrawItem(IDrawItem* item);				//元素旋转
	static void scaleDrawItemDown(IDrawItem* item);				//元素缩小



protected:
	std::list<IDrawItem*> m_static;	//所有静止
	std::list<IDrawItem*> m_active;	//所有激活数据
	PointF m_mouseStartPoint;						//鼠标的起始点
	
};
#endif
