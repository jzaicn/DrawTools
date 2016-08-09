#pragma once
/************************************************************************/
#include <vector>
#include <list>
/*  I线段 IDataLine   
 *  只用于做数据存储，多个线段按照顺序排列可以组成一个多边形*/
/************************************************************************/
#if 1
class IDataLine
{
public:
	virtual void loadPoints(std::list<PointF>& points)const = 0;	//从线型数据中取得集合点
	virtual void updatePoints(std::list<PointF>& points) = 0;	//从外部取得点更新到集合中
	virtual void getPath(GraphicsPath& path)const = 0;				//用内部点集合构建到图形中
	virtual void getPaint(Graphics &g) = 0;						//用内部点集合画到图形中
};
#endif
/************************************************************************/
/* 线段基类 DrawLineBase                                                */
/************************************************************************/
#if 1
class DataLineBase : public IDataLine
{
public:
	DataLineBase(PointF first,PointF last);

public:
	virtual void loadPoints(std::list<PointF>& points)const;	//从线型数据中取得集合点
	virtual void updatePoints(std::list<PointF>& points);	//从外部取得点更新到集合中
	virtual void getPath(GraphicsPath& path)const;				//用内部点集合构建到图形中
	virtual void getPaint(Graphics &g);						//用内部点集合画到图形中

protected:
	PointF m_first;
	PointF m_last;
};
#endif
/************************************************************************/
/* 直线 DrawStraightLine                                                */
/************************************************************************/
#if 1
class DataStraightLine : public DataLineBase
{
public:
	DataStraightLine(PointF first,PointF last) :DataLineBase(first,last){};
};
#endif
/************************************************************************/
/* 曲线 DrawArcLine                                                     */
/************************************************************************/
#if 1
class DrawArcLine : public DataLineBase
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
public:
	virtual void getPath(GraphicsPath& path)const;				//用内部点集合构建到图形中
	virtual void getPaint(Graphics &g);						//用内部点集合画到图形中
private:
	float m_radius;
	int m_sign;
};
#endif
