#pragma once
#include "stdafx.h"
#include <vector>
#include <list>
#include "DrawLine.h"
#include "DrawTools.h"

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
	virtual void setState(int state);	//״̬
	virtual int getState();				//״̬

	virtual void setType(CString type);	//����
	virtual CString getType();			//����

	virtual void setID(CString id);		//ID
	virtual CString getID();			//ID

	virtual void setOrder(int order);	//���
	virtual int getOrder();				//���

	virtual void setRect(RectF rect);	//����
	virtual RectF getRect();			//����

	virtual Region getRegion();			//����

	virtual void readPoints(std::list<PointF>& points);	//�㼯��
	virtual void writePoints(std::list<PointF>& points;	//�㼯��

	virtual void moveTo(PointF point);	//�ƶ���
	virtual void move(PointF offset);	//ƫ��

	virtual void OnPaint( Graphics &g );	//��ͼ

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
/*  ��ͼ��״ DrawItemShape                                               */
/************************************************************************/
#if 1
class DrawItemShape : public DrawItemBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemShape(RectF rect,std::vector<IDrawLine*> lines);
	virtual ~DrawItemShape();

public:
	//////////////////////////////////////////////////////////////////////////
	// �ӿ�ʵ��
	virtual Region getRegion();				//����

	virtual void readPoints(std::list<PointF>& points);	//�㼯��
	virtual void writePoints(std::list<PointF>& points;	//�㼯��

	virtual void moveTo(PointF point);		//�ƶ���
	virtual void move(PointF offset);		//ƫ��

	virtual void OnPaint( Graphics &g );	//��ͼ

protected:
	//////////////////////////////////////////////////////////////////////////
	// ����
	std::vector<IDrawLine*> m_lines;
};
#endif
/************************************************************************/
/*  ��ͼ��״ DrawItemCircle                                             */
/************************************************************************/
#if 1
// DrawItemCircle* CreateVirtical(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
// {
// 	DrawItemCircle* virtical = new DrawItemCircle(pos_x,pos_y,size_x/2.0);
// }
// DrawItemRectangle* CreateSide(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
// {
// 	RectF rect;
// 	DrawItemRectangle* side = new DrawItemRectangle(rect,DrawTools::buildDrawStraightLine(rect));
// }

class DrawItemCircle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemCircle(RectF rect,float pos_x,float pos_y,float radius);
	virtual ~DrawItemShape();
};
#endif
/************************************************************************/
/*  ��ͼ��״ DrawItemRectangle                                          */
/************************************************************************/
#if 1
class DrawItemRectangle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemRectangle(RectF rect,std::vector<IDrawLine*> lines);
	virtual ~DrawItemShape();
};
#endif