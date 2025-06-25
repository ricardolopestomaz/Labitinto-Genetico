#include "graficos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GERACOES 1000
#define MAX_LINHA 1024

typedef struct {
    int totalFitness;
    int melhorFitness;
    int contador;
} Estatisticas;

void gerarCSVFitnessPorGeracao(const char *arquivoLog, const char *arquivoSaida) {
    FILE *entrada = fopen(arquivoLog, "r");
    if (!entrada) {
        perror("Erro ao abrir arquivo de log");
        return;
    }

    FILE *saida = fopen(arquivoSaida, "w");
    if (!saida) {
        perror("Erro ao criar arquivo de saída");
        fclose(entrada);
        return;
    }

    Estatisticas stats[MAX_GERACOES] = {0};

    char linha[MAX_LINHA];
    fgets(linha, sizeof(linha), entrada); // Pular cabeçalho

    while (fgets(linha, sizeof(linha), entrada)) {
        int geracao, fitness;
        char *token = strtok(linha, ",");
        if (!token) continue;
        geracao = atoi(token);

        // pula id e cromossomo
        token = strtok(NULL, ","); // id
        token = strtok(NULL, ","); // cromossomo

        token = strtok(NULL, ","); // fitness
        if (!token) continue;
        fitness = atoi(token);

        if (geracao >= 0 && geracao < MAX_GERACOES) {
            stats[geracao].totalFitness += fitness;
            stats[geracao].contador++;
            if (fitness > stats[geracao].melhorFitness)
                stats[geracao].melhorFitness = fitness;
        }
    }

    fprintf(saida, "geracao,media,melhor\n");

    for (int i = 0; i < MAX_GERACOES; i++) {
        if (stats[i].contador > 0) {
            float media = (float)stats[i].totalFitness / stats[i].contador;
            fprintf(saida, "%d,%.2f,%d\n", i, media, stats[i].melhorFitness);
        }
    }

    fclose(entrada);
    fclose(saida);
    printf("Gráfico salvo em %s\n", arquivoSaida);
}

void mostrarGraficoTerminal(const char *arquivoCSV) {
    FILE *f = fopen(arquivoCSV, "r");
    if (!f) {
        perror("Erro ao abrir CSV de fitness");
        return;
    }

    char linha[MAX_LINHA];
    fgets(linha, sizeof(linha), f); // Pular cabeçalho

    printf("\n=== Grafico: Evolucao do Melhor Fitness ===\n\n");

    int geracao;
    float media;
    int melhor;

    while (fgets(linha, sizeof(linha), f)) {
        sscanf(linha, "%d,%f,%d", &geracao, &media, &melhor);

        printf("G%03d [%4d]: ", geracao, melhor);
        int barras = melhor / 10; // 1 "□" a cada 10 pontos de fitness
        for (int i = 0; i < barras; i++) {
            printf("%c", 219);
        }
        printf("\n");
    }

    fclose(f);
}
