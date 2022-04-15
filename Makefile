all: main.cpp Tabuleiro.cpp
	g++ main.cpp Tabuleiro.cpp -lpthread -lrt -o tabuleiro
