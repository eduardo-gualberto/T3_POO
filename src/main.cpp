#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "ArquivoRanking.h"
#include "Meteoro.h"
#include "NaveInimiga.h"
#include "Item.h"
#include "Nave.hpp"
#include <sstream> //para imprimir coisas na tela
#include <iostream>
using namespace sf;

/*



            ESSA MAIN É EXPERIMENTAL
            SERVE PRA TESTAR O QUE FOI FEITO ATÉ ENTÃO



*/
void meteoro_tocou_nave(Meteoro &, Nave &, int &, bool, Clock &, Sound &);
void laser_tocou_nave(Laser &, Nave &, int &, Clock &);
void meteoro_saiu_da_tela(Meteoro &, int &, bool);
void dano(Clock, Sprite &);
void startMenu(RenderWindow *);
void mainGame(RenderWindow *);
void endMenu(RenderWindow *);

void startMenu(RenderWindow *window)
{

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

    SoundBuffer buffer;
    if (!buffer.loadFromFile("music/som_blaster.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound som;
    som.setBuffer(buffer);

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if (e.type == Event::Closed)
                window->close();
            if (e.type == Event::KeyPressed)
            {
                transition = true;
                dalpha_bg_txt = 3;
                text_alpha = bg_txt_alpha = 255;
                som.setVolume(50);
                som.play();
            }
        }

        text.setFillColor(Color(255, 255, 255, text_alpha -= 3));
        backgorund_txt.setColor(Color(255, 255, 255, bg_txt_alpha -= dalpha_bg_txt));
        if (!transition && text_alpha <= 70)
            text_alpha = 255;
        if (transition && text_alpha <= 10)
        {
            mainGame(window);
            return;
        }
        window->clear(Color(255, 255, 255));

        window->draw(backgorund);
        window->draw(backgorund_txt);
        window->draw(text);

        window->display();
    }
}

void endMenu(RenderWindow *window)
{

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

    SoundBuffer buffer_sabre;
    if (!buffer_sabre.loadFromFile("music/sabredeluz.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound sabre;
    sabre.setBuffer(buffer_sabre);

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if (e.type == Event::Closed)
                window->close();
            if (e.type == Event::KeyPressed)
            {
                transition = true;
                text2_alpha = 255;
                sabre.play();
            }
        }

        text2.setFillColor(Color(255, 255, 255, text2_alpha -= 3));
        if (!transition && text2_alpha <= 70)
            text2_alpha = 255;
        if (transition && text2_alpha <= 10)
            return;

        window->clear(Color(255, 255, 255));

        window->draw(backgorund);
        window->draw(text);
        window->draw(text2);

        window->display();
    }
}

//janela formada será de LARGURA x ALTURA
#define LARGURA 900
#define ALTURA 600

