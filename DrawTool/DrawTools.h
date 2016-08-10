#pragma once

#include "stdafx.h"
#include <vector>
#include <list>
#include <algorithm>
#include "DrawLine.h"
#include "DrawItem.h"


class DrawTools
{
private:
	DrawTools(void){}
	~DrawTools(void){}

public:
	/************************************************************************/
	/* 常用常量定义                                                         */
	/************************************************************************/
	static Color ColorNormal;				//正常颜色
	static Color ColorHovered;				//覆盖颜色
	static Color ColorDisable;				//失效颜色
	static Color ColorDown;					//下按颜色
	static Color ColorError;				//错误颜色	

	static Color ColorBorder;				//边框填充颜色
	static Color ColorShapeBorder;			//异形边框填充颜色
	static Color ColorVertical;				//孔填充颜色
	static Color ColorSaw;					//槽填充颜色


public:
	/************************************************************************/
	/* 类型转换                                                             */
	/************************************************************************/
	static CRect buildCRect(RectF rect);

	static RectF buildRectF(CRect rect);
	static RectF buildRectF(PointF topleft,PointF bottomRight);

	static PointF getTopLeft(const RectF& rect);
	static PointF getBottomRight(const RectF& rect);
	static PointF getTopRight(const RectF& rect);
	static PointF getBottomLeft(const RectF& rect);
	static PointF getMiddle(const RectF& rect);

	static PointF buildPointF(CPoint point);
	static CPoint buildCPoint(PointF point);

	static std::list<IDataLine*> buildDrawStraightLine( const RectF& rect );

public:
	/************************************************************************/
	/* 计算算法                                                             */
	/************************************************************************/


	const static int ArcSignLeft;
	const static int ArcSignRight;

	//生成圆心，sign=0圆心在线段方向的左手边，sign=1圆心在线段方向的右手边
	// ...................
	// .......last........
	// ......./|\.........
	// .sign=1.|..........
	// .@......|...@......
	// ........|...sign=2.
	// ........|..........
	// ........|..........
	// ......first........
	// ...................
	static PointF getCircleCenter(PointF first, PointF last , float radius , int sign);

	//两点算角度  
	static double getRadFrom2Point(const PointF& pointCenter,const PointF& pointDis) ;
	//角度转弧度  
	static double getRadFromAngle(double angle);
	//弧度转角度  
	static double getAngleFromRad(double rad) ;
	//根据某点，旋转一个角度   
	static void rotateByAngle(PointF pointCenter,PointF &pointNeedRotate,double dAngleDegree)  ;
	//通过两点以及圆弧和方向，得到圆弧线组成的参数（ rect,beginAngle,endAngle 输出参数）
	static void getArc(PointF first, PointF last,float radius,int sign,RectF& rect,double& beginAngle,double& sweepAngle);
	//按大小排序
	static void sortAngle(double& angle1, double& angle2);
	//角坐标两点追及问题，圆形圆弧上两点，一点沿角坐标正方向追及第二点需要移动的角度数
	static void getAngularCoordinate_DegreeCatch( PointF center, PointF first, PointF last, float radius, double &beginAngle, double &sweepAngle );
	//角坐标两点追及问题，圆形圆弧上两点，某一点沿角坐标正方向追及另一点点需要移动的角度数
	static void getAngularCoordinate_DegreeCatchShort( PointF center, PointF one, PointF other, float radius, double &beginAngle, double &sweepAngle );
	//角坐标X轴翻转
	static double getAngularCoordinate_Mirror(double beginAngle);
	//正式角坐标到画弧用角坐标转换
	static void getDrawArcAngularCoordinate(double& beginAngle, double& sweepAngle);


private:
	static void DrawTools::getCircleCenter(float beginx,float endx,float beginy,float endy,float radius,int sign,float & center_x,float & center_y);
};

