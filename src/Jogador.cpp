#include "Jogador.h"

Jogador::Jogador()
{
    //ctor
}

Jogador::~Jogador()
{
    //dtor
}

string Jogador::getNome(){
    return this->nome;
}
int Jogador::getPontuacao(){
    return this->pontuacao;
}
void Jogador::setNome(string nome){
    this->nome = nome;
}
void Jogador::setPontuacao(int pontuacao){
    this->pontuacao = pontuacao;
}
