#pragma once
#include <list>
#include "DrawCommon.h"

#include "DrawItem.h"

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
	virtual void OnLButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;	//响应左键按下
	virtual void OnLButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//响应左键弹起
	virtual void OnRButtonDown(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;	//响应右键按下
	virtual void OnRButtonUp(UINT nFlags, PointF point, std::list<IDrawItem*> all) = 0;		//响应右键弹起
	virtual void OnClear(std::list<IDrawItem*> all) = 0;									//响应清除数据
	virtual ~IDrawItemStrategy(){};
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
	DrawItemStrategyBase():m_pressFlag(false){};
	virtual ~DrawItemStrategyBase(){};

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
	virtual void OnClear(std::list<IDrawItem*> all);									//响应清除数据
	
protected:
	PointF m_mouseStartPoint;						//鼠标的起始点
	bool m_pressFlag;								//鼠标按下
	
};
#endif
