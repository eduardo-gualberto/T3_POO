#include "Laser.h"

Laser::Laser(int tipo, float x, float y){
    Texture* txtr = new Texture();
    if(tipo == ALIADO) txtr->loadFromFile("../img/laser_aliado.png");
    if(tipo == INIMIGO) txtr->loadFromFile("../img/laser_inimigo.png");
    this->setTexture(*txtr);
    this->setPosition(x, y);
    dx = DX; dy = DY;
}