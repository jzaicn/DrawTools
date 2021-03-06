#pragma once
#include "DrawItem.h"
#include "DrawItemStrategy.h"
#include <map>
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
	SmallPanel( RectF rect );
	SmallPanel(const SmallPanel &smallpanel);
	SmallPanel& operator=(const SmallPanel &smallpanel);
	~SmallPanel(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// 接口实现
	virtual void setState( int state );
	virtual const std::shared_ptr<Region>& getRegion();
	virtual void readPoints( std::list<PointF>& points )const;
	virtual void writePoints( std::list<PointF>& points );
	virtual void OnPaint( Graphics &g );

public:
	//////////////////////////////////////////////////////////////////////////
	// 设置数据
	void OutterFrame(DrawItemBasePtrList val) { m_outterFrame = val; }
	void InnerFrame(DrawItemBasePtrList val) { m_innerFrame = val; }
	void InnerShape(DrawItemBasePtrList val) { m_innerShape = val; }
	void OutterShape(DrawItemBasePtrList val) { m_outterShape = val; }
	void InfoSide(DrawItemBasePtrList val) { m_infoSide = val; }
	void InfoVertical(DrawItemBasePtrList val) { m_infoVertical = val; }
	void InfoSaw(DrawItemBasePtrList val) { m_infoSaw = val; }
	
	void setInnerShape(DrawItemBase* val) { m_innerShape.push_back(val); }

	virtual void foreachPoint(void (*func) (PointF&));

	virtual void foreachPoint(void (*func) (const PointF&))const;

	virtual void move(PointF offset);
	std::vector<DrawItemBasePtrList*> getAllDrawItem();
	std::vector<const DrawItemBasePtrList*> getAllDrawItem()const;

	virtual bool isChangeRegion() const;

	virtual void ResetRegion();



private:
	DrawItemBasePtrList m_outterFrame;	//外边框
	DrawItemBasePtrList m_innerFrame;	//内边框
	DrawItemBasePtrList m_innerShape;	//内异形
	DrawItemBasePtrList m_outterShape;	//外异形（刀路）
	DrawItemBasePtrList m_infoSide;		//侧面孔
	DrawItemBasePtrList m_infoVertical;	//垂直孔
	DrawItemBasePtrList m_infoSaw;		//锯缝
};
/************************************************************************/
/* 编辑板件策略 PanelEditionStrategy                                    */
/************************************************************************/
#if 1
class SmallPanelStrategy : public DrawItemStrategyBase
{
public:
	SmallPanelStrategy(){};
	~SmallPanelStrategy(){};

public:
	//////////////////////////////////////////////////////////////////////////
	// 接口
	virtual void OnInitial( std::list<IDrawItem*> all );
	virtual void OnPaint( Graphics& g, std::list<IDrawItem*> all );
	virtual bool PreTranslateMessage( MSG* pMsg, std::list<IDrawItem*> all );
	virtual bool OnEraseBkgnd( CDC* pDC, std::list<IDrawItem*> all );
	virtual void OnMouseMove( UINT nFlags, PointF point, std::list<IDrawItem*> all );



	virtual void OnLButtonDown( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnLButtonUp( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnRButtonDown( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnRButtonUp( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnClear(std::list<IDrawItem*> all);
public:
	//////////////////////////////////////////////////////////////////////////
	// 操作
	void addNewActiveItem(IDrawItem* item);

	//bool IsActiveCraseWithStatic(Graphics &g1);
	bool IsActiveCraseWithStatic();
	void SetStaticHoveredByPoint( PointF point );
	void SetActiveState(int state);
	void MoveAllActive( PointF diff );

	static void RotateItem(IDrawItem* item);

private:
	std::list<IDrawItem*> m_active;
	std::list<IDrawItem*> m_static;

};
#endif
