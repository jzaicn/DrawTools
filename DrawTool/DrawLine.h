#pragma once

/************************************************************************/
/*  I线段 IDrawLine                                                     */
/************************************************************************/
#if 1
class IDrawLine
{
public:
	virtual void loadPoints(std::list<PointF>& points) = 0;	//从线型数据中取得集合点
	virtual void updatePoints(std::list<PointF>& points) = 0;	//从外部取得点更新到集合中
	virtual void getPath(GraphicsPath& path) = 0;				//用内部点集合构建到图形中
	virtual void getPaint(Graphics &g) = 0;						//用内部点集合画到图形中
};
#endif
/************************************************************************/
/* 线段基类 DrawLineBase                                                */
/************************************************************************/
#if 1
class DrawLineBase : public IDrawLine
{
public:
	DrawLineBase(PointF first,PointF last);
public:
	virtual void loadPoints(std::list<PointF>& points);	//从线型数据中取得集合点
	virtual void updatePoints(std::list<PointF>& points);	//从外部取得点更新到集合中
	virtual void getPath(GraphicsPath& path);				//用内部点集合构建到图形中
	virtual void getPaint(Graphics &g);						//用内部点集合画到图形中
public:
	void setPen(Pen pen);									//Pen
	Pen getPen();											//Pen
protected:
	Pen m_pen;
	PointF m_first;
	PointF m_last;
};
#endif
/************************************************************************/
/* 直线 DrawStraightLine                                                */
/************************************************************************/
#if 1
class DrawStraightLine : public DrawLineBase
{
public:
	DrawStraightLine(PointF first,PointF last) :DrawLineBase(first,last){};
};
#endif
/************************************************************************/
/* 曲线 DrawArcLine                                                     */
/************************************************************************/
#if 1
class DrawArcLine : public DrawLineBase
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
public:
	virtual void getPath(GraphicsPath& path);				//用内部点集合构建到图形中
	virtual void getPaint(Graphics &g);						//用内部点集合画到图形中
private:
	float m_radius;
	int m_sign;
};
#endif
