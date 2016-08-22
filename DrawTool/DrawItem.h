#pragma once
#include <vector>
#include <list>
#include "DrawCommon.h"

#include "DataLine.h"

/************************************************************************/
/*  ��ͼ�ӿ� IDrawItem                                                  */
/************************************************************************/
#if 1
class IDrawItem
{
public:
	virtual void setState(const int& state) = 0;	//״̬
	virtual const int& getState()const = 0;				//״̬

	virtual void setType(const CString& type) = 0;	//����
	virtual const CString& getType()const = 0;			//����

	virtual void setID(const CString& id) = 0;		//ID
	virtual const CString& getID()const = 0;			//ID

	virtual void setOrder(const int& order) = 0;	//���
	virtual const int& getOrder()const = 0;				//���

	virtual void setRect(RectF rect) = 0;	//����
	virtual RectF getRect()const = 0;		//����

	virtual const std::shared_ptr<Region>& getRegion() = 0;			//����

	virtual void readPoints(std::list<PointF>& points)const = 0;	//�㼯��
	virtual void writePoints(std::list<PointF>& points) = 0;	//�㼯��

	virtual void foreachPoint(void (*func)(PointF&)) = 0;
	virtual void foreachPoint(void (*func)(const PointF&))const = 0;

	//virtual void moveTo(PointF point) = 0;	//�ƶ���
	virtual void move(PointF offset) = 0;	//ƫ��

	virtual void OnPaint( Graphics &g ) = 0;	//��ͼ
	virtual ~IDrawItem(){};
};
#endif
/************************************************************************/
/*  ��ͼ���� DrawItemBase                                               */
/************************************************************************/
#if 1
class DrawItemBase : public IDrawItem
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ��������
	DrawItemBase();
	DrawItemBase(PointF topLeft,PointF bottomRight);
	DrawItemBase(RectF rect);
	virtual ~DrawItemBase(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// ʵ�ֽӿ�
	virtual void setState(const int& state);	//״̬
	virtual const int& getState()const;				//״̬

	virtual void setType(const CString& type);	//����
	virtual const CString& getType()const;			//����

	virtual void setID(const CString& id);		//ID
	virtual const CString& getID()const;			//ID

	virtual void setOrder(const int& order);	//���
	virtual const int& getOrder()const;				//���

	virtual void setRect(RectF rect);	//����
	virtual RectF getRect()const;			//����

	virtual void setDrawPath(bool isDrawPath);				//������
	virtual void setFillPath(bool isFillPath);				//���

 	virtual const std::shared_ptr<Region>& getRegion();			//����

	virtual bool isChangeRegion() const = 0;
	virtual void ResetRegion() = 0;

// 	virtual void readPoints(std::list<PointF>& points)const;		//�㼯��
// 	virtual void writePoints(std::list<PointF>& points);	//�㼯��
// 
// 	virtual void moveTo(PointF point);	//�ƶ���
// 	virtual void move(PointF offset);	//ƫ��

//	virtual void OnPaint( Graphics &g );	//��ͼ

protected:
	//////////////////////////////////////////////////////////////////////////
	// ����
	CString m_type;							//����
	CString m_ID;							//ID
	int m_order;							//���
	int m_state;							//״̬
	RectF m_myRect;							//����
	bool m_isDrawPath;						//������
	bool m_isFillPath;						//���
	Color m_drawColor;						//�Ի�������ɫ
	Color m_fillColor;						//�Ի������ɫ
	std::shared_ptr<Region> m_region;		//��ǰͼ��ķ�Χ

public:
	//////////////////////////////////////////////////////////////////////////
	// ��������
	const static int StateSelfDefine;		//�Զ���״̬
	const static int StateNormal;			//����״̬
	const static int StateHovered;			//����״̬
	const static int StateDisable;			//ʧЧ״̬
	const static int StateDown;				//�°�״̬
	const static int StateError;			//����״̬
};
typedef std::vector<DrawItemBase*> DrawItemBasePtrList;



#endif
/************************************************************************/
/*  ��ͼ��״ DrawItemShape                                               */
/************************************************************************/
#if 1
class DrawItemShape : public DrawItemBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemShape(RectF rect,const std::list<IDataLine*>& lines);
	virtual ~DrawItemShape();

public:
	//////////////////////////////////////////////////////////////////////////
	// �ӿ�ʵ��
	//virtual const std::shared_ptr<Region>& getRegion()const;			//����
	virtual void setRegion(const std::list<IDataLine*>& lines);			//����

	virtual void readPoints(std::list<PointF>& points)const;		//�㼯��
	virtual void writePoints(std::list<PointF>& points);	//�㼯��

	virtual void move(PointF offset);		//ƫ��

	virtual void OnPaint( Graphics &g );	//��ͼ

	virtual void foreachPoint(void (*func) (PointF&));

	virtual void foreachPoint(void (*func) (const PointF&))const;

	template<class T>
	void foreachPoint(T func){
		std::for_each(m_lines.begin(),m_lines.end(),[&func](IDataLine* dataline)
		{
			auto line = dynamic_cast<DataLineBase*>(dataline);
			if(line)	line->foreachPoint(func);
			
			auto linelist = dynamic_cast<DrawLineList*>(dataline);
			if(linelist)	linelist->foreachPoint(func);
		});
	}

	template<class T>
	void foreachPoint(T func)const{
		std::for_each(m_lines.begin(),m_lines.end(),[&func](const IDataLine* dataline)
		{
			auto line = dynamic_cast<const DataLineBase*>(dataline);
			if(line)	line->foreachPoint(func);

			auto linelist = dynamic_cast<const DrawLineList*>(dataline);
			if(linelist)	linelist->foreachPoint(func);
		});
	}

	virtual bool isChangeRegion() const;

	virtual void ResetRegion();

protected:
	//////////////////////////////////////////////////////////////////////////
	// ����
	std::list<IDataLine*> m_lines;
	
};
//
typedef std::vector<DrawItemShape*> DrawItemShapePtrList;

#endif
/************************************************************************/
/*  ��ͼ��״ DrawItemCircle                                             */
/************************************************************************/
#if 1

class DrawItemCircle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemCircle(RectF rect,float pos_x,float pos_y,float radius);
	void initCircle(RectF rect,float pos_x,float pos_y,float radius);
	virtual ~DrawItemCircle(){};
};
#endif
/************************************************************************/
/*  ��ͼ��״ DrawItemRectangle                                          */
/************************************************************************/
#if 1
class DrawItemRectangle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// ����
	DrawItemRectangle(RectF rect,std::list<IDataLine*> lines);
	virtual ~DrawItemRectangle(){};
};
#endif