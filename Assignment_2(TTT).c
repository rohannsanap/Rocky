#include <stdio.h>

char board[3][3];
char human = 'X';
char computer = 'O';

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '1' + i * 3 + j;
        }
    }
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n-----------\n");
    }
    printf("\n");
}

int checkWinner(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return 0;
        }
    }
    return 1;
}

int minimax(char currentPlayer, int depth) {
    if (checkWinner(computer)) return 10 - depth;
    if (checkWinner(human)) return depth - 10;
    if (isBoardFull()) return 0;

    int bestScore = (currentPlayer == computer) ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = currentPlayer;

                int score = minimax((currentPlayer == computer) ? human : computer, depth + 1);

                board[i][j] = temp;
                bestScore = (currentPlayer == computer) ? (score > bestScore ? score : bestScore) : (score < bestScore ? score : bestScore);
            }
        }
    }

    return bestScore;
}

void bestMove() {
    int bestScore = -1000;
    int moveRow, moveCol;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = computer;

                int score = minimax(human, 0);

                board[i][j] = temp;
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }
    board[moveRow][moveCol] = computer;
}

int main() {
    int move;
    initializeBoard();

    while (1) {
        displayBoard();

        printf("Enter your move (1-9): ");
        scanf("%d", &move);
        if (move < 1 || move > 9 || board[(move - 1) / 3][(move - 1) % 3] == 'X' || board[(move - 1) / 3][(move - 1) % 3] == 'O') {
            printf("Invalid move! Try again.\n");
            continue;
        }
        board[(move - 1) / 3][(move - 1) % 3] = human;

        if (checkWinner(human)) {
            displayBoard();
            printf("You win!\n");
            break;
        }
        if (isBoardFull()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        bestMove();
        if (checkWinner(computer)) {
            displayBoard();
            printf("Computer wins!\n");
            break;
        }
        if (isBoardFull()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}
