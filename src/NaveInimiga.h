#pragma once

#include <SFML/Graphics.hpp>
#include "Laser.h"
using namespace sf;


class NaveInimiga : public Sprite {
    public:
        NaveInimiga(bool alive, float x, float y, float speed);

        bool isAlive();
        void die();
        void SaiuDaTela();
        //void shoot(); A implementar
        void update();
        float getSpeed();
    private:
        float speed;
        bool alive;
        Vector2f position;
};

#include "NaveInimiga.cpp"