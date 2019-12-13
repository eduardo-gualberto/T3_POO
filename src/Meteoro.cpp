#pragma once
#include "Meteoro.h"
#include "time.h"

#define LARGURA 900

Meteoro::Meteoro(float startX, float startY, bool especial)
{
    position.x = startX;
    position.y = startY;

    Texture* texture = new Texture();
    if (especial)
    	texture->loadFromFile("img/meteoro_grande.png");
    else
    	texture->loadFromFile("img/meteoro.png");

    this->setPosition(position);
    this->setTexture(*texture);
}

float Meteoro::getVelocity(){
    return Velocity;
}

void Meteoro::hit(bool especial) //meteoro "bateu no chao" ou encostou na nave
{
    position.y = -1000;
    position.x = rand() % LARGURA;
    if (especial)
    	Velocity = 1;	//meteoro especial tem velocidade fixa
    else
    	Velocity *= 1.01; //aumenta velocidade em 1%
    this->setPosition(position);
}

void Meteoro::update()
{
    position.y += Velocity;
    this->setPosition(position);
}
