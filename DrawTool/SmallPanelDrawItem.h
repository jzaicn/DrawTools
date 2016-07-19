#pragma once
#include "DrawItem.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
class IDrawInfo
{
public:
	virtual void loadPoints(std::vector<PointF>& points) = 0;	//������������ȡ�ü��ϵ�
	virtual void updatePoints(std::vector<PointF>& points) = 0;	//���ⲿȡ�õ���µ�������
	virtual void drawLineToGraphic(Graphics &g) = 0;			//���ڲ��㼯�ϻ���ͼ����
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
};
//////////////////////////////////////////////////////////////////////////
//
class DrawVertical_0 : public DrawInfoBase
{
public:
	DrawVertical_0(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );

};
class DrawVertical_1 : public DrawInfoBase
{
public:
	DrawVertical_1(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );

};
class DrawVertical_2 : public DrawInfoBase
{
public:
	DrawVertical_2(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );

};
class DrawVertical_3 : public DrawInfoBase
{
public:
	DrawVertical_3(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );

};
class DrawVertical_4 : public DrawInfoBase
{
public:
	DrawVertical_4(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );

};
class DrawVertical_5 : public DrawInfoBase
{
public:
	DrawVertical_5(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
	virtual void drawLineToGraphic( Graphics &g );

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
	virtual void OnPaint( Graphics &g );		//��ͼ
	void OnPaintBorder( Graphics &g );			//���߿�
	void OnPaintOtherShape( Graphics &g );		//������
	void OnPaintVertical( Graphics &g );		//����
	void OnPaintSaw( Graphics &g );				//����

	virtual void moveTo( PointF point );		//�ƶ���
	virtual void move( PointF offset );			//�ƶ�

	virtual void setRect( RectF rect );			//����
	virtual RectF getRect();					//����

	virtual Gdiplus::Region* getCloneRigon();	//����
	virtual bool IsVisible( PointF point );		//����

public:
	void setOutterLine(std::vector<IDrawLine*> outterline);		//����

	void addInnerLine(std::vector<IDrawLine*> outterline);				//�ڱ���
	void setInnerLine(std::vector<std::vector<IDrawLine*>> outterline);	//�ڱ���
	std::vector<std::vector<IDrawLine*>> getInnerLine();				//�ڱ���

	void setVertical(std::vector<IDrawInfo*> infos);					//

	virtual void setAllPoints( std::vector<PointF>& points );			//������
	virtual std::vector<PointF> getAllPoints();							//������

private:
	std::vector<IDrawInfo*> m_infos;
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
