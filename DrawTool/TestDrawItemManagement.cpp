#include "StdAfx.h"
#include "DrawItemManagement.h"
#include "TestDrawItemManagement.h"


bool TestDrawItemManagement::TestDrawItemManagementAll()
{
	Test_rotateDrawItem();
	return true;
}

void TestDrawItemManagement::Test_rotateDrawItem()
{
#if TestOnce //测试形状的旋转,坐标
	DrawItemManagement manager;


	RectF rect = RectF(0,0,281,531);
	std::list<PointF> points;

	std::list<IDrawLine*> lines;
	lines.push_back(new DrawStraightLine(PointF(0,0),PointF(0,381)));
	lines.push_back(new DrawArcLine(PointF(0,381),PointF(150,531),150,1));
	lines.push_back(new DrawStraightLine(PointF(150,531),PointF(281,531)));
	lines.push_back(new DrawStraightLine(PointF(281,531),PointF(281,0)));
	lines.push_back(new DrawStraightLine(PointF(281,0),PointF(0,0)));

	DrawItemShape* shape = new DrawItemShape(rect,lines);

	m_manager.addDrawItem(shape);

	points.clear();
	shape->readPoints(points);
	ASSERT(shape->getRect().GetLeft() == 0);
	ASSERT(shape->getRect().GetTop() == 0);
	ASSERT(points.front().X == 0);
	ASSERT(points.front().Y == 0);

	//移动板件
	shape->move(PointF(200,0));

	ASSERT(shape->getRect().GetLeft() == 200);
	ASSERT(shape->getRect().GetTop() == 0);
		
	points.clear();
	shape->readPoints(points);
	ASSERT(points.front().X == 200);
	ASSERT(points.front().Y == 0);

	//旋转板件
	m_manager.rotateDrawItem(shape);
	points.clear();
	shape->readPoints(points);
	ASSERT(points.front().X == 731);
	ASSERT(points.front().Y == 0);
	ASSERT(shape->getRect().GetTop() == 0);
	ASSERT(shape->getRect().GetLeft() == 200);

	m_manager.clear();
	
#endif //测试形状的旋转,坐标
}