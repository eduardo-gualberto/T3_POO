#pragma once
#include "NaveInimiga.h"

NaveInimiga::NaveInimiga(bool alive, float x, float y, float speed):
speed(speed) {

    alive = true;

    position.x = x;
    position.y = y;

    //sp = speed;

    Texture *texture = new Texture();
    // imagem da aliada para testes
    texture->loadFromFile("img/nave_inimiga.png");

    this->setTexture(*texture);
    this->setPosition(position);
}

bool NaveInimiga::isAlive() {
    return alive;
}

void NaveInimiga::die() {
    alive = false;
}

float NaveInimiga::getSpeed(){
    return speed;
}

void NaveInimiga::SaiuDaTela(){
    speed = speed * (-1);
    //position.x *= speed;
    //this->setPosition(position);
    this->move(speed,0);
}
void NaveInimiga::update() {
    this->move(speed,0);
}
