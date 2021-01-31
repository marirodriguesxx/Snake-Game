#include"Game.h"
#include"Screen.h"
#include "Snake.h"
//contrutor ======================================================
Game::Game(const int altura,const int largura,const int tamSnake){
    //chamamos os construtores de tais classes
    tela = new Screen (altura,largura);
    cobra = new Snake(tamSnake);
    cobra->draw(*tela,Screen::SNAKE);
}

//Construtor de cópia e operador de atribuição =================
Game::Game(const Game &other){
    tela = NULL;
    cobra = NULL;
    *this = other;      //Chmamos o operador de atribuição
}

Game & Game::operator=(const Game &other){
    if(this==&other) return *this;      //verificando a autoatribuição!
    tela = NULL;
    cobra = NULL;
    //Aqui, iremos chamar os operados implementados nas outras classes e redesenhamos a cobra
    cobra = new Snake (*other.cobra);
    tela = new Screen (*other.tela);
    cobra->draw(*tela, Screen::SNAKE);

    return *this;
}

//Destrutor ======================================================
Game::~Game(){ //Aqui, chamamos os destrutores dos recpectivos objetos criados 
    delete tela;
    delete cobra;
}

//Método que retorna a tela em seu estado atual===================
const Screen &Game::getScreen()const{
    return *tela;               
}

//Método eating - verifica se a cobra irá comer ==============
bool Game::eating (const int dr, const int dc) {
    //Criamos variáveis, contendo as próximas coordenadas desejadas da cobra
    int linha = cobra->getNextrow(dr);
    int coluna = cobra->getNextcol(dc);
    //caso nessas posições haja comida, devemos percorrer o novvo vetor de comida
    if(tela->get(linha,coluna) == Screen::FOOD){
        for(int i=0; i<10;i++){
                if(comida[i].foodrow==linha && comida[i].foodcol==coluna){      //ao encontrar a linha e a coluna que possui a comida
                    comida[i].lifetime=-1;
                    comida[i].foodrow =-1;
                    comida[i].foodcol = -1;         //deletamos tudo que havia nela, de forma a representar que não há mais comida naquela posição
                }
            }        
        NumFood --;         //por fim, deve-se decrementar o número de comidas no jogo
        return true;
    }
    else 
        return false;
}

//Método que reduz o tempo de vida de cada comida ===============
void Game::reduceTtl(){
    for(int i=0;i<10;i++){
        comida[i].lifetime--;           //iremos sempre decrementar o ttlf de cada comida no mapa

        if (comida[i].lifetime<0){      //no caso em que não há mais comida, ou seja, seu tempo de vida acabou
            tela->set(comida[i].foodrow,comida[i].foodcol,Screen::EMPTY);       //setamos a posição com empty
            comida[i].foodrow = -1;     // e deletamos a comida naquela posição
            comida[i].foodcol = -1;
            comida[i].lifetime = -1;
            
        }
    }
}

//Método step ==================================================
bool Game::step(const int dr,const int dc){
    int linha_ = dr;
    int coluna_ = dc;
    reduceTtl();        //a cada iteração deve-se diminuir o tempo de vida das comidas

    //no caso em que tivermos uma cobra de tamanho maior que 1 e tentarmos mover para uma direção oposta da anterior
    //alteramos as variaveis de direcionamento para que permaneçam na antiga direção
    if(cobra->getLength()>1){
        //Para isso, basta verificar se a próxima posição é igual as coordenadas do nodo anterior à cabeça da cobra
        if(cobra->getNextrow(dr) == cobra->getPrevrow() && cobra->getNextcol(dc) == cobra->getPrevcol()){
        linha_ = -1*dr;
        coluna_=-1*dc;
        }
    }
    //Aqui, tratamos o caso em que a cobra bate na parede ou nela mesma
    if(tela->get(cobra->getNextrow(linha_),cobra->getNextcol(coluna_))==Screen::WALL 
    || tela->get(cobra->getNextrow(linha_),cobra->getNextcol(coluna_))==Screen::SNAKE ){
        return false;
    }
    else{//caso a próxima posição não seja WALL ou SNAKE, devemos apagar a cobra, chamar o método move e redesenha-la
        cobra->draw(*tela,Screen::EMPTY);
        cobra->move(linha_,coluna_,eating(linha_,coluna_));
        cobra->draw(*tela,Screen::SNAKE);
        return true;
    }

}

//Método addFood=============================================
void Game::addFood(const int r,const int c,const int ttl){
    if(tela->get(r,c) == Screen::EMPTY){        //verificamos se a posição está vazia
        for(int i=0;i<10;i++){                  //percorremos o vetor, procurando alguma posição em que não há comida
            if(comida[i].lifetime < 0 ){
            comida[i].foodrow = r;
            comida[i].foodcol = c;
            comida[i].lifetime = ttl;           //atualizamos as coordenadas e o tempo de vida da comida naquela posição 
            tela->set(r, c, Screen::FOOD);      // e a 'setamos' na tela
            NumFood ++;                         //por fim, incrementamos o numero de comidas no jogo
            break;                              //o break é necessário por queremos adicionar essa comida apenas uma vez
            }
        }
    }
}