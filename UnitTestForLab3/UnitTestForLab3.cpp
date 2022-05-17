#include "pch.h"
#include "CppUnitTest.h"
#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>

#include "..\lab3AiSD\find.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForLab3
{
	TEST_CLASS(UnitTestForLab3)
	{
	public:
		
		TEST_METHOD(FindingPrice)
		{
			Node_List<ElementString> FindingPrice;
			FindingPrice.PushBack(ElementString("MSK", "SPB", 100, 5));
			FindingPrice.PushBack(ElementString("SPB", "KIROW", 1, 100));
			FindingPrice.PushBack(ElementString("ADLER", "SPB", 90, 500));
			FindingPrice.PushBack(ElementString("SPB", "NYC", 7, 144));
			FindingPrice.PushBack(ElementString("KIROW", "SPB", 300, 969));
			FindingPrice.PushBack(ElementString("VENA", "SPB", 8, 999));
			FindingPrice.PushBack(ElementString("ANAPA", "KIROW", 1000, 666));

			double Price = findingFullPrice(FindingPrice, "SPB", "KIROW");

			Assert::AreEqual(Price, 1.00);
		}

		
	};
}


