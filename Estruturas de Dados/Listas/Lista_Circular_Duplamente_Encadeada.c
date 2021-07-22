#include<stdio.h>
#include<stdlib.h>

struct no
{
    int valor;
    struct no *prox;
    struct no *ant;
};
typedef struct no tipoNo;

void insereInicio(tipoNo **lst,int valor);
void insereFim(tipoNo **lst,int valor);
void inserePos(tipoNo **lst,int valor, int pos);
void imprime(tipoNo *lst);
int removeInicio(tipoNo **lst);
int removeFim(tipoNo **lst);
int removePosicao(tipoNo **lst,int pos);
int removeBus(tipoNo **lst,int valor);
tipoNo *inicializaNo(int valor);


int main (){
    tipoNo *lista;
    lista=NULL;
    /*insereInicio(&lista,10);
    insereInicio(&lista,20);
    imprime(lista);
    printf("Inserindo ao  final das lista\n");
    insereFim(&lista, 50);
    insereFim(&lista, 60);
    imprime(lista);*/
    printf("Inserindo por posicao\n");
    inserePos(&lista, 100,0);
    inserePos(&lista, 200,1);
    //inserePos(&lista, 300,2);
    imprime(lista);
    removeInicio(&lista);
    imprime(lista);



}

tipoNo *inicializaNo (int valor){
    tipoNo *novoNo;
    novoNo =(tipoNo*) malloc (sizeof(tipoNo));
    if (novoNo==NULL)
        printf("n foi alocado");
    else {
        novoNo->valor=valor;
        novoNo->prox=novoNo;
        novoNo->ant=novoNo; 
    }
    return novoNo;
}

void insereInicio(tipoNo **lst, int valor){
    tipoNo *aux;
    aux=(*lst);
    if ((*lst)==NULL)
        (*lst)=inicializaNo(valor);
    else{
        tipoNo *novoNo;
        novoNo=inicializaNo(valor);
        if (novoNo==NULL)
            printf("nao alocou");
        else{
            aux->ant->prox=novoNo;
            novoNo->prox=(*lst);
            novoNo->ant=aux->ant;
            aux->ant=novoNo;
            (*lst)=novoNo;
        }
    }
}
void insereFim(tipoNo **lst, int valor){
    tipoNo *aux;
    aux=(*lst);
    if ((*lst)==NULL)
        (*lst)=inicializaNo(valor);
    else{
        tipoNo *novoNo;
        novoNo=inicializaNo(valor);
        if (novoNo==NULL)
            printf("nao alocou");
        else{
            aux->ant->prox=novoNo;
            novoNo->prox=(*lst);
            novoNo->ant=aux->ant;
            aux->ant=novoNo;
        }
    }
}
void inserePos(tipoNo **lst, int valor, int pos)
{
	tipoNo *novoNo, *aux1, *aux2;
	int cont = 0;
	
	if( (*lst) == NULL || pos == 0 )
		insereInicio(lst, valor);
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
			novoNo = inicializaNo(valor);
			aux2->prox = novoNo;
			novoNo->ant = aux2;
			novoNo->prox = aux1;
			aux1->ant = novoNo;
		}
		else
			insereFim(lst, valor);
	}
}
int removeInicio(tipoNo **lst){
    if((*lst)==NULL)
        printf("Impossivel remover pois lista esta vazia");
    else{
        tipoNo *aux;
        int dado;
        dado=aux->valor;
        (*lst)=aux->prox;
        aux->ant->prox=(*lst);
        aux->prox->ant=aux->ant;
        free (aux);
        return dado;
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
                printf("%d\n",aux->valor);
            }
            else{
               do
                {
                    printf("%d\t",aux->valor);
                    aux=aux->prox;
                }while ( aux!= lst);
            }
        }
        printf("\n");

}