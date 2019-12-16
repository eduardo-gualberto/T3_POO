#pragma once
#include "Jogador.h"

Jogador::Jogador(){
    id = ++Jogador::ObjectCount;
    score = ((Jogador::ObjectCount % 2) + 1) * 3;
}

Jogador::~Jogador(){
    Jogador::ObjectCount--;
}

void Jogador::scored(int points){
    score += points;
}

void Jogador::fault(int qntd){
    lives -= qntd;
}

bool Jogador::comparaScore(Jogador a, Jogador b){
    return a.getScore() > b.getScore();
}

int Jogador::getScore(){return score;}
int Jogador::getLives(){return lives;}
int Jogador::getID(){return id;}