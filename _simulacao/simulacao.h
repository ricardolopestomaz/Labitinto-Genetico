#ifndef SIMULACAO_H
#define SIMULACAO_H

#include <stdbool.h>
#include "../_populacao/populacao.h"  // Definição de Populacao, No, Individuo
#include "../_props/props.h"          // constantes do projeto

void simularIndividuo(Individuo *ind, int **mapa, int linhas, int colunas);
void simularPopulacao(Populacao *pop, int **mapa, int linhas, int colunas);
void ordenarPopulacaoPorFitness(Populacao *pop);
Populacao selecionarElite(Populacao *pop, int qtd);
void aplicarCrossoverMutacao(Populacao *pais, Populacao *novaGeracao);
void evoluirPopulacao(Populacao *pop, int **mapa, int linhas, int colunas);
void inserirNoFinal(Populacao *pop, No *novoNo);
void liberarVisao(int **visao, int linhas);


#endif
