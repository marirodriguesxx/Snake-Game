
#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
using namespace std;

class Screen{
    public:
    //definindo o valor das variáveis constantes
    static const int  FOOD=1, SNAKE=2, EMPTY=0,  WALL=3;

    //Construtores da classe da classe e operador de atribuição
    Screen(const Screen &);
    Screen& operator=(const Screen &);
    Screen(int altura_, int largura_);

    //Destrutor
    ~Screen(){ destroy(); };

    //métodos get e set
    int getWidth()const{return largura;};
    int getHeight()const{return altura;};
    int get(const int r,const int c)const;
    void set(const int r,const int c,const int val);
    
    //metodo que será auxiliar para a função set e que foram implementados no trabalho 1
    //a função sofreu algumas alterações para que fosse implementada nesse trabalho
    void resizeCol(const int pos,const int newrows); 
    void destroy();
    void create();

    private:
    int largura;
    int altura;
    int **data;
    int *dataHeight ;
};


#endif