# Labirinto Genético

![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)

Projeto em C que implementa um **Algoritmo Genético** para navegação em labirintos, onde indivíduos evoluem para encontrar o melhor caminho até a saída.

---

## 📌 Sobre o Projeto

Este projeto utiliza técnicas de computação evolutiva para resolver o problema de navegação em labirintos. Cada indivíduo possui um cromossomo que codifica movimentos no mapa, e a evolução ocorre por meio de seleção, crossover e mutação.

---
### Grafico de Melhor individuo por Geração
<p align="center">
  <img src="https://i.ibb.co/pBLMVMRZ/Captura-de-tela-2025-06-25-101349.png" alt="Exemplo do projeto">
</p>


---
## ⚙️ Funcionalidades

- Representação do indivíduo com cromossomo contendo movimentos:  
  - `C` - Cima  
  - `B` - Baixo  
  - `E` - Esquerda  
  - `D` - Direita
- Simulação do percurso no labirinto considerando colisões e limites do mapa.
- Controle dos movimentos visíveis na posição inicial via fila de movimentos válidos.
- Algoritmo Genético completo: seleção, crossover, mutação e evolução da população.
- Avaliação do fitness baseada em distância até a saída, passos realizados e sucesso.
- Geração de gráficos e relatórios para análise dos resultados.

---

## 🧩 Estrutura do Código

- `individuo.c/h` - Criação, inicialização e liberação dos indivíduos.
- `simulacao.c/h` - Simulação dos movimentos dos indivíduos no labirinto.
- `populacao.c/h` - Manipulação da população e ordenação por fitness.
- `crossover.c/h` - Operações de cruzamento dos cromossomos.
- `mutacao.c/h` - Funções para mutação dos cromossomos.
- `fitness.c/h` - Cálculo da aptidão dos indivíduos.
- `mapa.c/h` - Representação e manipulação do labirinto.
- `logs.c/h` - Geração de logs e registros da simulação.
- `graficos/` - Geração de gráficos com resultados.

---

## 🚀 Como Rodar

1. Clone o repositório:
   ```bash
   git clone https://github.com/ricardolopestomaz/labirinto-genetico.git
   cd labirinto-genetico

## Compile o projeto:
 ```bash
gcc main.c _crossover/crossover.c _fitness/fitness.c _individuo/individuo.c _mapa/mapa.c _mutacao/mutacao.c _populacao/populacao.c _props/props.c _selecao/selecao.c _simulacao/simulacao.c _logs/logs.c graficos/graficos.c -o main.exe

## Execute o programa:
./main.exe

