#include "Nave.h"
#define ALTURA 50
#define LARGURA 50

Nave::Nave(float startX, float startY) : Sprite()
{
    Texture* txtr = new Texture();
    txtr->loadFromFile("pedra2.png");
    this->setTexture(*txtr);
    position = new Vector2f();
    position->x = startX;
    position->y = startY;
    
    this->setPosition(position->x, position->y);
}
 
void Nave::moveLeft()
{
    position->x -= naveSpeed;
}
 
void Nave::moveRight()
{
    position->x += naveSpeed;
}
 
void Nave::update()
{
    this->setPosition(position->x, position->y);
} 
