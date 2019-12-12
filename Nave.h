#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Nave
{
    public:
        Nave(float startX, float startY);
        FloatRect getPosition();
        RectangleShape getShape();
        void moveLeft();
        void moveRight();
        void update();
    private:
        Vector2f position;
        RectangleShape naveShape;
        float naveSpeed = .4f;  //velocidade de 0.4
};