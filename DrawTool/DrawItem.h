#pragma once
#include "stdafx.h"
#include "DrawTools.h"
#include <vector>

/************************************************************************/
/*  绘图接口                                                            */
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

	virtual void OnPaint( Graphics &g ) = 0;	//画图

	virtual void moveTo(PointF point) = 0;	//移动到
	virtual void move(PointF offset) = 0;	//偏移

	virtual void setRect(RectF rect) = 0;	//区域
	virtual RectF getRect() = 0;			//区域

	virtual Gdiplus::Region* getCloneRigon() = 0;	//区域（需要外部释放）
	virtual bool IsVisible(PointF point) = 0;		//区域判断
};
#endif
/************************************************************************/
/*  绘图基类                                                            */
/************************************************************************/
#if 1
class DrawItemBase : public IDrawItem
{
public:
	DrawItemBase();
	DrawItemBase(PointF topLeft,PointF bottomRight);
	DrawItemBase(RectF rect);
	virtual ~DrawItemBase(void);

	virtual void OnPaint( Graphics &g );	//画图

	virtual void moveTo(PointF point);		//移动到
	virtual void move(PointF offset);		//偏移

	virtual void setState(int state);		//状态
	virtual int getState();					//状态

	virtual void setType(CString type);		//类型
	virtual CString getType();				//类型

	virtual void setID(CString id);			//ID
	virtual CString getID();				//ID

	virtual void setOrder(int order);		//序号
	virtual int getOrder();					//序号


	virtual void setRect( RectF rect );		//区域
	void setRect(PointF topLeft,PointF bottomRight);	//区域
	void setRect(int x1,int y1,int x2,int y2);			//区域
	virtual RectF getRect();				//区域

	std::vector<PointF> getPoints();		//区域顶点
	virtual Gdiplus::Region* getCloneRigon();			//区域
	virtual bool IsVisible(PointF point);	//区域判断

public:
	static Color ColorNormal;				//正常颜色
	static Color ColorHovered;				//覆盖颜色
	static Color ColorDisable;				//失效颜色
	static Color ColorDown;					//下按颜色
	static Color ColorError;				//错误颜色
	
	const static int StateNormal;			//正常状态
	const static int StateHovered;			//覆盖状态
	const static int StateDisable;			//失效状态
	const static int StateDown;				//下按状态
	const static int StateError;			//错误状态

protected:
	CString m_type;							//类型
	CString m_ID;							//ID
	int m_order;							//序号
	int m_state;							//状态
	RectF m_myRect;							//区域
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
	virtual void loadPoints(std::vector<PointF>& points) = 0;		//从线型数据中取得集合点
	virtual void updatePoints(std::vector<PointF>& points) = 0;	//从外部取得点更新到集合中
	virtual void getLineToPath(GraphicsPath& path) = 0;		//用内部点集合构建到图形中
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
public:
	const static int ArcSignLeft;
	const static int ArcSignRight;
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

	void setAllPoints(std::vector<PointF> outlines);//设置多边形点
	std::vector<PointF> getAllPoints();				//设置多边形点

	virtual void setRect(RectF rect);				//区域
	virtual RectF getRect();						//区域

	virtual Gdiplus::Region* getCloneRigon();		//区域
	virtual bool IsVisible(PointF point);			//区域判断

protected:
	std::vector<IDrawLine*> m_lines;
};
#endif