#pragma once

#include <SFML/Graphics.hpp>
#include "Laser.h"
using namespace sf;


class NaveInimiga : public Sprite {
    public:
        NaveInimiga(bool alive, int life, float x, float y, float speed);

        bool isAlive();
        void die();
        void SaiuDaTela();
        void update();
        float getSpeed();
        int getLife();
        void respawn();
    private:
        int life;
        float speed;
        bool alive;
        Vector2f position;
};

#include "NaveInimiga.cpp"