#include <SFML/Graphics.hpp>

using namespace sf;

int main(){

    RenderWindow window(VideoMode(500, 500), "Teste!");

    CircleShape circle(100.f);
    circle.setFillColor(Color(0,0,0));

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }
        
        window.clear(Color(255,255,255));

        window.draw(circle);

        window.display();
    }
    


    return 0;
}