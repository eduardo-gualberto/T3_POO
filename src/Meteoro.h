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
