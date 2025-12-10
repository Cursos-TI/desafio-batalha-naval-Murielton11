#include <stdio.h>

#define TAM 10          // Tabuleiro 10x10
#define AGUA   0
#define NAVIO  3
#define HABIL  5        // Posição afetada por habilidade

int tabuleiro[TAM][TAM];

/* ============================================================= */
/* 1) INICIALIZAÇÃO DO TABULEIRO                                */
/* ============================================================= */
void inicializar() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

/* ============================================================= */
/* 2) POSICIONAMENTO DOS NAVIOS (exemplo simples)               */
/* ============================================================= */
void colocar_navios() {
    // Navio horizontal na linha 2
    for (int c = 2; c <= 4; c++) tabuleiro[2][c] = NAVIO;
    // Navio vertical na coluna 7
    for (int l = 5; l <= 7; l++) tabuleiro[l][7] = NAVIO;
}

/* ============================================================= */
/* 3) CONSTRUÇÃO DINÂMICA DAS MATRIZES DE HABILIDADE (5x5)       */
/* ============================================================= */

/* Cone apontando para baixo (origem no topo) */
void aplicar_cone(int centro_linha, int centro_coluna) {
    int tamanho = 5;                 // matriz 5x5
    int metade = tamanho / 2;        // 2

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int l = centro_linha - metade + i;
            int c = centro_coluna - metade + j;

            // Dentro do tabuleiro?
            if (l >= 0 && l < TAM && c >= 0 && c < TAM) {
                // Cone: quanto mais baixo, mais largo
                int distancia_do_topo = i;               // 0 = topo
                int largura_na_linha = distancia_do_topo + 1;
                int inicio = metade - distancia_do_topo;
                int fim    = metade + distancia_do_topo;

                if (j >= inicio && j <= fim) {
                    tabuleiro[l][c] = HABIL;
                }
            }
        }
    }
}

/* Cruz (centro marcado) */
void aplicar_cruz(int centro_linha, int centro_coluna) {
    int tamanho = 5;
    int metade = tamanho / 2;

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int l = centro_linha - metade + i;
            int c = centro_coluna - metade + j;

            if (l >= 0 && l < TAM && c >= 0 && c < TAM) {
                if (i == metade || j == metade) {   // linha ou coluna central
                    tabuleiro[l][c] = HABIL;
                }
            }
        }
    }
}

/* Octaedro / Losango (vista frontal) */
void aplicar_octaedro(int centro_linha, int centro_coluna) {
    int tamanho = 5;
    int metade = tamanho / 2;

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int l = centro_linha - metade + i;
            int c = centro_coluna - metade + j;

            if (l >= 0 && l < TAM && c >= 0 && c < TAM) {
                int dist = abs(i - metade) + abs(j - metade);
                if (dist <= metade) {               // forma de losango
                    tabuleiro[l][c] = HABIL;
                }
            }
        }
    }
}

/* ============================================================= */
/* 4) EXIBIÇÃO DO TABULEIRO                                      */
/* ============================================================= */
void exibir() {
    printf("\n   ");
    for (int c = 0; c < TAM; c++) printf(" %d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf(" %d ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == NAVIO)      printf("[N]");
            else if (tabuleiro[i][j] == HABIL) printf("[*]");
            else                               printf("[ ]");
        }
        printf(" %d\n", i);
    }
    printf("   ");
    for (int c = 0; c < TAM; c++) printf(" %d ", c);
    printf("\n\n");

    printf("LEGENDA:\n");
    printf(" [ ] = Agua\n");
    printf(" [N] = Navio\n");
    printf(" [*] = Area afetada por habilidade\n\n");
}

int main() {
    inicializar();
    colocar_navios();

    printf("=== BATALHA NAVAL - HABILIDADES ESPECIAIS ===\n");

    // === DEFINIÇÃO DOS PONTOS DE ORIGEM DAS HABILIDADES (mude aqui se quiser) ===
    aplicar_cone(3, 5);         // Cone centrado na posição (3,5)
    aplicar_cruz(7, 2);         // Cruz centrada na posição (7,2)
    aplicar_octaedro(5, 8);     // Octaedro/losango centrado na (5,8)

    exibir();

    printf("Habilidades aplicadas:\n");
    printf(" - Cone (apontando para baixo) em (3,5)\n");
    printf(" - Cruz centrada em (7,2)\n");
    printf(" - Octaedro (losango) centrado em (5,8)\n");

    return 0;
}
