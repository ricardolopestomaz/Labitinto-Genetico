#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "_props/props.h"
#include "_mapa/mapa.h"
#include "_individuo/individuo.h"
#include "_populacao/populacao.h"
#include "_fitness/fitness.h"
#include "_simulacao/simulacao.h"
#include "_logs/logs.h"
#include "_selecao/selecao.h"
#include "_crossover/crossover.h"
#include "_mutacao/mutacao.h"
#include "graficos/graficos.h"

int main() {
    srand(time(NULL));

    printf("Iniciando programa...\n");
    ler_arquivo_ini("_props/props.ini");

    printf("[Parametros]\n");
    printf("\tNumero de individuos: %d\n", numero_individuos);
    printf("\tTamanho do genoma: %d\n", tamanho_genoma);
    printf("\tTaxa de mutacao: %.2f\n", taxa_mutacao);
    printf("\tNumero maximo de geracoes: %d\n\n", numero_maximo_geracoes);

    printf("[Labirinto]\n");
    printf("\tArquivo do labirinto: %s\n", arquivo_labirinto);
    printf("\tPosicao inicial: (%d, %d)\n", posicao_inicial_x, posicao_inicial_y);
    printf("\tPosicao final: (%d, %d)\n\n", posicao_final_x, posicao_final_y);

    printf("[Avaliacao]\n");
    printf("\tMovimento invalido penalidade: %d\n", movimento_invalido_penalidade);
    printf("\tChegou objetivo bonus: %d\n", chegou_objetivo_bonus);
    printf("\tLimite passos: %d\n\n", limite_passos);

    printf("Carregando mapa...\n");
    carregarMapa(arquivo_labirinto);
    imprimirMapa();

    printf("Iniciando log...\n");
    iniciarLog();

    Populacao pop;
    printf("Gerando populacao inicial...\n");
    gerarPopulacao(&pop, numero_individuos);

    for (int geracao = 0; geracao < numero_maximo_geracoes; geracao++) {
        printf("\n========== Inicio da geracao %d ==========\n", geracao + 1);
        fflush(stdout);

        simularPopulacao(&pop, mapa, linhas, colunas);
        ordenarPopulacaoPorFitness(&pop);

        int somaFitness = 0;
        int melhorFitness = 0;
        int cont = 0;

        for (No *no = pop.inicio; no != NULL; no = no->prox) {
            somaFitness += no->ind.fitness;
            if (no->ind.fitness > melhorFitness) melhorFitness = no->ind.fitness;
            cont++;
        }

        printf("Fitness medio: %.2f\n", cont > 0 ? (float)somaFitness / cont : 0);
        printf("Melhor fitness: %d\n", melhorFitness);
        fflush(stdout);

        registrarLog(geracao, &pop);

        if (geracao < numero_maximo_geracoes - 1) {
            printf("Tamanho da populacao: %d\n", pop.tamanho);
            printf("Evoluindo populacao para a proxima geracao...\n");
            fflush(stdout);

            int qtdElite = numero_individuos / 4;
            int qtdPais = numero_individuos / 2;

            Populacao elite = selecionarElite(&pop, qtdElite);
            Populacao pais = selecionarElite(&pop, qtdPais);

            Populacao novaGeracao = {NULL, 0};
            copiarPopulacao(&elite, &novaGeracao);

            printf("Aplicando crossover e mutacao...\n");
            aplicarCrossoverMutacao(&pais, &novaGeracao);

            while (novaGeracao.tamanho < numero_individuos) {
                Individuo novo;
                gerarIndividuoAleatorio(&novo);
                inserirIndividuo(&novaGeracao, &novo);
            }

            printf("Liberando populacoes antigas...\n");
            liberarPopulacao(&pop);
            liberarPopulacao(&elite);
            liberarPopulacao(&pais);

            pop = novaGeracao;

            printf("Populacao atualizada para geracao %d.\n", geracao + 2);
            fflush(stdout);
        }

        printf("========== Fim da geracao %d ==========\n", geracao + 1);
    }

    Individuo *melhor = encontrarMelhorIndividuo(&pop);
    if (melhor) {
        printf("\nMelhor individuo final:\n");
        printf("Cromossomo: ");
        for (int i = 0; i < tamanho_genoma; i++) {
            printf("%c", melhor->cromossomo[i]);
        }
        printf("\nFitness: %d\n", melhor->fitness);
        printf("Passos: %d\n", melhor->passos);
        printf("Concluido: %s\n", melhor->concluido ? "Sim" : "Nao");
        fflush(stdout);
    }

    printf("Gerando CSV e exibindo grafico...\n");
    gerarCSVFitnessPorGeracao("_logs/logs.csv", "graficos/fitness_por_geracao.csv");
    mostrarGraficoTerminal("graficos/fitness_por_geracao.csv");

    finalizarLog();
    liberarPopulacao(&pop);
    liberarMapa();

    printf("Programa finalizado.\n");
    return 0;
}
