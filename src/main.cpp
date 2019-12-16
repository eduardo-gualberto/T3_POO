#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "Meteoro.h"
#include "Jogador.h"
#include "NaveInimiga.h"
#include "Item.h"
#include "Nave.hpp"
#include <sstream> //para imprimir coisas na tela
#include <iostream>
#include <vector>
#include <algorithm>
using namespace sf;


void meteoro_tocou_nave(Meteoro &, Nave &, Jogador&, bool, Clock &, Sound &);
void laser_tocou_nave(Laser &, Nave &, Jogador&, Clock &);
void meteoro_saiu_da_tela(Meteoro &, Jogador&, bool);
void dano(Clock, Sprite &);
void showLeaderBoard(RenderWindow *);
void startMenu(RenderWindow *);
void mainGame(RenderWindow *);
void endMenu(RenderWindow *);
void writeFile(std::string, Jogador);
std::vector<Jogador> readFile(std::string);
std::vector<Jogador> getRanking(std::string);



void writeFile(std::string fileName, Jogador data){
    std::ofstream file(fileName.c_str(), std::ios::binary | std::ios::app);
    if(file){
        file.write(reinterpret_cast<char*>(&data), sizeof(Jogador));
    }
    file.close();
}

std::vector<Jogador> readFile(std::string fileName){
    std::ifstream file(fileName.c_str(), std::ios::binary);
    Jogador aux;
    std::vector<Jogador> data; 
    if(file){
        file.read(reinterpret_cast<char*>(&aux), sizeof(Jogador));
        while (file.good()){
            data.push_back(aux);
            file.read(reinterpret_cast<char*>(&aux), sizeof(Jogador));
        }
    }
    file.close();
    return data;
}

std::vector<Jogador> getRanking(std::string fileName){
    std::vector<Jogador> file_content = readFile(fileName);
    std::sort(file_content.begin(), file_content.end(), Jogador::comparaScore);
    return file_content;
}

void showLeaderBoard(RenderWindow* window){
    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Font font;
    font.loadFromFile("font_start_menu.ttf");

    Text text;
    text.setFont(font);
    text.setString("LEADERBOARD");
    text.setPosition(335, 40);
    text.setCharacterSize(30);

    Text text2;
    text2.setFont(font);
    text2.setString("QUIT [ESC]");
    text2.setPosition(40, ALTURA - 30);
    text2.setCharacterSize(20);

    std::vector<Jogador> ranking = getRanking("io_files/data_base.dat");
    int n = ranking.size();
    Text scores[n];

    for(int i = 0; i < ranking.size(); i++){
        std::string id = std::to_string(i + 1);
        std::string points = std::to_string(ranking[i].getScore());
        std::string str = "ID: " + id + " Score: " + points;
        scores[i].setFont(font);
        scores[i].setString(str);
        scores[i].setCharacterSize(20);
        scores[i].setPosition(335, (i + 2) * 40);
    }


    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if(e.type == Event::Closed)
                window->close();
            if(e.type == Event::KeyPressed){
                if(e.key.code == Keyboard::Escape)
                    return;
            }
        }
        
    window->clear(Color(255,255,255));

    window->draw(backgorund);
    window->draw(text);
    window->draw(text2);
    for(int i = 0; i < ranking.size(); i++)
        window->draw(scores[i]);
    
    window->display();
    }

}

