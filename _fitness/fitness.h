#ifndef FITNESS_H
#define FITNESS_H

#include "../_individuo/individuo.h"
#include <stdbool.h>

int calcularFitness(Individuo *ind, int xObjetivo, int yObjetivo, int xFinal, int yFinal, bool bateu);

#endif
