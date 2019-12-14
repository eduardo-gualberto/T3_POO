#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Nave : public Sprite{
    public:
        Nave();
        void update(int dir);
    
    private:
        Vector2f position;
};
#include "Nave.cpp"