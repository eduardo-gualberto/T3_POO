#pragma once
#ifndef JOGADOR_H
#define JOGADOR_H
#include <string>
#include <fstream>
using namespace std;
class Jogador
{
private:
    int id;
    int score;
    int lives;
public:
    Jogador();
    ~Jogador();
    void scored(int);
    void fault(int);
    void heal(int);
    int getScore();
    int getLives();
    int getID();
    static bool comparaScore(Jogador, Jogador);
};
#include "Jogador.cpp"
#endif // JOGADOR_H