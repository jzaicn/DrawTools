#pragma once
#include "stdafx.h"
#include <vector>

class IDrawItem
{
public:
	virtual void setType(CString type) = 0;	//类型
	virtual CString getType() = 0;			//类型

	virtual void setID(CString id) = 0;		//ID
	virtual CString getID() = 0;			//ID

	virtual void setOrder(int order) = 0;	//序号
	virtual int getOrder() = 0;				//序号

	virtual void OnPaint( Graphics &g ) = 0;	//画图

	virtual void moveTo(CPoint point) = 0;	//移动到
	virtual void move(CPoint offset) = 0;	//偏移

	virtual void setRect(CRect rect) = 0;	//区域
	virtual CRect getRect() = 0;			//区域

	virtual Region getRigon() = 0;			//区域
};

class DrawItemBase : public IDrawItem
{
public:
	DrawItemBase();
	DrawItemBase(CPoint topLeft,CPoint bottomRight);
	DrawItemBase(CRect rect);
	virtual ~DrawItemBase(void);

	virtual void setType(CString type);
	virtual CString getType();

	virtual void setID(CString id);
	virtual CString getID();

	virtual void setOrder(int order);
	virtual int getOrder();

	virtual void OnPaint( Graphics &g );
	
	virtual void moveTo(CPoint point);
	void moveTo(LONG x,LONG y);

	virtual void move(CPoint offset);
	void move(LONG x,LONG y);

	virtual void setRect(CRect rect);
	void setRect(CPoint topLeft,CPoint bottomRight);
	void setRect(int x1,int y1,int x2,int y2);
	virtual CRect getRect();

	std::vector<CPoint> getPoints();
	virtual Region getRigon();

	void setState(int state);
	int getState();
	
public:
	static Color ColorNormal;
	static Color ColorHovered;
	static Color ColorDisable;
	static Color ColorDown;
	static Color ColorError;

	static int StateNormal;
	static int StateHovered;
	static int StateDisable;
	static int StateDown;
	static int StateError;

protected:
	CString m_type;
	CString m_ID;
	int m_order;
	int m_state;
	CRect m_myRect;
};
/*
class DrawItemSmallPanel : public DrawItemBase
{
public:
	DrawItemSmallPanel();
	~DrawItemSmallPanel();

public:
	void setOutline(const std::vector<CPoint>& outlines);

protected:
	std::vector<CPoint> outlines;
};*/