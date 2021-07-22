#include<stdio.h>
#include<stdlib.h>

#define N 5

typedef struct{
	int vetFila[N];
	int qtdDados;
}tipoFila;
//escropo das funções
int filaCheia(tipoFila fl);
int filaVazia(tipoFila fl);
int insere(tipoFila *fl, int valor);
void imprimeFila(tipoFila fl);
int removeFila(tipoFila *fl);

//              *********Função principal************
int main (){
	tipoFila fila;
	fila.qtdDados=0;
	
	insere( &fila, 10);
	insere( &fila, 20);
	insere( &fila, 30);
	insere( &fila, 40);
	imprimeFila (fila);
	removeFila(&fila);
	removeFila(&fila);
	removeFila(&fila);
	removeFila(&fila);
	imprimeFila(fila);

	return 1;
}

//implementação das funções
	//função para verificar se fila esta cheia
int filaCheia (tipoFila fl){
	if (fl.qtdDados<N){
		return 0;
	}else{
		return 1;
	}
}
	//função para inserir valor na fila
int insere(tipoFila *fl, int valor){
	if (! filaCheia(*fl) ){
		fl->vetFila[fl->qtdDados]=valor;
		fl->qtdDados++;
		return 1;
	}else{
		return 0;
	}

}
	//função para veirificar se fila esta vazia
int filaVazia (tipoFila fl){
	if (fl.qtdDados==0){
		return 1;
	}else{
		return 0;
	}
}

	//função para imprimir fila
void imprimeFila(tipoFila fl){
	int i;
	printf("Fila=[");
	for ( i=0; i<fl.qtdDados; i++ ){
		printf("%d,", fl.vetFila[i]);
	}
	printf("]\n");
}

int removeFila(tipoFila *fl){
	if (! filaVazia(*fl) ){
		int aux,i;
		aux=fl->vetFila[0];
		fl->qtdDados=fl->qtdDados-1;
		for (i=0; i<fl->qtdDados;i++){
			fl->vetFila[i]=fl->vetFila[i+1];
		}
	return aux;
	}else{
		return -1;
	}

}



