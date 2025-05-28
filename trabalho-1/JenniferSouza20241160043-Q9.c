#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>  

#define TAM_TABULEIRO 10
#define MAX_NAVIOS 5 // Mínimo: 1 de 4, 1 de 3, 3 de 1. Total 5 barcos.

// Estrutura para um barco
typedef struct {
    int tamanho;
    char orientacao; // 'H' para horizontal, 'V' para vertical
    int linhaInicial;
    int colunaInicial;
    int hits; // Quantos pedaços do barco já foram atingidos
    int afundado; // 1 se afundado, 0 caso contrário
} Barco;

// Mapas dos jogadores
char mapaJogador1[TAM_TABULEIRO][TAM_TABULEIRO]; // Mapa real do Jogador 1
char mapaVisaoJogador1[TAM_TABULEIRO][TAM_TABULEIRO]; // Visão do J1 sobre o J2

char mapaJogador2[TAM_TABULEIRO][TAM_TABULEIRO]; // Mapa real do Jogador 2
char mapaVisaoJogador2[TAM_TABULEIRO][TAM_TABULEIRO]; // Visão do J2 sobre o J1

// Arrays para armazenar os barcos de cada jogador
Barco barcosJogador1[MAX_NAVIOS];
Barco barcosJogador2[MAX_NAVIOS];

// Protótipos das funções
void limparTela();
void inicializarMapas();
void exibirMapa(char mapa[TAM_TABULEIRO][TAM_TABULEIRO], int isSeuProprioMapa, int jogador);
int validarPosicionamento(char mapa[TAM_TABULEIRO][TAM_TABULEIRO], Barco barco);
void posicionarBarco(char mapa[TAM_TABULEIRO][TAM_TABULEIRO], Barco *barco, int numBarcos);
int fazerTiro(char mapaOponente[TAM_TABULEIRO][TAM_TABULEIRO], char mapaVisao[TAM_TABULEIRO][TAM_TABULEIRO], Barco barcosOponente[], int numBarcosOponente, char linhaChar, int coluna);
int verificarVitoria(Barco barcosOponente[], int numBarcosOponente);

