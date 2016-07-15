#pragma once
#include "stdafx.h"
#include <vector>

/************************************************************************/
/*  ��ͼ�ӿ�                                                            */
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

	virtual void OnPaint( Graphics &g ) = 0;	//��ͼ

	virtual void moveTo(CPoint point) = 0;	//�ƶ���
	virtual void move(CPoint offset) = 0;	//ƫ��

	virtual void setRect(CRect rect) = 0;	//����
	virtual CRect getRect() = 0;			//����

	virtual Gdiplus::Region* getCloneRigon() = 0;	//������Ҫ�ⲿ�ͷţ�
	virtual bool IsVisible(CPoint point) = 0;		//�����ж�
};
#endif
/************************************************************************/
/*  ��ͼ����                                                            */
/************************************************************************/
#if 1
class DrawItemBase : public IDrawItem
{
public:
	DrawItemBase();
	DrawItemBase(CPoint topLeft,CPoint bottomRight);
	DrawItemBase(CRect rect);
	virtual ~DrawItemBase(void);

	virtual void setState(int state);		//״̬
	virtual int getState();					//״̬

	virtual void setType(CString type);		//����
	virtual CString getType();				//����

	virtual void setID(CString id);			//ID
	virtual CString getID();				//ID

	virtual void setOrder(int order);		//���
	virtual int getOrder();					//���

	virtual void OnPaint( Graphics &g );	//��ͼ
	
	virtual void moveTo(CPoint point);		//�ƶ���
	virtual void move(CPoint offset);		//ƫ��

	virtual void setRect( CRect rect );		//����
	void setRect(CPoint topLeft,CPoint bottomRight);	//����
	void setRect(int x1,int y1,int x2,int y2);			//����
	virtual CRect getRect();				//����

	std::vector<CPoint> getPoints();		//���򶥵�
	virtual Gdiplus::Region* getCloneRigon();			//����
	virtual bool IsVisible(CPoint point);	//�����ж�

	
public:
	static Color ColorNormal;				//������ɫ
	static Color ColorHovered;				//������ɫ
	static Color ColorDisable;				//ʧЧ��ɫ
	static Color ColorDown;					//�°���ɫ
	static Color ColorError;				//������ɫ
	
	const static int StateNormal;			//����״̬
	const static int StateHovered;			//����״̬
	const static int StateDisable;			//ʧЧ״̬
	const static int StateDown;				//�°�״̬
	const static int StateError;			//����״̬

protected:
	CString m_type;							//����
	CString m_ID;							//ID
	int m_order;							//���
	int m_state;							//״̬
	CRect m_myRect;							//����
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
	DrawItemPolygon(CPoint topLeft,CPoint bottomRight);
	DrawItemPolygon(CRect rect);
	DrawItemPolygon(const std::vector<CPoint>& outlines);
	~DrawItemPolygon();

public:
	void setOutline(std::vector<CPoint> outlines);	//���ö���ε�
	std::vector<CPoint> getOutline();				//���ö���ε�

	virtual void OnPaint( Graphics &g );			//����

	virtual void moveTo(CPoint point);				//�ƶ���
	virtual void move(CPoint offset);				//ƫ��

	virtual void setRect(CRect rect);				//����
	virtual CRect getRect();						//����

	virtual Gdiplus::Region* getCloneRigon();		//����
	virtual bool IsVisible(CPoint point);			//�����ж�

private:
	Point* getOutlineArrClone();					//��õ�����Ҫ�ⲿ�ͷţ�

protected:
	std::vector<CPoint> m_outlines;
};
#endif
/************************************************************************/
/*  ��ͼֱ�߼����߶����                                                */
/************************************************************************/
#if 0
// class DrawItemShape : public DrawItemBase
// {
// public:
// 	DrawItemShape();	
// 	DrawItemShape(CRect outterRect,std::map<int,);
// 	DrawItemShape(CRect rect);
// 	DrawItemShape(const std::vector<CPoint>& outlines);
// 	~DrawItemShape();
// 
// public:
// 	void setOutline(std::vector<CPoint> outlines);	//���ö���ε�
// 	std::vector<CPoint> getOutline();				//���ö���ε�
// 
// 	virtual void OnPaint( Graphics &g );			//����
// 
// 	virtual void moveTo(CPoint point);				//�ƶ���
// 	virtual void move(CPoint offset);				//ƫ��
// 
// 	virtual void setRect(CRect rect);				//����
// 	virtual CRect getRect();						//����
// 
// 	virtual Gdiplus::Region* getCloneRigon();		//����
// 	virtual bool IsVisible(CPoint point);			//�����ж�
// 
// private:
// 	Point* getOutlineArrClone();					//��õ�����Ҫ�ⲿ�ͷţ�
// 
// protected:
// 	std::vector<CPoint> m_outlines;
// };
#endif