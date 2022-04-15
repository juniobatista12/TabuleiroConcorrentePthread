#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "Tabuleiro.h"

using namespace std;

Tabuleiro tabuleiro;

bool fim_de_jogo1 = false, fim_de_jogo2 = false, interrompido = false;

sem_t jogador1a, jogador1b, jogador2a, jogador2b;
pthread_t jogadores[2];

static void trataInt(int signum){
    sem_destroy(&jogador1a);
    sem_destroy(&jogador1b);
    sem_destroy(&jogador2a);
    sem_destroy(&jogador2b);
    fim_de_jogo1 = true;
    fim_de_jogo2 = true;
    pthread_exit(&jogadores[0]);
    pthread_exit(&jogadores[1]);
    interrompido = true;
}

void *jogador(void *arg){
    int *indice = (int*)arg;
    int x, y;
    switch(*indice){
    case 1:
        while(!fim_de_jogo1){
            if(!tabuleiro.tentaJogada(1, x, y)){
                fim_de_jogo1 = true;
            }
            sem_post(&jogador1a);
            sem_wait(&jogador1b);
        }
        break;
    case 2:
        while(!fim_de_jogo2){
            if(!tabuleiro.tentaJogada(2, x, y)){
                fim_de_jogo2 = true;
            }
            sem_post(&jogador2a);
            sem_wait(&jogador2b);
        }
        break;
    }
}

int main(){
    tabuleiro.inicializaTabuleiro();
    int indice[] = {1, 2};
    sem_init(&jogador1a, 0, 0);
    sem_init(&jogador1b, 0, 0);
    sem_init(&jogador2a, 0, 0);
    sem_init(&jogador2b, 0, 0);
    signal(SIGINT, trataInt);
    sleep(2);
    for (int i = 0; i < 2; i++){
        pthread_create(&(jogadores[i]), NULL, jogador, &indice[i]);
    }
    // for (int i = 0; i < 2; i++){
    //     pthread_join(jogadores[i], NULL);
    // }
    while(!fim_de_jogo1 || !fim_de_jogo2){
        cout << "Aguardando 1 e 2" << endl;
        if(!fim_de_jogo1) sem_wait(&jogador1a);
        if(!fim_de_jogo2) sem_wait(&jogador2a);
        tabuleiro.printaTabuleiro();
        sem_post(&jogador1b);
        sem_post(&jogador2b);
    }
    cout << "O jogador" << tabuleiro.verificaVitoria() << " venceu" << endl;
    if(!interrompido){
        sem_destroy(&jogador1a);
        sem_destroy(&jogador1b);
        sem_destroy(&jogador2a);
        sem_destroy(&jogador2b);
        pthread_exit(&jogadores[0]);
        pthread_exit(&jogadores[1]);
    }
}