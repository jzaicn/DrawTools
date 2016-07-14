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

	virtual Gdiplus::Region* getCloneRigon() = 0;	//区域（需要外部释放）
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

	virtual void setState(int state);		//状态
	virtual int getState();					//状态

	virtual void setType(CString type);		//类型
	virtual CString getType();				//类型

	virtual void setID(CString id);			//ID
	virtual CString getID();				//ID

	virtual void setOrder(int order);		//序号
	virtual int getOrder();					//序号

	virtual void OnPaint( Graphics &g );	//画图
	
	virtual void moveTo(CPoint point);		//移动到
	virtual void move(CPoint offset);		//偏移

	virtual void setRect( CRect rect );		//区域
	void setRect(CPoint topLeft,CPoint bottomRight);	//区域
	void setRect(int x1,int y1,int x2,int y2);			//区域
	virtual CRect getRect();				//区域

	std::vector<CPoint> getPoints();		//区域顶点
	virtual Gdiplus::Region* getCloneRigon();			//区域
	virtual bool IsVisible(CPoint point);	//区域判断

	
public:
	static Color ColorNormal;				//正常颜色
	static Color ColorHovered;				//覆盖颜色
	static Color ColorDisable;				//失效颜色
	static Color ColorDown;					//下按颜色
	static Color ColorError;				//错误颜色
	
	const static int StateNormal;			//正常状态
	const static int StateHovered;			//覆盖状态
	const static int StateDisable;			//失效状态
	const static int StateDown;				//下按状态
	const static int StateError;			//错误状态

protected:
	CString m_type;							//类型
	CString m_ID;							//ID
	int m_order;							//序号
	int m_state;							//状态
	CRect m_myRect;							//区域
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
	void setOutline(std::vector<CPoint> outlines);	//设置多边形点
	std::vector<CPoint> getOutline();				//设置多边形点

	virtual void OnPaint( Graphics &g );			//绘制

	virtual void moveTo(CPoint point);				//移动到
	virtual void move(CPoint offset);				//偏移

	virtual void setRect(CRect rect);				//区域
	virtual CRect getRect();						//区域

	virtual Gdiplus::Region* getCloneRigon();		//区域
	virtual bool IsVisible(CPoint point);			//区域判断

private:
	Point* getOutlineArrClone();					//获得点阵（需要外部释放）

protected:
	std::vector<CPoint> m_outlines;
};
#endif