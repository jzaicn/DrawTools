#pragma once

/************************************************************************/
/*  I�߶� IDrawLine                                                     */
/************************************************************************/
#if 1
class IDrawLine
{
public:
	virtual void loadPoints(std::list<PointF>& points) = 0;	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::list<PointF>& points) = 0;	//���ⲿȡ�õ���µ�������
	virtual void getPath(GraphicsPath& path) = 0;				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void getPaint(Graphics &g) = 0;						//���ڲ��㼯�ϻ���ͼ����
};
#endif
/************************************************************************/
/* �߶λ��� DrawLineBase                                                */
/************************************************************************/
#if 1
class DrawLineBase : public IDrawLine
{
public:
	DrawLineBase(PointF first,PointF last);
public:
	virtual void loadPoints(std::list<PointF>& points);	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::list<PointF>& points);	//���ⲿȡ�õ���µ�������
	virtual void getPath(GraphicsPath& path);				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void getPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
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
/* ֱ�� DrawStraightLine                                                */
/************************************************************************/
#if 1
class DrawStraightLine : public DrawLineBase
{
public:
	DrawStraightLine(PointF first,PointF last) :DrawLineBase(first,last){};
};
#endif
/************************************************************************/
/* ���� DrawArcLine                                                     */
/************************************************************************/
#if 1
class DrawArcLine : public DrawLineBase
{
public:
	DrawArcLine(PointF first, PointF last, float radius, int sign);
public:
	virtual void getPath(GraphicsPath& path);				//���ڲ��㼯�Ϲ�����ͼ����
	virtual void getPaint(Graphics &g);						//���ڲ��㼯�ϻ���ͼ����
private:
	float m_radius;
	int m_sign;
};
#endif
