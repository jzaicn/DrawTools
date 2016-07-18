#pragma once
#include "DrawItem.h"

class SmallPanelDrawItem : public DrawItemShape
{
private:
	SmallPanelDrawItem(void);
	~SmallPanelDrawItem(void);

public:
	static SmallPanelDrawItem* SmallPanelFactory(
		RectF rect)
	{
		SmallPanelDrawItem* smallPanel = new SmallPanelDrawItem();
		smallPanel->setType(L"SmallPanel");
		return smallPanel;
	}

public:
	virtual void OnPaint( Graphics &g );

	virtual void moveTo( PointF point );

	virtual void move( PointF offset );

	virtual void setRect( RectF rect );

	virtual RectF getRect();

	virtual Gdiplus::Region* getCloneRigon();

	virtual bool IsVisible( PointF point );

public:
	void setOutterLine(std::vector<IDrawLine*> outterline);

	void addInnerLine(std::vector<IDrawLine*> outterline);

	void setInnerLine(std::vector<std::vector<IDrawLine*>> outterline);

	std::vector<std::vector<IDrawLine>> getInnerLine();

	void OnPaintBorder( Graphics &g );

private:
	std::vector<std::vector<IDrawLine*>> m_innerlines;
	float m_scale;

private:
	static Color ColorBorder;
};

