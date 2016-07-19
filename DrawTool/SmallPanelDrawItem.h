#pragma once
#include "DrawItem.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
class IDrawInfo
{
public:
	virtual void loadPoints(std::vector<PointF>& points) = 0;	//从线型数据中取得集合点
	virtual void updatePoints(std::vector<PointF>& points) = 0;	//从外部取得点更新到集合中
	virtual void drawLineToGraphic(Graphics &g) = 0;			//用内部点集合画到图形中
};
//////////////////////////////////////////////////////////////////////////
class DrawInfoBase : public IDrawInfo
{
public:
	DrawInfoBase(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);

	virtual void loadPoints( std::vector<PointF>& points );
	virtual void updatePoints( std::vector<PointF>& points );
	virtual void drawLineToGraphic( Graphics &g );

private:
	float m_pos_x;
	float m_pos_y;
	float m_angle;
	float m_size_x;
	float m_size_y;
	float m_depth;
};
// class DrawVertical : public IDrawInfo
// {
// public:
// 	DrawVertical(PointF pos,)
// 
// 		virtual void loadPoints( std::vector<PointF>& points );
// 	virtual void updatePoints( std::vector<PointF>& points );
// 	virtual void drawLineToGraphic( Graphics &g );
// 
// };
// //////////////////////////////////////////////////////////////////////////
// class DrawSaw : public IDrawInfo
// {
// 
// 
// 	virtual void loadPoints( std::vector<PointF>& points );
// 
// 	virtual void updatePoints( std::vector<PointF>& points );
// 
// 	virtual void drawLineToGraphic( Graphics &g );
// 
// };

/************************************************************************/
/*                                                                      */
/************************************************************************/
class SmallPanelDrawItem : public DrawItemShape
{
private:
	SmallPanelDrawItem(void);
	~SmallPanelDrawItem(void);

public:
	static SmallPanelDrawItem* SmallPanelFactory(RectF rect);

public:
	virtual void OnPaint( Graphics &g );		//画图
	void OnPaintBorder( Graphics &g );			//画边框
	void OnPaintOtherShape( Graphics &g );		//画异形
	void OnPaintVertical( Graphics &g );		//画孔
	void OnPaintSaw( Graphics &g );				//画槽

	virtual void moveTo( PointF point );		//移动到
	virtual void move( PointF offset );			//移动

	virtual void setRect( RectF rect );			//区域
	virtual RectF getRect();					//区域

	virtual Gdiplus::Region* getCloneRigon();	//区域
	virtual bool IsVisible( PointF point );		//区域

public:
	void setOutterLine(std::vector<IDrawLine*> outterline);		//异形

	void addInnerLine(std::vector<IDrawLine*> outterline);				//内边线
	void setInnerLine(std::vector<std::vector<IDrawLine*>> outterline);	//内边线
	std::vector<std::vector<IDrawLine*>> getInnerLine();				//内边线

	virtual void setAllPoints( std::vector<PointF> outlines );			//点坐标
	virtual std::vector<PointF> getAllPoints();							//点坐标


private:
	static Color ColorBorder;
	static Color ColorShapeBorder;
	static Color ColorVertical;
	static Color ColorSaw;
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
