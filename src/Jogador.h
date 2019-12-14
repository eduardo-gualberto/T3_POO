#pragma once
#ifndef JOGADOR_H
#define JOGADOR_H
#include <string>
#include <fstream>
using namespace std;
class Jogador
{
    public:
        Jogador();
        virtual ~Jogador();
        void setNome(string nome);
        void setPontuacao(int pontuacao);
        string getNome();
        int getPontuacao();

    protected:

    private:
        string nome;
        int pontuacao;
};

#include "Jogador.cpp"

#endif // JOGADOR_H
