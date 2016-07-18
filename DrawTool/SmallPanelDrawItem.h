#pragma once
#include "DrawItem.h"

class SmallPanelDrawItem : public DrawItemShape
{
private:
	SmallPanelDrawItem(void);
	~SmallPanelDrawItem(void);

public:
	static SmallPanelDrawItem* SmallPanelFactory(RectF rect);

public:
	virtual void OnPaint( Graphics &g );		//»­Í¼
	void OnPaintBorder( Graphics &g );			//»­±ß¿ò
	void OnPaintOtherShape( Graphics &g );		//»­ÒìÐÎ
	void OnPaintVertical( Graphics &g );		//»­¿×
	void OnPaintSaw( Graphics &g );				//»­²Û

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
	std::vector<std::vector<IDrawLine*>> getInnerLine();

	virtual void setAllPoints( std::vector<PointF> outlines );
	virtual std::vector<PointF> getAllPoints();

private:
	std::vector<std::vector<IDrawLine*>> m_innerlines;
	float m_scale;

private:
	static Color ColorBorder;
	static Color ColorShapeBorder;
	static Color ColorVertical;
	static Color ColorSaw;
};

