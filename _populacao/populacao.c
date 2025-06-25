#include <stdlib.h>
#include <stdio.h>
#include "populacao.h"
#include "../_props/props.h"

// Copia profunda do indivíduo
void copiarIndividuo(Individuo *origem, Individuo *destino) {
    destino->fitness = origem->fitness;
    destino->passos = origem->passos;
    destino->concluido = origem->concluido;

    destino->cromossomo = malloc(tamanho_genoma * sizeof(char));
    if (!destino->cromossomo) {
        fprintf(stderr, "Erro ao alocar cromossomo na copia do individuo.\n");
        exit(1);
    }

    for (int i = 0; i < tamanho_genoma; i++) {
        destino->cromossomo[i] = origem->cromossomo[i];
    }
}

// Copiar população com cópia profunda dos indivíduos
void copiarPopulacao(Populacao *origem, Populacao *destino) {
    destino->inicio = NULL;
    destino->tamanho = 0;

    No *atual = origem->inicio;
    while (atual) {
        No *novo = malloc(sizeof(No));
        if (!novo) {
            fprintf(stderr, "Erro ao alocar No na copia da populacao.\n");
            exit(1);
        }

        copiarIndividuo(&atual->ind, &novo->ind);
        novo->prox = destino->inicio;
        destino->inicio = novo;
        destino->tamanho++;

        atual = atual->prox;
    }
}

// Inserir individuo com cópia profunda na população
void inserirIndividuo(Populacao *pop, Individuo *ind) {
    No *novo = malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro ao alocar novo individuo.\n");
        exit(1);
    }

    copiarIndividuo(ind, &novo->ind);

    novo->prox = pop->inicio;
    pop->inicio = novo;
    pop->tamanho++;
}

// Gera população inicial (individuos aleatórios)
void gerarPopulacao(Populacao* pop, int tamanho) {
    pop->inicio = NULL;
    pop->tamanho = 0;

    for (int i = 0; i < tamanho; i++) {
        No* novo = malloc(sizeof(No));
        if (!novo) {
            fprintf(stderr, "Erro ao alocar memória para indivíduo.\n");
            exit(1);
        }
        gerarIndividuoAleatorio(&novo->ind);  // Gera cromossomo aleatório
        novo->prox = pop->inicio;
        pop->inicio = novo;
        pop->tamanho++;
    }
}

// Libera memória da população (individuos e cromossomos)
void liberarPopulacao(Populacao* pop) {
    No* atual = pop->inicio;
    while (atual) {
        free(atual->ind.cromossomo);  // liberar cromossomo
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    pop->inicio = NULL;
    pop->tamanho = 0;
}

// Encontra o melhor indivíduo da população
Individuo* encontrarMelhorIndividuo(Populacao *pop) {
    if (pop->inicio == NULL) return NULL;

    No *atual = pop->inicio;
    Individuo *melhor = &atual->ind;
    atual = atual->prox;

    while (atual != NULL) {
        if (atual->ind.fitness > melhor->fitness) {
            melhor = &atual->ind;
        }
        atual = atual->prox;
    }

    return melhor;
}

// Gera indivíduo aleatório para inicializar população
void gerarIndividuoAleatorio(Individuo *ind) {
    ind->cromossomo = malloc(sizeof(char) * tamanho_genoma);
    if (!ind->cromossomo) {
        fprintf(stderr, "Erro ao alocar cromossomo.\n");
        exit(1);
    }

    for (int i = 0; i < tamanho_genoma; i++) {
        int r = rand() % 4;
        switch (r) {
            case 0: ind->cromossomo[i] = 'C'; break;
            case 1: ind->cromossomo[i] = 'B'; break;
            case 2: ind->cromossomo[i] = 'E'; break;
            case 3: ind->cromossomo[i] = 'D'; break;
        }
    }

    ind->fitness = 0;
    ind->passos = 0;
    ind->concluido = 0;
}
