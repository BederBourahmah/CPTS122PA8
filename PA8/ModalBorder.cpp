#include "ModalBorder.h"
#include <iostream>

ModalBorder::ModalBorder(float width, float height)
{
    height = height < (cornerDoubleBorderSquareLength * 2 + verticalDoubleBorderLength) ? cornerDoubleBorderSquareLength * 2 + verticalDoubleBorderLength : height;
    width = width < (cornerDoubleBorderSquareLength * 2 + horizontalDoubleBorderLength) ? cornerDoubleBorderSquareLength * 2 + horizontalDoubleBorderLength : width;

    topLeftBorder.setTexture(&topLeftDoubleBorder);
    topLeftBorder.setSize(sf::Vector2f(cornerDoubleBorderSquareLength, cornerDoubleBorderSquareLength));

    bottomLeftBorder.setTexture(&bottomLeftDoubleBorder);
    bottomLeftBorder.setOrigin(0, cornerDoubleBorderSquareLength);
    bottomLeftBorder.setSize(sf::Vector2f(cornerDoubleBorderSquareLength, cornerDoubleBorderSquareLength));

    topRightBorder.setTexture(&topRightDoubleBorder);
    topRightBorder.setOrigin(cornerDoubleBorderSquareLength, 0);
    topRightBorder.setSize(sf::Vector2f(cornerDoubleBorderSquareLength, cornerDoubleBorderSquareLength));
    
    bottomRightBorder.setTexture(&bottomRightDoubleBorder);
    bottomRightBorder.setOrigin(cornerDoubleBorderSquareLength, cornerDoubleBorderSquareLength);
    bottomRightBorder.setSize(sf::Vector2f(cornerDoubleBorderSquareLength, cornerDoubleBorderSquareLength));

    auto borderWidth = (int)width - 2 * cornerDoubleBorderSquareLength;

    topBorder.setTexture(&topDoubleBorder);
    topBorder.setTextureRect(sf::IntRect(0, 0, borderWidth, longDoubleBorderThickness));
    topBorder.setOrigin((width - 2 * cornerDoubleBorderSquareLength) / (float)2, 0);
    topBorder.setSize(sf::Vector2f(width-2* cornerDoubleBorderSquareLength, longDoubleBorderThickness));

    bottomBorder.setTexture(&bottomDoubleBorder);
    bottomBorder.setTextureRect(sf::IntRect(0, 0, borderWidth, longDoubleBorderThickness));
    bottomBorder.setOrigin((width - 2 * cornerDoubleBorderSquareLength) / (float)2, longDoubleBorderThickness);
    bottomBorder.setSize(sf::Vector2f(width - 2 * cornerDoubleBorderSquareLength, longDoubleBorderThickness));

    auto borderHeight = (int)height - 2 * cornerDoubleBorderSquareLength;

    leftBorder.setTexture(&leftDoubleBorder);
    leftBorder.setTextureRect(sf::IntRect(0, 0, longDoubleBorderThickness, borderHeight));
    leftBorder.setOrigin(0, (height - 2 * cornerDoubleBorderSquareLength) / (float)2);
    leftBorder.setSize(sf::Vector2f(longDoubleBorderThickness, height - 2 * cornerDoubleBorderSquareLength));

    rightBorder.setTexture(&rightDoubleBorder);
    rightBorder.setTextureRect(sf::IntRect(0, 0, longDoubleBorderThickness, borderHeight));
    rightBorder.setOrigin(longDoubleBorderThickness, (height - 2 * cornerDoubleBorderSquareLength) / (float)2);
    rightBorder.setSize(sf::Vector2f(longDoubleBorderThickness, height - 2 * cornerDoubleBorderSquareLength));

    totalHeight = height;
    totalWidth = width;
    centerPosX = totalWidth / 2;
    centerPosY = totalHeight / 2;
    updatePosition();
}

void ModalBorder::updatePosition()
{
    topLeftBorder.setPosition(getLeftPosXToCenter(), getTopPosYToCenter());
    bottomLeftBorder.setPosition(getLeftPosXToCenter(), getBottomPosYToCenter());
    topRightBorder.setPosition(getRightPosXToCenter(), getTopPosYToCenter());
    bottomRightBorder.setPosition(getRightPosXToCenter(), getBottomPosYToCenter());
    topBorder.setPosition(centerPosX, getTopPosYToCenter());
    bottomBorder.setPosition(centerPosX, getBottomPosYToCenter());
    leftBorder.setPosition(getLeftPosXToCenter(), centerPosY);
    rightBorder.setPosition(getRightPosXToCenter(), centerPosY);
}

void ModalBorder::drawTo(sf::RenderWindow& window)
{
    window.draw(topLeftBorder);
    window.draw(bottomLeftBorder);
    window.draw(topRightBorder);
    window.draw(bottomRightBorder);
    window.draw(topBorder);
    window.draw(bottomBorder);
    window.draw(leftBorder);
    window.draw(rightBorder);
}
