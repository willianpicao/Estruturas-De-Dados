#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct no {
    int inf;
    struct no *esq;
    struct  no *dir;
    int cor;
};
typedef struct no* ArvLLRB;

int cor(struct no* h){
    if(h == NULL)
        return BLACK;
    else
        return h->cor;
}

void trocaCor(struct no* h){
    h->cor = !h->cor;
    if(h->esq != NULL)
        h->esq->cor = !h->esq->cor;
    if (h->dir != NULL)
        h->dir->cor= !h->dir->cor;
}

struct no* rotacionaEsq(struct no* a){
    struct no* b= a->dir;
    a->dir= b->esq;
    b->esq= a;
    b->cor= a->cor;
    a->cor= RED;
    return b;
}

struct no* rotacionaDir(struct no* a){
    struct no* b = a->esq;
    a->esq= b->dir;
    b->dir= a;
    b->cor= a->cor;
    a->cor= RED;
    return b;
}

struct no* move2esqRed(struct no* h){
    trocaCor(h);
    if(cor(h->dir->esq) == RED ){
        h->dir = rotacionaDir(h->dir);
        h= rotacionaEsq(h);
        trocaCor(h);
    }
    return h;
}

struct no* move2DirRed(struct no* h){
    trocaCor(h);
    if(cor(h->esq->esq)==RED){
        h= rotacionaDir(h);
        trocaCor(h);
    }
    return h;
}

struct no* balancear(struct no* h){
    if( cor(h->dir)== RED)
        h= rotacionaEsq(h);
    if( (h->esq !=NULL) && (cor(h->dir)== RED) && (cor(h->esq->esq)==RED) )
        h= rotacionaDir(h);
    if( (cor(h->esq)==RED) && (cor(h->dir)==RED) )
        trocaCor(h);
    return h;
}

struct no* insereNo(struct no* h, int valor, int *resp){
    if(h == NULL){
        struct no *novo;
        novo = (struct no*)malloc (sizeof(struct no));
        if(novo == NULL){
            *resp=0;
            printf("Erro ao alocar novo no\n");
            return NULL;
        }
        novo->inf= valor;
        novo->cor= RED;
        novo->dir= NULL;
        novo->esq= NULL;
        *resp= 1;
        return novo;
    }

    if (valor == h->inf)
        *resp= 0;
    else
    {
        if(valor < h->inf)
            h->esq= insereNo(h->esq,valor,resp);
        else
            h->dir= insereNo(h->dir,valor,resp);
    }

    if( (cor(h->dir) == RED) && (cor(h->esq) == BLACK) )
        h= rotacionaDir(h);
    
    if ( (cor(h->esq) == RED) && (cor(h->dir) == RED) )
        trocaCor(h);
    
    return h;
}

struct no* removeMenor(struct no* h){
    if(h->esq == NULL){
        free (h);
        return NULL;
    }
    if ( (cor(h->esq) == BLACK) && (cor(h->esq->esq) == BLACK) )
        h= move2esqRed(h);
    
    h->esq= removeMenor(h->esq);
    return balancear(h);
}

struct no* procuraMenor(struct no* atual){
    struct no *no1= atual;
    struct no *no2= atual->esq;
    while ( no2 != NULL ){
        no1= no2;
        no2= no2->esq;
    }
    return no1;
    
}

struct no* removeNo(struct no* h, int valor){
    if(valor < h->inf){
        if( (cor(h->esq) == BLACK) && (cor(h->esq->esq) == BLACK) )
            h= move2esqRed(h);
        h->esq= removeNo(h->esq, valor);
    }else{
        if( cor(h->esq) == RED )
            h= rotacionaDir(h);
        if( (valor == h->inf) && (h->dir == NULL) ){
            free(h);
            return NULL;
        }
        if( (cor(h->dir)== BLACK) && (cor(h->dir->esq)== BLACK) )
            h= move2DirRed(h);
        if( valor== h->inf){
            struct no* x=procuraMenor(h->dir);
            h->inf= x->inf;
            h->dir= removeMenor(h->dir);
        }else
            h->dir= removeNo(h->dir,valor);
    }
    return balancear(h);
}

int insere_ArvLLRB(ArvLLRB* raiz, int valor){
    int resp;
    *raiz= insereNo(*raiz,valor,&resp);
    if( (*raiz) != NULL)
        (*raiz)->cor= BLACK;
    return resp;
}


int estaVazia(ArvLLRB *raiz){
    if(raiz==NULL)
        return 1;
    if(*raiz==NULL)
        return 1;
    return 0;
}

int remove_ArvLLRB(ArvLLRB *raiz, int valor){
    if( estaVazia(raiz) ){
        struct no* h= *raiz;
        *raiz= removeNo(h,valor);
        if(*raiz != NULL)
            (*raiz)->cor= BLACK;
        return 1;
    }else{
        return 0;
    }

}
//impressão em Ordem.
void print_emOrdem_ArvLLRB(ArvLLRB *raiz){
    if (raiz==NULL)
        return;
    if(*raiz != NULL){
        print_emOrdem_ArvLLRB(&((*raiz)->esq));
        printf("%d\n",(*raiz)->inf);
        print_emOrdem_ArvLLRB(&((*raiz)->dir));
    }
}
