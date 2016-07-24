#pragma once
#include "stdafx.h"
#include <vector>
#include <list>

#include "DrawLine.h"

/************************************************************************/
/*  绘图接口 IDrawItem                                                  */
/************************************************************************/
#if 1
class IDrawItem
{
public:
	virtual void setState(int state) = 0;	//状态
	virtual int getState() = 0;				//状态

	virtual void setType(CString type) = 0;	//类型
	virtual CString getType() = 0;			//类型

	virtual void setID(CString id) = 0;		//ID
	virtual CString getID() = 0;			//ID

	virtual void setOrder(int order) = 0;	//序号
	virtual int getOrder() = 0;				//序号

	virtual void setRect(RectF rect) = 0;	//区域
	virtual RectF getRect() = 0;			//区域

	virtual std::shared_ptr<Region> getRegion() = 0;			//区域

	virtual void readPoints(std::list<PointF>& points) = 0;	//点集合
	virtual void writePoints(std::list<PointF>& points) = 0;	//点集合

	virtual void moveTo(PointF point) = 0;	//移动到
	virtual void move(PointF offset) = 0;	//偏移

	virtual void OnPaint( Graphics &g ) = 0;	//画图
};
#endif
/************************************************************************/
/*  绘图基类 DrawItemBase                                               */
/************************************************************************/
#if 1
class DrawItemBase : public IDrawItem
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造数据
	DrawItemBase();
	DrawItemBase(PointF topLeft,PointF bottomRight);
	DrawItemBase(RectF rect);
	virtual ~DrawItemBase(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// 实现接口
	virtual void setState(int state);	//状态
	virtual int getState();				//状态

	virtual void setType(CString type);	//类型
	virtual CString getType();			//类型

	virtual void setID(CString id);		//ID
	virtual CString getID();			//ID

	virtual void setOrder(int order);	//序号
	virtual int getOrder();				//序号

	virtual void setRect(RectF rect);	//区域
	virtual RectF getRect();			//区域

	virtual void setDrawPath(bool isDrawPath);				//画轮廓
	virtual void setFillPath(bool isFillPath);				//填充

	virtual std::shared_ptr<Region> getRegion();			//区域

	virtual void readPoints(std::list<PointF>& points);		//点集合
	virtual void writePoints(std::list<PointF>& points);	//点集合

	virtual void moveTo(PointF point);	//移动到
	virtual void move(PointF offset);	//偏移

	virtual void OnPaint( Graphics &g );	//画图

protected:
	//////////////////////////////////////////////////////////////////////////
	// 数据
	CString m_type;							//类型
	CString m_ID;							//ID
	int m_order;							//序号
	int m_state;							//状态
	RectF m_myRect;							//区域
	bool m_isDrawPath;						//画轮廓
	bool m_isFillPath;						//填充
	Color m_drawColor;						//自画边线颜色
	Color m_fillColor;						//自画填充颜色

public:
	//////////////////////////////////////////////////////////////////////////
	// 公共数据
	const static int StateSelfDefine;		//自定义状态
	const static int StateNormal;			//正常状态
	const static int StateHovered;			//覆盖状态
	const static int StateDisable;			//失效状态
	const static int StateDown;				//下按状态
	const static int StateError;			//错误状态
};
#endif
/************************************************************************/
/*  绘图形状 DrawItemShape                                               */
/************************************************************************/
#if 1
class DrawItemShape : public DrawItemBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemShape(RectF rect,std::list<IDrawLine*> lines);
	virtual ~DrawItemShape();

public:
	//////////////////////////////////////////////////////////////////////////
	// 接口实现
	virtual std::shared_ptr<Region> getRegion();			//区域

	virtual void readPoints(std::list<PointF>& points);		//点集合
	virtual void writePoints(std::list<PointF>& points);	//点集合

	virtual void move(PointF offset);		//偏移

	virtual void OnPaint( Graphics &g );	//画图

protected:
	//////////////////////////////////////////////////////////////////////////
	// 数据
	std::list<IDrawLine*> m_lines;
};
#endif
/************************************************************************/
/*  绘图形状 DrawItemCircle                                             */
/************************************************************************/
#if 1

class DrawItemCircle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemCircle(RectF rect,float pos_x,float pos_y,float radius);
	void initCircle(RectF rect,float pos_x,float pos_y,float radius);
	virtual ~DrawItemCircle(){};
};
#endif
/************************************************************************/
/*  绘图形状 DrawItemRectangle                                          */
/************************************************************************/
#if 1
class DrawItemRectangle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemRectangle(RectF rect,std::list<IDrawLine*> lines);
	virtual ~DrawItemRectangle(){};
};
#endif