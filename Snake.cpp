#include "Snake.h"
//Construtores da classe ===========================
Snake::Snake(int tamInicialSnake){
    dataFirst = dataLast  = NULL;
    for(int i=0;i<tamInicialSnake;i++){ 
        push_back(0,i); 
	}
}

Snake::Snake(const Snake &other) {
	dataFirst = dataLast  = NULL;
	*this = other; 
}

//operador de atribuição ==========================
Snake& Snake::operator=(const Snake &other) {
	if(this==&other) return *this; 
	destroy();
	dataFirst = dataLast  = NULL;
	
	if(other.dataFirst == NULL) {		//verificando o caso de ser uma cobra "vazia", n precisaremos reatribuir, pois acabamos de setar NULL
		dataFirst = dataLast = NULL;
	} 
	else{
		Node *curr = other.dataFirst;		//criamos um nodo copiando o outro
		//percorrermos a lista, copiando seus valores
		while(curr!=NULL) { 				//enquanto houver nodos, salvaremos as posições respectivas da cobra
			push_back(curr->data.row,curr->data.col);
			curr = curr->next; 
		}
		
	}
	return *this;
}

//Funções auxiliares - destrutor =================
void Snake::destroy(Node  *first) {
	if(first==NULL) return;			//Se o dataFirst aponta pra NUMM, temos uma lista vazia
	destroy(first->next);			//caso contrário, vamos pegando seu next ate o final da lista
	delete first;					//por fim, saímos apagando na pilha de chamada recursiva
}

void Snake::destroy() { 
	destroy(dataFirst);				
}

//Função auxilia para criar a cabeça da cobra =======
void Snake::push_back(const int &r, const int &c) {
	coordinates elem;
	elem.row = r;
	elem.col =c;
	if(dataFirst==NULL) { 					//caso a lista esteja vazia, precisamos apenas criar um nodo
		dataFirst = dataLast = new Node(elem);
	} 
    else {									//caso contrário, devemos criar um nodo e atualizar os ponteiro next e prev
		dataLast->next = new Node(elem);
		dataLast->next->prev = dataLast;
		dataLast = dataLast->next;
	}	
}

//Método - pega tamanho da cobra =====================
int Snake::getLength()const{
	int cont = 0;
	Node *first = dataFirst;
	while(first!=NULL){				//anadamos até o final da lista, incrementando um contador, que retornará o tamanho da cobra
		cont++;
		first = first->next;
	}
	return cont;
}

//Funções auxiliares ===============================
int Snake::getNextcol(const int dc)const{
	Node* aux = dataLast;				//copiamos o datalast e acessamos o elemento que contém a respectiva coluna da cobra
	return aux->data.col +dc;			//somamos a variação(0, 1 ou -1) na coluna, atualizando o valor de sua coordenada
}

int Snake::getNextrow(const int dr)const{
	Node* aux = dataLast;				//copiamos o datalast e acessamos o elemento que contém a respectiva linha da cobra
	return aux->data.row +dr;			//somamos a variação(0, 1 ou -1) na linha, atualizando o valor de sua coordenada

}

int Snake::getPrevrow()const{
	 Node* aux = dataLast;				//copiamos o datalast e acessamos o elemento que contém a respectiva linha anterior da cobra
	 return aux->prev->data.row;
	 
}

int Snake::getPrevcol()const{
	Node* aux = dataLast;				//copiamos o datalast e acessamos o elemento que contém a respectiva coluna anterior da cobra
	return aux->prev->data.col;
}

//Método draw =================================
void Snake::draw(Screen &s,int state){
	Node* cobra = dataFirst;			//fazemos uma copia do primeiro nodo, para que possamos ter acesso ao seu next com segurança, sem alterar o objeto
	while(cobra != NULL){				//enquanto não chegarmos na cabeça da cobra
		s.set(cobra->data.row,cobra->data.col,state);		//vamos 'setando' suas coordenadas na tela
		cobra = cobra -> next;
	}
}

//Método move =================================
void Snake::move(int dr,int dc,bool eating){
	coordinates newHead_;					//criamos as novas coordenadas
	newHead_.row = getNextrow(dr);
	newHead_.col = getNextcol(dc);
	push_back(newHead_.row,newHead_.col);	//adicionamos a nova cabeça, contendo essas novas coordenadas
	//Quando a cobra não estiver comendo, o seu rabo deverá ser apagado
	if(!eating ){
		Node* oldTail = dataFirst;		//salvamos em um nodo sua antiga posição
		dataFirst = dataFirst -> next;	//alteramos a posição de datafirst, fazendo com que seja o proximo nodo (note que por isso este método não pode ser const!)
		delete oldTail;					//por fim, deletamos o antigo nodo representante do rabo da cobra
	}
}