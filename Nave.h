#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Nave : public Sprite
{
    public:
        Nave(float startX, float startY);
        float getSpeed();
        void moveLeft();
        void moveRight();
        void update();
    private:
        Vector2f* position;
        float naveSpeed = .4f;  //velocidade de 0.4
};