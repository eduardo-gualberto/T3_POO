#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
 
class Meteoro : public Sprite
{
    public:
        Meteoro(float startX, float startY);
        FloatRect getPosition();
        void hit();
        void update();
        float getVelocity();
    private:
        Vector2f position;
        Sprite MeteoroShape;
        float Velocity = .4f;
}; 

/*
    Metodo getPosition() sobescreve o da classe Sprite, nao é interessante
    this->getGlobalBounds() já é um método de Sprite, não precisa fazer outro metodo so pra retornar ele
    
    position é um atributo. atribuir valores diferentes a ele, nao muda a posicao do sprite na tela. Pra
isso é necessário usar os métodos move() ou setPosition().

    Gostei do jeito de acelerar o meteoro.

*/