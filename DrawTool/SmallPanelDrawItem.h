// #pragma once
// #include "DrawItem.h"
// 
// /************************************************************************/
// /*                                                                      */
// /************************************************************************/
// //////////////////////////////////////////////////////////////////////////
// class IDrawInfo
// {
// public:
// 	virtual void loadPoints(std::list<PointF>& points) = 0;	//������������ȡ�ü��ϵ�
// 	virtual void updatePoints(std::list<PointF>& points) = 0;	//���ⲿȡ�õ���µ�������
// 	virtual void drawLineToGraphic(Graphics &g) = 0;			//���ڲ��㼯�ϻ���ͼ����
// };
// //////////////////////////////////////////////////////////////////////////
// class DrawInfoBase : public IDrawInfo
// {
// public:
// 	DrawInfoBase(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
// 	virtual ~DrawInfoBase();
// 
// 	virtual void loadPoints( std::list<PointF>& points );
// 	virtual void updatePoints( std::list<PointF>& points );
// 	virtual void drawLineToGraphic( Graphics &g );
// 
// protected:
// 	static std::list<IDrawLine*> InfosByRect( RectF rect );
// 
// protected:
// 	float m_pos_x;
// 	float m_pos_y;
// 	float m_angle;
// 	float m_size_x;
// 	float m_size_y;
// 	float m_depth;
// 	RectF m_rect;
// 	
// 	std::list<IDrawLine*> m_infos;							//ͨ��IDrawLine��Ա��������ת������
// };
// //////////////////////////////////////////////////////////////////////////
// //
// class DrawVertical : public DrawInfoBase
// {
// public:
// 	DrawVertical(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
// 		
// 	virtual void drawLineToGraphic( Graphics &g );
// 
// };
// //////////////////////////////////////////////////////////////////////////
// //
// class DrawSideVertical : public DrawInfoBase
// {
// public:
// 	DrawSideVertical(int side,float pos_x,float pos_y,float angle,float size_x,float size_y,float depth);
// public:
// 	virtual void drawLineToGraphic( Graphics &g );				//��ͼ
// protected:
// 	std::list<IDrawLine*> InfosByRect(RectF rect);			//ͨ��������δ����׵Ļ�ͼ��Ϣ
// };
// 
// //////////////////////////////////////////////////////////////////////////
// //
// class DrawSaw : public DrawInfoBase
// {
// public:
// 	DrawSaw(float pos_x,float pos_y,float angle,float size_x,float size_y,float depth)
// 		:DrawInfoBase(pos_x,pos_y,angle,size_x,size_y,depth){}
// 	virtual void drawLineToGraphic( Graphics &g );
// };
// 
// /************************************************************************/
// /*                                                                      */
// /************************************************************************/
// class SmallPanelDrawItem : public DrawItemShape
// {
// private:
// 	SmallPanelDrawItem(void);
// 	~SmallPanelDrawItem(void);
// 
// public:
// 	static SmallPanelDrawItem* SmallPanelFactory(RectF rect);
// 
// public:
// 	virtual void OnPaint( Graphics &g );		//��ͼ
// 	void OnPaintBorder( Graphics &g );			//���߿�
// 	void OnPaintOtherShape( Graphics &g );		//������
// 	void OnPaintInfo( Graphics &g );			//���ײ�
// 
// 	virtual void moveTo( PointF point );		//�ƶ���
// 	virtual void move( PointF offset );			//�ƶ�
// 
// 	virtual void setRect( RectF rect );			//����
// 	virtual RectF getRect();					//����
// 
// 	virtual Gdiplus::Region* getCloneRigon();	//����
// 	virtual bool IsVisible( PointF point );		//����
// 
// public:
// 	void setOutterLine(std::list<IDrawLine*> outterline);		//����
// 
// 	void addInnerLine(std::list<IDrawLine*> outterline);				//�ڱ���
// 	void setInnerLine(std::list<std::list<IDrawLine*>> outterline);	//�ڱ���
// 	std::list<std::list<IDrawLine*>> getInnerLine();				//�ڱ���
// 
// 	void setVertical(std::list<IDrawInfo*> infos);					//
// 
// 	virtual void setAllPoints( std::list<PointF>& points );			//������
// 	virtual std::list<PointF> getAllPoints();							//������
// 
// private:
// 	std::list<IDrawInfo*> m_infos;
// };
// /************************************************************************/
// /*                                                                      */
// /************************************************************************/
