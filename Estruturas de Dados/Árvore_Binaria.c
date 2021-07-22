#include <stdio.h>
#include <stdlib.h>

struct arv
{
    int dado;
    struct arv *esq;
    struct arv *dir;
    
}; typedef struct arv tipoArv;

//ESCROPO DAS FUNÇÕES 
tipoArv *alocaNo(int valor);
void insereNo(tipoArv **arv, int valor);
void imprimePre (tipoArv *arv);
void imprimeOrdem(tipoArv *arv);
void imprimePos(tipoArv *arv);
void imprimeNivel (tipoArv *arv, int nv);
int altura(tipoArv *arv);
void maiorValor (tipoArv *arv);
tipoArv *menorValor(tipoArv *arv);
tipoArv *removeVl(tipoArv *arv,int vl);

//FUNÇÃOM MAIN
int main (){
    tipoArv *arv;
    (arv)=NULL;

    insereNo (&arv,5);
    insereNo (&arv,10);
    insereNo (&arv,20);
    insereNo (&arv,30);
    insereNo (&arv,1);
    insereNo (&arv,2);
    insereNo (&arv,3);
    

            //Imprimindo em Pre Ordem
    //printf ("IMPRIMINDO EM PRE ORDEM\n");
    //    imprimePre(arv);
            //Imprimindo em Ordem
    printf ("\nIMPRIMINDO EM ORDEM\n");
        imprimeOrdem(arv);
            //Imprimindo em Pos ordem
    //printf("\nIMPRIMINDO EM POS ORDEM\n");
    //    imprimePos(arv);
            //Imprimindo Nivel
    printf ("\nIMPRIMINDO NIVEL\n");
        imprimeNivel(arv,2);
            //Imprimindo altura da arvore
    printf ( "\nA ALTURA DA ARVORE EH: %d\n" , altura(arv) );

            //Imprimindo maior valor da arvore
    maiorValor(arv);
            //Imprimindo o menor valor
    menorValor(arv);
            //removendo valor //
    printf("\nREMOVENDO VALOR\n");
        removeVl(arv,10);
        imprimeOrdem(arv);

}



//IMPLEMENTAÇÃO DAS FUNÇÕES
tipoArv *alocaNo(int valor){
    tipoArv *novoNo;
    novoNo = (tipoArv*) malloc (sizeof (tipoArv));
    if (novoNo==NULL)
        printf ("ERRO AO ALOCAR NO");
    else {
        novoNo->dado= valor;
        novoNo->esq= NULL;
        novoNo->dir= NULL;
    
        return novoNo;
    }
    
}
void insereNo (tipoArv **arv, int valor){
    if ((*arv)==NULL){
        (*arv)= alocaNo(valor);
    }
    else {
        if (valor<(*arv)->dado)
            insereNo( &(*arv)->esq,valor);
        else
            insereNo( &(*arv)->dir,valor);
    }
}

void imprimePre (tipoArv *arv){
    if(  (arv)!=NULL  ){
        printf("%d\t", (arv)->dado);
        imprimePre( (arv)->esq);
        imprimePre( (arv)->dir);
    }
}
void imprimeOrdem(tipoArv *arv){
    if ( (arv)!=NULL){
        imprimeOrdem( (arv)->esq );
        printf ("%d\t", (arv)->dado);
        imprimeOrdem( (arv)->dir );
    }
}
void imprimePos(tipoArv *arv){

    if ( (arv)!=NULL){
        imprimeOrdem( (arv)->esq );
        imprimeOrdem( (arv)->dir );
        printf ("%d\t", (arv)->dado);
    }
}
void imprimeNivel (tipoArv *arv, int nv){
    if (arv!=NULL){
        if (nv==0)
            printf ("%d\t", (arv)->dado);
        else{
            if(nv>0){
                imprimeNivel( (arv)->esq,nv-1);
                imprimeNivel( (arv)->dir,nv-1);
            }
        }
    }
}
int altura(tipoArv *arv)
{
	int hdir, hesq;
	if( arv != NULL )
	{
		if( (arv->esq == NULL) && (arv->dir == NULL) )
			return 0;
		else
		{
			hesq = altura(arv->esq);
			hdir = altura(arv->dir);
		}
		if( hesq > hdir )
			return hesq +1;
		else
			return hdir+1;
	}
	else
		return -1;
}
void maiorValor (tipoArv *arv){
    if (arv !=NULL){
        if (arv->dir != NULL)
            maiorValor(arv->dir);
        else
            printf ("O MAIOR VALOR EH:%d\n", arv->dado);
    }
}

tipoArv *menorValor (tipoArv *arv){
    if (arv != NULL){
        if(arv->esq != NULL)
            menorValor(arv->esq);
        else{
            printf("O MENOR VALOR EH:%d\n",arv->dado);
            return arv;
        }
    }
    else
    {
        return NULL;
    }
    
}
int busca(tipoArv *arv, int vl){
    if ( arv != NULL){
        if (vl==arv->dado){
            printf("\nValor Encontrado:\n%d\n", arv->dado);
            return 1;
        }
        else{
            if (vl < arv->dado)
                busca(arv->esq,vl);
            else
                busca(arv->dir,vl);
            
        }
    }
}
tipoArv *removeVl(tipoArv *arv,int vl){
    tipoArv *aux;
    if (arv!=NULL){
        if ( vl<arv->dado ){
            removeVl(arv->esq,vl);
        }else if(vl>arv->dado){
            removeVl(arv->dir,vl);
        }else{
            if ( (arv->esq==NULL) && (arv->dir==NULL) ){
                free (arv);
                return NULL;
            }else if ( (arv->esq==NULL) && (arv->dir!=NULL) ){
                aux=arv->dir;
                free(arv);
                return aux;
            }else if( (arv->dir==NULL) && (arv->esq != NULL) ){
                aux=arv->esq;
                free (arv);
                return aux;
                
            }else{
                int menor;
                menor=menorValor(arv->dir);
                arv=removeVl(arv->dir,menor);
                arv->dado=menor;
                return arv;
            }
        }
    }

}