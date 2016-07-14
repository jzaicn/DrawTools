#pragma once
#include "stdafx.h"
#include <vector>

/************************************************************************/
/*  绘图接口                                                            */
/************************************************************************/
#if 1
class IDrawItem
{
public:
	virtual void setState(int state) = 0;	//状态
	virtual int getState() = 0;				//状态

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

	virtual Gdiplus::Region* getCloneRigon() = 0;			//区域
	virtual bool IsVisible(CPoint point) = 0;		//区域判断
};
#endif
/************************************************************************/
/*  绘图基类                                                            */
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
/*  绘图小板类                                                            */
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