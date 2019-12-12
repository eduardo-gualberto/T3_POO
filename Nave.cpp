#include "Nave.h"
#define ALTURA 50
#define LARGURA 50

Nave::Nave(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
 
    naveShape.setSize(sf::Vector2f(LARGURA, ALTURA));
    naveShape.setPosition(position);
}

FloatRect Nave::getPosition()
{
    return naveShape.getGlobalBounds();
}
 
RectangleShape Nave::getShape()
{
    return naveShape;
}
 
void Nave::moveLeft()
{
    position.x -= naveSpeed;
}
 
void Nave::moveRight()
{
    position.x += naveSpeed;
}
 
void Nave::update()
{
    naveShape.setPosition(position);
} 
