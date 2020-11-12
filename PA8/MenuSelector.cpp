#include "MenuSelector.h"

MenuSelector::MenuSelector(float width, float height)
{
    topLeftSprite.setTexture(baseTexture);
    topLeftSprite.setTextureRect(sf::IntRect(865, 399, 19, 19));
    topRightSprite.setTexture(baseTexture);
    topRightSprite.setTextureRect(sf::IntRect(982, 399, 19, 19));
    topRightSprite.move(19 + width, 0);
    bottomLeftSprite.setTexture(baseTexture);
    bottomLeftSprite.setTextureRect(sf::IntRect(865, 498, 19, 19));
    bottomLeftSprite.move(0, 19 + height);
    bottomRightSprite.setTexture(baseTexture);
    bottomRightSprite.setTextureRect(sf::IntRect(982, 498, 19, 19));
    bottomRightSprite.move(19 + width, 19 + height);
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

void MenuSelector::move(float offsetX, float offsetY)
{
    topLeftSprite.move(offsetX, offsetY);
    topRightSprite.move(offsetX, offsetY);
    bottomLeftSprite.move(offsetX, offsetY);
    bottomRightSprite.move(offsetX, offsetY);
}