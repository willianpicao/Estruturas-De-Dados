/*Etapa 3:
Desenvolva um sistema para avaliação da função Hash. 
Implemente 2 funções Hash distintas. Este sistema irá utilizar uma tabela Hash de tamanho 100. 
A avaliação deverá executar um mesmo aquivo de entrada para cada função Hash implementada.
Para cada execução, contabilize o número de colisões que ocorreram.
Gere 10 entradas com 20, com 50 e 80 registros (total de 30 arquivos) diferentes que serão utilizadas nos testes. 
Em cada conjunto de 10 arquivos, 5 são do tipo 1 e 5 do tipo 2.
Ao final, elabore um relatório contendo a média do número de colisões entre os elementos para 
cada contexto avaliado (sugestão: utilize uma planilha eletrônica para tabular os resultados).*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "getFile.c"

typedef struct fileData
{
    int key;
    char value[3];

    struct fileData *next;
} fData;

typedef fData* hashTable;

// Hashtable functions
void startHashTable(hashTable *table, int size)
{
    for(int i = 0; i < size; i++)
        table[i] = NULL;
}

int getHashMult(int key, const int size)
{
    float words = 64, primeNum = 19;

    int hashNum = key * (primeNum/words);

    if(hashNum >= size)
        return size - 1;
    else
        return hashNum;
}

int getHashDiv(int key, const int size)
{
    return key % size;
}

//Struct functions
fData *allocData(int code, char *value)
{
    fData *new = (fData*) malloc(sizeof(fData));
    new->key = code;
    strcpy(new->value, value);
    new->next = NULL;

    return new;
}

void insertData(hashTable *table, int key, char *value, int hashType, const int size)
{
    
    int hashNum;
    
    if(hashType = 1)
        hashNum = getHashDiv(key, size);
    else
        hashNum = getHashMult(key, size);

    fData *temp = table[hashNum];
    fData *back = NULL;

    while ((temp != NULL) && (temp->key != key))
    {
        back = temp;
        temp = temp->next;
    }
    
    if(temp)
    {
        strcpy(temp->value,value);
        return;
    }

    fData *new = allocData(key, value);

    if(!back)
        table[hashNum] = new;
    else
        back->next = new;

}

int printData(hashTable *table, int size)
{   
    int coli = 0;
    printf("\nIndex    Code     GPA     Next\n");

    for(int i = 0; i < size; i++)
    {
        printf("%d", i);
        if (table[i])
        {
            fData *temp = table[i];
            printf("\n");
            while(temp)
            {
                if(temp->next != NULL)
                    coli ++;
                printf("\t| %d |\t| %s |\t| %p |\n", temp->key, temp->value, temp->next);
                temp = temp->next;
            }
        }
        else
            printf("\nNULL DATA\n");     
    }
    printf("---------------------------\n");
    
    return coli;
}

void freeData(hashTable *table, int size)
{
    for(int i = 0; i < size; i++)
    {
        if (table[i])
        {
            fData *temp1 = table[i];
            fData *temp2;

            while(temp1)
            {
                temp2 = temp1;
                temp1 = temp1->next;
                free(temp2);
            }
        }
    }
    //printf("\n Data freed\n");
}

// File's functions
void getInput(int inputSize)
{
    int inputType;
    char fileName[30];

    for(int j = 1; j <= 10; j++)
    {
        srand((unsigned int) j * time(NULL));

        if(j == 6)
            inputType = 2;
        else
            inputType = 1;
        sprintf(fileName, "arq%d-%d",inputSize,j);
        fflush(stdout);
        createFile(inputSize,inputType,fileName);
    }
}


FILE *openFile(char *filename)
{   
    FILE *dataFile;
    
    dataFile = fopen(filename, "r");
    if( dataFile == NULL)
	{
		printf("Can't open this file");
		return 0;
	}

    return dataFile;
}

void getOutput( int hashType, int inputSize, const int size)
{
    FILE *dataFile; 
    char filename[15];

    int key, coli = 0;
    float mean = 0;
    char value[4] = " ", temp[5];

    for(int i = 0; i < 3; i++)
    {
        hashTable *table[size];
        startHashTable(table, size);

        sprintf(filename, "arq%d-%d.txt",inputSize,i+1);
        dataFile = openFile(filename);
        while(EOF != fscanf(dataFile, "%d", &key) && fgets(temp, 5, dataFile))
        {
            strncpy(value, temp + 1, 3);
            insertData(table, key, value, hashType, size);
            strcpy(temp, " ");
        }
        fclose(dataFile);
        printf("\nFile [%d] \nHash type: %d Input size: %d\n", i, hashType, inputSize);
        coli = printData(table,size);
        mean += coli;
        printf("\nColisions: %d\n###################\n", coli);
        freeData(table,size);
    }   
    printf("\nColisions' mean: %.2f",mean/10);
}

int main()
{
    const int size = 100;
    int inputSize, hashtype;
    
    printf("\nInput size (20, 50 or 80): ");
    scanf("%d", &inputSize);
    printf("\nHashtype (1 = Div; 2 = Mult): ");
    scanf("%d", &hashtype);
    
    getInput(inputSize);
    getOutput(hashtype,inputSize, size);

    return 0;
}