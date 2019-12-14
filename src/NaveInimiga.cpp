#pragma once
#include "NaveInimiga.h"

NaveInimiga::NaveInimiga(bool alive, float x, float y, float sp) {

    alive = true;

    position.x = x;
    position.y = y;

    sp = speed;

    Texture *texture = new Texture();
    // imagem da aliada para testes
    texture->loadFromFile("img/xwingsprite.png");

    this->setTexture(*texture);
    this->setPosition(position);
}

bool NaveInimiga::isAlive() {
    return alive;
}

void NaveInimiga::die() {
    alive = false;
}
/*
void NaveInimiga::update(int direcao, Time elapsedTime) {
    this->move(direcao * speed * elapsedTime.asSeconds(), 0.f);
}
*/