#include "simulacao.h"
#include "../_mutacao/mutacao.h"
#include "../_crossover/crossover.h"
#include "../_props/props.h"
#include "../_logs/logs.h"
#include "../_mapa/mapa.h"
#include "../_fitness/fitness.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Inserir indivíduo na população
void inserirIndividuoNaPopulacao(Populacao *pop, Individuo *ind) {
    No *novo = malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro ao alocar No\n");
        exit(1);
    }
    novo->ind = *ind;
    novo->prox = NULL;

    if (pop->inicio == NULL) {
        pop->inicio = novo;
    } else {
        No *atual = pop->inicio;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo;
    }
    pop->tamanho++;
}

int compararFitness(const void *a, const void *b) {
    No *noA = *(No **)a;
    No *noB = *(No **)b;
    return noB->ind.fitness - noA->ind.fitness;
}

void ordenarPopulacaoPorFitness(Populacao *pop) {
    if (pop->tamanho <= 1) return;

    /***
     * Aloca o vetor com pop->tamanho posições.
     * Cada pocisao guarda um ponteiro no.
     */
    No **vetor = malloc(sizeof(No *) * pop->tamanho);

    // Copia os nós da lista para o vetor
    No *atual = pop->inicio;
    for (int i = 0; i < pop->tamanho; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }

    //Ordena os ponteiros do vetor
    qsort(vetor, pop->tamanho, sizeof(No *), compararFitness);

    //Reconstrói a lista.
    for (int i = 0; i < pop->tamanho - 1; i++) vetor[i]->prox = vetor[i + 1];
    vetor[pop->tamanho - 1]->prox = NULL;
    pop->inicio = vetor[0];

    free(vetor);
}

void simularIndividuo(Individuo *ind, int **mapa, int linhas, int colunas) {
    int x = posicao_inicial_x, y = posicao_inicial_y;
    int saidaX = posicao_final_x, saidaY = posicao_final_y;
    int passos = 0;
    bool bateu = false;
    ind->concluido = false;

    int movimentosConsumidosNaFila = 0; // conta quantos movimentos válidos foram feitos na fila
    int maxMovimentosFila = 10;

    for (int i = 0; i < tamanho_genoma; i++) {
        if (movimentosConsumidosNaFila < maxMovimentosFila) {
            // Atualiza fila de movimentos possíveis da posição atual
            char filaMovimentos[4];
            int filaTamanho = 0;

            if (x - 1 >= 0 && mapa[x - 1][y] != PAREDE) filaMovimentos[filaTamanho++] = 'C';
            if (x + 1 < linhas && mapa[x + 1][y] != PAREDE) filaMovimentos[filaTamanho++] = 'B';
            if (y - 1 >= 0 && mapa[x][y - 1] != PAREDE) filaMovimentos[filaTamanho++] = 'E';
            if (y + 1 < colunas && mapa[x][y + 1] != PAREDE) filaMovimentos[filaTamanho++] = 'D';

            bool moveu = false;
            for (int j = 0; j < filaTamanho; j++) {
                if (ind->cromossomo[i] == filaMovimentos[j]) {
                    // movimento válido e gene bate com movimento possível
                    int novoX = x, novoY = y;
                    switch (ind->cromossomo[i]) {
                        case 'C': novoX--; break;
                        case 'B': novoX++; break;
                        case 'E': novoY--; break;
                        case 'D': novoY++; break;
                    }

                    // Não precisa checar parede, pois já checou na fila

                    x = novoX;
                    y = novoY;
                    passos++;
                    movimentosConsumidosNaFila++;
                    moveu = true;
                    break;
                }
            }

            if (!moveu) {
                // gene não bate com nenhum movimento válido atual, ignora movimento
                continue;
            }
        } else {
            // Passou dos 10 movimentos que usam a fila, anda normalmente pelo cromossomo
            int novoX = x, novoY = y;
            switch (ind->cromossomo[i]) {
                case 'C': novoX--; break;
                case 'B': novoX++; break;
                case 'E': novoY--; break;
                case 'D': novoY++; break;
                default: continue;
            }

            if (novoX < 0 || novoX >= linhas || novoY < 0 || novoY >= colunas || mapa[novoX][novoY] == PAREDE) {
                bateu = true;
                break;
            }

            x = novoX;
            y = novoY;
            passos++;
        }

        if (x == saidaX && y == saidaY) {
            ind->concluido = true;
            break;
        }
    }

    ind->passos = passos;
    ind->fitness = calcularFitness(ind, saidaX, saidaY, x, y, bateu);
}


void simularPopulacao(Populacao *pop, int **mapa, int linhas, int colunas) {
    int id = 1;
    for (No *no = pop->inicio; no != NULL; no = no->prox) {
        simularIndividuo(&no->ind, mapa, linhas, colunas);
        id++;
    }
}

Populacao selecionarElite(Populacao *pop, int qtd) {
    Populacao elite = {NULL, 0};
    No *atual = pop->inicio;
    for (int i = 0; i < qtd && atual != NULL; i++) {
        inserirIndividuoNaPopulacao(&elite, &atual->ind);
        atual = atual->prox;
    }
    return elite;
}

void aplicarCrossoverMutacao(Populacao *pais, Populacao *novaGeracao) {
    No *p1 = pais->inicio;
    No *p2 = p1 ? p1->prox : NULL;

    while (novaGeracao->tamanho < numero_individuos) {
        if (!p1 || !p2) break;

        Individuo filho1, filho2;

        // Aloca cromossomo para filhos
        filho1.cromossomo = malloc(tamanho_genoma * sizeof(char));
        filho2.cromossomo = malloc(tamanho_genoma * sizeof(char));
        if (!filho1.cromossomo || !filho2.cromossomo) {
            fprintf(stderr, "Erro ao alocar cromossomo para filhos no crossover.\n");
            exit(1);
        }

        crossover(&p1->ind, &p2->ind, &filho1, &filho2);
        mutar(&filho1);
        mutar(&filho2);

        // Insere cópia profunda (ou faça a cópia corretamente)
        inserirIndividuo(novaGeracao, &filho1);
        if (novaGeracao->tamanho >= numero_individuos) {
            // liberar cromossomo do filho2 pois nao será usado
            free(filho2.cromossomo);
            break;
        }
        inserirIndividuo(novaGeracao, &filho2);

        // Liberar os cromossomos originais dos filhos, pois inseriu cópia
        free(filho1.cromossomo);
        free(filho2.cromossomo);

        p1 = p1->prox;
        p2 = p2->prox ? p2->prox : pais->inicio;
    }
}


void evoluirPopulacao(Populacao *pop, int **mapa, int linhas, int colunas) {
    simularPopulacao(pop, mapa, linhas, colunas);
    ordenarPopulacaoPorFitness(pop);

    int qtd_elite = pop->tamanho / 10;
    if (qtd_elite < 1) qtd_elite = 1;
    Populacao elite = selecionarElite(pop, qtd_elite);

    Populacao novaGeracao = {NULL, 0};
    for (No *no = elite.inicio; no != NULL; no = no->prox) {
        inserirIndividuoNaPopulacao(&novaGeracao, &no->ind);
    }

    aplicarCrossoverMutacao(pop, &novaGeracao);

    liberarPopulacao(pop);
    liberarPopulacao(&elite);

    *pop = novaGeracao;
}
