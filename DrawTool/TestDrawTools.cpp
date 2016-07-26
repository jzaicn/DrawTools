#include "StdAfx.h"
#include "TestDrawTools.h"
#include "DrawTools.h"

bool TestDrawTools::TestDrawToolsAll()
{
	Test_getAngleFromRad();
	Test_getAngularCoordinate_DegreeCatch0();
	Test_getAngularCoordinate_DegreeCatch1();
	Test_getAngularCoordinate_Mirror();
	return true;
}


//点角度计算
void TestDrawTools::Test_getAngleFromRad()
{
#if TEST_ONCE
	PointF center(50,50);

	//正轴
	PointF point1(100,50);
	double angle1 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point1));
	ASSERT(angle1 == 0.0);

	//正半轴
	PointF point2(100,0);
	double angle2 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point2));
	ASSERT(angle2 == 45.0);

	//正半轴
	PointF point3(50,00);
	double angle3 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point3));
	ASSERT(angle3 == 90.0);

	//正半轴
	PointF point4(00,00);
	double angle4 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point4));
	ASSERT(angle4 == 135.0);

	//正轴
	PointF point5(0,50);
	double angle5 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point5));
	ASSERT(angle5 == 180.0);

	//正半轴
	PointF point6(0,100);
	double angle6 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point6));
	ASSERT(angle6 == 225.0);

	//正半轴
	PointF point7(50,100);
	double angle7 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point7));
	ASSERT(angle7 == 270.0);

	//正半轴
	PointF point8(100,100);
	double angle8 = DrawTools::getAngleFromRad(DrawTools::getRadFrom2Point(center,point8));
	ASSERT(angle8 == 315.0);

#endif
}

//角坐标计算测试
void TestDrawTools::Test_getAngularCoordinate_DegreeCatch0()
{
#if TEST_ONCE
	PointF center(50.0,50.0);
	double beginAngle = 0.0 ,sweepAngle = 0.0;

	//正向4个象限
	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50),PointF(50.0,0.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 0.0);
	ASSERT(sweepAngle == 90.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,0.0),PointF(0.0,50.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 90.0);
	ASSERT(sweepAngle == 90.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50),PointF(50.0,100.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 180.0);
	ASSERT(sweepAngle == 90.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,100),PointF(100,50.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 270.0);
	ASSERT(sweepAngle == 90.0);



	//再追一圈4个象限
	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,0.0),PointF(100,50),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 90.0);
	ASSERT(sweepAngle == 270.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50.0),PointF(50,0.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 180.0);
	ASSERT(sweepAngle == 270.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,100.0),PointF(0.0,50),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 270.0);
	ASSERT(sweepAngle == 270.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50.0),PointF(50,100),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 0.0);
	ASSERT(sweepAngle == 270.0);
#endif
}

//最短追及
void TestDrawTools::Test_getAngularCoordinate_DegreeCatch1()
{
#if TEST_ONCE
	PointF center(50.0,50.0);
	double beginAngle = 0.0 ,sweepAngle = 0.0;

	//正向4个象限
	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50),PointF(50.0,0.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 0.0);
	ASSERT(sweepAngle == 90.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,0.0),PointF(0.0,50.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 90.0);
	ASSERT(sweepAngle == 90.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50),PointF(50.0,100.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 180.0);
	ASSERT(sweepAngle == 90.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50,100),PointF(100,50.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 270.0);
	ASSERT(sweepAngle == 90.0);



	//再追一圈4个象限
	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,0.0),PointF(100,50),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 90.0);
	ASSERT(sweepAngle == 270.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(0.0,50.0),PointF(50,0.0),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 180.0);
	ASSERT(sweepAngle == 270.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(50.0,100.0),PointF(0.0,50),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 270.0);
	ASSERT(sweepAngle == 270.0);

	DrawTools::getAngularCoordinate_DegreeCatch(center,PointF(100,50.0),PointF(50,100),50,beginAngle,sweepAngle);
	ASSERT(beginAngle == 0.0);
	ASSERT(sweepAngle == 270.0);
#endif
}


//正式角坐标到显示用角坐标转换
void TestDrawTools::Test_getAngularCoordinate_Mirror()
{
#if TEST_ONCE
	ASSERT(DrawTools::getAngularCoordinate_Mirror(60.0) == 300.0);
	ASSERT(DrawTools::getAngularCoordinate_Mirror(270.0) == 90.0);

	double begin1 = 90.0;
	double sweep1 = 90;
	DrawTools::getDrawArcAngularCoordinate(begin1,sweep1);
	ASSERT(begin1 == 270);
	ASSERT(sweep1 == -90);
#endif
}