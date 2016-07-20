#pragma once
#include "stdafx.h"
#include "DrawTools.h"
#include <vector>

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

	virtual Region getRegion() = 0;			//区域

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

	virtual Region getRegion() = 0;			//区域

	virtual void readPoints(std::list<PointF>& points) = 0;	//点集合
	virtual void writePoints(std::list<PointF>& points) = 0;	//点集合

	virtual void moveTo(PointF point) = 0;	//移动到
	virtual void move(PointF offset) = 0;	//偏移

	virtual void OnPaint( Graphics &g ) = 0;	//画图

protected:
	//////////////////////////////////////////////////////////////////////////
	// 数据
	CString m_type;							//类型
	CString m_ID;							//ID
	int m_order;							//序号
	int m_state;							//状态
	RectF m_myRect;							//区域

public:
	//////////////////////////////////////////////////////////////////////////
	// 公共数据
	const static int StateNormal;			//正常状态
	const static int StateHovered;			//覆盖状态
	const static int StateDisable;			//失效状态
	const static int StateDown;				//下按状态
	const static int StateError;			//错误状态
};
#endif
/************************************************************************/
/*  绘图直线多边形                                                      */
/************************************************************************/
#if 1
class DrawItemPolygon : public DrawItemBase
{
public:
	DrawItemPolygon();	
	DrawItemPolygon(PointF topLeft,PointF bottomRight);
	DrawItemPolygon(RectF rect);
	DrawItemPolygon(const std::vector<PointF>& outlines);
	~DrawItemPolygon();

public:
	virtual void OnPaint( Graphics &g );			//绘制

	virtual void moveTo(PointF point);				//移动到
	virtual void move(PointF offset);				//偏移

	void setOutline(std::vector<PointF> outlines);	//设置多边形点
	std::vector<PointF> getOutline();				//设置多边形点

	virtual void setRect(RectF rect);				//区域
	virtual RectF getRect();						//区域

	virtual Gdiplus::Region* getCloneRigon();		//区域

	void buildPath( GraphicsPath &path );			//区域

	virtual bool IsVisible(PointF point);			//区域判断

private:
	PointF* getOutlineArrClone();					//获得点阵（需要外部释放）

protected:
	std::vector<PointF> m_outlines;
};
#endif
/************************************************************************/
/*  绘图直线加曲线多边形                                                */
/************************************************************************/
#if 1
class IDrawLine
{
public:
	virtual void loadPoints(std::vector<PointF>& points) = 0;	//从线型数据中取得集合点
	virtual void updatePoints(std::vector<PointF>& points) = 0;	//从外部取得点更新到集合中
	virtual void getLineToPath(GraphicsPath& path) = 0;			//用内部点集合构建到图形中
};
class DrawStraightLine : public IDrawLine
{
public:
	DrawStraightLine(PointF first,PointF last);
public:
	virtual void loadPoints(std::vector<PointF>& points);
	virtual void updatePoints(std::vector<PointF>& points);
	virtual void getLineToPath(GraphicsPath& path);
protected:
	const static int m_MaxPointNum;
private:
	PointF m_first;
	PointF m_last;
};
class DrawArcLine : public IDrawLine
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
public:
	virtual void loadPoints(std::vector<PointF>& points);
	virtual void updatePoints(std::vector<PointF>& points);
	virtual void getLineToPath(GraphicsPath& path);
protected:
	const static int m_MaxPointNum;
private:
	PointF m_first;
	PointF m_last;
	float m_radius;
	int m_sign;
};


class DrawItemShape : public DrawItemBase
{
public:
	DrawItemShape(RectF outterRect,std::vector<IDrawLine*> lines);
	~DrawItemShape();

public:
	virtual void OnPaint( Graphics &g );			//绘制

	virtual void moveTo(PointF point);				//移动到
	virtual void move(PointF offset);				//偏移

	virtual void setAllPoints(std::vector<PointF>& outlines);	//设置多边形点
	virtual std::vector<PointF> getAllPoints();					//设置多边形点

	virtual void setRect(RectF rect);				//区域
	virtual RectF getRect();						//区域

	virtual Gdiplus::Region* getCloneRigon();		//区域

	void buildPath( GraphicsPath &path );

	virtual bool IsVisible(PointF point);			//区域判断

protected:
	std::vector<IDrawLine*> m_lines;
};
#endif