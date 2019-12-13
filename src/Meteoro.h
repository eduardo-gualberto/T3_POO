#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
 
class Meteoro : public Sprite
{
    public:
        Meteoro(float startX, float startY, bool especial);
        void hit(bool especial);
        void update();
        float getVelocity();
    private:
        Vector2f position;
        float startX, startY;
    	float Velocity = 2;
        
}; 

#include "Meteoro.cpp"
