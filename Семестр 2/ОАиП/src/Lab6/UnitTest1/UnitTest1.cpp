#include "pch.h"
#include "CppUnitTest.h"
#include "../Task5/Task5.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(run(14, 1000, "cup", "russia"), 752LL);
		}
	};
}
