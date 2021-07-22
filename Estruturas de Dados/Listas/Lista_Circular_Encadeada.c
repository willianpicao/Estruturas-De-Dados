#include <stdio.h>
#include<stdlib.h>
struct no
{
	int dado;
	struct no *prox;
};

typedef struct no tipoNo;

void insereInicio(tipoNo **lst,int dado);
void insereFim(tipoNo **lst,int valor);
void inserePos(tipoNo **lst,int valor, int pos);
void imprime(tipoNo *lst);
int removeInicio(tipoNo **lst);
int removeFim(tipoNo **lst);
int removePosicao(tipoNo **lst, int pos);
int removeNum(tipoNo **lst, int n);

int main ()
{
    tipoNo *no;
    no=NULL;
   insereInicio(&no,4);
   insereInicio(&no,3);
   insereInicio(&no,2);
   insereInicio(&no,1);
   insereInicio(&no,10);
   insereInicio(&no,20);
   imprime(no);
   printf("\n");
   
   removePosicao(&no,0);
   imprime(no);
   removePosicao(&no,3);
   imprime(no);
   removePosicao(&no,5);
   imprime(no);
   printf("Removendo numero por busca\n");
   removeNum(&no,1);
   imprime(no);
  
    return 1;
}
int removeNum(tipoNo **lst, int n)
{
	tipoNo *aux1, *aux2;
	int dado;
	
	if( (*lst) == NULL )
		printf("LISTA VAZIA\n");
	else if( (*lst)->dado == n )
		removeInicio(lst);
	else
	{
		aux1 = (*lst);
		
		while( (aux1->prox != (*lst)) && (aux1->dado != n) )
		{
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( aux1->dado == n )
		{
			dado = aux1->dado;
			aux2->prox = aux1->prox;
			free(aux1);
			
			return dado;
		}
		else
			removeFim(lst);
	}
}
void insereInicio(tipoNo **lst, int valor)
{
	tipoNo *novoNo, *aux;
	if ((*lst)==NULL){
        novoNo = (tipoNo*) malloc ( sizeof (tipoNo) );
        novoNo->dado=valor;
        (*lst)=novoNo;
        novoNo->prox=(*lst);
        

    }else{
        novoNo = (tipoNo*) malloc ( sizeof (tipoNo) );
        novoNo->dado=valor;
        novoNo->prox=(*lst);
        aux=(*lst);
        while ( aux->prox!=(*lst) )
            aux=aux->prox;
        aux->prox=novoNo;
        (*lst)=novoNo;
        
    }

    
}
void insereFim(tipoNo **lst, int valor){
   tipoNo *novoNo,*aux;
   aux=(*lst);

    if ((*lst)==NULL){
        novoNo = (tipoNo*)malloc(sizeof(tipoNo*) );
        novoNo->dado=valor;
        (*lst)=novoNo;
        novoNo->prox=(*lst);
    }else{
        while ( aux->prox!=(*lst))
            aux=aux->prox;
        novoNo = (tipoNo*)malloc(sizeof(tipoNo*) );
        novoNo->dado=valor;
        aux->prox=novoNo;
        novoNo->prox=(*lst);
    }
}
void inserePos(tipoNo **lst,int valor,int posicao){
    tipoNo *aux1,*aux2,*novoNo;
    int cont=0;
    aux1=(*lst);
    novoNo= (tipoNo*) malloc (sizeof (tipoNo));
    if (novoNo==NULL)
        printf("O novo nó n foi alocado");
    else {
        if((posicao==0) && ((*lst)==NULL)){
            novoNo->dado=valor;
            novoNo->prox=(*lst);
            (*lst)=novoNo;
            
        }
            
        novoNo->dado=valor;
        while( (cont<posicao) && (aux1->prox!=(*lst)) ){
            aux2=aux1;
            aux1=aux1->prox;
            cont++;
        }
        aux2->prox=novoNo;
        novoNo->prox=aux1;
    }
}
int removeInicio(tipoNo **lst)
{
	tipoNo *aux1, *aux2;
	int dado;
	
	
	if( (*lst) == NULL )
		printf("\nLISTA VAZIA\n");
	else if( (*lst) == (*lst)->prox )
	{
		aux1 = (*lst);
		dado = aux1->dado;
		free( (*lst) );
		(*lst) = NULL;
		
		return dado;
		
	}
	else
	{
		aux2 = (*lst);
		while( aux2->prox != (*lst) )
			aux2 = aux2->prox;
		aux1 = (*lst);
		dado = aux1->dado;
		(*lst) = (*lst)->prox;
		aux2->prox = (*lst);
		
		free(aux1);
		
		return dado;
	}
	
}
int removeFim(tipoNo **lst)
{
	tipoNo *aux1, *aux2;
	int dado;
	
	if( (*lst) == NULL ) 
		printf("LISTA VAZIA\n");
	else if ( (*lst) == (*lst)->prox )
	{
		aux1 = (*lst);
		dado = aux1->dado;
		free( (*lst) );
		(*lst) = NULL;
		
		return dado;
	}
	else
	{
		aux1 = (*lst);
		while( aux1->prox != (*lst) )
		{
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		dado = aux1->dado;
		aux2->prox = aux1->prox;
		free(aux1);
		
		return dado;
	}
}
int removePosicao(tipoNo **lst, int pos)
{
	tipoNo *aux1, *aux2;
	int dado, cont;
	
	cont = 0;
	
	if( (*lst) == NULL )
		printf("LISA VAZIA\n");
	else if( (*lst) == (*lst)->prox)
	{
		aux1 = (*lst);
		dado = aux1->dado;
		free( (*lst) );
		(*lst) = NULL;
		
		return dado;
	}
	else if(pos == 0)
		removeInicio(lst);
	else
	{
		aux1 = (*lst);
		
		while( ( aux1->prox != (*lst) ) && (cont < pos) )
		{
			cont++;
			aux2 = aux1;
			aux1 = aux1->prox;
		}
		if( (cont == pos) && (pos > 0) )
		{
			dado = aux1->dado;
			aux2->prox = aux1->prox;
			free(aux1);
			
			return dado;
		}
		else
			removeFim(lst);
	}
}
void imprime(tipoNo *lst)
{
	tipoNo *aux;	
	aux=(lst);

        if((lst==NULL))
            printf("Lista Vazia");
        else{

            if (aux->prox==lst){
                printf("%d\n",aux->dado);
            }
            else{
               do
                {
                    printf("%d\t",aux->dado);
                    aux=aux->prox;
                }while ( aux!= lst);
            }
        }
        printf("\n");

}