#pragma once
#include "TestBase.h"

class TestDrawTools : public TestBase
{
public:
	static bool TestDrawToolsAll();

	static void Test_getAngleFromRad();
	static void Test_getAngularCoordinate_DegreeCatch0();
	static void Test_getAngularCoordinate_DegreeCatch1();
	static void Test_getAngularCoordinate_Mirror();
};