void mainGame(RenderWindow *window)
{
START:
    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Laser laserAliado1(ALIADO, 487.5, 450, 0, -20);
    Laser laserInimigo1(INIMIGO, 0, 0, 0, 8);
    Laser laserInimigo2(INIMIGO, 0, 0, 1, 7);
    Laser laserInimigo3(INIMIGO, 0, 0, -1, 7);
    Meteoro meteoro1(LARGURA / 2, 0, 0, 3);
    Meteoro meteoro2(LARGURA / 7, -500, 0, 3);
    Meteoro meteoro3(LARGURA / 5, -1000, 0, 3);
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
    Clock demage_aliado;
    Clock demage_inimigo;

    //sons usados no jogo
    /*                                                                          */
    SoundBuffer buffer_explosao;
    if (!buffer_explosao.loadFromFile("music/jogador_explode.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound explosao;
    explosao.setBuffer(buffer_explosao);

    SoundBuffer buffer_explosao_inimigo;
    if (!buffer_explosao.loadFromFile("music/inimigo_explode.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound explosao_inimigo;
    explosao_inimigo.setBuffer(buffer_explosao_inimigo);

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

    SoundBuffer buffer_tiroinimigo;
    if (!buffer_tiroinimigo.loadFromFile("music/inimigo_atira.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound som_tiroinimigo;
    som_tiroinimigo.setBuffer(buffer_tiroinimigo);
    /*                                                                          */

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if (e.type == Event::Closed)
                window->close();
        }
        if ((Keyboard::isKeyPressed(Keyboard::W)) || (Keyboard::isKeyPressed(Keyboard::Up)))
            nave.update(1);
        if ((Keyboard::isKeyPressed(Keyboard::S)) || (Keyboard::isKeyPressed(Keyboard::Down)))
            nave.update(2);
        if ((Keyboard::isKeyPressed(Keyboard::D)) || (Keyboard::isKeyPressed(Keyboard::Right)))
            nave.update(3);
        if ((Keyboard::isKeyPressed(Keyboard::A)) || (Keyboard::isKeyPressed(Keyboard::Left)))
            nave.update(4);

        // Atira o laser aliado
        if (laserAliado1.getPosition().y <= 0)
        {
            som_tiro.play();
            laserAliado1.setPosition(nave.getPosition().x + nave.getTexture()->getSize().x / 2, nave.getPosition().y);
            laserAliado1.update();
        }

        // Bloco que faz a nave inimiga atiraar
        if (laserInimigo1.getPosition().y >= ALTURA && laserInimigo2.getPosition().y >= ALTURA && laserInimigo3.getPosition().y >= ALTURA)
        {
            som_tiroinimigo.play();
            laserInimigo1.setPosition(inimigo.getPosition().x + inimigo.getTexture()->getSize().x / 2, inimigo.getPosition().y + inimigo.getTexture()->getSize().y);
            laserInimigo2.setPosition(inimigo.getPosition().x + inimigo.getTexture()->getSize().x / 2, inimigo.getPosition().y + inimigo.getTexture()->getSize().y);
            laserInimigo3.setPosition(inimigo.getPosition().x + inimigo.getTexture()->getSize().x / 2, inimigo.getPosition().y + inimigo.getTexture()->getSize().y);
            laserInimigo1.update();
            laserInimigo2.update();
            laserInimigo3.update();
        }

        //verifica se o inimigo n vai sair da tela
        if ((inimigo.getGlobalBounds().left > LARGURA - inimigo.getTexture()->getSize().x) || (inimigo.getGlobalBounds().left < 0))
            inimigo.SaiuDaTela();

        //verifica se os meteoros ja sairam da tela
        meteoro_saiu_da_tela(meteoro1, score, 0);
        meteoro_saiu_da_tela(meteoro2, score, 0);
        meteoro_saiu_da_tela(meteoro3, score, 0);
        meteoro_saiu_da_tela(meteoroE, score, 1);

        //verifca se os lasers tocaram na nave
        laser_tocou_nave(laserInimigo1, nave, lives, demage_aliado);
        laser_tocou_nave(laserInimigo2, nave, lives, demage_aliado);
        laser_tocou_nave(laserInimigo3, nave, lives, demage_aliado);

        //verifica se os meteoros tocaram na nave
        meteoro_tocou_nave(meteoro1, nave, lives, 0, demage_aliado, explosao);
        meteoro_tocou_nave(meteoro2, nave, lives, 0, demage_aliado, explosao);
        meteoro_tocou_nave(meteoro3, nave, lives, 0, demage_aliado, explosao);
        meteoro_tocou_nave(meteoroE, nave, lives, 1, demage_aliado, explosao);

        //verifca se o inimigo tocou na nave
        if (inimigo.getGlobalBounds().intersects(nave.getGlobalBounds()))
        {
            lives--;
            explosao_inimigo.play();
            demage_inimigo.restart();
            demage_aliado.restart();
            //implementar morte da nave inimiga
        }

        //verifca se os lasers tocaram na nave inimiga
        if (laserAliado1.getGlobalBounds().intersects(inimigo.getGlobalBounds()))
        {
            //implementar dano da nave inimiga
            score++;
            demage_inimigo.restart();
            laserAliado1.setPosition(-10000, -10000);
        }

        //contador para o item vida
        Time tempoPassado = clk.getElapsedTime();
        if (int(tempoPassado.asSeconds()) > 10)
        { //nova vida aparecera a cada 10 segundos
            clk.restart();
            ItemDesativado *= -1;
            vida.ItemAction(ItemDesativado);
        }

        //verifica se o jogador tocou na vida
        if (vida.getGlobalBounds().intersects(nave.getGlobalBounds()))
        {
            som_vida.play();
            lives++; //no lugar vai ser setlife de jogador
            vida.ItemCatch();
        }
        /*
        Time tempo_respawn = tempo_morto.getElapsedTime();
        if (int(tempo_respawn.asSeconds()) > 10)*/

        dano(demage_aliado, nave);
        dano(demage_inimigo, inimigo);

        //se as vidas acabaram o jogo termina
        if (lives <= 0)
        {
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
        laserAliado1.update();
        laserInimigo1.update();
        laserInimigo2.update();
        laserInimigo3.update();

        //imprimindo hud
        std::stringstream ss;
        ss << " -> Score:" << score << std::endl
           << " -> Lives:" << lives << std::endl;
        hud.setString(ss.str());

        window->clear(Color(255, 255, 255, 255));
        window->draw(backgorund);
        window->draw(laserAliado1);
        window->draw(laserInimigo1);
        window->draw(laserInimigo2);
        window->draw(laserInimigo3);
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

//funcao responsavel por verificar se o objeto deve
//ficar avermelhado (recebeu dano) ou voltar a cor normal
void dano(Clock tempo_demage, Sprite &sprite)
{
    Time tempo_dano = tempo_demage.getElapsedTime();
    if (int(tempo_dano.asMilliseconds()) < 100)
        sprite.setColor(Color(255, 0, 0, 250));
    else
        sprite.setColor(Color(255, 255, 255, 255));
}

void meteoro_saiu_da_tela(Meteoro &meteoro, int &score, bool especial)
{
    if (meteoro.getGlobalBounds().top > ALTURA)
    {
        meteoro.hit(especial);
        score++;
    }
}

void laser_tocou_nave(Laser &laser, Nave &nave, int &lives, Clock &demage_aliado)
{
    if (laser.getGlobalBounds().intersects(nave.getGlobalBounds()))
    {
        lives--;
        laser.setPosition(10000, 10000);
        demage_aliado.restart();
    }
}

void meteoro_tocou_nave(Meteoro &meteoro, Nave &nave, int &lives, bool especial, Clock &demage_aliado, Sound &explosao)
{
    if (meteoro.getGlobalBounds().intersects(nave.getGlobalBounds()))
    {
        if (especial)
            lives = lives - 3;
        else
            lives--;
        explosao.play();
        meteoro.hit(especial);
        demage_aliado.restart();
    }
}

int main()
{
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