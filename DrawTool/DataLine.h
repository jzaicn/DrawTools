#pragma once
/************************************************************************/
#include <vector>
#include <list>
#include "DrawCommon.h"
/*  I�߶� IDataLine   
 *  ֻ���������ݴ洢������߶ΰ���˳�����п������һ�������*/
/************************************************************************/
#if 1
class IDataLine
{
public:
	virtual void loadPoints(std::list<PointF>& points)const = 0;	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::list<PointF>& points) = 0;	//���ⲿȡ�õ���µ�������
	virtual void getPath(GraphicsPath& path)const = 0;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void onPaint(Graphics &g) = 0;						//���ڲ��㼯�ϻ���ͼ����
	virtual void foreachPoint(void (*func)(PointF&)) = 0;
	virtual void foreachPoint(void (*func)(const PointF&))const = 0;
	virtual bool isChange()const = 0;
	virtual ~IDataLine(){};
};
#endif
/************************************************************************/
/* �߶λ��� DrawLineBase                                                */
/************************************************************************/
#if 1
class DataLineBase : public IDataLine
{
public:
	DataLineBase(PointF first,PointF last);
	~DataLineBase(){}
public:
	virtual void loadPoints(std::list<PointF>& points)const;	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::list<PointF>& points);	//���ⲿȡ�õ���µ�������
	virtual void getPath(GraphicsPath& path)const;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void onPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
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
/* ֱ�� DrawStraightLine                                                */
/************************************************************************/
#if 1
class DataStraightLine : public DataLineBase
{
public:
	DataStraightLine(PointF first,PointF last) :DataLineBase(first,last){};
};
#endif
/************************************************************************/
/* ���� DrawArcLine    point[0]��ʼ�� point[1]������ point[0]Բ��		*/
/************************************************************************/
#if 1
class DrawArcLine : public DataLineBase
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
	DrawArcLine(PointF first, PointF last,PointF center);		//Բ���뿪ʼ������
	virtual void getPath(GraphicsPath& path)const;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void onPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
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
/* ���߶����		*/
/************************************************************************/
#if 1
class DrawLineList : public IDataLine
{
public:
	DrawLineList(const std::list<std::shared_ptr<DataLineBase>>& linelist):m_linelist(linelist){}
	
	virtual void getPath(GraphicsPath& path)const;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void onPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
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



