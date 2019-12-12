#include <SFML/Graphics.hpp>
#include "Laser.h"
using namespace sf;

/*



            ESSA MAIN É EXPERIMENTAL
            SERVE PRA TESTAR O QUE FOI FEITO ATÉ ENTÃO



*/

int main(){

    RenderWindow window(VideoMode(500, 500), "Teste!");

    Laser laser1(ALIADO, 400, 400, 2, 0);
    Laser laser2(INIMIGO, 350, 350, -2, -2);

    CircleShape circle(100.f);
    circle.setFillColor(Color(0,0,0));

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
            if(e.type == Event::KeyPressed){
                switch(e.key.code){
                    case Keyboard::Down:
                        laser1.update(); break;
                    case Keyboard::Up:
                        laser2.update(); break;
                }
            }
        }
        
        window.clear(Color(255,255,255));

        window.draw(circle);
        window.draw(laser1);
        window.draw(laser2);

        window.display();
    }
    


    return 0;
}