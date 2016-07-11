#pragma once
#include "stdafx.h"
#include <vector>

class IDrawItem
{
public:
	virtual CRect getRect() = 0;
	virtual CString getType() = 0;
	virtual CString getID() = 0;
	virtual int getZIndex() = 0;

	virtual void OnPaint(Graphics &g) = 0;
	virtual bool isActive() = 0;
	virtual bool checkSelected(CPoint point) = 0;
	virtual bool checkMovable(const std::vector<IDrawItem>& allItem,CPoint dstPoint) = 0;

	virtual void OnCommand(CString command,CString param) = 0;
	virtual void OnMouseMove( CPoint point ) = 0;
	virtual void OnLButtonDown(CPoint point) = 0;
	virtual void OnLButtonUp(CPoint point) = 0;
	virtual void OnRButtonDown(CPoint point) = 0;
	virtual void OnRButtonUp(CPoint point) = 0;
};

class DrawItemBase : public IDrawItem
{
public:
	DrawItemBase();
	~DrawItemBase(void);

	virtual CRect getRect();
	virtual CString getType();
	virtual CString getID();
	virtual int getZIndex();

	virtual void OnPaint( Graphics &g );

	virtual bool isActive();
	virtual bool checkSelected( CPoint point );
	virtual bool checkMovable( const std::vector<IDrawItem>& allItem,CPoint dstPoint );

	virtual void OnCommand( CString command,CString param );
	virtual void OnMouseMove( CPoint point );
	virtual void OnLButtonDown(CPoint point);
	virtual void OnLButtonUp(CPoint point);
	virtual void OnRButtonDown(CPoint point);
	virtual void OnRButtonUp(CPoint point);

	void setRect(int x1,int y1,int x2,int y2);
	void setRect(CPoint topLeft,CPoint bottomRight);
	void beginActive();
	void endActive();
private:
	bool m_isActive;
	CRect m_myRect;
	CPoint m_posStart;
};

