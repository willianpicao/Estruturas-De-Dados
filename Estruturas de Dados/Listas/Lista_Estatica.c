#ifndef lista_c
#define lista_c

#include<stdio.h>
#include<stdlib.h>

struct lista 
{
	int *vet;
	int frente;
	int tras;
	int tam;
	int contador;
};
typedef struct lista tipoLista;
void inicializaLista(tipoLista *lst, int tamanho);
int listaCheia(tipoLista *lst);
int listaVazia(tipoLista *lst);
void insereFim(tipoLista *lst, int valor);
void insereInicio(tipoLista *lst, int valor);
void inserePosicao(tipoLista *lst, int valor, int posicao);
void imprime(tipoLista *lst);
/*int removerFim(tipoLista *lst);
int removerInicio(tipoLista *lst);
int removerPosicao(tipoLista *lst, int posicao);*/


void inicializaLista(tipoLista *lst, int tamanho)
{
	lst->tam=tamanho;
	lst->frente=0;
	lst->tras=-1;
	lst->vet=(int*) malloc( tamanho*sizeof(int) );
}
int listaCheia(tipoLista *lst)
{
	if(lst->tras == lst->tam)
		return 1;
	else
		return 0;
}
int listaVazia(tipoLista *lst)
{
	if(lst->frente > lst->tras)
		return 1;
	else
		return 0;
}
void insereFim(tipoLista *lst, int valor)
{
	if(listaCheia(lst))
		printf("\nFILA CHEIA\n");
	else
	{
		lst->tras++;
		lst->vet[lst->tras]=valor;
	}
}
void imprime(tipoLista *lst)
{
	int i;
	if(listaVazia(lst))
		printf("\nFILA VAZIA\n");
	else
	{
		for(i = lst->frente; i <= lst->tras; i++)
			printf("%d\t", lst->vet[i]);
		printf("\ntras %d\n", lst->tras);
		printf("frente %d\n", lst->frente);
		printf("Tam %d\n", lst->tam);

	}
}
void insereInicio(tipoLista *lst, int valor)
{
	int i;
	if(listaCheia(lst))
		printf("\nFILA CHEIA\n");
	else
	{
		lst->tras++;
		for(i = lst->tras; i > lst->frente; i--)
			lst->vet[i]=lst->vet[i-1];
		lst->vet[lst->frente]=valor;
	}
}
void inserePosicao(tipoLista *lst, int valor, int posicao)
{
	int i;
	if(listaCheia(lst))
		printf("\nFILA CHEIA\n");
	else
	{	
		lst->tras++;
		if( (posicao >= 0) && (posicao < lst->tras) )
		{
			
			for(i = lst->tras; i > posicao; i--)
				lst->vet[i]=lst->vet[i-1];
			lst->vet[posicao]=valor;
			
		}
		else
			printf("\nIMPOSSIVEL COLOCAR VALOR NESTA POSIÇÃO\n");
	}
}	
/*int removerFim(tipoLista *lst)
{
	int aux, i;
	if(listaVazia(*lst))
	{
		printf("\nLISTA VAZIA\n");
		return 0;
	}
	else
	{
		aux=lst->tras;
		lst->tras--;
		return aux;
	}
}
int removerInicio(tipoLista *lst)
{
	int aux, i;
	if(listaVazia(*lst))
	{
		printf("\nLISTA VAZIA\n");
		return 0;
	}
	else
	{
		aux=lst->frente;
		for(i = lst->frente; i <= lst->tras; i++)
			lst->vet[i]=lst->vet[i+1];
		lst->tras--;
		return aux;
	}
}
int removerPosicao(tipoLista *lst, int posicao)
{
	int i, aux;
	if(listaVazia(*lst))
	{
		printf("\nLISTA VAZIA\n");
		return 0;
	}
	else
	{
		aux=lst->vet[posicao];
		if( (posicao >= 0) && (posicao < TAM) )
		{
			for(i = posicao; i < lst->tras; i++)
				lst->vet[i]=lst->vet[i+1];
		}
		else
			return 0;
		lst->tras--;

		return aux;
	}
}*/	

#endif			
