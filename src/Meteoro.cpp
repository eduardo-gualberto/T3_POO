#pragma once
#include "Meteoro.h"
#include "time.h"

#define LARGURA 500

Meteoro::Meteoro(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    Texture* texture = new Texture();

    texture->loadFromFile("../img/meteoro.png");

    this->setPosition(position);
    this->setTexture(*texture);
}

float Meteoro::getVelocity(){
    return Velocity;
}

void Meteoro::hit() //meteoro "bateu no chao" ou encostou na nave
{
    position.y = 1;
    position.x = rand() % LARGURA;
    this->setPosition(position);
}

void Meteoro::update()
{
    Velocity += Velocity / 100; //aumenta velocidade gradativamente
    position.y += Velocity;
    this->setPosition(position);
}
