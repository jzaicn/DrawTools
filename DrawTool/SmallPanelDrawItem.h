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

protected:
	float m_pos_x;
	float m_pos_y;
	float m_angle;
	float m_size_x;
	float m_size_y;
	float m_depth;
	RectF m_rect;
};
//////////////////////////////////////////////////////////////////////////
//
class DrawVertical : public DrawInfoBase
{
public:
	DrawVertical(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
		
	virtual void drawLineToGraphic( Graphics &g );

};
//////////////////////////////////////////////////////////////////////////
//
class DrawSideVertical : public DrawInfoBase
{
public:
	DrawSideVertical(int side,float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
public:
	virtual void drawLineToGraphic( Graphics &g );				//画图
	virtual void loadPoints( std::vector<PointF>& points );		//获得坐标信息
	virtual void updatePoints( std::vector<PointF>& points );	//更新坐标信息
protected:
	std::vector<IDrawLine*> InfosByRect(RectF rect);			//通过构造矩形创建孔的画图信息
private:
	std::vector<IDrawLine*> m_infos;							//通过IDrawLine成员来管理旋转等问题
};

//////////////////////////////////////////////////////////////////////////
//
class DrawSaw : public DrawInfoBase
{
public:
	DrawSaw(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );
};

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
	void OnPaintInfo( Graphics &g );			//画孔槽

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

	void setVertical(std::vector<IDrawInfo*> infos);					//

	virtual void setAllPoints( std::vector<PointF>& points );			//点坐标
	virtual std::vector<PointF> getAllPoints();							//点坐标

private:
	std::vector<IDrawInfo*> m_infos;
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
