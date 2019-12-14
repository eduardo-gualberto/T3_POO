#pragma once

#include <SFML/Graphics.hpp>
#include "Laser.h"
using namespace sf;


class NaveInimiga : public Sprite {
    public:
        NaveInimiga(bool alive, float x, float y, float sp);

        bool isAlive();
        void die();
        //void shoot(); A implementar
        void update(int direcao, Time elapsedTime);
    private:
        float speed;
        bool alive;
        Vector2f position;
};

#include "NaveInimiga.cpp"