#include "Tabuleiro.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Tabuleiro::Tabuleiro(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            this->tabuleiro[i][j] = 0;
        }
    }
}

void Tabuleiro::inicializaTabuleiro(){
    srand(time(NULL));
    int x1 = rand() % 8;
    int x2 = rand() % 8;
    int y1 = rand() % 8;
    int y2 = rand() % 8;
    cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    this->tabuleiro[x1][y1] = 1;
    this->tabuleiro[x2][y2] = 2;
    this->printaTabuleiro();
}

bool Tabuleiro::getVizinhanca(int base, int x, int y){
    if (this->tabuleiro[x][y]){
        return false;
    }
    if (x < 7 && this->tabuleiro[x+1][y] == base){
        return true;
    }
    if (x > 0 && this->tabuleiro[x-1][y] == base){
        return true;
    }
    if (y < 7 && this->tabuleiro[x][y+1] == base){
        return true;
    }
    if (y > 0 && this->tabuleiro[x][y-1] == base){
        return true;
    }
    return false;
}

int Tabuleiro::getCasa(int x, int y){
    return this->tabuleiro[x][y];
}

bool Tabuleiro::facaJogada(int base, int x, int y){
    if (this->getVizinhanca(base, x, y)){
        this->tabuleiro[x][y] = base;
        return true;
    }
    return false;
}

void Tabuleiro::sudoFacaJogada(int base, int x, int y){
    this->tabuleiro[x][y] = base;
}

void Tabuleiro::printaTabuleiro(){
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            cout << this->tabuleiro[i][j] << " ";
        }
        cout << endl;
    }
}

int Tabuleiro::verificaVitoria(){
    int cont1 = 0, cont2 = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (this->tabuleiro[i][j] == 1) cont1++;
            else if (this->tabuleiro[i][j] == 2) cont2++;
        }
    }
    return cont1 > cont2 ? 1 : 2;
}

bool Tabuleiro::tentaJogada(int base, int &x, int &y){
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(this->facaJogada(base, i, j)){
                x = i;
                y = j;
                return true;
            }
        }
    }
    return false;
}