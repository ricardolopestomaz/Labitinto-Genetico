#ifndef LOGS_H
#define LOGS_H

#include "../_individuo/individuo.h"
#include "../_populacao/populacao.h"

void iniciarLog();
void registrarIndividuo(int id, Individuo *ind);
void registrarLog(int geracao, Populacao *pop);
void finalizarLog();

#endif // LOGS_H
