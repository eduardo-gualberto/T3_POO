#pragma once
#include "Nave.hpp"
using namespace sf;
Nave::Nave(){
    Texture* texture = new Texture();
    texture->loadFromFile("img/xwingsprite.png");
    this->setPosition(450,450);
    this->setTexture(*texture);
}
void Nave::update(int dir){
    Vector2f pos = this->getPosition();
    int px = pos.x;
    int py = pos.y;
    switch(dir){
        case(1): //Eixo y para cima
            if(py >= 0){
                this->move(0,-10);
                break;
            }else{
                this->move(0,0);
                break;
            }
        case (2):
            if(py + this->getTexture()->getSize().y <= 595){
                this->move(0,10);  //Eixo y para baixo;
                break;
            }else{
                this->move(0,0);
                break;
            }
        case(3):
            if(px + this->getTexture()->getSize().x <= 900){
                this->move(10,0); //Eixo x para a direita;
                break;
            }else{
                this->move(0,0);
                break;
            }
        case(4):
            if(px>=0){
                this->move(-10,0); //Eixo x para a esquerda;
                break;
            }else{
                this->move(0,0);
                break;
            }
            
    }

}
