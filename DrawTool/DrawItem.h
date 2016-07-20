#pragma once
#include "stdafx.h"
#include "DrawTools.h"
#include <vector>

/************************************************************************/
/*  ��ͼ�ӿ� IDrawItem                                                  */
/************************************************************************/
#if 1
class IDrawItem
{
public:
	virtual void setState(int state) = 0;	//״̬
	virtual int getState() = 0;				//״̬

	virtual void setType(CString type) = 0;	//����
	virtual CString getType() = 0;			//����

	virtual void setID(CString id) = 0;		//ID
	virtual CString getID() = 0;			//ID

	virtual void setOrder(int order) = 0;	//���
	virtual int getOrder() = 0;				//���

	virtual void setRect(RectF rect) = 0;	//����
	virtual RectF getRect() = 0;			//����

	virtual Region getRegion() = 0;			//����

	virtual void readPoints(std::list<PointF>& points) = 0;	//�㼯��
	virtual void writePoints(std::list<PointF>& points) = 0;	//�㼯��

	virtual void moveTo(PointF point) = 0;	//�ƶ���
	virtual void move(PointF offset) = 0;	//ƫ��

	virtual void OnPaint( Graphics &g ) = 0;	//��ͼ
};
#endif
/************************************************************************/
/*  ��ͼ���� DrawItemBase                                               */
/************************************************************************/
#if 1
class DrawItemBase : public IDrawItem
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ��������
	DrawItemBase();
	DrawItemBase(PointF topLeft,PointF bottomRight);
	DrawItemBase(RectF rect);
	virtual ~DrawItemBase(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// ʵ�ֽӿ�
	virtual void setState(int state) = 0;	//״̬
	virtual int getState() = 0;				//״̬

	virtual void setType(CString type) = 0;	//����
	virtual CString getType() = 0;			//����

	virtual void setID(CString id) = 0;		//ID
	virtual CString getID() = 0;			//ID

	virtual void setOrder(int order) = 0;	//���
	virtual int getOrder() = 0;				//���

	virtual void setRect(RectF rect) = 0;	//����
	virtual RectF getRect() = 0;			//����

	virtual Region getRegion() = 0;			//����

	virtual void readPoints(std::list<PointF>& points) = 0;	//�㼯��
	virtual void writePoints(std::list<PointF>& points) = 0;	//�㼯��

	virtual void moveTo(PointF point) = 0;	//�ƶ���
	virtual void move(PointF offset) = 0;	//ƫ��

	virtual void OnPaint( Graphics &g ) = 0;	//��ͼ

protected:
	//////////////////////////////////////////////////////////////////////////
	// ����
	CString m_type;							//����
	CString m_ID;							//ID
	int m_order;							//���
	int m_state;							//״̬
	RectF m_myRect;							//����

public:
	//////////////////////////////////////////////////////////////////////////
	// ��������
	const static int StateNormal;			//����״̬
	const static int StateHovered;			//����״̬
	const static int StateDisable;			//ʧЧ״̬
	const static int StateDown;				//�°�״̬
	const static int StateError;			//����״̬
};
#endif
/************************************************************************/
/*  ��ͼֱ�߶����                                                      */
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
	virtual void OnPaint( Graphics &g );			//����

	virtual void moveTo(PointF point);				//�ƶ���
	virtual void move(PointF offset);				//ƫ��

	void setOutline(std::vector<PointF> outlines);	//���ö���ε�
	std::vector<PointF> getOutline();				//���ö���ε�

	virtual void setRect(RectF rect);				//����
	virtual RectF getRect();						//����

	virtual Gdiplus::Region* getCloneRigon();		//����

	void buildPath( GraphicsPath &path );			//����

	virtual bool IsVisible(PointF point);			//�����ж�

private:
	PointF* getOutlineArrClone();					//��õ�����Ҫ�ⲿ�ͷţ�

protected:
	std::vector<PointF> m_outlines;
};
#endif
/************************************************************************/
/*  ��ͼֱ�߼����߶����                                                */
/************************************************************************/
#if 1
class IDrawLine
{
public:
	virtual void loadPoints(std::vector<PointF>& points) = 0;	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::vector<PointF>& points) = 0;	//���ⲿȡ�õ���µ�������
	virtual void getLineToPath(GraphicsPath& path) = 0;			//���ڲ��㼯�Ϲ�����ͼ����
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
	virtual void OnPaint( Graphics &g );			//����

	virtual void moveTo(PointF point);				//�ƶ���
	virtual void move(PointF offset);				//ƫ��

	virtual void setAllPoints(std::vector<PointF>& outlines);	//���ö���ε�
	virtual std::vector<PointF> getAllPoints();					//���ö���ε�

	virtual void setRect(RectF rect);				//����
	virtual RectF getRect();						//����

	virtual Gdiplus::Region* getCloneRigon();		//����

	void buildPath( GraphicsPath &path );

	virtual bool IsVisible(PointF point);			//�����ж�

protected:
	std::vector<IDrawLine*> m_lines;
};
#endif