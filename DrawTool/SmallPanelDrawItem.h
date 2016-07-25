#pragma once
#include "DrawItem.h"
#include "DrawItemStrategy.h"

/************************************************************************/
/* ��ֱ�� DrawVertical                                                  */
/************************************************************************/
#if 1
class DrawVertical : public DrawItemCircle
{
public:
	DrawVertical(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
};
#endif
/************************************************************************/
/* ����� DrawSideVertical                                              */
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
/* ����� DrawSaw                                                       */
/************************************************************************/
#if 1
class DrawSaw : public DrawItemRectangle
{
public:
	DrawSaw(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
};
#endif
/************************************************************************/
/* С����Ϣ SmallPanel                                                  */
/************************************************************************/
class SmallPanel : public DrawItemBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	SmallPanel( RectF rect );
	SmallPanel(const SmallPanel &smallpanel);
	SmallPanel& operator=(const SmallPanel &smallpanel);
	~SmallPanel(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// �ӿ�ʵ��
	virtual void setState( int state );
	virtual std::shared_ptr<Region> getRegion();
	virtual void readPoints( std::list<PointF>& points );
	virtual void writePoints( std::list<PointF>& points );
	virtual void OnPaint( Graphics &g );

public:
	//////////////////////////////////////////////////////////////////////////
	// ��������
	void OutterFrame(std::list<IDrawItem*> val) { m_outterFrame = val; }
	void InnerFrame(std::list<IDrawItem*> val) { m_innerFrame = val; }
	void InnerShape(std::list<IDrawItem*> val) { m_innerShape = val; }
	void OutterShape(std::list<IDrawItem*> val) { m_outterShape = val; }
	void InfoSide(std::list<IDrawItem*> val) { m_infoSide = val; }
	void InfoVertical(std::list<IDrawItem*> val) { m_infoVertical = val; }
	void InfoSaw(std::list<IDrawItem*> val) { m_infoSaw = val; }
	
	void setInnerShape(IDrawItem* val) { m_innerShape.push_back(val); }

private:
	std::list<IDrawItem*> m_outterFrame;	//��߿�
	std::list<IDrawItem*> m_innerFrame;		//�ڱ߿�
	std::list<IDrawItem*> m_innerShape;		//������
	std::list<IDrawItem*> m_outterShape;	//�����Σ���·��
	std::list<IDrawItem*> m_infoSide;		//�����
	std::list<IDrawItem*> m_infoVertical;	//��ֱ��
	std::list<IDrawItem*> m_infoSaw;		//���
};
/************************************************************************/
/* �༭������� PanelEditionStrategy                                    */
/************************************************************************/
#if 1
class SmallPanelStrategy : public DrawItemStrategyBase
{
public:
	SmallPanelStrategy(){};
	~SmallPanelStrategy(){};

public:
	//////////////////////////////////////////////////////////////////////////
	// �ӿ�
	virtual void OnInitial( std::list<IDrawItem*> all );
	virtual void OnPaint( Graphics& g, std::list<IDrawItem*> all );
	virtual bool PreTranslateMessage( MSG* pMsg, std::list<IDrawItem*> all );
	virtual bool OnEraseBkgnd( CDC* pDC, std::list<IDrawItem*> all );
	virtual void OnMouseMove( UINT nFlags, PointF point, std::list<IDrawItem*> all );



	virtual void OnLButtonDown( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnLButtonUp( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnRButtonDown( UINT nFlags, PointF point, std::list<IDrawItem*> all );
	virtual void OnRButtonUp( UINT nFlags, PointF point, std::list<IDrawItem*> all );

public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	void setNewActiveItem(IDrawItem* item);

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
