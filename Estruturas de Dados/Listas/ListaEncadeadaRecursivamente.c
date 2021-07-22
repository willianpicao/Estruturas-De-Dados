#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int valor;
    struct no *prox;
}tipoNo;

void insereFimRec (tipoNo **lst, int vl); /*Função recursiva para inserção no final da lista*/
void imprimeEn(tipoNo *lst);
int excluiVl(tipoNo **lst, int num); /*Função para excluir um elemento da lista:*/
int removeFim(tipoNo **lst);
int removeInicio(tipoNo **lst);
int removePosicao(tipoNo **lst, int pos);
int alteraValor(tipoNo **lst, int vlantigo, int vlnovo);/*Função para alterar o valor de um elemento da lista:*/

int main (){
    tipoNo *no;
    no=NULL;

    insereFimRec(&no,5);
    insereFimRec(&no,9);
    insereFimRec(&no,14);
    insereFimRec(&no,15);
    insereFimRec(&no,16);
    insereFimRec(&no,17);
    removeFim(&no);
    imprimeEn(no);
    alteraValor(&no,5,15);
    imprimeEn(no);
    excluiVl(&no,9);
    imprimeEn(no);
	removeInicio(&no);
	imprimeEn(no);
}

void insereFimRec(tipoNo **lst, int vl)
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
		insereFimRec(&(*lst)->prox,vl);
	}
	else
		(*lst) = novoNo;
}

int excluiVl(tipoNo **lst, int num)
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
int removeInicio(tipoNo **lst)
{
	int valor;
    tipoNo aux1;

    if((*lst) == NULL)
             printf("A lista esta vazia\n");
    else
    {
        tipoNo *aux1;
        aux1 = (*lst);
        (*lst) = aux1->prox;
        valor = aux1->valor;
        free(aux1);
    }
    return valor;
	
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
int alteraValor(tipoNo **lst, int vlantigo, int vlnovo)
{
	tipoNo *aux1;
	int cont = 0;
    

	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else
	{
		aux1 = (*lst);
		
		while( (aux1->prox != NULL) && (aux1->valor != vlantigo) )
		{
			aux1 = aux1->prox;		
		}
        aux1->valor=vlnovo;
		
	}
}