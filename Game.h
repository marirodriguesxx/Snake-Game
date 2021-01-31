#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Snake.h"
#include "Screen.h"

using namespace std;
struct Food{
    int foodrow=-1;
    int foodcol=-1;
    int lifetime=-1;
};

class Game{
    public:
    //Construtor da classe
    Game(const int altura,const int largura,const int tamSnake);
    ~Game();

    Game(const Game &);
	Game & operator=(const Game &);

    //Método que retorna o estado atual do jogo  - deve ser const pois não modificará o objeto
    const Screen &getScreen()const;

    //Método indicando se o movimento foi realizado com sucesso (true) ou não (false) 
    bool step(const int dr,const int dc);

    // adiciona um alimento na posição (r,c) (linha, coluna) da tela. 
    //"O terceiro argumento (ttl -- time to live) indica por quanto tempo (em termos de iterações) o alimento deve existir" 
    void addFood(const int r,const int c,const int ttl);

    //retorna um inteiro representando a quantidade de comida (ativa) atualmente no jogo.
    int getNumFood()const{return NumFood;};

    //Método que irá verificar se na próxima direção a cobra estará comendoou ou não
    bool eating (const int dr, const int dc);
    //Método que verificará o tempo de vida de cada alimento, de forma a mudar a posição na tela quando acabar esse tempo
    void reduceTtl();


    
    private:
    Snake *cobra;
    Screen* tela;
    Food comida[10];
    int NumFood = 0;
};

#endif