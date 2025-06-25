#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include "../_props/props.h" // para tamanho_genoma

static FILE *arquivoLog = NULL;

void iniciarLog() {
    arquivoLog = fopen("_logs/logs.csv", "w");
    if (!arquivoLog) {
        printf("Erro ao abrir o arquivo de log.\n");
        exit(1);
    }
    fprintf(arquivoLog, "geracao,id,cromossomo,fitness,passos,concluido\n");
    fflush(arquivoLog);
}

void registrarIndividuo(int id, Individuo *ind) {
    if (!arquivoLog) return;

    fprintf(arquivoLog, "%d,", id);
    for (int i = 0; i < tamanho_genoma; i++) {
        fprintf(arquivoLog, "%c", ind->cromossomo[i]);
    }
    fprintf(arquivoLog, ",%d,%d,%s\n",
            ind->fitness,
            ind->passos,
            ind->concluido ? "sim" : "nao");
    fflush(arquivoLog);
}

void registrarLog(int geracao, Populacao *pop) {
    if (!arquivoLog) return;

    No *atual = pop->inicio;
    int id = 0;

    while (atual != NULL) {
        fprintf(arquivoLog, "%d,", geracao);  // Número da geração
        fprintf(arquivoLog, "%d,", id++);     // ID do indivíduo

        for (int i = 0; i < tamanho_genoma; i++) {
            fprintf(arquivoLog, "%c", atual->ind.cromossomo[i]);
        }

        fprintf(arquivoLog, ",%d,%d,%s\n",
                atual->ind.fitness,
                atual->ind.passos,
                atual->ind.concluido ? "sim" : "nao");

        atual = atual->prox;
    }
    fflush(arquivoLog);
}

void finalizarLog() {
    if (arquivoLog) {
        fclose(arquivoLog);
        arquivoLog = NULL;
        printf("Log salvo em _logs/logs.csv\n");
    }
}
