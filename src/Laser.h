#pragma once

#include <SFML/Graphics.hpp>

#define ALIADO 1
#define INIMIGO 2
#define DX 5
#define DY 5

using namespace sf;

class Laser : public Sprite{
    private:
        float dx, dy;
    public:
        Laser(int, float, float);
        ~Laser(){}
        void update();
};