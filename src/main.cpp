#include <SFML/Graphics.hpp>
#include "Laser.h"
using namespace sf;

/*



            ESSA MAIN É EXPERIMENTAL
            SERVE PRA TESTAR O QUE FOI FEITO ATÉ ENTÃO



*/

void startMenu(RenderWindow* window){
    
    bool transition = false;

    Font font;
    font.loadFromFile("font_start_menu.ttf");
    Text text;
    text.setFont(font);
    text.setString("PRESS ANY KEY TO START"); 
    text.setPosition(235, 272.5);
    text.setCharacterSize(30);
    float text_alpha = 255;

    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Texture backgorund_txt_img;
    backgorund_txt_img.loadFromFile("img/start_menu_txt_bg.png");

    Sprite backgorund_txt(backgorund_txt_img);
    backgorund_txt.setScale(12.5, 4.5);
    backgorund_txt.setPosition(160, 255);
    float bg_txt_alpha = 255;
    float dalpha_bg_txt = 0;
    
    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if(e.type == Event::Closed)
                window->close();
            if(e.type == Event::KeyPressed){
                transition = true;
                dalpha_bg_txt = 3;
                text_alpha = bg_txt_alpha = 255;
            }
                
        }


        text.setFillColor(Color(255,255,255,text_alpha-=3));
        backgorund_txt.setColor(Color(255,255,255,bg_txt_alpha-=dalpha_bg_txt));
        if(!transition && text_alpha <= 70)
            text_alpha = 255;
        if(transition && text_alpha <= 10)
            return;
        window->clear(Color(255,255,255));

        window->draw(backgorund);
        window->draw(backgorund_txt);
        window->draw(text);

        window->display();
    }
    
}


int main(){

    RenderWindow window(VideoMode(900, 600), "Teste!");
    window.setFramerateLimit(60);

    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Laser laser1(ALIADO, 400, 400, 2, 0);
    Laser laser2(INIMIGO, 350, 350, -2, -2);

    CircleShape circle(100.f);
    circle.setFillColor(Color(255,255,255));

    startMenu(&window);

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
        window.draw(backgorund);

        window.draw(circle);
        window.draw(laser1);
        window.draw(laser2);

        window.display();
    }
    


    return 0;
}