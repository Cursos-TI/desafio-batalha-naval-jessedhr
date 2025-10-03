#include <stdio.h>

// Definições de constantes para o tabuleiro
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// --- Protótipo da função para exibir o tabuleiro ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // 1. Representar o Tabuleiro: Matriz 10x10 inicializada com 0 (ÁGUA)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Loop aninhado para inicializar todas as posições com AGUA (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Coordenadas Iniciais dos Navios (Definidas diretamente no código)
    
    // NAVIO HORIZONTAL (tamanho 3): Posição inicial (Linha: 1, Coluna: 2)
    int linha_h = 1; 
    int coluna_h = 2; 

    // NAVIO VERTICAL (tamanho 3): Posição inicial (Linha: 5, Coluna: 6)
    int linha_v = 5; 
    int coluna_v = 6; 

    // --- Validação Simplificada de Limites do Tabuleiro ---
    // A validação verifica se o navio não ultrapassa a borda.
    
    // Validação do Navio Horizontal:
    // Deve garantir que coluna_h + TAMANHO_NAVIO - 1 seja <= 9 (TAMANHO_TABULEIRO - 1)
    if (coluna_h + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("ERRO: O Navio Horizontal excede os limites do tabuleiro.\n");
        return 1; // Encerra o programa com erro
    }
    
    // Validação do Navio Vertical:
    // Deve garantir que linha_v + TAMANHO_NAVIO - 1 seja <= 9 (TAMANHO_TABULEIRO - 1)
    if (linha_v + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("ERRO: O Navio Vertical excede os limites do tabuleiro.\n");
        return 1; // Encerra o programa com erro
    }

    // --- Posicionamento dos Navios na Matriz ---

    // Posicionamento do NAVIO HORIZONTAL:
    // Percorre as colunas a partir da coluna_h, mantendo a linha_h fixa.
    // Como o tabuleiro foi inicializado com 0s, a validação de sobreposição
    // é simplificada: apenas verificamos se a posição atual é ÁGUA (0).
    // Neste exemplo, as coordenadas foram escolhidas para NÃO sobrepor.
    for (int j = 0; j < TAMANHO_NAVIO; j++) {
        // Verifica sobreposição (simples): Se já houver um navio (3), não posiciona
        if (tabuleiro[linha_h][coluna_h + j] == AGUA) {
            tabuleiro[linha_h][coluna_h + j] = NAVIO; // Posição ocupada = 3
        } else {
            printf("AVISO: O Navio Horizontal tentou sobrepor uma posição já ocupada.\n");
            // No nível novato, podemos apenas emitir um aviso e seguir.
        }
    }

    // Posicionamento do NAVIO VERTICAL:
    // Percorre as linhas a partir da linha_v, mantendo a coluna_v fixa.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Verifica sobreposição (simples): Se já houver um navio (3), não posiciona
        if (tabuleiro[linha_v + i][coluna_v] == AGUA) {
            tabuleiro[linha_v + i][coluna_v] = NAVIO; // Posição ocupada = 3
        } else {
            printf("AVISO: O Navio Vertical tentou sobrepor uma posição já ocupada.\n");
            // No nível novato, podemos apenas emitir um aviso e seguir.
        }
    }

    // 3. Exibir o Tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0; // Encerra o programa com sucesso
}

// --- Definição da função para exibir o tabuleiro ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- Tabuleiro Batalha Naval (10x10) ---\n\n");
    
    // Cabeçalho de Colunas (0 a 9)
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");
    
    // Separador
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("-\n");


    // Loop aninhado para percorrer e imprimir a matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o índice da linha (0 a 9)
        printf("%d|", i); 
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula (0 = Água, 3 = Navio)
            // Um espaço é adicionado para separar os elementos
            printf(" %d", tabuleiro[i][j]); 
        }
        printf("\n"); // Quebra de linha após cada linha do tabuleiro
    }
    printf("\n0 = Água | 3 = Navio\n");
}