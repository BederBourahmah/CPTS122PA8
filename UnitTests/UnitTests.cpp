#include "pch.h"
#include "CppUnitTest.h"
#include "MoveableRectangle.cpp"
#include <SFML/Graphics.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(MoveableRectangleTests)
	{
	public:
		
		TEST_METHOD(OverlappingRectanglesDidCollideTrue)
		{
			MoveableRectangle leftRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			MoveableRectangle rightRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			leftRectangle.moveTo(100.0f, 100.0f);
			rightRectangle.moveTo(100.0f, 109.99f);
			Assert::IsTrue(leftRectangle.didCollideWithOtherComponent(rightRectangle));
			Assert::IsTrue(rightRectangle.didCollideWithOtherComponent(leftRectangle));
		}

		TEST_METHOD(NonOverlappingRectanglesDidCollideFalse)
		{
			MoveableRectangle leftRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			MoveableRectangle rightRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			leftRectangle.moveTo(100.0f, 100.0f);
			rightRectangle.moveTo(100.0f, 110.01f);
			Assert::IsFalse(leftRectangle.didCollideWithOtherComponent(rightRectangle));
			Assert::IsFalse(rightRectangle.didCollideWithOtherComponent(leftRectangle));
		}
	};
}
