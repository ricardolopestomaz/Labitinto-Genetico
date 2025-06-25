#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "individuo.h"
#include "../_props/props.h"

void gerarIndividuo(Individuo *ind) {
    const char movimentos[] = {'C', 'B', 'E', 'D'};
    ind->cromossomo = malloc(tamanho_genoma * sizeof(char));
    if (!ind->cromossomo) {
        fprintf(stderr, "Erro ao alocar cromossomo\n");
        exit(1);
    }

    for (int i = 0; i < tamanho_genoma; i++) {
        int r = rand() % 4;
        ind->cromossomo[i] = movimentos[r];
    }

    ind->passos = 0;
    ind->concluido = false;
    ind->fitness = 0;
}

void liberarIndividuo(Individuo *ind) {
    if (ind && ind->cromossomo) {
        free(ind->cromossomo);
        ind->cromossomo = NULL;
    }
}
