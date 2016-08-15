#pragma once
/************************************************************************/
#include <vector>
#include <list>
#include "DrawCommon.h"
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
	virtual void foreachPoint(void (*func)(PointF&)) = 0;
	virtual void foreachPoint(void (*func)(const PointF&))const = 0;
	virtual bool isChange()const = 0;
	virtual ~IDataLine(){};
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
	~DataLineBase(){}
public:
	virtual void loadPoints(std::list<PointF>& points)const;	//从线型数据中取得集合点
	virtual void updatePoints(std::list<PointF>& points);	//从外部取得点更新到集合中
	virtual void getPath(GraphicsPath& path)const;				//用内部点集合构建到图形中
	virtual void onPaint(Graphics &g);						//用内部点集合画到图形中
	virtual const PointF& getFrist()const{return *m_points.begin();}
	virtual const PointF& getLast()const{return *(++m_points.begin());}

	virtual void foreachPoint(void (*func)(PointF&));
	virtual void foreachPoint(void (*func)(const PointF&))const;

 	template<class T>
 	void foreachPoint(T func){for_each(m_points.begin(),m_points.end(),func);};
 
 	template<class T>
 	void foreachPoint(T func)const{for_each(m_points.cbegin(),m_points.cend(),func);};

	virtual bool isChange()const;

protected:
	std::vector<PointF> m_points;
	std::vector<PointF> m_points_last;
	bool m_isChange;
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
	virtual void getPath(GraphicsPath& path)const;				//用内部点集合构建到图形中
	virtual void onPaint(Graphics &g);						//用内部点集合画到图形中
	const PointF& getcenter()const;	
	const float& getRadius()const{return m_radius;}	
	const int& getSign()const{ assert(m_sign!=-1);return m_sign;}	
private:
	PointF m_center;
	float m_radius;
	int m_sign;
};
#endif


/************************************************************************/
/* 多线段组成		*/
/************************************************************************/
#if 1
class DrawLineList : public IDataLine
{
public:
	DrawLineList(const std::list<std::shared_ptr<DataLineBase>>& linelist):m_linelist(linelist){}
	
	virtual void getPath(GraphicsPath& path)const;				//用内部点集合构建到图形中
	virtual void onPaint(Graphics &g);						//用内部点集合画到图形中
	const std::list<std::shared_ptr<DataLineBase>>& getlinelist()const{return m_linelist;}

	virtual void loadPoints(std::list<PointF>& points) const;

	virtual void updatePoints(std::list<PointF>& points);

	virtual void foreachPoint(void (*func) (PointF&));

	virtual void foreachPoint(void (*func) (const PointF&))const;

	template<class T>
	void foreachPoint(T func){
		std::for_each(m_linelist.begin(),m_linelist.end()
		,[&func](std::shared_ptr<DataLineBase>& line){
			line.get()->foreachPoint(func);
		});
	}

	template<class T>
	void foreachPoint(T func)const{
		std::for_each(m_linelist.cbegin(),m_linelist.cend()
			,[&func](const std::shared_ptr<DataLineBase>& line){
				line.get()->foreachPoint(func);
		});
	}

private:
	std::list<std::shared_ptr<DataLineBase>> m_linelist;
};
#endif



