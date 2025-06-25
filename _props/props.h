#define MAX_LINHA 128

// Parâmetros
extern int numero_individuos;
extern int tamanho_genoma;
extern float taxa_mutacao;
extern int numero_maximo_geracoes;

// Labirinto
extern char arquivo_labirinto[100];
extern int posicao_inicial_x;
extern int posicao_inicial_y;
extern int posicao_final_x;
extern int posicao_final_y;

// Avaliação
extern int movimento_invalido_penalidade;
extern int chegou_objetivo_bonus;
extern int limite_passos;

// Remove espaçoes em branco
void remover_espaco(char *str);

// ler o arquivo props.ini
void ler_arquivo_ini(const char *caminho);