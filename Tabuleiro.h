#ifndef Tabuleiro_H
#define Tabuleiro_H

using namespace std;

class Tabuleiro{
    int tabuleiro[8][8];
public:
    Tabuleiro();
    void inicializaTabuleiro();
    bool getVizinhanca(int base, int x, int y);
    int getCasa(int x, int y);
    bool facaJogada(int base, int x, int y);
    void sudoFacaJogada(int base, int x, int y);
    void printaTabuleiro();
    int verificaVitoria();
    bool tentaJogada(int base, int &x, int &y);
};
#endif