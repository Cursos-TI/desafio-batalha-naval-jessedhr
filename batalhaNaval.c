#include <stdio.h>
#include <stdbool.h>

// Definições de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// --- Protótipos das Funções ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha_inicio, int coluna_inicio, 
                     int orientacao_linha, int orientacao_coluna, 
                     const char *nome);


int main() {
    // 1. Criar o Tabuleiro 10x10 e Inicializar com ÁGUA (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa todas as posições com AGUA (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    printf("--- Posicionamento de Navios no Tabuleiro (Tamanho %dx%d) ---\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    
    posicionarNavio(tabuleiro, 1, 1, 0, 1, "Navio 1 (Horizontal)");
    posicionarNavio(tabuleiro, 5, 8, 1, 0, "Navio 2 (Vertical)");
    posicionarNavio(tabuleiro, 3, 3, 1, 1, "Navio 3 (Diagonal Principal)");
    posicionarNavio(tabuleiro, 9, 1, -1, 1, "Navio 4 (Diagonal Secundária)");


    // 3. Exibir o Tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}

// --- Implementação da Função de Posicionamento ---
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha_inicio, int coluna_inicio, 
                     int orientacao_linha, int orientacao_coluna, 
                     const char *nome) {
    
    int nova_linha, nova_coluna;
    
    // O navio só será posicionado se todas as suas partes estiverem no limite.
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        nova_linha = linha_inicio + (k * orientacao_linha);
        nova_coluna = coluna_inicio + (k * orientacao_coluna);

        // Validação de Limites
        if (nova_linha < 0 || nova_linha >= TAMANHO_TABULEIRO || 
            nova_coluna < 0 || nova_coluna >= TAMANHO_TABULEIRO) {
            printf("ERRO: %s - Fora dos limites do tabuleiro. Posicionamento cancelado.\n", nome);
            return false;
        }

        // Validação de Sobreposição
        if (tabuleiro[nova_linha][nova_coluna] == NAVIO) {
            printf("ERRO: %s - Sobreposição detectada na posição (%d, %d). Posicionamento cancelado.\n", 
                   nome, nova_linha, nova_coluna);
            return false;
        }
    }
    
    printf("SUCESSO: %s posicionado a partir de (%d, %d).\n", nome, linha_inicio, coluna_inicio);
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        nova_linha = linha_inicio + (k * orientacao_linha);
        nova_coluna = coluna_inicio + (k * orientacao_coluna);
        
        tabuleiro[nova_linha][nova_coluna] = NAVIO;
    }
    
    return true;
}


// --- Implementação da Função de Exibição
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- Tabuleiro Final ---\n");
    
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


    // Corpo do Tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d|", i); 
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]); 
        }
        printf("\n"); 
    }
    printf("\nLegenda: 0 = Água | 3 = Navio\n");
}