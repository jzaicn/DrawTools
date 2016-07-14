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

	virtual Gdiplus::Region* getCloneRigon() = 0;			//����
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

	virtual void setState(int state);
	virtual int getState();

	virtual void setType(CString type);
	virtual CString getType();

	virtual void setID(CString id);
	virtual CString getID();

	virtual void setOrder(int order);
	virtual int getOrder();

	virtual void OnPaint( Graphics &g );
	
	virtual void moveTo(CPoint point);
	virtual void move(CPoint offset);

	virtual void setRect( CRect rect );
	void setRect(CPoint topLeft,CPoint bottomRight);
	void setRect(int x1,int y1,int x2,int y2);
	virtual CRect getRect();

	std::vector<CPoint> getPoints();
	virtual Gdiplus::Region* getCloneRigon();
	virtual bool IsVisible(CPoint point);

	
public:
	static Color ColorNormal;
	static Color ColorHovered;
	static Color ColorDisable;
	static Color ColorDown;
	static Color ColorError;
	
	const static int StateNormal;
	const static int StateHovered;
	const static int StateDisable;
	const static int StateDown;
	const static int StateError;

protected:
	CString m_type;
	CString m_ID;
	int m_order;
	int m_state;
	CRect m_myRect;
};
#endif
/************************************************************************/
/*  ��ͼС����                                                            */
/************************************************************************/
#if 1
class DrawItemSmallPanel : public DrawItemBase
{
public:
	DrawItemSmallPanel();	
	DrawItemSmallPanel(CPoint topLeft,CPoint bottomRight);
	DrawItemSmallPanel(CRect rect);
	DrawItemSmallPanel(const std::vector<CPoint>& outlines);
	~DrawItemSmallPanel();

public:
	void setOutline(std::vector<CPoint> outlines);
	std::vector<CPoint> getOutline();

	virtual void OnPaint( Graphics &g );

	virtual void moveTo(CPoint point);
	virtual void move(CPoint offset);

	virtual void setRect(CRect rect);
	virtual CRect getRect();

	virtual Gdiplus::Region* getCloneRigon();
	virtual bool IsVisible(CPoint point);

private:
	Point* getOutlineArr();

protected:
	std::vector<CPoint> m_outlines;
};
#endif