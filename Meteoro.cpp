#include "Meteoro.h"
#include "time.h"

#define LARGURA 400

Meteoro::Meteoro(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    Texture texture;

    texture.loadFromFile("pedra2.png");

    MeteoroShape.setSize(sf::Vector2f(30, 30));
    MeteoroShape.setPosition(position);
    MeteoroShape.setTexture(&texture);
}

FloatRect Meteoro::getPosition()
{
    return MeteoroShape.getGlobalBounds();
}

RectangleShape Meteoro::getShape()
{
    return MeteoroShape;
}

float Meteoro::getVelocity(){
    return Velocity;
}

void Meteoro::hit() //meteoro "bateu no chao" ou encostou na nave
{
    position.y = 1;
    position.x = rand() % LARGURA;
    Velocity += Velocity / 100; //aumenta velocidade gradativamente
}

void Meteoro::update()
{
    position.y += Velocity;
    MeteoroShape.setPosition(position);
}