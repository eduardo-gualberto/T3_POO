#pragma once
#include "Jogador.h"

Jogador::Jogador(){
    lives = 5;
    score = 0;
}

Jogador::~Jogador(){
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

void Jogador::heal(int qntd){
    lives += qntd;
}

int Jogador::getScore(){return score;}
int Jogador::getLives(){return lives;}
int Jogador::getID(){return id;}