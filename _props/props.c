#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "props.h"


// [Parametros]
int numero_individuos = 0;
int tamanho_genoma = 0;
float taxa_mutacao = 0.0;
int numero_maximo_geracoes = 0;

// [Labirinto]
char arquivo_labirinto[100] = "";
int posicao_inicial_x = 0;
int posicao_inicial_y = 0;
int posicao_final_x = 0;
int posicao_final_y = 0;

// [Avaliacao]
int movimento_invalido_penalidade = 0;
int chegou_objetivo_bonus = 0;
int limite_passos = 0;


void remover_espaco(char *str){
    char *fim;
    while (*str == ' ' || *str == '\t') str++;
    {
        fim = str + strlen(str) - 1;
        while (fim > str && (*fim == '\n' || *fim == '\r' || *fim == ' ' || *fim == '\t')){
            *fim = '\0';
            fim--;
        }
    }
}

void ler_arquivo_ini(const char *caminho){
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo INI");
        exit(1);
    }

    char linha[MAX_LINHA];
    char secao_atual[50] = "";

    while (fgets(linha, sizeof(linha), arquivo)){
        remover_espaco(linha);

        if (linha[0] == '#' || linha[0] == ';' || linha[0] == '\n'){
            continue; // Ignora comentários e linhas vazias.
        } else if (linha[0] == '['){
            sscanf(linha, "[%[^]]", secao_atual); // Lê a seção
        } else{
            char chave[50], valor[50];
            sscanf(linha, "%[^=]=%s", chave, valor);
            remover_espaco(chave);
            remover_espaco(valor);

            if(strcmp(secao_atual, "Parametros") == 0){
                if (strcmp(chave, "numero_individuos") == 0)
                    numero_individuos = atoi(valor);
                else if (strcmp(chave, "tamanho_genoma") == 0)
                    tamanho_genoma = atoi(valor);
                else if (strcmp(chave, "taxa_mutacao") == 0)
                    taxa_mutacao = atof(valor);
                else if (strcmp(chave, "numero_maximo_geracoes") == 0)
                    numero_maximo_geracoes = atoi(valor);
            } else if(strcmp(secao_atual, "Labirinto") == 0){
                if(strcmp(chave, "arquivo_labirinto") == 0){
                    strncpy(arquivo_labirinto, valor, sizeof(arquivo_labirinto)-1);
                    arquivo_labirinto[sizeof(arquivo_labirinto)-1] = '\0';
                } else if (strcmp(chave, "posicao_inicial_x") == 0){
                    posicao_inicial_x = atoi(valor);
                } else if (strcmp(chave, "posicao_inicial_y") == 0){
                    posicao_inicial_y = atoi(valor);
                } else if (strcmp(chave, "posicao_final_x") == 0){
                    posicao_final_x = atoi(valor);
                } else if (strcmp(chave, "posicao_final_y") == 0){
                    posicao_final_y = atoi(valor);
                }
            } else if(strcmp(secao_atual, "Avaliacao") == 0){
                if(strcmp(chave, "movimento_invalido_penalidade") == 0){
                    movimento_invalido_penalidade = atoi(valor);
                } else if(strcmp(chave, "chegou_objetivo_bonus") == 0){
                    chegou_objetivo_bonus = atoi(valor);
                } else if(strcmp(chave, "limite_passos") == 0){
                    limite_passos = atoi(valor);
                } 
            }
        }
    }
    fclose(arquivo);
}