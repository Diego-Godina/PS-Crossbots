#include <stdio.h>

#define PLAYER 'X'
#define BOT 'O'
#define EMPTY ' '

char board[3][3];

// preenche o tabuleiro
void initBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Exibe o tabuleiro
void printBoard() {
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);

        if (i < 2) {
            printf("---+---+---\n");
        }
    }

    printf("\n");
}

// Verifica se há vitória
char checkWinner() {
    // Verifica nas linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }

        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    // Verifica nas diagonais
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }

    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return EMPTY;
}

// Verifica se ainda há jogadas possíveis
int isMovesLeft() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return 1;
            }
        }
    }

    return 0;
}

// Função de avaliação
int evaluate() {
    char winner = checkWinner();

    if (winner == BOT) {
        return +10;
    } else if (winner == PLAYER) {
        return -10;
    }

    return 0;
}

// Algoritmo minimax
int minimax(int depth, int isMax) {
    int score = evaluate();

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;

    // Bot
    if (isMax) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = BOT;
                    int val = minimax(depth + 1, 0);

                    if (val > best) {
                        best = val;
                    }

                    board[i][j] = EMPTY;
                }
            }
        }

        return best;
    } else {
        // Jogador
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int val = minimax(depth + 1, 1);

                    if (val < best) {
                        best = val;
                    }

                    board[i][j] = EMPTY;
                }
            }
        }

        return best;
    }
}

// Melhor jogada para o bot
void botMove() {
    int bestVal = -1000;
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = BOT;
                int moveVal = minimax(0, 0);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestRow][bestCol] = BOT;
    printf("Bot marcou (%d, %d)\n", bestRow + 1, bestCol + 1);
}

// Jogada do player 1
void playerMove() {
    int row;
    int col;

    while (1) {
        printf("Digite sua jogada (linha e coluna de 1 a 3): ");
        scanf("%d %d", &row, &col);
        row--;
        col--;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY) {
            board[row][col] = PLAYER;
            printf("Jogador 1 marcou (%d, %d): ", row, col);
            break;
        } else {
            printf("Posição inválida, tente novamente.\n");
        }
    }
}

// Função main
int main() {
    initBoard();

    while (1) {
        playerMove();
        printBoard();

        if (checkWinner() == PLAYER) {
            printf("Você venceu!\n");
            break;
        }

        if (!isMovesLeft()) {
            printf("Empate!\n");
            break;
        }

        botMove();
        printBoard();

        if (checkWinner() == BOT) {
            printf("O bot venceu!\n");
            break;
        }

        if (!isMovesLeft()) {
            printf("Empate!\n");
            break;
        }
    }

    return 0;
}
