#include "MenuSelector.h"



MenuSelector::MenuSelector(float width, float height)
{
    sf::Vector2f borderSquareSize(cornerSingleBorderSquareLength, cornerSingleBorderSquareLength);
    topLeftBorder.setTexture(&topLeftSingleBorder);
    topLeftBorder.setSize(borderSquareSize);
    bottomLeftBorder.setTexture(&bottomLeftSingleBorder);
    bottomLeftBorder.setOrigin(0, -cornerSingleBorderSquareLength);
    bottomLeftBorder.setSize(borderSquareSize);
    topRightBorder.setTexture(&topRightSingleBorder);
    topRightBorder.setOrigin(-cornerSingleBorderSquareLength, 0);
    topRightBorder.setSize(borderSquareSize);
    bottomRightBorder.setTexture(&bottomRightSingleBorder);
    bottomRightBorder.setOrigin(-cornerSingleBorderSquareLength, -cornerSingleBorderSquareLength);
    bottomRightBorder.setSize(borderSquareSize);
    
    totalHeight = height;
    totalWidth = width + (cornerSingleBorderSquareLength * 2);
    centerPosX = totalWidth / 2;
    centerPosY = totalHeight / 2;
}

void MenuSelector::updatePosition()
{
    topLeftBorder.setPosition(getLeftPosXToCenter(), getTopPosYToCenter());
    topRightBorder.setPosition(getRightPosXToCenter(), getTopPosYToCenter());
    bottomLeftBorder.setPosition(getLeftPosXToCenter(), getBottomPosYToCenter());
    bottomRightBorder.setPosition(getRightPosXToCenter(), getBottomPosYToCenter());
}

void MenuSelector::drawTo(sf::RenderWindow& window)
{
    window.draw(topLeftBorder);
    window.draw(topRightBorder);
    window.draw(bottomLeftBorder);
    window.draw(bottomRightBorder);
}
