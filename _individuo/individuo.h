#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <stdbool.h>

typedef struct {
    char *cromossomo;
    int passos;
    bool concluido;
    int fitness;
} Individuo;

void gerarIndividuo(Individuo *ind);
void liberarIndividuo(Individuo *ind);

#endif
