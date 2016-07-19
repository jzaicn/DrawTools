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

	virtual void setAllPoints( std::vector<PointF> outlines );			//������
	virtual std::vector<PointF> getAllPoints();							//������


private:
	static Color ColorBorder;
	static Color ColorShapeBorder;
	static Color ColorVertical;
	static Color ColorSaw;
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
