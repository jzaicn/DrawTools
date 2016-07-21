#pragma once
#include "DrawItem.h"

/************************************************************************/
/* 垂直孔 DrawVertical                                                  */
/************************************************************************/
#if 1
class DrawVertical : public DrawItemCircle
{
public:
	DrawVertical(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
};
#endif
/************************************************************************/
/* 侧面孔 DrawSideVertical                                              */
/************************************************************************/
#if 1
class DrawSideVertical : public DrawItemRectangle
{
public:
	DrawSideVertical(int side,float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
public:
	static RectF DrawSideVertical::buildRect_1_Left( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth );
	static RectF DrawSideVertical::buildRect_2_Right( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth );
	static RectF DrawSideVertical::buildRect_3_Bottom( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth );
	static RectF DrawSideVertical::buildRect_4_Top( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth );
	static RectF DrawSideVertical::buildRect_0_Face( float pos_x,float pos_y,float angle,float size_x,float size_y,float depth );
};
#endif
/************************************************************************/
/* 侧面孔 DrawSaw                                                       */
/************************************************************************/
#if 1
class DrawSaw : public DrawItemRectangle
{
public:
	DrawSaw(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
};
#endif
/************************************************************************/
/* 小板信息 SmallPanel                                                  */
/************************************************************************/
class SmallPanel : public DrawItemBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	SmallPanel(void);
	SmallPanel(const SmallPanel &smallpanel);
	SmallPanel& operator=(const SmallPanel &smallpanel);
	~SmallPanel(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// 接口实现
	virtual void setState( int state );

	virtual std::shared_ptr<Region> getRegion();

	virtual void readPoints( std::list<PointF>& points );
	virtual void writePoints( std::list<PointF>& points );

	virtual void move( PointF offset );

	virtual void OnPaint( Graphics &g );

private:
	std::list<IDrawItem*> m_outterFrame;	//外边框
	std::list<IDrawItem*> m_innerFrame;		//内边框
	std::list<IDrawItem*> m_innerShape;		//内异形
	std::list<IDrawItem*> m_outterShape;	//外异形（刀路）
private:
	std::list<IDrawItem*> m_info_Side;		//侧面孔
	std::list<IDrawItem*> m_info_Vertical;	//垂直孔
	std::list<IDrawItem*> m_info_Saw;		//锯缝
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
// DrawItemCircle* CreateVirtical(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
// {
// 	DrawItemCircle* virtical = new DrawItemCircle(pos_x,pos_y,size_x/2.0);
// }
// DrawItemRectangle* CreateSide(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
// {
// 	RectF rect;
// 	DrawItemRectangle* side = new DrawItemRectangle(rect,DrawTools::buildDrawStraightLine(rect));
// }
