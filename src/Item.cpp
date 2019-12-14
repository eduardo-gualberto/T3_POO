#pragma once
#include "Item.h"
#include "time.h"

#define LARGURA 900
#define ALTURA 600

Item::Item(int tipo)
{
    srand(time(NULL));
    position.x = -1000;
    position.y = -1000;
    Texture *texture = new Texture();
    if (tipo == 1)
        texture->loadFromFile("img/vida.png");
    this->setTexture(*texture);
    this->setPosition(position);
}

void Item::ItemAction(int desativado)
{
    srand(time(NULL));
    if (desativado == 1){
        position.y = -1000;
        position.x = -1000;
    }
    else{
        position.x = rand() % LARGURA;
        position.y = rand() % ALTURA;
    }
    this->setPosition(position);
}

void Item::ItemCatch(){
    position.y = -1000;
    position.x = -1000;
    this->setPosition(position);
}

void Item::update()
{
    this->move(0, 0);
}