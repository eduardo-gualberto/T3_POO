#pragma once
#include "ArquivoRanking.h"
#include <iostream>
#include <vector>
#include <algorithm>
ArquivoRanking::ArquivoRanking()
{
    //ctor
}

ArquivoRanking::~ArquivoRanking()
{
    //dtor
}

void ArquivoRanking::EscritaArquivo(string filename, Jogador player){
    ofstream arq;
    arq.open(filename.c_str(),ios::binary);
    arq.write(reinterpret_cast<char*>(&player),sizeof(Jogador));
    arq.close();
}
bool ArquivoRanking::comparaPontuacao(Jogador a, Jogador b){
    return a.getPontuacao() < b.getPontuacao();
}
Jogador ArquivoRanking::LeituraArquivo(string filename){
    ifstream arq(filename.c_str(), ios::binary);
    Jogador a;
    
    if (arq.is_open()) {
        arq.read(reinterpret_cast<char *> (&a), sizeof (Jogador));
    }
    arq.close();
    return a;
}