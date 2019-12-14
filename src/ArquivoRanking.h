#ifndef ARQUIVORANKING_H
#define ARQUIVORANKING_H
#include <string>
#include <vector>
#include "Jogador.h"
#include <fstream>
using namespace std;
class ArquivoRanking
{
    public:
        ArquivoRanking();
        virtual ~ArquivoRanking();
        void EscritaArquivo(string filename,Jogador player);
        vector<Jogador> LeituraArquivo(string filename);
        static bool comparaPontuacao(Jogador a, Jogador b);

    protected:

    private:
        string filname;
        vector<Jogador> jogadores;

};

#endif // ARQUIVORANKING_H
