#include "MenuSelector.h"

static const int textureSquareLength = 19;

MenuSelector::MenuSelector(float width, float height)
{
    topLeftSprite.setTexture(baseTexture);
    topLeftSprite.setTextureRect(sf::IntRect(865, 399, textureSquareLength, textureSquareLength));
    topRightSprite.setTexture(baseTexture);
    topRightSprite.setTextureRect(sf::IntRect(982, 399, textureSquareLength, textureSquareLength));
    topRightSprite.setOrigin(-textureSquareLength, 0);
    bottomLeftSprite.setTexture(baseTexture);
    bottomLeftSprite.setTextureRect(sf::IntRect(865, 498, textureSquareLength, textureSquareLength));
    bottomLeftSprite.setOrigin(0, -textureSquareLength);
    bottomRightSprite.setTexture(baseTexture);
    bottomRightSprite.setTextureRect(sf::IntRect(982, 498, textureSquareLength, textureSquareLength));
    bottomRightSprite.setOrigin(-textureSquareLength, -textureSquareLength);
    totalHeight = height + (textureSquareLength * 2);
    totalWidth = width + (textureSquareLength * 2);
    centerPosX = totalWidth / 2;
    centerPosY = totalHeight / 2;
}

sf::Sprite MenuSelector::getTopLeftSprite()
{
    return topLeftSprite;
}

sf::Sprite MenuSelector::getBottomLeftSprite()
{
    return bottomLeftSprite;
}

sf::Sprite MenuSelector::getTopRightSprite()
{
    return topRightSprite;
}

sf::Sprite MenuSelector::getBottomRightSprite()
{
    return bottomRightSprite;
}

void MenuSelector::updatePosition()
{
    topLeftSprite.setPosition(getLeftPosXToCenter(), getTopPosYToCenter());
    topRightSprite.setPosition(getRightPosXToCenter(), getTopPosYToCenter());
    bottomLeftSprite.setPosition(getLeftPosXToCenter(), getBottomPosYToCenter());
    bottomRightSprite.setPosition(getRightPosXToCenter(), getBottomPosYToCenter());
}

void MenuSelector::drawTo(sf::RenderWindow& window)
{
    window.draw(topLeftSprite);
    window.draw(topRightSprite);
    window.draw(bottomLeftSprite);
    window.draw(bottomRightSprite);
}
