#pragma once
#include "Nave.hpp"
using namespace sf;
Nave::Nave(){
    Texture* texture = new Texture();
    texture->loadFromFile("/home/lucas/Desktop/JOGO/xwingsprite.png");
    this->setPosition(450,450);
    this->setTexture(*texture);
}
void Nave::update(int dir){
    switch(dir){
        case(1): //Eixo y para cima
            this->move(0,-20);
            break;
        case (2):
            this->move(0,20);  //Eixo y para baixo;
            break;
        case(3):
            this->move(20,0); //Eixo x para a direita;
            break;
        case(4):
            this->move(-20,0); //Eixo y para a esquerda;
            break;
    }

}