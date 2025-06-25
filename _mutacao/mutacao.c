#include "mutacao.h"
#include <stdlib.h>
#include "../_props/props.h"

void mutar(Individuo *ind) {
    const char movimentos[] = {'C', 'B', 'E', 'D'};

    for (int i = 0; i < tamanho_genoma; i++) {
        float r = (float)rand() / RAND_MAX;
        if (r < taxa_mutacao) {
            ind->cromossomo[i] = movimentos[rand() % 4];
        }
    }
}
