#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include "Game.h"

using namespace std;

//ATENCAO
//ATENCAO
//ATENCAO
//ATENCAO
//Nao considere este programa como um exemplo de boa implementacao!
//Por exemplo, ha partes deles que foram desenvolvidas propositalmente de forma "nao muito correta" com o objetivo de fazer com que
//implementacoes nao 100% corretas da classe Game compilem e executem corretamente
//Tais implementacoes "nao 100% corretas" provavelmente falharao em outros casos de teste usados no Submitty
//
//Observacoes: este jogo foi implementado sem muitos cuidados!
//Exemplo: o tempo de espera entre cada iteracao depende ligeiramente do tempo que o programa gasta
//processando (o certo seria descontar tal tempo...)
//Alem disso, quando uma nova iteracao do jogo e' iniciada quando qualquer tecla e' pressionada (o que pode acelerar o jogo)
//ATENCAO
//ATENCAO
//ATENCAO
//ATENCAO

//Exibe o jogo (armazenado em "s") em tela
//usa a funcao mvprintw da biblioteca ncurses para imprimir caracteres na tela
void exibeJogo(const Screen &s) {
	for(int j=0;j<s.getWidth()+2;j++) mvprintw(0, j, "%c",'-');
	for(int i=0;i<s.getHeight();i++) {
		mvprintw(i+1, 0, "|");
		for(int j=0;j<s.getWidth();j++) {
			int elem = s.get(s.getHeight()-1-i,j);
			char ch = ' ';
			if(elem==Screen::SNAKE) ch = 'x';
			else if(elem==Screen::FOOD) ch = '*';
			mvprintw(i+1, j+1, "%c",ch);
		}
		mvprintw(i+1, s.getWidth()+1, "|");
	}	
	for(int j=0;j<s.getWidth()+2;j++) mvprintw(s.getHeight()+1, j, "%c",'-');
}

int main() {	
	const int larguraJogo = 20;
	const int alturaJogo = 20;
	Game game(alturaJogo,larguraJogo,5); 
	int ultimaTecla = -1;

	int direcaoAtual = 0; //qual a direcao corrente na qual o jogador deve ir? inicialmente ele esta indo para a direita
	int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} }; //armazena do deslocamento (linhas,colunas) referente a cada uma das 4 direcoes que o jogador pode ir

	int itCnt = 0; //conta o numero de iteracoes ja realizadas	

	//comandos da biblioteca ncurses
	initscr(); 
	noecho(); 
	curs_set(false);
	keypad(stdscr,true);
	cbreak(); 
	//raw();
	int tecla;

	halfdelay(5); //a funcao getch aguardara 0.2 segundos por uma entrada do usuario... Se o usuario nao digitar nada, getch retorna ERR
				 //ou seja, o laco infinito abaixo ira fazer em torno de 5 iteracoes por segundo... 
	exibeJogo(game.getScreen());
	while(true) { //o jogo fica em um laco infinito que so termina quando ele perde... (seria interessante ter uma tela informando que perdeu, mostrando pontuacao, etc...)			
 		if(ultimaTecla==KEY_LEFT) { 	
 			direcaoAtual = 2;
 		} else if(ultimaTecla==KEY_RIGHT){
 			direcaoAtual = 0;
 		} else if(ultimaTecla==KEY_UP){
 			direcaoAtual = 1;
 		} else if(ultimaTecla==KEY_DOWN){
 			direcaoAtual = 3;
 		} 
		bool ok = game.step(dirs[direcaoAtual][0],dirs[direcaoAtual][1]); //move na direcao informada -- se houver colisao para...
		if(!ok) break;

		if(itCnt%10==rand()%10 && game.getNumFood()<10) { //adiciona uma comida mais ou menos de forma aleatoria a cada aproximadamente 10 iteracoes.. 
			game.addFood(rand()%alturaJogo,rand()%larguraJogo,rand()%20+5);
		}

		exibeJogo(game.getScreen());
		
 		ultimaTecla = getch(); //ve qual tecla esta pressionada agora 
 		 		
 		refresh();
 		itCnt++;
	}
	endwin();
}