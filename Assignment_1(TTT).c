#include <stdio.h>

char board[3][3];
char player = 'X';

void initializeBoard() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
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

int isValidMove(int pos) {
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    return board[row][col] != 'X' && board[row][col] != 'O';
}

void makeMove(int pos) {
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    board[row][col] = player;
}

int checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}

void switchPlayer() {
    player = (player == 'X') ? 'O' : 'X';
}

int main() {
    int move, totalMoves = 0;
    initializeBoard();

    while (1) {
        displayBoard();
        printf("Player %c, enter your move (1-9): ", player);
        scanf("%d", &move);

        if (move < 1 || move > 9 || !isValidMove(move)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        makeMove(move);
        totalMoves++;

        if (checkWinner()) {
            displayBoard();
            printf("Player %c wins!\n", player);
            break;
        }

        if (totalMoves == 9) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        switchPlayer();
    }

    return 0;
}
