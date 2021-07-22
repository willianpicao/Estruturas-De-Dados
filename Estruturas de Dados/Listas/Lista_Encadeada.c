#ifndef listaEncadeada_c
#define listaEncadeada_c

#include<stdio.h>
#include<stdlib.h>

struct no
{
	int valor;
	struct no *prox;
};

typedef struct no tipoNo;


void insereFimEn(tipoNo **lst, int);
void imprimeEn(tipoNo *lst);
void insereInicioEn(tipoNo **lst, int);
void inserePosicaoEn(tipoNo **lst, int, int pos);
int removeInicio(tipoNo **lst);
int removeFim(tipoNo **lst);
int removePosicao(tipoNo **lst, int pos);
int removeNum(tipoNo **lst, int);
void removeEspecial(tipoNo **lst);

/*int main()
{
	tipoNo *no;
	no =  NULL;
	
	printf("INSERINDO VALOR NA LISTA\n");
	//INSERINDO NO FIM
	insereFim(&no, 7);
	insereFim(&no, 2);
	insereFim(&no, 3);
	insereFim(&no, 10);
	insereFim(&no, 6);
	
	imprime(no);
	
	//INSERINDO NO INICIO
	/*insereInicio(&no, 3);
	insereInicio(&no, 2);
	insereInicio(&no, 5);*/
	
	//INSERINDO POR POSIÇÃO
	/*inserePosicao(&no, 37, 0);
	inserePosicao(&no, 266, 1);
	inserePosicao(&no, 40, 2);
	inserePosicao(&no, 157, 0);
	inserePosicao(&no, 17, 1);
	inserePosicao(&no, 15, 2);*/
	
	/*removeInicio(&no);
	removeInicio(&no);*/
	
	/*removeFim(&no);
	removeFim(&no);*/
	
	/*removePosicao(&no, 2);
	removePosicao(&no, 0);
	removePosicao(&no, 4);*/
	
	/*removeNum(&no, 2);
	removeNum(&no, 3);
	removeNum(&no, 4);
	
	// QUESTÃO DA PROVAAA
	removeEspecial(&no);
	
	printf("REMOVENDO\n");
	
	imprime(no);
	
	
	return 1;
	
}*/
void insereFimEn(tipoNo **lst, int vl)
{
	tipoNo *aux, *novoNo;
	novoNo = (tipoNo*) malloc ( sizeof (tipoNo) );
	if(novoNo == NULL)
		printf("IMPOSSIVEL ALOCAR\n");
	else
	{
		novoNo->valor = vl;
		novoNo->prox = NULL;
	}
	
	if((*lst) != NULL)
	{
		aux = (*lst);
		
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novoNo;
	}
	else
		(*lst) = novoNo;
}
void insereInicioEn(tipoNo **lst, int vl)
{
	tipoNo *novoNo;
	novoNo = (tipoNo*) malloc ( sizeof (tipoNo) );
	if(novoNo == NULL)
		printf("IMPOSSIVEL ALOCAR\n");
	else
	{
		novoNo->valor = vl;
		novoNo->prox = NULL;
	}
	
	if( (*lst) == NULL )
		(*lst) = novoNo;
	else
	{
		novoNo->prox = (*lst);
		(*lst) = novoNo;
	}	
}
void inserePosicaoEn(tipoNo **lst, int vl, int pos)
{
	tipoNo *aux1, *aux2, *novoNo;
	int cont;
	
	cont = 0;
	
	novoNo = (tipoNo*) malloc ( sizeof (tipoNo) );
	if(novoNo == NULL)
		printf("IMPOSSIVEL ALOCAR\n");
	else
	{
		novoNo->valor = vl;
		novoNo->prox = NULL;
	}
	if( (*lst) == NULL )
		(*lst) = novoNo;
		
	else	
	{
		aux1 = (*lst);
		
		while( (cont < pos) && (aux1 != NULL) )
		{
			cont ++;
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( (cont == pos) && (pos > 0) )
		{
			novoNo->prox = aux1;
			aux2->prox = novoNo;
		}
		else
			insereInicioEn(lst, vl);
	} 	
}
int removeInicio(tipoNo **lst)
{
	tipoNo *aux1, *aux2;
	int dado;
	
	aux1 = (*lst);
	
	if( (*lst) == NULL )
		printf("\nLISTA VAZIA\n");
	else if( aux1->prox == (*lst)->prox )
	{
		dado = aux1->valor;
		free(aux1);
		(*lst)->prox = NULL;
		
		return dado;
	}
	else
	{
		aux2 = (*lst);
		while( aux2->prox != (*lst) )
			aux2 = aux2->prox;
		aux1 = (*lst);
		dado = aux1->valor;
		(*lst) = (*lst)->prox;
		aux2->prox = (*lst);
		
		free(aux1);
		
		return dado;
	}
	
}					
int removeFim(tipoNo **lst)
{
	tipoNo *aux1, *aux2;
	int dado, cont = 0;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else if ( (*lst)->prox == NULL )
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
	}
	
	return dado;	
}
int removePosicao(tipoNo **lst, int pos)
{
	tipoNo *aux1, *aux2;
	int cont = 0, dado;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else if ( pos == 0 )
		removeInicio(lst);
	else
	{
		aux1 = (*lst);
		while( ( cont < pos ) && ( aux1->prox != NULL) )
		{
			cont++;
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( cont == pos)
		{
			dado = aux1->valor;
			aux2->prox = aux1->prox;
			free(aux1);
		}
		else
			removeFim(lst);
	}	
	return dado;
}	
int removeNum(tipoNo **lst, int num)
{
	tipoNo *aux1, *aux2;
	int dado, cont = 0;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else
	{
		aux1 = (*lst);
		
		while( (aux1->prox != NULL) && (aux1->valor != num) )
		{
			cont++;
			aux1 = aux1->prox;		
		}
		removePosicao(lst, cont);
	}
}		
void imprimeEn(tipoNo *lst)
{	
	
	if( lst == NULL )
		printf("Lista vazia\n");
	else
	{
		
		while( lst != NULL)
		{
			printf("%d\t", lst->valor);
			lst = lst->prox;
		}
		printf("\n");
	}
}
void removeEspecial(tipoNo **lst)
{
	tipoNo *aux1, *aux2;

	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else if( (*lst)->prox == NULL )
	{
		free( (*lst) );
		(*lst) = NULL;
	}
	else
	{
		aux1 = (*lst);
		(*lst) = (*lst)->prox;
		free( aux1 );
		
		aux1 = (*lst);
		while( aux1->prox != NULL )
		{
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		free( aux1 );
		aux2->prox = NULL;
	}
}	

#endif
