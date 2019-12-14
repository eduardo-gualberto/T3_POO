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

void ArquivoRanking::EscritaArquivo(string filename,Jogador player){
    ofstream arq;
    arq.open(filename.c_str(),ofstream::app);
    if(arq.is_open()){
        arq.write(reinterpret_cast<char*>(&player),sizeof(Jogador));
        arq.close();
    }else{
        cout <<"ERRO"<< endl;
    }

}
bool ArquivoRanking::comparaPontuacao(Jogador a, Jogador b){
    return a.getPontuacao() > b.getPontuacao();
}
vector<Jogador> ArquivoRanking::LeituraArquivo(string filename){
    int i=0;
    vector<Jogador> copia;
    Jogador player;
    ifstream arq(filename.c_str(),ios::binary);
    if(arq.is_open()){
        arq.read(reinterpret_cast<char*>(&player), sizeof(Jogador));
        while(arq.good()){
            jogadores.push_back(player);
            cout << jogadores[i].getNome() << endl;
            i++;
            arq.read(reinterpret_cast<char*>(&player), sizeof(Jogador));
        }
        copia = jogadores;
        sort(copia.begin(), copia.end(),ArquivoRanking::comparaPontuacao);
        return copia;
    }else{
        cout << "ERRO" << endl;
    }

    arq.close();

}

