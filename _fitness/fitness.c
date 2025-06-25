#include "fitness.h"
#include <stdlib.h>
#include <stdbool.h>
#include "../_props/props.h"

int calcularFitness(Individuo *ind, int xObjetivo, int yObjetivo, int xFinal, int yFinal, bool bateu) {
    int distancia = abs(xObjetivo - xFinal) + abs(yObjetivo - yFinal);
    int fitness = 1000 - (distancia * 10);

    if (xFinal == xObjetivo && yFinal == yObjetivo) {
        fitness += chegou_objetivo_bonus;
    }

    if (ind->passos > 0) {
        fitness -= ind->passos * 2;
    }

    if (bateu) {
        fitness -= movimento_invalido_penalidade;
    }

    return fitness < 0 ? 0 : fitness;
}
