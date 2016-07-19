#include "StdAfx.h"
#include "DrawTools.h"

/************************************************************************/
/* 常用常量定义                                                         */
/************************************************************************/
Color DrawTools::ColorNormal		 = Color(228, 238, 249);
Color DrawTools::ColorHovered		 = Color(242, 247, 252);
Color DrawTools::ColorDisable		 = Color(211, 216, 224);
Color DrawTools::ColorDown			 = Color(255, 255 ,255);
Color DrawTools::ColorError			 = Color(230, 12,3);

Color DrawTools::ColorBorder		 = Color::Black;
Color DrawTools::ColorShapeBorder	 = Color::Yellow;
Color DrawTools::ColorVertical		 = Color::Blue;
Color DrawTools::ColorSaw			 = Color::Blue;


/************************************************************************/
/* 转换部分                                                                     */
/************************************************************************/
CRect DrawTools::buildCRect(RectF rect)
{
	return CRect(rect.X,rect.Y,rect.X + rect.Width, rect.Y + rect.Height);
}

RectF DrawTools::buildRectF(CRect rect)
{
	return RectF(rect.left,rect.top,rect.Width(),rect.Height());
}
RectF DrawTools::buildRectF(PointF topLeft,PointF bottomRight)
{
	return RectF(topLeft.X ,
		topLeft.Y ,
		bottomRight.X - topLeft.X ,
		bottomRight.Y - topLeft.Y
		);
}

PointF DrawTools::getTopLeft(RectF rect)
{
	return PointF(rect.GetLeft(),rect.GetTop());
}
PointF DrawTools::getBottomRight(RectF rect)
{
	return PointF(rect.GetRight(),rect.GetBottom());
}
PointF DrawTools::getTopRight(RectF rect)
{
	return PointF(rect.GetRight(),rect.GetTop());
}
PointF DrawTools::getBottomLeft(RectF rect)
{
	return PointF(rect.GetLeft(),rect.GetBottom());
}

PointF DrawTools::buildPointF(CPoint point)
{
	return PointF(point.x,point.y);
}
CPoint DrawTools::buildCPoint(PointF point)
{
	return CPoint(point.X,point.Y);
}
/************************************************************************/
/*   计算算法                                                           */
/************************************************************************/
#include <math.h>  
#define MY_PI 3.14159265358979323846  

const int DrawTools::ArcSignLeft = 1;
const int DrawTools::ArcSignRight = 2;

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
PointF DrawTools::getCircleCenter(PointF first, PointF last , float radius , int sign)
{
	PointF center;
	if (sign == ArcSignLeft)
	{
		DrawTools::getCircleCenter(first.X,last.X,first.Y,last.Y,radius,sign,center.X,center.Y);
	}
	else if (sign == ArcSignRight)
	{
		DrawTools::getCircleCenter(last.X,first.X,last.Y,first.Y,radius,sign,center.X,center.Y);
	}
	return center;
}

void DrawTools::getCircleCenter(float beginx,float endx,float beginy,float endy,float radius,int sign,float & center_x,float & center_y)
{
	float len_beginToend = sqrt((beginx - endx)*(beginx - endx) + (beginy - endy)*(beginy - endy));
	if (radius != 0.0 && len_beginToend != 0.0)
	{
		float dis_x = (beginx - endx)/len_beginToend * radius;
		float dis_y = (beginy - endy)/len_beginToend * radius;

		float mid_x = endx + dis_x;
		float mid_y = endy + dis_y;

		float mid_x_move = mid_x - endx;
		float mid_y_move = mid_y - endy;

		float arc = (MY_PI-2*asin((0.5*len_beginToend)/radius))/2;

		center_x = mid_x_move*cos(arc) - mid_y_move*sin(arc);
		center_y = mid_x_move*sin(arc) + mid_y_move*cos(arc);

		center_x = center_x + endx;
		center_y = center_y + endy;
	}
	else
	{
		center_x = 0.0;
		center_y = 0.0;
	}
}

//通过两点以及圆弧和方向，得到圆弧线组成的参数（ rect,beginAngle,endAngle 输出参数）
void DrawTools::getArc(PointF first, PointF last,float radius,int sign,RectF& rect,double& beginAngle,double& sweepAngle)
{
	ASSERT(!first.Equals(last));	//起始和结束在同一点，有无数个圆，所以不能计算
	ASSERT(radius != 0.0);			//半径为0
	ASSERT(sign == ArcSignLeft || sign == ArcSignRight);	//sign	取值
	
	//取得圆心和外矩形
	PointF center = getCircleCenter(first,last,radius,sign);
	rect = RectF(center.X - radius,center.Y - radius,radius+radius,radius+radius);

	getAngularCoordinate_DegreeCatchShort(center , first, last, radius, beginAngle, sweepAngle);
	getDrawArcAngularCoordinate(beginAngle,sweepAngle);
}