int main() {
    inicializarMapas();

    // Definição dos barcos (exemplo para o mínimo de 5 barcos)
    // O ideal seria fazer um loop e permitir que o jogador defina os tipos dentro das regras
    barcosJogador1[0] = (Barco){4, ' ', -1, -1, 0, 0}; // Navio de 4
    barcosJogador1[1] = (Barco){3, ' ', -1, -1, 0, 0}; // Navio de 3
    barcosJogador1[2] = (Barco){1, ' ', -1, -1, 0, 0}; // Navio de 1
    barcosJogador1[3] = (Barco){1, ' ', -1, -1, 0, 0}; // Navio de 1
    barcosJogador1[4] = (Barco){1, ' ', -1, -1, 0, 0}; // Navio de 1

    barcosJogador2[0] = (Barco){4, ' ', -1, -1, 0, 0};
    barcosJogador2[1] = (Barco){3, ' ', -1, -1, 0, 0};
    barcosJogador2[2] = (Barco){1, ' ', -1, -1, 0, 0};
    barcosJogador2[3] = (Barco){1, ' ', -1, -1, 0, 0};
    barcosJogador2[4] = (Barco){1, ' ', -1, -1, 0, 0};


    // --- FASE DE POSICIONAMENTO ---
    printf("--- Posicionamento dos Barcos do Jogador 1 ---\n");
    posicionarBarco(mapaJogador1, barcosJogador1, MAX_NAVIOS);

    printf("--- Posicionamento dos Barcos do Jogador 2 ---\n");
    posicionarBarco(mapaJogador2, barcosJogador2, MAX_NAVIOS);

    // --- FASE DE JOGO ---
    int jogadorAtual = 1;
    int jogoAtivo = 1;

    while (jogoAtivo) {
        limparTela();
        printf("--- VEZ DO JOGADOR %d ---\n\n", jogadorAtual);

        // Exibe o mapa do jogador atual (seu mapa)
        printf("Seu Mapa:\n");
        exibirMapa( (jogadorAtual == 1) ? mapaJogador1 : mapaJogador2, 1, jogadorAtual);
        
        // Exibe o mapa de visão do oponente
        printf("\nMapa do Oponente:\n");
        exibirMapa( (jogadorAtual == 1) ? mapaVisaoJogador1 : mapaVisaoJogador2, 0, (jogadorAtual == 1 ? 2 : 1) );

        char linhaChar;
        int coluna;
        int resultadoTiro;

        printf("\nJogador %d, informe a celula para atirar (ex: A5): ", jogadorAtual);
        while (1) {
            char input[5];
            scanf("%s", input);
            linhaChar = toupper(input[0]);
            coluna = atoi(&input[1]);

            if (linhaChar >= 'A' && linhaChar <= 'A' + TAM_TABULEIRO - 1 && coluna >= 1 && coluna <= TAM_TABULEIRO) {
                // Tentar atirar no mapa do oponente e atualizar a visão
                if (jogadorAtual == 1) {
                    resultadoTiro = fazerTiro(mapaJogador2, mapaVisaoJogador1, barcosJogador2, MAX_NAVIOS, linhaChar, coluna);
                } else {
                    resultadoTiro = fazerTiro(mapaJogador1, mapaVisaoJogador2, barcosJogador1, MAX_NAVIOS, linhaChar, coluna);
                }

                if (resultadoTiro == -1) { // Tiro já feito naquela posição
                    printf("Voce ja atirou nesta posicao. Tente novamente: ");
                } else {
                    if (resultadoTiro == 1) {
                        printf("ACERTOU!\n");
                    } else {
                        printf("AGUA!\n");
                    }
                    break; // Sai do loop de leitura de tiro
                }
            } else {
                printf("Entrada invalida. Formato esperado (ex: B3): ");
            }
        }
        
        // Verifica vitória
        if (jogadorAtual == 1) {
            if (verificarVitoria(barcosJogador2, MAX_NAVIOS)) {
                limparTela();
                exibirMapa(mapaJogador2, 1, 2); // Exibe o mapa final do oponente
                printf("Fim de jogo! JOGADOR 1 VENCEU!\n");
                jogoAtivo = 0;
            }
        } else {
            if (verificarVitoria(barcosJogador1, MAX_NAVIOS)) {
                limparTela();
                exibirMapa(mapaJogador1, 1, 1); // Exibe o mapa final do oponente
                printf("Fim de jogo! JOGADOR 2 VENCEU!\n");
                jogoAtivo = 0;
            }
        }
        
        // Troca de jogador, se o jogo continuar
        if (jogoAtivo) {
            printf("\nPressione ENTER para o proximo jogador...\n");
            getchar(); // Consome o \n restante do scanf anterior
            getchar(); // Espera por um ENTER
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }

    return 0;
}

// Implementações das funções auxiliares (precisam ser feitas)
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void inicializarMapas() {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            mapaJogador1[i][j] = ' ';
            mapaVisaoJogador1[i][j] = ' ';
            mapaJogador2[i][j] = ' ';
            mapaVisaoJogador2[i][j] = ' ';
        }
    }
}

void exibirMapa(char mapa[TAM_TABULEIRO][TAM_TABULEIRO], int isSeuProprioMapa, int jogador) {
    printf("  ");
    for (int c = 1; c <= TAM_TABULEIRO; c++) {
        printf("%3d", c);
    }
    printf("\n");

    for (int r = 0; r < TAM_TABULEIRO; r++) {
        printf("%c ", 'A' + r);
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            if (isSeuProprioMapa) {
                printf(" %c ", mapa[r][c]); // Exibe tudo no seu próprio mapa
            } else {
                // No mapa do oponente, só mostra 'O' (acerto) ou 'X' (erro), esconde 'N'
                if (mapa[r][c] == 'N') {
                    printf("   "); // Esconde o navio
                } else {
                    printf(" %c ", mapa[r][c]);
                }
            }
        }
        printf("\n");
    }
}

// Valida se um barco pode ser posicionado
int validarPosicionamento(char mapa[TAM_TABULEIRO][TAM_TABULEIRO], Barco barco) {
    int r = barco.linhaInicial;
    int c = barco.colunaInicial;
    int tamanho = barco.tamanho;
    char orientacao = barco.orientacao;

    if (orientacao == 'H') { // Horizontal
        if (c + tamanho > TAM_TABULEIRO) return 0; // Sai do tabuleiro
        for (int i = 0; i < tamanho; i++) {
            if (mapa[r][c + i] == 'N') return 0; // Colide com outro barco
        }
    } else if (orientacao == 'V') { // Vertical
        if (r + tamanho > TAM_TABULEIRO) return 0; // Sai do tabuleiro
        for (int i = 0; i < tamanho; i++) {
            if (mapa[r + i][c] == 'N') return 0; // Colide com outro barco
        }
    } else {
        return 0; // Orientação inválida
    }
    return 1; // Posicionamento válido
}


