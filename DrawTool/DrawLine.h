#pragma once
/************************************************************************/
#include <vector>
#include <list>
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
public:
	virtual void loadPoints(std::list<PointF>& points)const;	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::list<PointF>& points);	//���ⲿȡ�õ���µ�������
	virtual void getPath(GraphicsPath& path)const;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void onPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
	const PointF& getFrist()const{return *m_points.begin();}
	const PointF& getLast()const{return *(++m_points.begin());}
protected:
	std::vector<PointF> m_points;
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
public:
	virtual void getPath(GraphicsPath& path)const;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void onPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
	const PointF& getcenter()const;	
private:
	PointF m_center;
	float m_radius;
	int m_sign;

};
#endif
