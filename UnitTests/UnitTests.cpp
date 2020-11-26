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

		TEST_METHOD(RectangleLeftOfCenterIsLeftOfCenterTrue)
		{
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.moveTo(100.0f, 100.0f);
			Assert::IsTrue(testRectangle.isLeftOfCenter(105.0f));
		}

		TEST_METHOD(RectangleRightOfCenterIsLeftOfCenterFalse)
		{
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.moveTo(106.0f, 100.0f);
			Assert::IsFalse(testRectangle.isLeftOfCenter(105.0f));
		}

		TEST_METHOD(CenterHorizontal500WidthVideoModeSetsXTo250)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(500, 500);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.centerHorizontal(testVideoMode);
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)250);
		}

		TEST_METHOD(CenterVertical500LengthVideoModeSetsYTo250)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(500, 500);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.centerVertical(testVideoMode);
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)250);
		}

		TEST_METHOD(SnapToVerticalSection1Of2With1000LengthVideoModeSetsYTo250)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToVertical(testVideoMode, 2, 1);
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)250);
		}

		TEST_METHOD(SnapToHorizontalSection1Of2With1000WidthVideoModeSetsXTo250)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToHorizontal(testVideoMode, 2, 1);
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)250);
		}

		TEST_METHOD(SnapToRightOffScreen1000WidthVideoMode10WidthRectangleSetsXTo1005)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToRightOffScreen(testVideoMode);
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)1005);
		}

		TEST_METHOD(SnapToLeftOffScreenAnyWidthVideoMode10WidthRectangleSetsXToNeg5)
		{
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToLeftOffScreen();
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)-5);
		}

		TEST_METHOD(SnapToBottomOffScreen1000LengthVideoMode10WidthRectangleSetsYTo1005)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToBottomOffScreen(testVideoMode);
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)1005);
		}

		TEST_METHOD(SnapToTopOffScreenAnyLengthVideoMode10LengthRectangleSetsYToNeg5)
		{
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToTopOffScreen();
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)-5);
		}

		TEST_METHOD(SnapToBottom1000LengthVideoMode10LengthRectangleSetsYTo995)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToBottom(testVideoMode);
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)995);
		}

		TEST_METHOD(SnapToTopAnyLengthVideoMode10LengthRectangleSetsYTo5)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToTop();
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)5);
		}

		TEST_METHOD(SnapToLeftAnyWidthVideoMode10LengthRectangleSetsXTo5)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToLeft();
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)5);
		}

		TEST_METHOD(SnapToRight1000WidthVideoMode10LengthRectangleSetsXTo995)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToRight(testVideoMode);
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)995);
		}

		TEST_METHOD(SnapToTopLeftAnyLengthWidthVideoMode10LengthWidthRectangleSetsXTo5YTo5)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.snapToTopLeft();
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)5);
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)5);
		}

		TEST_METHOD(MoveToX16Y13CenterPosReturnsCorrectly)
		{
			sf::VideoMode testVideoMode = sf::VideoMode(1000, 1000);
			MoveableRectangle testRectangle = MoveableRectangle(sf::Vector2f(10.0f, 10.0f));
			testRectangle.moveTo(16, 13);
			Assert::AreEqual(testRectangle.getCenterCoordinates().x, (float)16);
			Assert::AreEqual(testRectangle.getCenterCoordinates().y, (float)13);
		}
	};
}