// Função para o jogador posicionar seus barcos
void posicionarBarco(char mapa[TAM_TABULEIRO][TAM_TABULEIRO], Barco barcos[], int numBarcos) {
    char linhaChar;
    int coluna;
    char orientacaoChar;
    
    for (int i = 0; i < numBarcos; i++) {
        while (1) {
            limparTela();
            printf("Posicione seus barcos:\n");
            exibirMapa(mapa, 1, 0); // Exibe o mapa de posicionamento
            printf("Posicione o barco de tamanho %d (Ex: A1 H ou B5 V): ", barcos[i].tamanho);
            scanf(" %c%d %c", &linhaChar, &coluna, &orientacaoChar); // Espaço antes de %c para consumir \n

            barcos[i].linhaInicial = toupper(linhaChar) - 'A';
            barcos[i].colunaInicial = coluna - 1;
            barcos[i].orientacao = toupper(orientacaoChar);

            if (validarPosicionamento(mapa, barcos[i])) {
                // Aplica o posicionamento
                if (barcos[i].orientacao == 'H') {
                    for (int k = 0; k < barcos[i].tamanho; k++) {
                        mapa[barcos[i].linhaInicial][barcos[i].colunaInicial + k] = 'N';
                    }
                } else { // 'V'
                    for (int k = 0; k < barcos[i].tamanho; k++) {
                        mapa[barcos[i].linhaInicial + k][barcos[i].colunaInicial] = 'N';
                    }
                }
                printf("Barco posicionado com sucesso!\n");
                getchar(); // Consome o \n restante do scanf
                break; // Sai do loop de posicionamento para o barco atual
            } else {
                printf("Posicao ou orientacao invalida para o barco. Tente novamente.\n");
                getchar(); // Consome o \n restante do scanf
            }
        }
    }
    printf("Todos os barcos posicionados!\n");
    printf("Pressione ENTER para continuar...\n");
    getchar(); // Espera pelo Enter
}

// Função para fazer um tiro
// Retorna 1 se acertou, 0 se errou, -1 se já atirou naquela posição
int fazerTiro(char mapaOponente[TAM_TABULEIRO][TAM_TABULEIRO], char mapaVisao[TAM_TABULEIRO][TAM_TABULEIRO], Barco barcosOponente[], int numBarcosOponente, char linhaChar, int coluna) {
    int r = linhaChar - 'A';
    int c = coluna - 1;

    // Valida se a posição já foi atingida
    if (mapaVisao[r][c] == 'O' || mapaVisao[r][c] == 'X') {
        return -1; // Já atirou aqui
    }

    if (mapaOponente[r][c] == 'N') {
        mapaOponente[r][c] = 'O'; // Marca no mapa real do oponente
        mapaVisao[r][c] = 'O';    // Marca na sua visão
        
        // Encontra qual barco foi atingido para atualizar os hits
        for(int i = 0; i < numBarcosOponente; i++){
            Barco *b = &barcosOponente[i]; // Ponteiro para o barco
            if (b->afundado) continue; // Pula barcos já afundados

            if (b->orientacao == 'H') {
                if (r == b->linhaInicial && c >= b->colunaInicial && c < b->colunaInicial + b->tamanho) {
                    b->hits++;
                    if (b->hits == b->tamanho) {
                        b->afundado = 1;
                        printf("UM BARCO FOI AFUNDADO!\n");
                    }
                    break;
                }
            } else { // 'V'
                if (c == b->colunaInicial && r >= b->linhaInicial && r < b->linhaInicial + b->tamanho) {
                    b->hits++;
                    if (b->hits == b->tamanho) {
                        b->afundado = 1;
                        printf("UM BARCO FOI AFUNDADO!\n");
                    }
                    break;
                }
            }
        }
        return 1; // Acertou
    } else {
        mapaOponente[r][c] = 'X'; // Marca no mapa real do oponente (água)
        mapaVisao[r][c] = 'X';    // Marca na sua visão
        return 0; // Água (errou)
    }
}

// Verifica se todos os barcos do oponente foram afundados
int verificarVitoria(Barco barcosOponente[], int numBarcosOponente) {
    for (int i = 0; i < numBarcosOponente; i++) {
        if (!barcosOponente[i].afundado) {
            return 0; // Ainda há barcos não afundados
        }
    }
    return 1; // Todos os barcos afundados, jogador venceu
}
