#include <stdio.h>

#define TAMANHO_TABULEIRO 10   // Tabuleiro 10x10
#define TAMANHO_NAVIO 3        // Cada navio ocupa 3 casas
#define AGUA 0                 // Representa água
#define NAVIO 3                // Representa parte do navio

int main() {
    // === 1) DECLARAÇÃO E INICIALIZAÇÃO DO TABULEIRO (10x10 com água) ===
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Preenche todo o tabuleiro com 0 (água)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // === 2) DEFINIÇÃO DOS NAVIOS (coordenadas iniciais escolhidas manualmente) ===

    // Navio 1 - HORIZONTAL na linha 4, começando na coluna 2 (posições: 4,2 ; 4,3 ; 4,4)
    int linha_horizontal = 4;
    int coluna_inicio_horizontal = 2;

    // Navio 2 - VERTICAL na coluna 7, começando na linha 1 (posições: 1,7 ; 2,7 ; 3,7)
    int linha_inicio_vertical = 1;
    int coluna_vertical = 7;

    // === 3) VALIDAÇÃO SIMPLES: os navios cabem no tabuleiro? ===
    // Navio horizontal
    if (linha_horizontal < 0 || linha_horizontal >= TAMANHO_TABULEIRO ||
        coluna_inicio_horizontal + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO) {
        printf("ERRO: Navio horizontal fora dos limites!\n");
        return 1;
    }

    // Navio vertical
    if (coluna_vertical < 0 || coluna_vertical >= TAMANHO_TABULEIRO ||
        linha_inicio_vertical + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO) {
        printf("ERRO: Navio vertical fora dos limites!\n");
        return 1;
    }

    // === 4) VERIFICA SE NÃO HÁ SOBREPOSIÇÃO (validação simples) ===
    int sobreposicao = 0;

    // Verifica navio horizontal
    for (int c = coluna_inicio_horizontal; c < coluna_inicio_horizontal + TAMANHO_NAVIO; c++) {
        if (tabuleiro[linha_horizontal][c] != AGUA) {
            sobreposicao = 1;
        }
    }

    // Verifica navio vertical
    for (int l = linha_inicio_vertical; l < linha_inicio_vertical + TAMANHO_NAVIO; l++) {
        if (tabuleiro[l][coluna_vertical] != AGUA) {
            sobreposicao = 1;
        }
    }

    if (sobreposicao) {
        printf("ERRO: Os navios estao se sobrepondo!\n");
        return 1;
    }

    // === 5) POSICIONA OS NAVIOS NO TABULEIRO ===
    
    // Posiciona o navio HORIZONTAL
    for (int c = coluna_inicio_horizontal; c < coluna_inicio_horizontal + TAMANHO_NAVIO; c++) {
        tabuleiro[linha_horizontal][c] = NAVIO;
    }

    // Posiciona o navio VERTICAL
    for (int l = linha_inicio_vertical; l < linha_inicio_vertical + TAMANHO_NAVIO; l++) {
        tabuleiro[l][coluna_vertical] = NAVIO;
    }

    // === 6) EXIBE O TABULEIRO COM OS NAVIOS ===
    printf("\n=== TABULEIRO DA BATALHA NAVAL (10x10) ===\n");
    printf("   "); // espaçamento para os números das colunas
    for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
        printf(" %d ", c);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf(" %d ", i);  // número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                printf("[3]");   // Mostra o navio
            } else {
                printf("[ ]");   // Mostra água
            }
        }
        printf(" %d\n", i); // repete o número da linha no final
    }

    printf("   ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
        printf(" %d ", c);
    }
    printf("\n\n");

    printf("Legenda:\n");
    printf(" [ ] = Agua\n");
    printf(" [3] = Parte do navio (tamanho 3)\n");
    printf(" Navio horizontal: linha %d, colunas %d a %d\n", 
           linha_horizontal, coluna_inicio_horizontal, coluna_inicio_horizontal + 2);
    printf(" Navio vertical: coluna %d, linhas %d a %d\n", 
           coluna_vertical, linha_inicio_vertical, linha_inicio_vertical + 2);

    return 0;
}
