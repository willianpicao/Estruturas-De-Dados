#include<stdio.h>
#include<stdlib.h>

#define T 3

struct arvoreMF
{
	int dado[T];
	int qtd;
	struct arvoreMF *filhos[T+1];
};

typedef struct arvoreMF tipoArv;

tipoArv *alocaNo(int valor)
{
	tipoArv *novoNo;
	int i;
	
	novoNo = (tipoArv*) malloc ( sizeof (tipoArv) );
	
	if( novoNo == NULL )
		printf("IMPOSSIVEL ALOCAR\n");
	else
	{
		novoNo->dado[0] = valor;
		novoNo->qtd = 1;
		
		for(i=1; i<T; i++)
			novoNo->dado[i] = 0;
		for(i=0; i<T+1; i++)
			novoNo->filhos[i] = NULL;
		
		return novoNo;
	}
}
void insereArv(tipoArv **arv, int valor)
{
	int i;
	
	if( (*arv) == NULL )
		(*arv) = alocaNo(valor);
	else
	{
		if ( (*arv)->qtd < T )
		{
			i = (*arv)->qtd;
			
			while( (i > 0) && ( (*arv)->dado[i-1] > valor) )
			{
				(*arv)->dado[i] = (*arv)->dado[i-1];
				i--;
			}
			
			(*arv)->dado[i] = valor;
			(*arv)->qtd++;
		}
		else
		{
			if ( (*arv)->qtd == T )
			{
				i = 0;
				while ( (i < T) && (valor > (*arv)->dado[i]) )
					i++;
			}
			insereArv( &(*arv)->filhos[i], valor);
		}
			
	}	
	
}
void imprimePre(tipoArv *arv)
{
	int i;
	
	if ( arv != NULL )
	{
		for(i=0; i < T; i++)
			printf("%d\t", arv->dado[i]);
		printf("QUANTIDADE DE DADOS: %d\n", arv->qtd);
		
		for(i=0; i < T+1; i++)
		{
			if( arv->filhos[i] != NULL )
				imprimePre( arv->filhos[i] );
		}
	}
} 
void imprimeOrdem(tipoArv *arv)
{
	int i;
	
	if ( arv	!= NULL )
	{
		for( i=0; i < T; i++)
		{
			imprimeOrdem( arv->filhos[i] );
			printf("%d\t", arv->dado[i]);
		}
		imprimeOrdem( arv->filhos[i] );
		printf("\n");
	}
}	
int qtdDados(tipoArv *arv)
{
	int i, cont;
	
	if( arv == NULL )
		return 0;
	else
	{
		
		cont = arv->qtd;
		
		for(i=0; i < T+1; i++)
			cont += qtdDados( arv->filhos[i] );
	}
	return cont;
} 
int ehFolha(tipoArv *arv)
{
	int i;
	
	if ( arv == NULL )
		return 0;
	else
	{
		for(i=0; i < T+1; i++)
		{
			if( arv->filhos[i] != NULL )
				return 0;
		}
		return 1;
	}
}	
void imprimeFolha(tipoArv *arv)
{
	int i;
	
	if( arv != NULL )
	{
		if( ehFolha(arv) )
		{
			for(i=0; i < arv->qtd; i++)
				printf("%d\t", arv->dado[i]);
		}
		for(i=0; i < T+1; i++)
			imprimeFolha(arv->filhos[i]);
	}
}
void imprimePos(tipoArv *arv)
{
	int i;
	
	if( arv != NULL )
	{
		for(i=0; i < T+1; i++)
			imprimePos( arv->filhos[i] );
		imprimePos( arv->filhos[i] );
		for(i=0; i < T; i++)
			printf("%d\t", arv->dado[i]);
		printf("\n");
	}
}
void imprimeNivel(tipoArv *arv, int cont)
{
	int i;
	
	if( arv != NULL )
	{
		if ( cont == 0 )
		{
			for(i=0; i < arv->qtd; i++)
				printf("%d\t", arv->dado[i]);
		}
		else
		{
			for( i=0; i < T+1; i++)
				imprimeNivel( arv->filhos[i], cont-1);
			imprimeNivel( arv->filhos[i], cont);
		}
	}
}
int alturaArv(tipoArv *arv)
{
	int hesq, hdir, i;
	
	if( arv != NULL )
	{
		if(ehFolha)
			return 0;
		else
		{
			for(i=0; i < T+1; i++)
				hesq = alturaArv( arv->filhos[i] );
			hdir = alturaArv( arv->filhos[i] );
		}
		if( hesq > hdir )
			return hesq+1;
		else
			return hdir+1;
	}
	else
		return -1;
}
int main()
{
	tipoArv *raiz;
	int altura;
	
	raiz = NULL;
	
	insereArv(&raiz, 30);
	insereArv(&raiz, 60);
	insereArv(&raiz, 90);
	insereArv(&raiz, 6);
	insereArv(&raiz, 8);
	insereArv(&raiz, 10);
	insereArv(&raiz, 5);
	insereArv(&raiz, 40);
	insereArv(&raiz, 80);
	insereArv(&raiz, 100);
	insereArv(&raiz, 110);
	insereArv(&raiz, 120);
	
	
	imprimePos(raiz);
	printf("QUANTIDADE DE NÓS: %d\n", qtdDados(raiz) );
	
	printf("folhas:\n");	
	imprimeFolha(raiz);
	printf("\n");
	
	printf("IMPRIMINDO NIVEL\n");
	imprimeNivel(raiz, 1);
	printf("\n");
	
	altura = alturaArv(raiz);
	printf("IMPRIMINDO ALTURA: %d\n", altura);
		
	return 1;
}
