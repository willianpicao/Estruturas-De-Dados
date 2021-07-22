#include<stdio.h>
#include<stdlib.h>
#define N 5

	// definição de estrutura tipo pilha
typedef struct {
	int topo;
	int vetPilha[N];
}tipoPilha;
	//escropo das funções
void inicia(tipoPilha *pl);
void insere(tipoPilha *pl,int valor);
int remover(tipoPilha *pl);
void imprimePilha(tipoPilha *pl);
int pilhaCheia(tipoPilha *pl);
int pilhaVazia(tipoPilha *pl);

int main(){
	tipoPilha pilha;
	inicia(&pilha);
	insere(&pilha, 1);
	insere(&pilha, 2);
	insere(&pilha, 3);
	insere(&pilha, 4);
	insere(&pilha, 5);
	printf("Sua pilha é =[");	
	imprimePilha(&pilha);
	printf("]\n");	
	printf("Sua pilha desempilhada com a qntd que inseriu é= [");	
	remover(&pilha);
	
	imprimePilha(&pilha);
	printf("]\n");
	
	
	return 1;
	




}





//implementação das funções
	//Inicia topo
void inicia(tipoPilha *pl){
	pl->topo=-1;
}
	//verifica pilha vazia
int pilhaVazia(tipoPilha *pl){
	if (pl->topo==-1){
		return 1;
	}else{
		return 0;
	}
}

	//verifica pilha cheia
int pilhaCheia(tipoPilha *pl){
	if (pl->topo==N-1)
		return 1;
	 else 
		return 0;
	
}

	//Insere valores na pilha
void insere(tipoPilha *pl,int valor){
	if(pilhaCheia(pl)==1){
		printf("Sua pilha está cheia");
	}else{
		pl->topo++;
		pl->vetPilha[pl->topo]=valor;
	
	}
}

	//remove valor da pilha
int remover(tipoPilha *pl){
	int aux;
	if (pilhaVazia(pl)){
		printf("Impossivel retirar pois pilha esta vazia");
	}else{
		aux=pl->vetPilha[pl->topo];
		pl->topo--;
		return aux;
	}

}
	//imprime a pilha
void imprimePilha(tipoPilha *pl){
	int i;	
	for (i=0; i<=pl->topo;i++){
		printf("%d,",pl->vetPilha[i]);
	}
}

	
