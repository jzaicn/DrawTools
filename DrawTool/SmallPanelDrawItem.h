#pragma once
#include "DrawItem.h"

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
	SmallPanel(void);
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

	virtual void move( PointF offset );

	virtual void OnPaint( Graphics &g );

private:
	std::list<IDrawItem*> m_outterFrame;	//��߿�
	std::list<IDrawItem*> m_innerFrame;		//�ڱ߿�
	std::list<IDrawItem*> m_innerShape;		//������
	std::list<IDrawItem*> m_outterShape;	//�����Σ���·��
private:
	std::list<IDrawItem*> m_info_Side;		//�����
	std::list<IDrawItem*> m_info_Vertical;	//��ֱ��
	std::list<IDrawItem*> m_info_Saw;		//���
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
