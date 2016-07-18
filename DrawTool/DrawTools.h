#pragma once

class DrawTools
{
private:
	DrawTools(void){}
	~DrawTools(void){}

public:
	/************************************************************************/
	/* ����ת��                                                                     */
	/************************************************************************/
	static CRect buildCRect(RectF rect);

	static RectF buildRectF(CRect rect);
	static RectF buildRectF(PointF topleft,PointF bottomRight);

	static PointF getTopLeft(RectF rect);
	static PointF getBottomRight(RectF rect);
	static PointF getTopRight(RectF rect);
	static PointF getBottomLeft(RectF rect);

	static PointF buildPointF(CPoint point);
	static CPoint buildCPoint(PointF point);

public:
	/************************************************************************/
	/* �����㷨                                                                     */
	/************************************************************************/


	const static int ArcSignLeft;
	const static int ArcSignRight;

	//����Բ�ģ�sign=0Բ�����߶η�������ֱߣ�sign=1Բ�����߶η�������ֱ�
	// ...................
	// .......last........
	// ......./|\.........
	// .sign=0.|..........
	// .@......|...@......
	// ........|...sign=1.
	// ........|..........
	// ........|..........
	// ......first........
	// ...................
	static PointF getCircleCenter(PointF first, PointF last , float radius , int sign);

	//������Ƕ�  
	static double getRadFrom2Point(PointF pointCenter,PointF pointDis) ;
	//�Ƕ�ת����  
	static double getRadFromAngle(double angle);
	//����ת�Ƕ�  
	static double getAngleFromRad(double rad) ;
	//����ĳ�㣬��תһ���Ƕ�   
	static void rotateByAngle(PointF pointCenter,PointF &pointNeedRotate,double dAngleDegree)  ;
	//ͨ�������Լ�Բ���ͷ��򣬵õ�Բ������ɵĲ����� rect,beginAngle,endAngle ���������
	static void getArc(PointF first, PointF last,float radius,int sign,RectF& rect,double& beginAngle,double& sweepAngle);
	//����С����
	static void sortAngle(double& angle1, double& angle2);
	//����������׷�����⣬Բ��Բ�������㣬һ���ؽ�����������׷���ڶ�����Ҫ�ƶ��ĽǶ���
	static void getAngularCoordinate_DegreeCatch( PointF center, PointF first, PointF last, float radius, double &beginAngle, double &sweepAngle );
	//����������׷�����⣬Բ��Բ�������㣬ĳһ���ؽ�����������׷����һ�����Ҫ�ƶ��ĽǶ���
	static void getAngularCoordinate_DegreeCatchShort( PointF center, PointF one, PointF other, float radius, double &beginAngle, double &sweepAngle );
	//������X�ᷭת
	static double getAngularCoordinate_Mirror(double beginAngle);
	//��ʽ�����굽�����ý�����ת��
	static void getDrawArcAngularCoordinate(double& beginAngle, double& sweepAngle);


private:
	static void DrawTools::getCircleCenter(float beginx,float endx,float beginy,float endy,float radius,int sign,float & center_x,float & center_y);
};
