#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct parte{
    int prox;
    char txt[30];
    char nomeAr[20];
    int index;
} Parte;

typedef struct histo{
    int indice;
    char nomeAr[20];
    int status;
} Histo;

void zera(Histo * historico, Parte * vet);
void insere(Histo * historico, Parte * vet, char * noArquivo, int posHist, FILE * arq);
void busca(Histo * historico, Parte * vet, char * noArquivo, int histCount);
void remocao(Histo * historico, Parte * vet, char * noArquivo, int histCount);
int verif(Histo * historico, int histCount, char * noArquivo, int cond);
void slot(Histo * historico, int histCount, int posVet, Parte * vet);