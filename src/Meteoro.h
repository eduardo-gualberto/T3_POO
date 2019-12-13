#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
 
class Meteoro : public Sprite
{
    public:
        Meteoro(float startX, float startY);
        void hit();
        void update();
        float getVelocity();
    private:
        Vector2f position;
        float Velocity = .4f;
        float startX, startY;
}; 

#include "Meteoro.cpp"
