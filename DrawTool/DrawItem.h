#pragma once
#include <vector>
#include <list>
#include "DrawCommon.h"

#include "DataLine.h"

/************************************************************************/
/*  绘图接口 IDrawItem                                                  */
/************************************************************************/
#if 1
class IDrawItem
{
public:
	virtual void setState(const int& state) = 0;	//状态
	virtual const int& getState()const = 0;				//状态

	virtual void setType(const CString& type) = 0;	//类型
	virtual const CString& getType()const = 0;			//类型

	virtual void setID(const CString& id) = 0;		//ID
	virtual const CString& getID()const = 0;			//ID

	virtual void setOrder(const int& order) = 0;	//序号
	virtual const int& getOrder()const = 0;				//序号

	virtual void setRect(RectF rect) = 0;	//区域
	virtual RectF getRect()const = 0;		//区域

	virtual const std::shared_ptr<Region>& getRegion() = 0;			//区域

	virtual void readPoints(std::list<PointF>& points)const = 0;	//点集合
	virtual void writePoints(std::list<PointF>& points) = 0;	//点集合

	virtual void foreachPoint(void (*func)(PointF&)) = 0;
	virtual void foreachPoint(void (*func)(const PointF&))const = 0;

	//virtual void moveTo(PointF point) = 0;	//移动到
	virtual void move(PointF offset) = 0;	//偏移

	virtual void OnPaint( Graphics &g ) = 0;	//画图
	virtual ~IDrawItem(){};
};
#endif
/************************************************************************/
/*  绘图基类 DrawItemBase                                               */
/************************************************************************/
#if 1
class DrawItemBase : public IDrawItem
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造数据
	DrawItemBase();
	DrawItemBase(PointF topLeft,PointF bottomRight);
	DrawItemBase(RectF rect);
	virtual ~DrawItemBase(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// 实现接口
	virtual void setState(const int& state);	//状态
	virtual const int& getState()const;				//状态

	virtual void setType(const CString& type);	//类型
	virtual const CString& getType()const;			//类型

	virtual void setID(const CString& id);		//ID
	virtual const CString& getID()const;			//ID

	virtual void setOrder(const int& order);	//序号
	virtual const int& getOrder()const;				//序号

	virtual void setRect(RectF rect);	//区域
	virtual RectF getRect()const;			//区域

	virtual void setDrawPath(bool isDrawPath);				//画轮廓
	virtual void setFillPath(bool isFillPath);				//填充

 	virtual const std::shared_ptr<Region>& getRegion();			//区域

	virtual bool isChangeRegion() const = 0;
	virtual void ResetRegion() = 0;

// 	virtual void readPoints(std::list<PointF>& points)const;		//点集合
// 	virtual void writePoints(std::list<PointF>& points);	//点集合
// 
// 	virtual void moveTo(PointF point);	//移动到
// 	virtual void move(PointF offset);	//偏移

//	virtual void OnPaint( Graphics &g );	//画图

protected:
	//////////////////////////////////////////////////////////////////////////
	// 数据
	CString m_type;							//类型
	CString m_ID;							//ID
	int m_order;							//序号
	int m_state;							//状态
	RectF m_myRect;							//区域
	bool m_isDrawPath;						//画轮廓
	bool m_isFillPath;						//填充
	Color m_drawColor;						//自画边线颜色
	Color m_fillColor;						//自画填充颜色
	std::shared_ptr<Region> m_region;		//当前图标的范围

public:
	//////////////////////////////////////////////////////////////////////////
	// 公共数据
	const static int StateSelfDefine;		//自定义状态
	const static int StateNormal;			//正常状态
	const static int StateHovered;			//覆盖状态
	const static int StateDisable;			//失效状态
	const static int StateDown;				//下按状态
	const static int StateError;			//错误状态
};
typedef std::vector<DrawItemBase*> DrawItemBasePtrList;



#endif
/************************************************************************/
/*  绘图形状 DrawItemShape                                               */
/************************************************************************/
#if 1
class DrawItemShape : public DrawItemBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemShape(RectF rect,const std::list<IDataLine*>& lines);
	virtual ~DrawItemShape();

public:
	//////////////////////////////////////////////////////////////////////////
	// 接口实现
	//virtual const std::shared_ptr<Region>& getRegion()const;			//区域
	virtual void setRegion(const std::list<IDataLine*>& lines);			//区域

	virtual void readPoints(std::list<PointF>& points)const;		//点集合
	virtual void writePoints(std::list<PointF>& points);	//点集合

	virtual void move(PointF offset);		//偏移

	virtual void OnPaint( Graphics &g );	//画图

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
	// 数据
	std::list<IDataLine*> m_lines;
	
};
//
typedef std::vector<DrawItemShape*> DrawItemShapePtrList;

#endif
/************************************************************************/
/*  绘图形状 DrawItemCircle                                             */
/************************************************************************/
#if 1

class DrawItemCircle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemCircle(RectF rect,float pos_x,float pos_y,float radius);
	void initCircle(RectF rect,float pos_x,float pos_y,float radius);
	virtual ~DrawItemCircle(){};
};
#endif
/************************************************************************/
/*  绘图形状 DrawItemRectangle                                          */
/************************************************************************/
#if 1
class DrawItemRectangle : public DrawItemShape
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 构造
	DrawItemRectangle(RectF rect,std::list<IDataLine*> lines);
	virtual ~DrawItemRectangle(){};
};
#endif