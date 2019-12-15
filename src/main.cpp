#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "ArquivoRanking.h"
#include "Meteoro.h"
#include "NaveInimiga.h"
#include "Item.h"
#include "Nave.hpp"
#include <sstream>  //para imprimir coisas na tela
#include <iostream>
using namespace sf;

/*



            ESSA MAIN É EXPERIMENTAL
            SERVE PRA TESTAR O QUE FOI FEITO ATÉ ENTÃO



*/

void startMenu(RenderWindow*);
void mainGame(RenderWindow*);
void endMenu(RenderWindow*);


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
        if(transition && text_alpha <= 10){
            mainGame(window);
            return;
        }
        window->clear(Color(255,255,255));

        window->draw(backgorund);
        window->draw(backgorund_txt);
        window->draw(text);

        window->display();
    }
    
}

void endMenu(RenderWindow* window){
    
    bool transition = false;

    Font font;
    font.loadFromFile("font_start_menu.ttf");
    Text text;
    text.setFont(font);
    text.setString("END OF JOURNEY, JEDI"); 
    text.setPosition(235, 272.5);
    text.setCharacterSize(30);
    float text2_alpha = 255;

    Text text2;
    text2.setFont(font);
    text2.setString("PRESS ANY KEY TO RESTART"); 
    text2.setPosition(235, 307.5);
    text2.setCharacterSize(20);

    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if(e.type == Event::Closed)
                window->close();
            if(e.type == Event::KeyPressed){
                transition = true;
                text2_alpha = 255;
            }
                
        }


        text2.setFillColor(Color(255,255,255,text2_alpha-=3));
        if(!transition && text2_alpha <= 70)
            text2_alpha = 255;
        if(transition && text2_alpha <= 10)
            return;

        window->clear(Color(255,255,255));

        window->draw(backgorund);
        window->draw(text);
        window->draw(text2);

        window->display();
    }
}


//janela formada será de LARGURA x ALTURA
#define LARGURA 900  
#define ALTURA 600

