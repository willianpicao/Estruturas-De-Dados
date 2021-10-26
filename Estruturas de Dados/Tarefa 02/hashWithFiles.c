#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "generatesFile.c"

typedef struct hash
{
    int key;
    char worth[3];

    struct hash *next;
} hashTable;

typedef hashTable *typeHash;

//Escropo de funções ------------------------------------------------------
void startTable(typeHash *table, int sizeTable);
int hashDiv(int key, const int size);
int hashMult(int key, const int size);
typeHash *allocNode(int key, char *worth);
void insert(typeHash *table, int key, char *worth, int hashType, const int size);
int print(hashTable *table, int size);
void freeNode(hashTable *table, int size);
void input(int size);
FILE *openFile(char *filename);
void output( int hashType, int size, const int sizeTable);
//-------------------------------------------------------------------------



void startTable(typeHash *table, int sizeTable)
{
    for(int i = 0; i < sizeTable; i++)
        table[i] = NULL;
}
int hashDiv(int key, const int size){
    return key % size;
}

int hashMult(int key, const int size)
{
    float words = 64;
    float num = 19;
    int hashNum = key * (num/words);
    if(hashNum >= size)
        return size - 1;
    else
        return hashNum;
}
typeHash *allocNode(int key, char *worth){
    typeHash *novo= (*typeHash)malloc(sizeof(typeHash));
    novo->key= key;
    strcpy(novo->worth, worth);
    (novo)->next = NULL;

    return novo;
}

void insert(typeHash *table, int key, char *worth, int hashType, const int size)
{
    
    int hashNum;
    typeHash *(aux) = table[hashNum];
    typeHash *back = NULL;

    if(hashType = 1)
        hashNum = hashDiv(key, size);
    else
        hashNum = hashMult(key, size);
    while ((aux != NULL) && ((aux)->key != key)){
        back = aux;
        aux = (aux)->next;
    }
    if(aux){
        strcpy((aux)->value,worth);
        return;
    }

    typeHash *new = allocNode(key, worth);

    if(!back)
        table[hashNum] = new;
    else
        (back)->next = new;

}

int print(hashTable *table, int size)
{   
    int coli = 0;

    for(int i = 0; i < size; i++)
    {
        printf("%d", i);
        if (table[i])
        {
            typeHash *aux = table[i];
            printf("\n");
            while(aux)
            {
                if((aux)->next != NULL)
                    coli ++;
                printf("\t| %d |\t| %s |\t| %p |\n", (aux)->key, (aux)->value, (aux)->next);
                aux = (aux)->next;
            }
        }
        else
            printf("\nNULL DATA\n");     
    }
    printf("_________________________________\n");
    
    return coli;
}

void freeNode(hashTable *table, int size)
{
    for(int i = 0; i < size; i++){
        if (table[i]){
            typeHash *aux1 = table[i];
            typeHash *aux2;
             while(aux1){
                aux2 = aux1;
                aux1 = aux1->next;
                free(aux2);
            }
        }
    }
}

void input(int size)
{
    int keyType;
    char fileName[30];
    for(int j = 1; j <= 10; j++){
        srand((unsigned int) j * time(NULL));

        if(j == 6)
            keyType = 2;
        else
            keyType = 1;
        sprintf(fileName, "arq%d-%d",keyType,j);
        fflush(stdout);
        generatesFile(size,keyType,fileName);
    }
}


FILE *openFile(char *filename)
{   
    FILE *arq;
    
    arq = fopen(filename, "r");
    if( arq == NULL)
	{
		printf("Error\n");
		return 0;
	}

    return arq;
}

void output( int hashType, int size, const int sizeTable)
{
    FILE *arq; 
    char filename[15];

    int key, coli = 0;
    float mean = 0;
    char worth[4] = " ", aux[5];

    for(int i = 0; i < 3; i++)
    {
        hashTable *table[sizeTable];
        startTable(table, sizeTable);

        sprintf(filename, "arq%d-%d.txt",size,i+1);
        arq = openFile(filename);
        while(EOF != fscanf(arq, "%d", &key) && fgets(aux, 5, arq))
        {
            strncpy(worth, aux + 1, 3);
            insert(table, key, worth, hashType, size);
            strcpy(aux, " ");
        }
        fclose(arq);
        printf("\nFile [%d] \nHash type: %d size: %d\n", i, hashType, size);
        coli = print(table,size);
        mean += coli;
        printf("\nColisions: %d\n", coli);
        freeNode(table,size);
    }   
    printf("\nColisions' mean: %.2f",mean/10);
}

int main ()
{
    const int sizeTable = 100;
    int size, hashtype;
    
    printf("\nInput Size(20|50|80): ");
    scanf("%d", &size);
    printf("\nHashtype (1 = Div; 2 = Mult): ");
    scanf("%d", &hashtype);
    
    input(size);
    output(hashtype,size, sizeTable);

    return 0;
}