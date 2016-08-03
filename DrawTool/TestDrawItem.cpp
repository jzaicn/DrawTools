#include "StdAfx.h"
#include "TestDrawItem.h"


bool TestDrawItem::TestDrawItemAll()
{
	return true;
}



//测试画图形的点移动是否恰当
void TestDrawItem::Test_DrawStraightLine()
{
#if TestOnce
	ASSERT(DrawTools::ArcSignLeft == 1);

	RectF rect(10,10,390,360);
	std::list<IDataLine*> lines;
	lines.push_back(new DataStraightLine(PointF(400,10.0000),PointF(370.0000,10.0000)));
	lines.push_back(new DrawArcLine(PointF(370.0000,10.0000),PointF(10.0000,370.0000),360.00000,1));
	lines.push_back(new DataStraightLine(PointF(10.0000,370.0000),PointF(400.0000,370.0000)));
	lines.push_back(new DataStraightLine(PointF(400,370.0000),PointF(400,10.0000)));
	DrawItemShape* shape = new DrawItemShape(rect,lines);

	shape->move(PointF(0,0));
	std::list<PointF> points = shape->getAllPoints();
	ASSERT(points.front().Equals(PointF(400,10)));

	delete shape;
#endif
}