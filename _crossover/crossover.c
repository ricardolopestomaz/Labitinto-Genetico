#include "crossover.h"
#include <stdlib.h>
#include "../_props/props.h"

void crossover(Individuo *pai1, Individuo *pai2, Individuo *filho1, Individuo *filho2) {
    int ponto = rand() % tamanho_genoma;

    for (int i = 0; i < tamanho_genoma; i++) {
        if (i < ponto) {
            filho1->cromossomo[i] = pai1->cromossomo[i];
            filho2->cromossomo[i] = pai2->cromossomo[i];
        } else {
            filho1->cromossomo[i] = pai2->cromossomo[i];
            filho2->cromossomo[i] = pai1->cromossomo[i];
        }
    }

    filho1->passos = filho2->passos = 0;
    filho1->fitness = filho2->fitness = 0;
    filho1->concluido = filho2->concluido = false;
}
