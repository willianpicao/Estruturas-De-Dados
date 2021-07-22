#ifndef listaDuplamenteEncadeada_c
#define listaDuplamenteEncadeada_c

#include<stdio.h>
#include<stdlib.h>

struct listaDu
{
	int valor;
	struct listaDu *prox;
	struct listaDu *ant;
};

typedef struct listaDu tipoNoo;

tipoNoo *alocaNo(int vl);
void insereInicioDu(tipoNoo **lst, int vl);
void insereFimDu(tipoNoo **lst, int vl);
void inserePosicaoDu(tipoNoo **lst, int vl, int pos);
/*int removeInicio(tipoNo **lst);
int removeFim(tipoNo **lst);
int removePosicao(tipoNo **lst, int pos);
int removeBusca(tipoNo **lst, int n);
void imprimedu(tipoNo *lst);*/

/*int main()
{
	tipoNo *no;
	
	no = NULL;
	
	//INSERINDO VALORES NO INICIO DA LISTA
	insereInicio(&no, 1);
	insereInicio(&no, 10);
	insereInicio(&no, 5);
	insereInicio(&no, 7);
	insereInicio(&no, 2);
	
	//INSERINDO VALORES NO FIM DA LISTA
	insereFim(&no, 2);
	insereFim(&no, 3);
	insereFim(&no, 1);
	insereFim(&no, 10);
	insereFim(&no, 9);
	
	//INSERINDO POR POSIÇÃO
	inserePosicao(&no, 5, 0);
	inserePosicao(&no, 20, 2);
	inserePosicao(&no, 50, 7);
	
	//IMPRIMINDO OS VALORES DA LISTA
	imprime(no);
	
	//REMOVENDO NO INICIO DA LISTA
	//removeInicio(&no);
	//removeInicio(&no);
	
	//REMOVE NO FIM DA LISTA
	//removeFim(&no);
	//removeFim(&no);
	
	//REMOVE POR POSIÇÃO
	//removePosicao(&no, 0);
	//removePosicao(&no, 2);
	//removePosicao(&no, 4);
	
	//REMOVE NA LISTA POR BUSCA
	removeBusca(&no, 2);
	removeBusca(&no, 10);
	removeBusca(&no, 9);
	
	//IMPRIMINDO LISTA REMOVIDA
	imprime(no);
	
	return 1;
}*/

tipoNoo *alocaNo(int vl)
{
	tipoNoo *novoNo;
	
	novoNo = (tipoNoo*) malloc ( sizeof (tipoNoo) );
	if(novoNo == NULL)
		printf("IMPOSSIVEL ALOCAR\n");
	else
	{
		novoNo->valor = vl;
		novoNo->prox = NULL;
		novoNo->ant = NULL;
		
		return novoNo;
	}
}
void insereInicioDu(tipoNoo **lst, int vl)
{
	tipoNoo *aux;
	
	if( (*lst) == NULL )
		(*lst) = alocaNo(vl);
	else
	{
		aux = alocaNo(vl);
		aux->prox = (*lst);
		(*lst)->ant = aux;
		(*lst) = aux;
	}
}
void insereFimDu(tipoNoo **lst, int vl)
{
	tipoNoo *novoNo, *aux;
	
	if( (*lst) == NULL )
		(*lst) = alocaNo(vl);
	else
	{
		novoNo = alocaNo(vl);
		aux = (*lst);
		while( aux->prox != NULL )
			aux = aux->prox;
		aux->prox = novoNo;
		novoNo->ant = aux;
	}	
}
void inserePosicaoDu(tipoNoo **lst, int vl, int pos)
{
	tipoNoo *novoNo, *aux1, *aux2;
	int cont = 0;
	
	if( (*lst) == NULL )
		(*lst) = alocaNo(vl);
	else
	{
		aux1 = (*lst);
		while( (aux1->prox != NULL) && (cont < pos) )
		{
			cont++;
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( (cont == pos) && (pos > 0) )
		{
			novoNo = alocaNo(vl);
			aux2->prox = novoNo;
			novoNo->ant = aux2;
			novoNo->prox = aux1;
			aux1->ant = novoNo;
		}
		else if ( pos == 0 )
			insereInicioDu(lst, vl);
		else
			insereFimDu(lst, vl);
	}
}
/*int removeInicio(tipoNo **lst)
{
	tipoNo *aux;
	int dado;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else if( (*lst)->prox == NULL )
	{
		dado = (*lst)->valor;
		free( (*lst) );
		(*lst) = NULL;
		
		return dado;
	}
	else
	{
		aux = (*lst);
		dado = aux->valor;
		(*lst) = (*lst)->prox;
		(*lst)->ant = NULL;
		free(aux);
		
		return dado;
	}
}
int removeFim(tipoNo **lst)
{
	tipoNo *aux1, *aux2;
	int dado;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else if( (*lst)->prox == NULL )
		removeInicio(lst);
	else
	{
		aux1 = (*lst);
		while( aux1->prox != NULL )
		{
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		dado = aux1->valor;
		aux2->prox = NULL;
		free(aux1);
		
		return dado;
	}
}
int removePosicao(tipoNo **lst, int pos)
{
	tipoNo *aux1, *aux2;
	int dado, cont =0;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else
	{
		aux1 = (*lst);
		
		while( (aux1->prox != NULL) && (cont < pos) )
		{
			cont++;
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( (cont == pos) && (pos > 0) )
		{
			dado = aux1->valor;
			aux2->prox = aux1->prox;
			aux1->prox->ant = aux2;
			free(aux1);
			
			return dado;
		}
		else if(pos == 0)
			removeInicio(lst);
		else
			removeFim(lst);
	}
}
int removeBusca(tipoNo **lst, int n)
{
	tipoNo *aux1, *aux2;
	int cont = 0, dado;
	
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else
	{
		aux1 = (*lst);
		
		while( (aux1->prox != NULL) && (aux1->valor != n) )
		{
			cont++;
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( cont == 0 )
			removeInicio(lst);
		else if(aux1->prox == NULL)
			removeFim(lst);
		else
			removePosicao(lst, cont);
	}
}*/										 	
void imprimeDu(tipoNoo *lst)
{
	if( lst == NULL )
		printf("LISTA VAZIA\n");
	else
	{
		while( lst->prox != NULL )
		{
			printf("%d\t", lst->valor);
			lst = lst->prox;
		}
		printf("%d\t", lst->valor);
		printf("\n");	
	}
}

#endif
