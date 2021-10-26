#include <stdlib.h>
#include <stdio.h>

#include "Valores.c"

#define LINHAS 4
#define COLUNAS 7

typedef struct Node
{
    float valor;
    int coluna;
    struct Node *prox;
} Node;

typedef Node *list;

typedef struct
{
    list *ls;
    int linhas;
    int colunas;
} matrix;

void iniciaMatrix(matrix *m, int row, int col)
{
    m->linhas = row;
    m->colunas = col;
    m->ls = (list *) malloc(row * sizeof(list));

    for (int i = 0; i < row; i++)
        m->ls[i] = NULL;
}

int insereMatrix(matrix *m, int linha, int col, float valor)
{
    if (linha < 0 || linha >= m->linhas || col < 0 || col >= m->colunas)
        return 0;

    list prev = NULL;
    list curr = m->ls[linha];

    while (curr != NULL && curr->coluna < col)
    {
        prev = curr;
        curr = curr->prox;
    }

    if (curr != NULL && curr->coluna == col)
    {
        if (valor == 0.0)
        {
            if (prev == NULL)
                m->ls[linha] = curr->prox;
            else
                prev->prox = curr->prox;
            free(curr);
        }
        else
            curr->valor = valor;
    }
    else if (valor != 0)
    {
        list novo = (list)malloc(sizeof(Node));
        novo->coluna = col;
        novo->valor = valor;
        novo->prox = curr;

        if (prev == NULL)
            m->ls[linha] = novo;
        else
            prev->prox = novo;
    }

    return 1;
}

float procura(matrix *m, int linha, int col)
{
    if (linha < 0 || linha >= m->linhas || col < 0 || col >= m->colunas)
        return 0;

    list curr = m->ls[linha];

    while (curr != NULL && curr->coluna < col)
        curr = curr->prox;

    if (curr != NULL && curr->coluna == col)
        return curr->valor;

    return 0;
}

int deleta(matrix *m, int linha, int col)
{
    if (linha < 0 || linha >= m->linhas || col < 0 || col >= m->colunas)
        return 0;
    
    list prev = NULL;
    list curr = m->ls[linha];

    while (curr != NULL && curr->coluna < col)
    {
        prev = curr;
        curr = curr->prox;
    }

    if (curr != NULL && curr->coluna == col)
    {     
        if (prev == NULL)
            m->ls[linha] = curr->prox;
        else
            prev->prox = curr->prox;
        free(curr);

        return 1;
    }
    return 0;
}

void printMatrix(matrix *m)
{
    list curr;
    for (int i = 0; i < m->linhas; i++)
    {
        curr = m->ls[i];
        printf("\n");
        while (curr != NULL && curr->coluna < m->colunas)
        {
            printf("\nValor[%d][%d] = %.2f", i, curr->coluna, curr->valor);
            curr = curr->prox;
        }
    }
    printf("\n");
}


void multiplicaMatrix(matrix *m, int N)
{
    list curr;
    for (int i = 0; i < m->linhas; i++)
    {
        curr = m->ls[i];
        while (curr != NULL && curr->coluna < m->colunas)
        {
            curr->valor *= N; 
            curr = curr->prox;
        }
    }
}

//Soma todos os elementos da matriz
float somaElementos_da_Matrix(matrix *m)
{
    float soma = 0;
    list curr;
    for (int i = 0; i < m->linhas; i++)
    {
        curr = m->ls[i];
        while (curr != NULL && curr->coluna < m->colunas)
        {
            soma += curr->valor; 
            curr = curr->prox;
        }
    }
    return soma;
}

//Soma duas matrizes e retorna uma terceira

