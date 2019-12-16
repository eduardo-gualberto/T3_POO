#pragma once
#include "NaveInimiga.h"
#include "time.h"
#define LARGURA 900

NaveInimiga::NaveInimiga(bool alive, int life, float x, float y, float speed):
life(life), speed(speed) {

    alive = true;

    position.x = x;
    position.y = y;

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

void NaveInimiga::respawn() {
    alive = true;

    srand(time(NULL));
    position.y = 0;
    position.x = rand() % (LARGURA-this->getTexture()->getSize().x);

    this->setPosition(position);
}

int NaveInimiga::getLife() {
    return life;
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
