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
	virtual void getPaint(Graphics &g) = 0;						//���ڲ��㼯�ϻ���ͼ����
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
	virtual void getPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����

protected:
	PointF m_first;
	PointF m_last;
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
/* ���� DrawArcLine                                                     */
/************************************************************************/
#if 1
class DrawArcLine : public DataLineBase
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
public:
	virtual void getPath(GraphicsPath& path)const;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void getPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
private:
	float m_radius;
	int m_sign;
};
#endif
