#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// --- Definições de Constantes ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5 // Valor para marcar áreas de efeito

// --- Definições de Habilidades ---
#define RAIO_CRUZ 1 
#define RAIO_OCTAEDRO 2 

// --- Protótipos das Funções ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha_inicio, int coluna_inicio, 
                     int orientacao_linha, int orientacao_coluna, 
                     const char *nome);

// Funções para aplicar as habilidades
void aplicarHabilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int centro_l, int centro_c);
void aplicarHabilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int centro_l, int centro_c);
void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                              int centro_l, int centro_c);


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // 1. Inicializa o tabuleiro com ÁGUA (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    printf("--- Batalha Naval: Formas Geométricas Visíveis ---\n");
    
    // 2. Posicionamento Estratégico dos Navios
    posicionarNavio(tabuleiro, 1, 1, 0, 1, "Navio 1 (Horizontal)");
    posicionarNavio(tabuleiro, 7, 8, 1, 0, "Navio 2 (Vertical)");
    posicionarNavio(tabuleiro, 4, 0, 1, 1, "Navio 3 (Diagonal)");
    posicionarNavio(tabuleiro, 2, 9, 1, -1, "Navio 4 (Diagonal Inversa)");

    // 3. Aplicação das Habilidades no Tabuleiro
    printf("\n--- Aplicando Habilidades Especiais ---\n");
    
    // Ponto de Origem da Habilidade 1: Cone
    // Posicionado para encostar na ponta do Navio 1
    aplicarHabilidadeCone(tabuleiro, 2, 4); 

    // Ponto de Origem da Habilidade 2: Cruz
    // Posicionado para encostar no Navio 3
    aplicarHabilidadeCruz(tabuleiro, 5, 5); 
    
    // Ponto de Origem da Habilidade 3: Octaedro
    // Posicionado para encostar no Navio 2
    aplicarHabilidadeOctaedro(tabuleiro, 7, 6); 

    // 4. Exibir o Tabuleiro Final
    exibirTabuleiro(tabuleiro);

    return 0;
}

// FUNÇÕES DE APLICAÇÃO DE HABILIDADE

void aplicarHabilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int centro_l, int centro_c) {
    
    printf("Aplicando Habilidade Cone (Origem: %d, %d)\n", centro_l, centro_c);
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            
            int delta_linha = i - centro_l;
            int delta_coluna = abs(j - centro_c);
            
            // Lógica do Cone (expande para baixo, 3 níveis)
            if (delta_linha >= 0 && delta_linha < 3 && // Limita a 3 linhas abaixo
                delta_coluna <= delta_linha) 
            {
                // REQUISITO: Só marca se não for um Navio (sem sobreposição)
                if (tabuleiro[i][j] != NAVIO) {
                    tabuleiro[i][j] = HABILIDADE; 
                }
            }
        }
    }
}

void aplicarHabilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int centro_l, int centro_c) {
    
    printf("Aplicando Habilidade Cruz (Origem: %d, %d)\n", centro_l, centro_c);
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            
            // Lógica da Cruz (3x3 centrada)
            if ( (i == centro_l && abs(j - centro_c) <= RAIO_CRUZ) || // Linha central (3 células)
                 (j == centro_c && abs(i - centro_l) <= RAIO_CRUZ) )  // Coluna central (3 células)
            {
                // REQUISITO: Só marca se não for um Navio
                if (tabuleiro[i][j] != NAVIO) {
                    tabuleiro[i][j] = HABILIDADE; 
                }
            }
        }
    }
}

void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                              int centro_l, int centro_c) {
    
    printf("Aplicando Habilidade Octaedro (Origem: %d, %d)\n", centro_l, centro_c);
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            
            // Lógica do Losango
            int distancia_manhattan = abs(i - centro_l) + abs(j - centro_c);
            
            if (distancia_manhattan <= RAIO_OCTAEDRO) {
                // REQUISITO: Só marca se não for um Navio
                if (tabuleiro[i][j] != NAVIO) {
                    tabuleiro[i][j] = HABILIDADE;
                }
            }
        }
    }
}

// FUNÇÕES DE UTILIDADE (Exibição e Posicionamento)

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n====================================\n");
    printf("        TABULEIRO FINAL MESTRE      \n");
    printf("====================================\n");
    
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
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Área de Habilidade\n");
}

bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha_inicio, int coluna_inicio, 
                     int orientacao_linha, int orientacao_coluna, 
                     const char *nome) {
    
    int nova_linha, nova_coluna;
    
    // Validação de Limites e Sobreposição de Navios
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        nova_linha = linha_inicio + (k * orientacao_linha);
        nova_coluna = coluna_inicio + (k * orientacao_coluna);

        // Checa se a nova posição está fora do limite OU já contém um navio
        if (nova_linha < 0 || nova_linha >= TAMANHO_TABULEIRO || 
            nova_coluna < 0 || nova_coluna >= TAMANHO_TABULEIRO || 
            tabuleiro[nova_linha][nova_coluna] == NAVIO) {
            return false;
        }
    }
    
    // Posicionamento
    printf("Posicionado: %s\n", nome);
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        tabuleiro[linha_inicio + (k * orientacao_linha)][coluna_inicio + (k * orientacao_coluna)] = NAVIO;
    }
    
    return true;
}