#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
 
class Item : public Sprite
{
    public:
        Item(int tipo);
        void ItemAction(int desativado);
        void ItemCatch();
        void update();
    private:
        Vector2f position;    
}; 

#include "Item.cpp"
