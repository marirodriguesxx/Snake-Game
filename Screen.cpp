#include "Screen.h"

//Funções create e destroy auxiliares ==========================
void Screen::create(){
    //inicializa uma tela vazia
    data=NULL;
    dataHeight=NULL;
    altura=largura=0;

}
void Screen::destroy(){        
    for(int i=0; i<getWidth(); i++)
        delete []data[i];
    delete []data;
    delete []dataHeight;

}

//Construtores e operador de atribuição =========================
Screen::Screen(const int altura_,const int largura_){
    altura = altura_;
    largura = largura_;
    //Esse vetor recebera a quantidade de 'linhas' da matriz que representará a nossa tela
    //Primeiro, alocaremos da forma mais fácil, uma matriz retangular, iremos tratar os espeaços desnecessários na função set!
    dataHeight = new int[largura];
    data = new int *[largura];
    //Alocaremos agora as linhas de todas as colunas
    for(int i=0; i<largura; i++){
        dataHeight[i] = 0;
        data[i] = NULL;    //primeiro criamos as linhas apontando para NULL, pois dependerá do método set analisar se é necessário, ou não, aloca-las
    }
        
}

Screen & Screen::operator=(const Screen &other){  
    //Funciona semelhante ao construtor, porém aqui iremos, ao invés de inicializar com lixo, inicializar com os valores recebido de other
        if(this==&other) return *this;          //verificando a autoatribuição!
        destroy();
        create();
        altura = other.altura;
        largura = other.largura;
        
        //realocaremos os vetores com seus novos tamanhos respectivos e receberemos os elementos da screen other
        dataHeight = new int[getWidth()];
        for(int i=0; i<getWidth(); i++){
            dataHeight[i] = other.dataHeight[i];        
        }

        data = new int*[getWidth()];     
        for (int i = 0; i<getWidth(); i++){
            data[i] = new int [dataHeight[i]];
        }
        for (int i = 0; i<getWidth(); i++){
            for(int j=0; j<dataHeight[i]; j++){
                data[i][j] = other.data[i][j];
            }
        }
        return *this;

      
}

Screen::Screen(const Screen &other){
    create();
    //Chama a sobrecarga do operador de atribuição, e faz com que o objeto apontado por this seja igual ao recebido por parametro (other)
    *this = other;    
}


//Método get=================================================
int Screen::get(const int r,const int c)const{ //ok
    //Este if trata o caso em que é feita uma consulta em alguma posição fora dos limites da tela
    if((r>=getHeight() || c>=getWidth()) || (r<0 || c<0)){
        return WALL;
    }
    //Caso em que não há uma linha alocada ou acessamos posições acima do maior elemento da coluna
    else if(dataHeight[c]==0 || r>= dataHeight[c] ){
        return EMPTY;
    }
    //Tirando todas as exceções, podemos retornar o elemento correspondente a linha e coluna desejada
    else {
        return data[c][r];
    }

}

//Método set ====================================================================
void Screen::set(const int r,const int c,const int val){ 
    //sempre que setarmos um novo elemento, daremos resize na matriz, para que aloque apenas o necessário sempre o necessário
    if(r<altura && c<largura && r>=0 && c>=0 ){         //tratamento para evitar escrita em memória inválida
        if(val !=EMPTY){                                    //quando estivermos aumentando a altura da coluna
            resizeCol(c,r+1);
            data[c][r] = val;
        }
        if(val == EMPTY && dataHeight[c] != 0){             //caso tenha que desalocar uma linha inteira, ou diminuir a altura da coluna
            data[c][r] = val;
            for(int i=dataHeight[c]-1;i>=0;i--){
                if(data[c][i] != EMPTY){
                    int* aux = new int[i+1];
                    for(int j=0; j<=i; j++){
                        aux[j] = data[c][j];
                    }
                    delete []data[c];
                    data[c] = aux;
                    dataHeight[c] = i+1;
                    return;
                }
            }
            delete []data[c];
            data[c] = NULL;
            dataHeight[c]=0;
            
        }  
    }
}

//Função para redisionamento da matriz a cada chamada do método set
void Screen::resizeCol(const int pos,const int newrows){  
//Este método consiste em criar uma variável auxiliar, para salvar os valores antigos, realocar com o novo tamanho e, por fim, resgatar os antigos valores          
    if(dataHeight[pos] < newrows){
        int* aux = new int[newrows];
        for(int i=0; i<newrows; i++)
            aux[i]=EMPTY;      
        
        for(int i=0; i<dataHeight[pos]; i++)
            aux[i] = data[pos][i];        

        delete []data[pos];  
        //copiando os dados de um ponteiro para o outro
        data[pos] = aux; 

        dataHeight[pos] = newrows; 
    }  
        
}
