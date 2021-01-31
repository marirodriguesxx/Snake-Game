#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include "Screen.h"
#include<utility>
using namespace std;

//struct para armazenar as coordenadas da cobra na tela
struct coordinates{
    int row =0;
    int col=0;
};

class Node;
class Node {
	public:
		Node(const coordinates &elem): data(elem), next(NULL), prev(NULL) {}    //declaramos um node, com conteúdo do tipo coordinates
		coordinates data;
		Node *next;
		Node *prev;
};

class Snake{
    public:
    Snake (int tamInicialSnake);
    ~Snake(){ destroy(); };

    Snake(const Snake &);
	Snake & operator=(const Snake &);

    void draw(Screen &s,int state);
    void move(int dr,int dc,bool eating);
    int getLength()const;

    //Funções auxiliares - retornam, respectivamente, coordenada da coluna e linha da cabeça da cobra
    int getNextcol(const int dc)const;
    int getNextrow(const int dr)const;
    //Funções auxiliares - retornam, respectivamente, coordenada da coluna e linha anterior da cabeça da cobra
    int getPrevrow()const;
    int getPrevcol()const;

    //Função auxiliar - adiciona um novo node - atualiza a cabeça da cobra
    void push_back(const int &h, const int &w);
    //Função recursiva auxiliar, pois facilita a destruição do objeto
    void destroy();
    void destroy(Node *first);

    private:
    Node *dataFirst, * dataLast;
};

#endif