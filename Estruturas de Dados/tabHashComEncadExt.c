#include <stdio.h>
#include <stdlib.h>

typedef struct aluno
{
    int matricula;
    float cr;
    struct aluno *prox;
}TAluno;
typedef TAluno* Hash;

TAluno* aloca(int mat,float cr){
    TAluno *novo= (TAluno*)malloc (sizeof(TAluno));
    novo->matricula=mat;
    novo->cr=cr;
    novo->prox=NULL;
    return novo;
}

int hash(int mat, int tam){
    return mat%tam;
}

void inicializaTab(Hash *tab,int m){
    for(int i=0;i<m;i++)
        tab[i]=NULL;
}
void insere(Hash *tab, int m, int mat, float cr){
    int h= hash(mat,m);
    TAluno *p=tab[h];
    TAluno *ant=NULL;
    while((p!=NULL)&&(p->matricula!=mat)){
        ant=p;
        p=p->prox;
    }
    
    if (p){
        p->cr=cr;
        return;
    }

    TAluno *novo= aloca(mat,cr);
    if(!ant)
        tab[h]=novo;
    else
        ant->prox=novo;

}

TAluno* busca(Hash *tab,int m,int mat){
    int h=  hash(mat,m);
    TAluno *p=tab[h];
    while ((p)&&(p->matricula != mat))
    {
        p=p->prox;
    }
    return p;
    
}

float exclui(Hash *tab, int m, int mat){
    int h=hash(mat,m);
    if (tab[h]==NULL)
        return -1;
    
    TAluno *p=tab[h];
    TAluno *ant=NULL;
    float cr=-1;

    while ( (p!=NULL) && (p->matricula!=mat) ){
        ant=p;
        p= p->prox;
    }
    if (p==NULL)
        return cr;
    if (ant==NULL)
        tab[h]=p->prox;
    else
        ant->prox=p->prox;
    cr=p->cr;
    free(p);
    return cr;


}

void imprime(Hash *tab, int m){
    for(int i=0;i<m;i++){
        printf("%d",i);
        if(tab[i]){
            TAluno *p=tab[i];
            printf("\n");
            while (p)
            {
                printf("\t%d\t%f\t%p\n",p->matricula,p->cr,p->prox);
                p=p->prox;
            }
            
        }else
            printf("NULL\n");
    }
}

void libera(Hash *tab, int m){
    int i;
    for(i=0;i<m;i++){
        if (tab[i]){
            TAluno *p=tab[i];
            TAluno *q;
            while (p)
            {
                q=p;
                p=p->prox;
                free(q);
            }
            
        }
    }
}

int main ()
{
    int m;
    m =5;
    Hash *tab[m];
    inicializaTab(tab,m);
    insere(tab,m,12,5.8);
    insere(tab,m,3,7.2);
    insere(tab,m,12,4.5);
    insere(tab,m,18,9.1);
    insere(tab,m,9,6.3);
    insere(tab,m,13,9);
    insere(tab,m,21,7);
    insere(tab,m,25,4);
    insere(tab,m,21,7);
    insere(tab,m,25,4);

    imprime(tab,m);

    TAluno *p=busca (tab,m,18);
    if (!p)
        printf ("Elemento n encontrado!\n");
    else
        printf ("Elemento encontrado\n%d\t%f\n",p->matricula,p->cr);
    
    printf("................\n");
    int cr = exclui(tab,m,18);
    if (cr != -1)
        printf("\n%d\t%fFoi excluido\n",18,cr);

    imprime(tab,m);

    libera(tab,m);

}