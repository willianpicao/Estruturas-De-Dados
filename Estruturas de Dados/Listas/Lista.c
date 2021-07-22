#ifndef lista_c
#define lista_c

#include<stdio.h>
#include<stdlib.h>
#define N 5
typedef struct lista{
	int vetLista[10];
	int qtdDados;

} tipoLista;

		//escropo das funções
/*int listaVazia(tipoLista *ls);
int listaCheia(tipoLista *ls);
void insereInicio(tipoLista *ls, int valor);
void insereFim(tipoLista *ls, int valor);
void inserePosicao(tipoLista *ls, int valor, int posicao);
int removeInicio(tipoLista *ls);
int removeFim(tipoLista *ls);
int removeP(tipoLista *ls,int pos);
void imprimeLista(tipoLista *ls);
int removeBusca(tipoLista *ls, int valor);
*/

		//Implementação das funções//

int listaVazia(tipoLista *ls){
	if ( ls->qtdDados==0){
		printf("A lista está vazia\n");
		return 1;
	}else{
		return 0;
	}
}

int listaCheia(tipoLista *ls){
	if ( ls->qtdDados==N )
		return 1;
	else
		return 0;
}

void insereInicio(tipoLista *ls, int valor){
	if ( listaCheia(ls) == 1 ){
		printf("Impossível inserir um novo valor pois a lista esta cheia");
	}else{
		int i;
		for ( i=ls->qtdDados; i>0; i--){
			ls->vetLista[i]=ls->vetLista[i-1];
		}			
		ls->vetLista[0]=valor;
		ls->qtdDados++;
	}
		
}
void imprimeLista(tipoLista *ls){
	if ( listaVazia(ls)==1 )
		printf("A lista esta vazia\n[].\n");
	else{
		int i;
	printf("A Lista é esta: [");
		for (i=0; i<ls->qtdDados ; i++)
			printf("%d,",ls->vetLista[i]);
		printf("]\n");
	}
}

void insereFim(tipoLista *ls,int valor){
	if ( listaCheia(ls) )
		printf("Impossivel inserir um novo valor, lista cheia!");
	else
		ls->vetLista[ls->qtdDados]=valor;
	ls->qtdDados++;
}

	
void inserePosicao(tipoLista *ls, int valor, int posicao){
	int i;
	if ( listaCheia(ls)==1 ){
		printf("Impossivel inserir um novo valor, lista cheia!");
	}else{
		if ( (posicao>=0) && (posicao<=N) && (posicao<=ls->qtdDados)){
			for (i=ls->qtdDados; i<posicao; i--){
				ls->vetLista[i]=ls->vetLista[i-1];
			}
			ls->vetLista[posicao]=valor;
			ls->qtdDados++;
		}
	}
}

int removeFim(tipoLista *ls)
{	
	if ( listaVazia(ls) )
		printf("Impossivel remover, não ha valores");
	else
	{
		int aux;
		aux=ls->vetLista[ls->qtdDados-1];
		ls->qtdDados--;
		return aux;
	}
}

int removeInicio(tipoLista *ls)
{
	if ( listaVazia(ls) )
		printf("Impossivel remover, não ha valores");
	else
	{
		int aux,i;
		aux=ls->vetLista[0];
		for ( i=0; i<ls->qtdDados; i++)
			ls->vetLista[i]=ls->vetLista[1+i];
		ls->qtdDados--;
		return aux;
	}
}		

int removeP(tipoLista *ls, int pos)
{
	if ( listaVazia(ls) )
		printf("Impossivel remover, não ha valores");
	else
	{
		int aux,i;
		if ( (pos>=0) && (pos<N) )
		{
			aux=ls->vetLista[pos];
			for (i=pos ; i<ls->qtdDados; i++)
				ls->vetLista[i]=ls->vetLista[i+1];
		}
		else
		{
			return 0;
		}
	}
}	
		
int removeBusca(tipoLista *ls, int valor)
{
int i,aux=-1;
	if ( listaVazia(ls) ){
		printf("Impossivel, remover o valor, lista vazia");
		return 0;
	}	
	else
	{
		for (i=0; i<ls->qtdDados; i++)
		{
			if (ls->vetLista[i]==valor){
				aux=i;
				ls->qtdDados--;
			
			}
		}
		

			if(aux<0){
				printf("valor inexistente\n");
				return aux;
			}
			else
			{
				for(i=aux;i<ls->qtdDados;i++)
				{
					ls->vetLista[i]=ls->vetLista[i+1];
				}
				return aux;

			}		
	}
}


#endif






