#ifndef Valores_C
#define Valores_C

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 20.0

void criaArq(int tam)
{
    FILE *dataFile;
    float valor;
    
    dataFile = fopen("valores.txt", "w");
    
    if(dataFile == NULL)
    {
        printf("File Error\n");
    }
    setbuf(dataFile, NULL);
    srand((unsigned int) time(NULL));

    for (int i = 1; i <= tam; i++)
    {
        if(rand() % 2 == 0)
            valor = 0;
        else    
            valor = (float) rand() / ((float)RAND_MAX + 1) * MAX;

        if(valor < 0)
            valor *= -1;

        fprintf(dataFile, "%.2f ", valor);
        fprintf(dataFile,"\n");
    }
    fclose(dataFile);
}

#endif