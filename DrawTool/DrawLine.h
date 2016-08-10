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
	virtual void onPaint(Graphics &g) = 0;						//用内部点集合画到图形中
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
	virtual void onPaint(Graphics &g);						//用内部点集合画到图形中
	const PointF& getFrist()const{return *m_points.begin();}
	const PointF& getLast()const{return *(++m_points.begin());}
protected:
	std::vector<PointF> m_points;
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
/* 曲线 DrawArcLine    point[0]开始点 point[1]结束点 point[0]圆点		*/
/************************************************************************/
#if 1
class DrawArcLine : public DataLineBase
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
	DrawArcLine(PointF first, PointF last,PointF center);		//圆心与开始结束点
public:
	virtual void getPath(GraphicsPath& path)const;				//用内部点集合构建到图形中
	virtual void onPaint(Graphics &g);						//用内部点集合画到图形中
	const PointF& getcenter()const;	
private:
	PointF m_center;
	float m_radius;
	int m_sign;

};
#endif