//两点算角度  
double DrawTools::getRadFrom2Point(PointF pointCenter,PointF pointDis)  
{  
	PointF point1 = PointF(pointCenter);  
	PointF point2 = PointF(pointDis);  
	PointF deltaPoint = PointF(point2.X-point1.X,point2.Y-point1.Y);  

	//a = 3; b = -3;  
	//点的坐标为(a,b)
	//mod(atan2(b,a),2*pi)
	//只有
	double y = deltaPoint.Y;
	double x = deltaPoint.X;
	double modnum = 2*MY_PI;
	double dAngle = ( x != 0.0 ) ? fabs(fmod(atan2(y,x),modnum)) :  MY_PI*0.5;//处理arctan除零问题，当X方向是0时独立计算
	//下半
 	if (pointDis.Y > pointCenter.Y)
 	{
		dAngle = 2*MY_PI - dAngle;
 	}
	return dAngle;  
} 
//角度转弧度 
double DrawTools::getRadFromAngle(double angle)  
{  
	return (angle / 180 * MY_PI);  
}  

//弧度转角度  
double DrawTools::getAngleFromRad(double rad)  
{  
	return (rad / MY_PI * 180);  
} 
//根据某点，旋转一个角度   
void DrawTools::rotateByAngle(PointF pointCenter,  
	PointF &pointNeedRotate,  
	double dAngleDegree)  
{  
	//通过移动把旋转中心放到坐标原点  
	//旋转矩阵，公式如下（以原点旋转θ度）  
	//(x',y') = ( x*cosθ-y*sinθ , x*sinθ+y*cosθ )  
	PointF pointshifting = pointCenter-PointF(0,0);//旋转中心到坐标原点的距离  
	PointF point0 = pointCenter - pointshifting;  
	PointF point1 = pointNeedRotate - pointshifting;  
	double dAngle2Rad = getRadFromAngle(dAngleDegree);    
	PointF point2(point1.X*cos(dAngle2Rad) - point1.Y*sin(dAngle2Rad),  
		point1.X*sin(dAngle2Rad) + point1.Y*cos(dAngle2Rad));  
	pointNeedRotate = point2 + pointshifting;  
} 
//按大小排序
void DrawTools::sortAngle(double& angle1, double& angle2)
{
	if (angle1 > angle2)
	{
		double temp;
		temp = angle1;
		angle1 = angle2;
		angle2 = temp;
	}
}

//角坐标两点追及问题，圆形圆弧上两点，一点沿角坐标正方向追及第二点需要移动的角度数
void DrawTools::getAngularCoordinate_DegreeCatch( PointF center, PointF first, PointF last, float radius, double &beginAngle, double &sweepAngle )
{
	//角坐标正方向
	int sign = 1;

	//计算弧走的角度
	double beginrad = getRadFrom2Point(center,first);
	double beginAngleDegree = getAngleFromRad(beginrad);
	double endrad = getRadFrom2Point(center,last);
	double endAngleDegree = getAngleFromRad(endrad);

	
	if (endAngleDegree < beginAngleDegree)	//可能是360°也可能是0°，当点的顺序是逆时针的时候需要是大数，是顺时针时需要小数
	{
		endAngleDegree += 360.0;
	}

	beginAngle = beginAngleDegree;
	sweepAngle = endAngleDegree - beginAngleDegree;
}

//角坐标两点追及问题，圆形圆弧上两点，某一点沿角坐标正方向追及另一点点需要移动的角度数
void DrawTools::getAngularCoordinate_DegreeCatchShort( PointF center, PointF one, PointF other, float radius, double &beginAngle, double &sweepAngle )
{
	double beginAngle1 = 0.0;
	double sweepAngle1 = 0.0;
	getAngularCoordinate_DegreeCatch(center,one,other,radius,beginAngle1,sweepAngle1);

	double beginAngle2 = 0.0;
	double sweepAngle2 = 0.0;
	getAngularCoordinate_DegreeCatch(center,other,one,radius,beginAngle2,sweepAngle2);

	if (sweepAngle1 < sweepAngle2)
	{
		beginAngle = beginAngle1;
		sweepAngle = sweepAngle1;
	}
	else
	{
		beginAngle = beginAngle2;
		sweepAngle = sweepAngle2;
	}
}

//角坐标X轴翻转
double DrawTools::getAngularCoordinate_Mirror(double beginAngle)
{
	return fmod(360.0 - beginAngle,360.0);
}

//正式角坐标到画弧用角坐标转换
void DrawTools::getDrawArcAngularCoordinate(double& beginAngle, double& sweepAngle)
{
	//如果只考虑正弧度应该如下使用
	//beginAngle = getAngularCoordinate_Mirror(beginAngle + sweepAngle);

	//现在切割顺序是逆时针，所以通过角度sweep设成负数
	beginAngle = getAngularCoordinate_Mirror(beginAngle);
	sweepAngle = -sweepAngle;
}