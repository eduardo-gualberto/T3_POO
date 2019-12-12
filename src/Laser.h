#pragma once

#include <SFML/Graphics.hpp>

#define ALIADO 1
#define INIMIGO 2

using namespace sf;

class Laser : public Sprite{
    private:
        float dx, dy;
    public:
        Laser(int, float, float, float, float);
        ~Laser(){}
        void update();
};

#include "Laser.cpp"