void startMenu(RenderWindow *window)
{

    bool transition = false;

    Font font;
    font.loadFromFile("font_start_menu.ttf");
    Text text;
    text.setFont(font);
    text.setString("PRESS 'SPACEBAR' TO START");
    text.setPosition(235, 272.5);
    text.setCharacterSize(30);
    float text_alpha = 255;

    Text text2;
    text2.setFont(font);
    text2.setString("LEADERBOARD [TAB]");
    text2.setPosition(40, ALTURA - 30);
    text2.setCharacterSize(20);

    Texture backgorund_img;
    backgorund_img.loadFromFile("img/space_bg.jpg");

    Sprite backgorund(backgorund_img);
    backgorund.setScale(.475, .7);

    Texture backgorund_txt_img;
    backgorund_txt_img.loadFromFile("img/start_menu_txt_bg.png");

    Sprite backgorund_txt(backgorund_txt_img);
    backgorund_txt.setScale(14, 4.5);
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
                switch (e.key.code)
                {
                case Keyboard::Space:{
                    transition = true;
                    dalpha_bg_txt = 3;
                    text_alpha = bg_txt_alpha = 255;
                    som.setVolume(50);
                    som.play();
                    break;
                }
                case Keyboard::Tab:
                    showLeaderBoard(window);
                }
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
        window->draw(text2);

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
    text.setString("END OF JOURNEY,");
    text.setPosition(235, 272.5);
    text.setCharacterSize(30);
    float text2_alpha = 255;

    Text text2;
    text2.setFont(font);
    text2.setString("PRESS 'SPACEBAR' TO RESTART");
    text2.setPosition(235, 307.5);
    text2.setCharacterSize(20);

    Text text3;
    text3.setFont(font);
    text3.setString("LEADERBOARD [TAB]");
    text3.setPosition(40, ALTURA - 30);
    text3.setCharacterSize(20);

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
                if(e.key.code == Keyboard::Space){
                    transition = true;
                    text2_alpha = 255;
                    sabre.play();
                }
                else if(e.key.code == Keyboard::Tab)
                    showLeaderBoard(window);
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
        window->draw(text3);

        window->display();
    }
}


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
    NaveInimiga inimigo(true, 100,  1, 1, 1.5);
    Item vida(1);
    Nave nave;

    //Implementando hud
    Text hud;
    Font font;
    font.loadFromFile("font_start_menu.ttf");
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(sf::Color::White);

    Jogador jogador;
    int ItemDesativado = 1;
    int vidaInimigo = inimigo.getLife();
    Clock clk;
    Clock respawnInimigo;
    Clock demage_aliado;
    Clock demage_inimigo;

    //sons usados no jogo
    /*                                                                          */
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

    SoundBuffer buffer_tiroinimigo;
    if (!buffer_tiroinimigo.loadFromFile("music/inimigo_atira.ogg"))
        std::cout << "Não foi possível abrir arquivo de áudio" << std::endl;
    Sound som_tiroinimigo;
    som_tiroinimigo.setBuffer(buffer_tiroinimigo);
    /*                                                                          */

    // Rotacionando laser:
    laserInimigo2.rotate(345);
    laserInimigo3.rotate(15);

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
        if (laserInimigo1.getPosition().y >= ALTURA && laserInimigo2.getPosition().y >= ALTURA && laserInimigo3.getPosition().y >= ALTURA && inimigo.isAlive())
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
        meteoro_saiu_da_tela(meteoro1, jogador, 0);
        meteoro_saiu_da_tela(meteoro2, jogador, 0);
        meteoro_saiu_da_tela(meteoro3, jogador, 0);
        meteoro_saiu_da_tela(meteoroE, jogador, 1);

        //verifca se os lasers tocaram na nave
        laser_tocou_nave(laserInimigo1, nave, jogador, demage_aliado);
        laser_tocou_nave(laserInimigo2, nave, jogador, demage_aliado);
        laser_tocou_nave(laserInimigo3, nave, jogador, demage_aliado);

        //verifica se os meteoros tocaram na nave
        meteoro_tocou_nave(meteoro1, nave, jogador, 0, demage_aliado, explosao);
        meteoro_tocou_nave(meteoro2, nave, jogador, 0, demage_aliado, explosao);
        meteoro_tocou_nave(meteoro3, nave, jogador, 0, demage_aliado, explosao);
        meteoro_tocou_nave(meteoroE, nave, jogador, 1, demage_aliado, explosao);

        //verifca se o inimigo tocou na nave
        if (inimigo.getGlobalBounds().intersects(nave.getGlobalBounds()))
        {
            jogador.fault(1);
            explosao.play();
            demage_inimigo.restart();
            demage_aliado.restart();
        }

        //verifca se os lasers tocaram na nave inimiga
        if (laserAliado1.getGlobalBounds().intersects(inimigo.getGlobalBounds()))
        {
            if(vidaInimigo <= 0) {
            	explosao.play();
                jogador.scored(100);
                inimigo.die();
                inimigo.setPosition(0, -1000);
            } else {
                vidaInimigo = vidaInimigo - 10;
            }
            jogador.scored(1);
            demage_inimigo.restart();
            laserAliado1.setPosition(-10000, -10000);
        }

        // Tempo de respawn do inimigo (Aumentar/Diminuir, altere 10)
        Time tempoRespawn = respawnInimigo.getElapsedTime();
        if(!inimigo.isAlive()) {
            if(int(tempoRespawn.asSeconds()) > 10) {
                respawnInimigo.restart();
                vidaInimigo = 100;
                inimigo.respawn();
            }
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
            jogador.heal(1);
            vida.ItemCatch();
        }

        dano(demage_aliado, nave);
        dano(demage_inimigo, inimigo);

        //se as vidas acabaram o jogo termina
        if (jogador.getLives() <= 0)
        {
            writeFile("io_files/data_base.dat", jogador);
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
        ss << " -> Score:" << jogador.getScore() << std::endl
           << " -> Lives:" << jogador.getLives() << std::endl;
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

void meteoro_saiu_da_tela(Meteoro &meteoro, Jogador& j, bool especial)
{
    if (meteoro.getGlobalBounds().top > ALTURA)
    {
        meteoro.hit(especial);
        j.scored(1);
    }
}

void laser_tocou_nave(Laser &laser, Nave &nave, Jogador& j, Clock &demage_aliado)
{
    if (laser.getGlobalBounds().intersects(nave.getGlobalBounds()))
    {
        j.fault(1);
        laser.setPosition(10000, 10000);
        demage_aliado.restart();
    }
}

void meteoro_tocou_nave(Meteoro &meteoro, Nave &nave, Jogador& j, bool especial, Clock &demage_aliado, Sound &explosao)
{
    if (meteoro.getGlobalBounds().intersects(nave.getGlobalBounds()))
    {
        if (especial)
            j.fault(3);
        else
            j.fault(1);
        explosao.play();
        meteoro.hit(especial);
        demage_aliado.restart();
    }
}

int main()
{
    RenderWindow window(VideoMode(LARGURA, ALTURA), "SPACEPS INVADERPS!");
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