matrix *soma_e_nova_Matrix(matrix *m1, matrix *m2)
{
    matrix *m3 = (matrix *) malloc(sizeof(matrix));
    iniciaMatrix(m3,LINHAS,COLUNAS);

    int col = 0;
    float val= 0; 
    
    list curr1, curr2;
    for (int linhax = 0; linhax< m1->linhas; linhax++)
    {
        curr1 = m1->ls[linhax];
        curr2 = m2->ls[linhax];
        while (curr1 != NULL && curr2 != NULL)
        {
            if(curr1 == NULL && curr2 != NULL)
            {
                val = curr2->valor;
                col = curr2->coluna;
                curr2 = curr2->prox;
            }
            else if (curr2 == NULL && curr1 != NULL)
            {
                val = curr1->valor;
                col = curr1->coluna; 
                curr1 = curr1->prox;
            }    
            else if (curr1 != NULL && curr2 != NULL)
            {
                if(curr1->coluna == curr2->coluna)
                {
                    val = curr1->valor + curr2->valor;
                    col = curr1->coluna;
                }    
                curr1 = curr1->prox;
                curr2 = curr2->prox;
            }

           insereMatrix(m3,linhax,col,val);
            
            col++;
        }
    }

    return m3;
}

//Altere os elementos da Matriz 1 com base nos elementos da Matriz 2
matrix *muda_primeira_Matrix(matrix *m1, matrix *m2)
{
    int temp; 
    
    list curr1, curr2;
    for (int linhax = 0; linhax < m1->linhas; linhax++)
    {
        curr1 = m1->ls[linhax];
        curr2 = m2->ls[linhax];
        while (curr1 != NULL && curr2 != NULL)
        {   
            if(curr1->coluna == curr2->coluna)
                deleta(m1,linhax,curr1->coluna);
            
            if(curr1 == NULL && curr2 != NULL)
                curr2 = curr2->prox;
            else if(curr1 == NULL && curr2 != NULL)
                curr1 = curr1->prox;
            else
            {
                curr1 = curr1->prox;
                curr2 = curr2->prox;
            }
        }
    }
    return m1;
}


int main()
{
    matrix *m1 = (matrix *) malloc(sizeof(matrix));
    matrix *m2 = (matrix *) malloc(sizeof(matrix));
    matrix *m3;

    int i, flag, tam;
    float valor, somaVal;
    
    iniciaMatrix(m1,LINHAS,COLUNAS);
    iniciaMatrix(m2,LINHAS,COLUNAS);
    
    printf("##___Tamanho de entrada___##: ");
    scanf("%d", &tam);

    criaArq(tam);

    FILE *dataFile;
    
    srand((unsigned int) time(NULL)); 
    int r, c;

    printf("\n##___Inserindo valores___##\n");
    
    dataFile = fopen("valores.txt", "r");
    if( dataFile == NULL)
    {
        printf("#####ERRO AO ABRIR ARQUIVO#####");
    }
    while (EOF != fscanf(dataFile,"%f", &valor))
    {
        r = rand() % 10;
        c = rand() % 10;  

        insereMatrix(m1, r, c, valor); //Insere valores de m1

        r = rand() % 10;
        c = rand() % 10;  

        insereMatrix(m2, r, c, valor); //Insere valores de m1
    }
    fclose(dataFile);

    printf("\nMatrix 1");
    printMatrix(m1);

    printf("\nMatrix 2");
    printMatrix(m2);

    printf("\n##___Deletando Valores___##\n");
    
    deleta(m1, 1, 1);
    deleta(m1, 2, 4);
    deleta(m1, 3, 0);
    deleta(m1, 0, 0);

    deleta(m2, 2, 2);
    deleta(m1, 1, 0);

    printf("\nMatrix 1");
    printMatrix(m1);

    printf("\nMatrix 2");
    printMatrix(m2);

    printf("\n##___Produto dos elementos da Matrix 1___##\n");
    multiplicaMatrix(m1, 4);
    
    printf("\nMatrix 1");
    printMatrix(m1);

    somaVal = somaElementos_da_Matrix(m2);
    printf("\n##___Soma dos elementos da Matrix 2___ ##= %.2f\n", somaVal);

    printf("\n##___Criando Matrix 3___##\n");

    m3 = soma_e_nova_Matrix(m1,m2);
    printMatrix(m3);

    printf("\nNova Matrix 1\n");
    
    m1 = muda_primeira_Matrix(m1,m2);
    printMatrix(m1);

    return 0;
}