#pragma once
#include "Meteoro.h"
#include "time.h"

#define LARGURA 900
#define MAXVEL 15       //velocidade maxima do meteoro

Meteoro::Meteoro(float startX, float startY, bool especial, float Velocity):
Velocity(Velocity)
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
    srand(time(NULL));
    position.y = -1000;
    position.x = rand() % LARGURA;
    if (Velocity < MAXVEL){ //os meteoros possuem uma velocidade max
        if (especial)           //meteoro especial tem velocidade diferente
        	Velocity *= 1.02;	//aumenta velocidade em 2%
        else
        	Velocity *= 1.05;   //aumenta velocidade em 5%
    }
    else
        Velocity = MAXVEL;
    this->setPosition(position);
}

void Meteoro::update()
{
    this->move(0,Velocity);
}
