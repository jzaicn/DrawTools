#include "StdAfx.h"
#include "DrawTools.h"

/************************************************************************/
/* ���ó�������                                                         */
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
/* ת������                                                                     */
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
/*   �����㷨                                                           */
/************************************************************************/
#include <math.h>  
#define MY_PI 3.14159265358979323846  

const int DrawTools::ArcSignLeft = 1;
const int DrawTools::ArcSignRight = 2;

//����Բ�ģ�sign=0Բ�����߶η�������ֱߣ�sign=1Բ�����߶η�������ֱ�
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

//ͨ�������Լ�Բ���ͷ��򣬵õ�Բ������ɵĲ����� rect,beginAngle,endAngle ���������
void DrawTools::getArc(PointF first, PointF last,float radius,int sign,RectF& rect,double& beginAngle,double& sweepAngle)
{
	ASSERT(!first.Equals(last));	//��ʼ�ͽ�����ͬһ�㣬��������Բ�����Բ��ܼ���
	ASSERT(radius != 0.0);			//�뾶Ϊ0
	ASSERT(sign == ArcSignLeft || sign == ArcSignRight);	//sign	ȡֵ
	
	//ȡ��Բ�ĺ������
	PointF center = getCircleCenter(first,last,radius,sign);
	rect = RectF(center.X - radius,center.Y - radius,radius+radius,radius+radius);

	getAngularCoordinate_DegreeCatchShort(center , first, last, radius, beginAngle, sweepAngle);
	getDrawArcAngularCoordinate(beginAngle,sweepAngle);
}

//������Ƕ�  
double DrawTools::getRadFrom2Point(PointF pointCenter,PointF pointDis)  
{  
	PointF point1 = PointF(pointCenter);  
	PointF point2 = PointF(pointDis);  
	PointF deltaPoint = PointF(point2.X-point1.X,point2.Y-point1.Y);  

	//a = 3; b = -3;  
	//�������Ϊ(a,b)
	//mod(atan2(b,a),2*pi)
	//ֻ��
	double y = deltaPoint.Y;
	double x = deltaPoint.X;
	double modnum = 2*MY_PI;
	double dAngle = ( x != 0.0 ) ? fabs(fmod(atan2(y,x),modnum)) :  MY_PI*0.5;//����arctan�������⣬��X������0ʱ��������
	//�°�
 	if (pointDis.Y > pointCenter.Y)
 	{
		dAngle = 2*MY_PI - dAngle;
 	}
	return dAngle;  
} 
//�Ƕ�ת���� 
double DrawTools::getRadFromAngle(double angle)  
{  
	return (angle / 180 * MY_PI);  
}  

//����ת�Ƕ�  
double DrawTools::getAngleFromRad(double rad)  
{  
	return (rad / MY_PI * 180);  
} 
//����ĳ�㣬��תһ���Ƕ�   
void DrawTools::rotateByAngle(PointF pointCenter,  
	PointF &pointNeedRotate,  
	double dAngleDegree)  
{  
	//ͨ���ƶ�����ת���ķŵ�����ԭ��  
	//��ת���󣬹�ʽ���£���ԭ����ת�ȶȣ�  
	//(x',y') = ( x*cos��-y*sin�� , x*sin��+y*cos�� )  
	PointF pointshifting = pointCenter-PointF(0,0);//��ת���ĵ�����ԭ��ľ���  
	PointF point0 = pointCenter - pointshifting;  
	PointF point1 = pointNeedRotate - pointshifting;  
	double dAngle2Rad = getRadFromAngle(dAngleDegree);    
	PointF point2(point1.X*cos(dAngle2Rad) - point1.Y*sin(dAngle2Rad),  
		point1.X*sin(dAngle2Rad) + point1.Y*cos(dAngle2Rad));  
	pointNeedRotate = point2 + pointshifting;  
} 
//����С����
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

//����������׷�����⣬Բ��Բ�������㣬һ���ؽ�����������׷���ڶ�����Ҫ�ƶ��ĽǶ���
void DrawTools::getAngularCoordinate_DegreeCatch( PointF center, PointF first, PointF last, float radius, double &beginAngle, double &sweepAngle )
{
	//������������
	int sign = 1;

	//���㻡�ߵĽǶ�
	double beginrad = getRadFrom2Point(center,first);
	double beginAngleDegree = getAngleFromRad(beginrad);
	double endrad = getRadFrom2Point(center,last);
	double endAngleDegree = getAngleFromRad(endrad);

	
	if (endAngleDegree < beginAngleDegree)	//������360��Ҳ������0�㣬�����˳������ʱ���ʱ����Ҫ�Ǵ�������˳ʱ��ʱ��ҪС��
	{
		endAngleDegree += 360.0;
	}

	beginAngle = beginAngleDegree;
	sweepAngle = endAngleDegree - beginAngleDegree;
}

//����������׷�����⣬Բ��Բ�������㣬ĳһ���ؽ�����������׷����һ�����Ҫ�ƶ��ĽǶ���
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

//������X�ᷭת
double DrawTools::getAngularCoordinate_Mirror(double beginAngle)
{
	return fmod(360.0 - beginAngle,360.0);
}

//��ʽ�����굽�����ý�����ת��
void DrawTools::getDrawArcAngularCoordinate(double& beginAngle, double& sweepAngle)
{
	//���ֻ����������Ӧ������ʹ��
	//beginAngle = getAngularCoordinate_Mirror(beginAngle + sweepAngle);

	//�����и�˳������ʱ�룬����ͨ���Ƕ�sweep��ɸ���
	beginAngle = getAngularCoordinate_Mirror(beginAngle);
	sweepAngle = -sweepAngle;
}