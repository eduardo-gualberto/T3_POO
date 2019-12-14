#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "Meteoro.h"
#include "NaveInimiga.h"
#include "Item.h"
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
#define LARGURA 900 //obs: ao mudar largura deve-se mudar #define largura de meteoro.cpp    
#define ALTURA 600



void mainGame(RenderWindow* window){
START:
    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Laser laser1(ALIADO, 400, 400, 6, 0);
    Laser laser2(INIMIGO, 350, 350, 7, 0);

    Meteoro meteoro1(LARGURA / 2, 0, 0, 2);//iniciando meteoro no centro superior da tela
    Meteoro meteoro2(LARGURA / 7, -500, 0, 2);
    Meteoro meteoro3(LARGURA / 5, -1000, 0, 2);
    Meteoro meteoroE(LARGURA / 1.8, -2000, 1, 1);//meteoro especial
    NaveInimiga inimigo(true, 0, 0, 1.0);

    Item vida(1);
/*
    CircleShape circle(100.f);
    circle.setFillColor(Color(255,255,255));
*/
    //Implementando hud
    Text hud;
    Font font;
    font.loadFromFile("font_start_menu.ttf");
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(sf::Color::White);
    int score = 0;  //pontuação do jogador
    int lives = 50;  //vidas do jogador
    int ItemDesativado = 1;
    Clock clk;
    Clock ClockInimigo;
    int direcao = 1;
    int x = inimigo.getPosition().x;
    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if(e.type == Event::Closed)
                window->close();
            /*if(e.type == Event::KeyPressed){
                switch(e.key.code){
                    case Keyboard::Down:
                        laser1.update(); break;
                    case Keyboard::Up:
                        laser2.update(); break;
                }
            }*/
        }

        // Tentativa de fazer a nave inimiga ir e voltar(protótipo ainda errado) - método de update
        if(ClockInimigo.getElapsedTime().asSeconds() > 1.0f) {
            if(x >= LARGURA)
                direcao = -1;
            if(x <= 0)
                direcao = 1;
            inimigo.move(10 * direcao * ClockInimigo.getElapsedTime().asSeconds(), 0.f);
            ClockInimigo.restart().asSeconds();
            x = inimigo.getPosition().x;
        }

        if (meteoro1.getGlobalBounds().top > ALTURA)
        {
            meteoro1.hit(0);
            lives--;
            score++;
        }
        if (meteoro2.getGlobalBounds().top > ALTURA)
        {
            meteoro2.hit(0);
            lives--;
            score++;
        }
        if (meteoro3.getGlobalBounds().top > ALTURA)
        {
            meteoro3.hit(0);
            lives--;
            score++;
        }
        if (meteoroE.getGlobalBounds().top > ALTURA)
        {
            meteoroE.hit(1);
            lives = lives - 5;
            score++;
        }
/*
    Funcionará quando a nave for implementada
        //meteoro tocou na nave
        if (meteoro.getGlobalBounds().intersects(nave.getGlobalBounds())){
            lives--;
            meteoro.hit();
        }
*/
        if(lives == 0){
            endMenu(window);
            goto START;
        }

        Time tempoPassado = clk.getElapsedTime();
        std::cout << int(tempoPassado.asSeconds()) << std::endl;
        if (int(tempoPassado.asSeconds()) > 10){    //nova vida aparecera a cada 10 segundos
            clk.restart();
            ItemDesativado *= -1;
            vida.ItemAction(ItemDesativado);
        }
        /*if (vida.getGlobalBounds().intersects(nave.getGlobalBounds())){
            lives++;
            vida.ItemCatch();
        }*/
        vida.update();

        meteoro1.update();
        meteoro2.update();
        meteoro3.update();
        meteoroE.update();

        laser1.update();
        laser2.update();

        if(laser1.getPosition().x > LARGURA)
            laser1.setPosition(0, ALTURA/2);
        if(laser1.getPosition().y > ALTURA)
            laser1.setPosition(LARGURA, 0);

        if(laser2.getPosition().x > LARGURA)
            laser2.setPosition(0, ALTURA/2);
        if(laser2.getPosition().y > ALTURA)
            laser2.setPosition(LARGURA, 0);

        //imprimindo hud
        std::stringstream ss;
        ss << " -> Score:" << score << std::endl << " -> Lives:" << lives << std::endl << std::endl
           << " Speed1:" << int(100*meteoro1.Meteoro::getVelocity()) << "m/s" << std::endl
           << " Speed2:" << int(100*meteoro2.Meteoro::getVelocity()) << "m/s" << std::endl
           << " Speed3:" << int(100*meteoro3.Meteoro::getVelocity()) << "m/s" << std::endl
           << " SpeedE:" << int(100*meteoroE.Meteoro::getVelocity()) << "m/s" << std::endl;
        hud.setString(ss.str());
        
        window->clear(Color(255,255,255,255));
        window->draw(backgorund);
        //window->draw(circle);
        window->draw(laser1);
        window->draw(laser2);
        window->draw(meteoro1);
        window->draw(meteoro2);
        window->draw(meteoro3);
        window->draw(meteoroE);
        window->draw(vida);
        window->draw(inimigo);
        window->draw(hud);

        window->display();
    }
}

/*
    DIMINUI A MAIN, AGORA ELA SO FAZ A CHAMADA DE STARTMENU, QUE COMEÇA O GAME
    A IDEIA É AGORA DIVIDIR OS ARQUIVOS, FAZER UM ARQUIVO SÓ PARA ENDMENU
    OUTRO SO PARA MAINGAME E DA MESMA FORMA PRA STARTMENU

    VAI FICAR MAIS FACIL DE PROCURAR E ENTENDER O CODIGO
*/





int main(){

    RenderWindow window(VideoMode(LARGURA, ALTURA), "Teste!");
    window.setFramerateLimit(60);
    Music music;
    if (!music.openFromFile("music/music.ogg"))
        std::cout << "Não foi possível abrir arquivo de música" << std::endl;
    music.play();
    music.setLoop(true);

    startMenu(&window);
   

    return 0;
}