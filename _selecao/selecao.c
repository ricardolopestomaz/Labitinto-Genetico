#include "selecao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

void copiarIndividuos(Populacao *origem, Populacao *destino, int quantidade) {
    destino->inicio = NULL;
    destino->tamanho = 0;

    No *atual = origem->inicio;
    for (int i = 0; i < quantidade && atual != NULL; i++) {
        No *novo = (No *) malloc(sizeof(No));
        if (!novo) {
            printf("Erro ao alocar memoria para copia.\n");
            exit(1);
        }

        // Copia todos os dados do indivíduo
        novo->ind = atual->ind;
        novo->prox = destino->inicio;
        destino->inicio = novo;
        destino->tamanho++;

        atual = atual->prox;
    }
}
