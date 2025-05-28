#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>  

void inicializarTabuleiro(char tabuleiro[3][3]);
void exibirTabuleiro(char tabuleiro[3][3]);
int verificarJogada(char tabuleiro[3][3], char linhaChar, int coluna);
void aplicarJogada(char tabuleiro[3][3], char linhaChar, int coluna, char marca);
int verificarVitoria(char tabuleiro[3][3], char marca);
int verificarEmpate(char tabuleiro[3][3]);
void limparTela(); 
int main() {
    char tabuleiro[3][3];
    int jogadorAtual = 1; 
    char marcaAtual;
    char linhaChar;
    int coluna;
    int jogadas = 0;
    int jogoAtivo = 1;

    inicializarTabuleiro(tabuleiro);

    while (jogoAtivo) {
        limparTela();
        exibirTabuleiro(tabuleiro);

        // Define a marca do jogador atual
        marcaAtual = (jogadorAtual == 1) ? 'X' : 'O';
        printf("Jogador %d (%c), informe sua jogada (ex: B3): ", jogadorAtual, marcaAtual);
        
        // Loop para ler a jogada e validar
        while (1) {
            char input[5]; // Para ler a linha (char) e a coluna (int)
            scanf("%s", input);
            
            // Extrai a linha (primeiro char) e a coluna (segundo char convertido para int)
            linhaChar = toupper(input[0]); // Converte para maiúscula
            coluna = atoi(&input[1]); // Converte o restante para int

            // Verifica se a entrada do usuário é minimamente válida (ex: A1, B2)
            if ((linhaChar >= 'A' && linhaChar <= 'C') && (coluna >= 1 && coluna <= 3)) {
                if (verificarJogada(tabuleiro, linhaChar, coluna)) {
                    break; // Jogada válida, sai do loop de leitura
                } else {
                    printf("Posicao ja ocupada ou invalida. Tente novamente (ex: A1): ");
                }
            } else {
                printf("Entrada invalida. Formato esperado (ex: B3): ");
            }
        }
        
        aplicarJogada(tabuleiro, linhaChar, coluna, marcaAtual);
        jogadas++;

        if (verificarVitoria(tabuleiro, marcaAtual)) {
            limparTela();
            exibirTabuleiro(tabuleiro);
            printf("Fim de jogo! Jogador %d (%c) venceu!\n", jogadorAtual, marcaAtual);
            jogoAtivo = 0;
        } else if (verificarEmpate(tabuleiro)) {
            limparTela();
            exibirTabuleiro(tabuleiro);
            printf("Fim de jogo! Empate!\n");
            jogoAtivo = 0;
        } else {
            // Troca de jogador
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        }
    }

    return 0;
}

// Inicializa o tabuleiro com espaços vazios
void inicializarTabuleiro(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Exibe o tabuleiro no console
void exibirTabuleiro(char tabuleiro[3][3]) {
    printf("  1   2   3\n");
    printf("A %c | %c | %c\n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("  --+---+--\n");
    printf("B %c | %c | %c\n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("  --+---+--\n");
    printf("C %c | %c | %c\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
    printf("\n");
}

// Verifica se a jogada é válida (posição vazia)
int verificarJogada(char tabuleiro[3][3], char linhaChar, int coluna) {
    int linha = linhaChar - 'A'; // Converte 'A'->0, 'B'->1, 'C'->2
    int col = coluna - 1;       // Converte 1->0, 2->1, 3->2

    // Verifica se está dentro dos limites e se a célula está vazia
    if (linha >= 0 && linha < 3 && col >= 0 && col < 3 && tabuleiro[linha][col] == ' ') {
        return 1; // Jogada válida
    }
    return 0; // Jogada inválida
}

// Aplica a jogada no tabuleiro
void aplicarJogada(char tabuleiro[3][3], char linhaChar, int coluna, char marca) {
    int linha = linhaChar - 'A';
    int col = coluna - 1;
    tabuleiro[linha][col] = marca;
}

// Verifica se há um vencedor
int verificarVitoria(char tabuleiro[3][3], char marca) {
    // Verificar linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == marca && tabuleiro[i][1] == marca && tabuleiro[i][2] == marca) return 1;
    }
    // Verificar colunas
    for (int j = 0; j < 3; j++) {
        if (tabuleiro[0][j] == marca && tabuleiro[1][j] == marca && tabuleiro[2][j] == marca) return 1;
    }
    // Verificar diagonais
    if (tabuleiro[0][0] == marca && tabuleiro[1][1] == marca && tabuleiro[2][2] == marca) return 1;
    if (tabuleiro[0][2] == marca && tabuleiro[1][1] == marca && tabuleiro[2][0] == marca) return 1;

    return 0; // Nenhuma vitória
}

// Verifica se houve empate (tabuleiro cheio e sem vencedor)
int verificarEmpate(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0; // Ainda há espaços vazios, não é empate
            }
        }
    }
    return 1; // Tabuleiro cheio, é empate
}

// Função para limpar a tela do console (depende do SO)
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Para Windows
    #else
        system("clear"); // Para sistemas Unix-like (Linux, macOS)
    #endif
}