void mainGame(RenderWindow* window){
START:
    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Laser laser1(ALIADO, 400, 400, 6, 0);
    Laser laser2(INIMIGO, 350, 350, 7, 0);
    Meteoro meteoro1(LARGURA / 2, 0, 0, 2);
    Meteoro meteoro2(LARGURA / 7, -500, 0, 2);
    Meteoro meteoro3(LARGURA / 5, -1000, 0, 2);
    Meteoro meteoroE(LARGURA / 1.8, -2000, 1, 1);
    NaveInimiga inimigo(true, 1, 1, 1.5);
    Item vida(1);
    Nave nave;

    //Implementando hud
    Text hud;
    Font font;
    font.loadFromFile("font_start_menu.ttf");
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(sf::Color::White);
    //variaveis
    int score = 0;
    int lives = 5;
    int ItemDesativado = 1;
    Clock clk;

    SoundBuffer buffer_explosao;
    if (!buffer_explosao.loadFromFile("music/jogador_explode.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound explosao;
    explosao.setBuffer(buffer_explosao);

    SoundBuffer buffer_vida;
    if (!buffer_vida.loadFromFile("music/vida.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound som_vida;
    som_vida.setBuffer(buffer_vida);

    SoundBuffer buffer_tiro;
    if (!buffer_tiro.loadFromFile("music/jogador_atira.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound som_tiro;
    som_tiro.setBuffer(buffer_tiro);

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if(e.type == Event::Closed)
                window->close();
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
            nave.update(1);
        if (Keyboard::isKeyPressed(Keyboard::S))
            nave.update(2);
        if (Keyboard::isKeyPressed(sf::Keyboard::D))
            nave.update(3);
        if (Keyboard::isKeyPressed(sf::Keyboard::A))
            nave.update(4);

        if ((inimigo.getGlobalBounds().left > LARGURA) || (inimigo.getGlobalBounds().left < 0)){
            inimigo.SaiuDaTela();
        }
        if (meteoro1.getGlobalBounds().top > ALTURA)
        {
            meteoro1.hit(0);
            score++;        //no lugar vai ser setscore de jogador
        }
        if (meteoro2.getGlobalBounds().top > ALTURA)
        {
            meteoro2.hit(0);
            score++;        //no lugar vai ser setscore de jogador
        }
        if (meteoro3.getGlobalBounds().top > ALTURA)
        {
            meteoro3.hit(0);
            score++;        //no lugar vai ser setscore de jogador
        }
        if (meteoroE.getGlobalBounds().top > ALTURA)
        {
            meteoroE.hit(1);
            score++;        //no lugar vai ser setscore de jogador
        }

        //meteoro tocou na nave
        if (meteoro1.getGlobalBounds().intersects(nave.getGlobalBounds())){
            lives--;        //no lugar vai ser setlife de jogador
            explosao.play();
            meteoro1.hit(0);
        }
        if (meteoro2.getGlobalBounds().intersects(nave.getGlobalBounds())){
            lives--;        //no lugar vai ser setlife de jogador
            explosao.play();
            meteoro2.hit(0);
        }
        if (meteoro3.getGlobalBounds().intersects(nave.getGlobalBounds())){
            lives--;        //no lugar vai ser setlife de jogador
            explosao.play();
            meteoro3.hit(0);
        }
        if (meteoroE.getGlobalBounds().intersects(nave.getGlobalBounds())){
            lives = lives - 5;//no lugar vai ser setlife de jogador
            explosao.play();
            meteoroE.hit(1);
        }
        Time tempoPassado = clk.getElapsedTime();
        if (int(tempoPassado.asSeconds()) > 10){    //nova vida aparecera a cada 10 segundos
            clk.restart();
            ItemDesativado *= -1;
            vida.ItemAction(ItemDesativado);
        }
        if (vida.getGlobalBounds().intersects(nave.getGlobalBounds())){
            som_vida.play();
            lives++;        //no lugar vai ser setlife de jogador
            vida.ItemCatch();
        }
        if(lives <= 0){
            explosao.play();
            endMenu(window);
            goto START;
        }

        vida.update();
        meteoro1.update();
        meteoro2.update();
        meteoro3.update();
        meteoroE.update();
        inimigo.update();
        laser1.update();
        laser2.update();

        if(laser1.getPosition().x > LARGURA){
            som_tiro.play();
            laser1.setPosition(0, ALTURA/2);
        }
        if(laser1.getPosition().y > ALTURA){
            som_tiro.play();
            laser1.setPosition(LARGURA, 0);
        }
        if(laser2.getPosition().x > LARGURA){
            som_tiro.play();
            laser2.setPosition(0, ALTURA/2);
        }
        if(laser2.getPosition().y > ALTURA){
            som_tiro.play();
            laser2.setPosition(LARGURA, 0);
        }

        //imprimindo hud
        std::stringstream ss;
        ss << " -> Score:" << score << std::endl << " -> Lives:" << lives << std::endl
           << "Speed: " << int(meteoro1.Meteoro::getVelocity())*10 << "X" << std::endl;
        hud.setString(ss.str());
        
        window->clear(Color(255,255,255,255));
        window->draw(backgorund);
        window->draw(laser1);
        window->draw(laser2);
        window->draw(meteoro1);
        window->draw(meteoro2);
        window->draw(meteoro3);
        window->draw(meteoroE);
        window->draw(vida);
        window->draw(inimigo);
        window->draw(nave);
        window->draw(hud);

        window->display();
    }
}

int main(){

    RenderWindow window(VideoMode(LARGURA, ALTURA), "Teste!");
    window.setFramerateLimit(60);
    Music music;
    if (!music.openFromFile("music/music.ogg"))
        std::cout << "Não foi possível abrir arquivo de música" << std::endl;
    music.play();
    music.setVolume(70);
    music.setLoop(true);

    startMenu(&window);
    return 0;
}