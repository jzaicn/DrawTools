#include "StdAfx.h"
#include "TestBase.h"
#include <math.h>


bool TestBase::Equals( PointF p1, PointF p2 )
{
	return (fabs(p1.X - p2.X)<0.00001) && (fabs(p1.Y - p2.Y)<0.00001);;
}
