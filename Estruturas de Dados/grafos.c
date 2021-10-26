#include <stdio.h>
#include <stdlib.h>

//Estruturas.
typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
}TVizinho;

typedef struct grafo{
    int id_vertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
}TGrafo;


//Funções básicas.
TGrafo *inicializa(){
    return NULL;
}

void printGrafo(TGrafo *g){
    while (g != NULL)
    {
        printf ("Vertice %d\n",g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v= g->prim_vizinho;
        while(v !=NULL)
        {
            printf("%d ", v->id_vizinho);
            v= v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}
//Removendo vizinhos de forma iterativa__
void libera(TGrafo *g){
    while(g != NULL)
    {
        libera_vizinhos(g->prim_vizinho);
        TGrafo *aux = g;
        g= g->prox;
        free(aux);
    }
}
void libera_vizinhos(TVizinho *v){
    while(v != NULL){
        TVizinho *aux= v;
        v= v->prox;
        free(aux);
    }
}

//Removendo vizinhos de forma recursiva__
void libera_recursivo(TGrafo *g){
    if (g != NULL){
        libera_vizinho_recursivo(g->prim_vizinho);
        libera_recursivo(g->prox);
        free(g);
    }
}
void libera_vizinho_recursivo(TVizinho *v){
    if(v != NULL){
        libera_vizinho_recursivo(v->prox);
        free(v);
    }
}


//Buscas.
TGrafo* busca_vertice(TGrafo *g, int v){
    while ( (g != NULL) && (g->id_vertice != v) )
        g= g->prox;
    return g;
}

TVizinho* busca_aresta(TGrafo *g, int v1, int v2){
    TGrafo *pv1 = busca_vertice(g,v2);
    TGrafo *pv2= busca_vertice(g,v2);
    TVizinho *resp= NULL;
    //chega se ambos os vertices existem
    if ( (pv1 != NULL) && (pv2 != NULL) ){
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (resp->id_vizinho != v2) )
            resp= resp->prox;
    }
    return resp;
}


//Inserções.
TGrafo* insere_vertice(TGrafo *g, int v){
    TGrafo *p= busca_vertice(g,v);
    if (p == NULL){
        p = (TGrafo*) malloc (sizeof(TGrafo));
        p->id_vertice= v;
        p->prox=g;
        p->prim_vizinho= NULL;
        g= p;
    }
    return g;
}

//Inserções.
void insere_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p= busca_vertice(g,v1);
    TVizinho *nova= (TVizinho*)malloc(sizeof(TVizinho));
    nova->id_vizinho= v2;
    nova->prox=p->prim_vizinho;
    p->prim_vizinho= nova;
}
void insere_aresta(TGrafo *g, int v1, int v2){
    TVizinho *v= busca_aresta(g,v1,v2);
    if (v==NULL){
        insere_um_sentido(g,v1,v2);
        insere_um_sentido(g,v2,v1);
    }
}

void insere_aresta_digrafo(TGrafo *g, int v1, int v2){
    TVizinho *v= busca_aresta(g,v1,v2);
    if(v==NULL)
        insere_um_sentido(g,v1,v2);
}


//Retiradas.
void retira_um_sentido(TGrafo *g, int v1,int v2){
    TGrafo *p= busca_vertice(g,v1);
    if(p!= NULL){
        TVizinho *ant=NULL;
        TVizinho *atual= p->prim_vizinho;
        while ( (atual) && (atual->id_vizinho) ){
            ant= atual;
            atual= atual->prox;
        }
        if (ant == NULL)// v2 era o primeiro nó da lista
            p->prim_vizinho= atual->prox;
        else
            ant->prox= atual->prox;
        free(atual);
    }
}

void retira_aresta(TGrafo *g, int v1, int v2){
    TVizinho *v= busca_aresta(g,v1,v2);
    if(v != NULL){
        retira_um_sentido(g,v1,v2);
        retira_um_sentido(g,v2,v1);
    }
}

TGrafo *retira_vertice(TGrafo *g, int v){
    TGrafo *p= g;
    TGrafo *ant= NULL;
    while ( (p!=NULL) && (p->id_vertice!=v) ){
        ant=p;
        p= p->prox;
    }
    if(p!=NULL){
        while ( (p->prim_vizinho != NULL) )
            retira_aresta(g,v,p->prim_vizinho->id_vizinho);
        if(ant == NULL)
            g= g->prox;
        else
            ant->prox= p->prox;
        free(p);  
    }
    return g;
}
