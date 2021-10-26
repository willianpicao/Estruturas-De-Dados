#ifndef generatesFile_C
#define generatesFile_C
//Inclusao de bibliotecas necessarias ---------------------------------()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
//-------------------------------------------------------------------------------------------------------
//Funções que geram chaves aleatorias tipo 1 e 2.

int keyType1(int key)
{
    srand(time (NULL));
    key= abs(rand() % 1024);
    while (key % 2 != 0)
        key= abs(rand() % 1024);
    return key;
}

int keyType2(int key)
{
    srand(time (NULL));
    key= abs(rand() % 1024);
    return key;
}

int hasKey(int hasKey)
{
    hasKey = keyType1(hasKey);
    while (hasKey % 2 != 0)
        hasKey = keyType1(hasKey);
    return hasKey;
}

//-------------------------------------------------------------------------------------------------------
//Funlçao que gera valores.

char randomValue(){//ASCII A~Z (Uppercased)
    return (rand() % (92 - 66) + 65); 
}

//-------------------------------------------------------------------------------------------------------
//Função para criar Arquivo.

void generatesFile (int size, int type, char *fileName)
{
    FILE *fileOfdata;
    int key;
    char worth[4] = "   ";
    strcat(fileName, ".txt");
    fileOfdata = fopen(fileName, "w");
    if (fileOfdata==NULL)
        printf("Error\n");
    setbuf(fileOfdata, NULL);

    for (int i = 1; i <= size; i++){
        if ( type == 1 ){
            key=hasKey(key);
        }else if ( type == 2){
            key=keyType2(key);
        }
        for (int c = 0; c < 3; c++)
            worth[c] = randomValue();
        fprintf(fileOfdata, "%d ", key);
        fputs(worth, fileOfdata);
        fprintf(fileOfdata,"\n");
        strcpy(worth, "   ");
    }
    fclose(fileOfdata);
}
//-------------------------------------------------------------------------------------------------------
#endif




    
    




   