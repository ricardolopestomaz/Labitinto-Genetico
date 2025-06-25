#ifndef MAPA_H
#define MAPA_H

#define PAREDE 1
#define VAZIO 0
#define ENTRADA 2
#define SAIDA 3

extern int **mapa;
extern int linhas;
extern int colunas;

void carregarMapa();
void imprimirMapa();
void imprimirMapaComIndividuo(int x, int y);
void liberarMapa();

#endif
