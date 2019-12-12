#include "Meteoro.h"
#include "Nave.h"

#include <sstream>  //para imprimir coisas na tela
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf; //usando namespace da biblioteca sfml 

//janela formada será de LARGURA x ALTURA
#define LARGURA 400     
#define ALTURA 800

int main()
{
    RenderWindow window(VideoMode(LARGURA, ALTURA), "Nave");

    int score = 0;
    int lives = 5;

    //Largura / 2 para elementos aparecerem no meio da tela
    Nave nave(LARGURA / 2, ALTURA - 50);
    Meteoro meteoro(LARGURA / 2, 1);
    Text hud;
    Font font;
    font.loadFromFile("Hack Regular Nerd Font Complete Mono.ttf");

    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        //window.background("avatar.png");
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // fechando
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            //esquerda
            nave.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            //direita
            nave.moveRight();
        }
        else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // fechando
            window.close();
        }

        // meteoro tocou em baixo
        if (meteoro.getPosition().top > ALTURA)
        {
            meteoro.hit();
            score++;
        }

        if (meteoro.getPosition().intersects(nave.getPosition()))
        {
            //meteoro tocou na nave
            lives--;
            meteoro.hit();

            if (lives < 1){
                std::cout << "FIM DE JOGO" << std::endl;
                exit (0);
            }
        }

        //calculando novas posições da nave e do meteoro
        meteoro.update();
        nave.update();

        // Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << std::endl << "Lives:" << lives << std::endl << "Speed:" << int(100*meteoro.Meteoro::getVelocity()) << "m/s";
        hud.setString(ss.str());

        // Clear everything from the last frame
        window.clear(Color(0, 0, 0, 255));

        window.draw(nave.getShape());

        window.draw(meteoro.getShape());

        // Draw our score
        window.draw(hud);

        // Show everything we just drew
        window.display();
    }

    return 0;
}