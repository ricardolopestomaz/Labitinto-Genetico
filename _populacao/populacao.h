#ifndef POPULACAO_H
#define POPULACAO_H

#include "../_individuo/individuo.h"  // Inclui o struct Individuo de verdade

typedef struct No {
    Individuo ind;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Populacao;

// Protótipos das funções
void gerarPopulacao(Populacao* pop, int tamanho);
void liberarPopulacao(Populacao* pop);
Individuo* encontrarMelhorIndividuo(Populacao *pop);
void copiarPopulacao(Populacao *origem, Populacao *destino);
void gerarIndividuoAleatorio(Individuo *ind);
void inserirIndividuo(Populacao *pop, Individuo *ind);

#endif
