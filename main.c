#include <stdlib.h>
#include <stdio.h>

unsigned int SetBit(unsigned int value, int position);
unsigned int ClearBit(unsigned int value, int position);
unsigned int FlipBit(unsigned int value, int position);
int BitVal(unsigned int value, int position);
int CountBits(unsigned int value);
unsigned int ShiftLeft(unsigned int value, int positions);
unsigned int ShiftRight(unsigned int value, int positions);
void PrintBinary(unsigned int value);
void PrintHex(unsigned int value);

typedef struct {
    unsigned int player1_pieces;
    unsigned int player1_kings;
    unsigned int player2_pieces;
    unsigned int player2_kings;
    int current_turn;
} GameState;

void PrintBoard(GameState *game) {
    int bit_index = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 1) {
                printf("  ");
                continue;
            }

            if (BitVal(game->player1_kings, bit_index)) printf("R ");
            else if (BitVal(game->player1_pieces, bit_index)) printf("r ");
            else if (BitVal(game->player2_kings, bit_index)) printf("B ");
            else if (BitVal(game->player2_pieces, bit_index)) printf("b ");
            else printf(". ");

            bit_index++;
        }
        printf("\n");
    }
}

int RowColToBitIndex(int row, int col) {
    if ((row + col) % 2 == 0) return -1;
    return (row * 4) + (col / 2);
}

void MovePiece(GameState *game, int from_row, int from_col, int to_row, int to_col) {
    int from = RowColToBitIndex(from_row, from_col);
    int to = RowColToBitIndex(to_row, to_col);

    if (from == -1 || to == -1) {
        printf("Invalid square!\n");
        return;
    }

    int row_diff = to_row - from_row;
    int col_diff = to_col - from_col;

    // Check if destination is empty
    if (BitVal(game->player1_pieces | game->player2_pieces, to)) {
        printf("That square is already occupied!\n");
        return;
    }

    if (game->current_turn == 1) {
        if (!BitVal(game->player1_pieces, from)) {
            printf("No player 1 piece there!\n");
            return;
        }

        // Capture
        if (abs(row_diff) == 2 && abs(col_diff) == 2) {
            int middle_row = (from_row + to_row) / 2;
            int middle_col = (from_col + to_col) / 2;
            int middle = RowColToBitIndex(middle_row, middle_col);
            if (BitVal(game->player2_pieces, middle)) {
                game->player2_pieces = FlipBit(game->player2_pieces, middle);
                game->player2_kings  = FlipBit(game->player2_kings, middle);
            } else {
                printf("No opponent piece to capture!\n");
                return;
            }
        }

        game->player1_pieces = FlipBit(game->player1_pieces, from);
        game->player1_pieces = SetBit(game->player1_pieces, to);

        if (to_row == 7) {
            game->player1_kings = SetBit(game->player1_kings, to);
        }
    } else {
        if (!BitVal(game->player2_pieces, from)) {
            printf("No player 2 piece there!\n");
            return;
        }


        if (abs(row_diff) == 2 && abs(col_diff) == 2) {
            int middle_row = (from_row + to_row) / 2;
            int middle_col = (from_col + to_col) / 2;
            int middle = RowColToBitIndex(middle_row, middle_col);
            if (BitVal(game->player1_pieces, middle)) {
                game->player1_pieces = FlipBit(game->player1_pieces, middle);
                game->player1_kings  = FlipBit(game->player1_kings, middle);
            } else {
                printf("No opponent piece to capture!\n");
                return;
            }
        }

        game->player2_pieces = FlipBit(game->player2_pieces, from);
        game->player2_pieces = SetBit(game->player2_pieces, to);

        if (to_row == 0) {
            game->player2_kings = SetBit(game->player2_kings, to);
        }
    }

    game->current_turn = (game->current_turn == 1) ? 2 : 1;
}

int main(void) {
    GameState game;

    game.player1_pieces = 0;
    game.player1_kings = 0;
    game.player2_pieces = 0;
    game.player2_kings = 0;
    game.current_turn = 1;

    for (int i = 0; i <= 11; i++) game.player1_pieces = SetBit(game.player1_pieces, i);
    for (int i = 20; i <= 31; i++) game.player2_pieces = SetBit(game.player2_pieces, i);

    int from_row, from_col, to_row, to_col;

    while (1) {
        PrintBoard(&game);
        printf("\nPlayer %d, enter move (Example:2 3 2 1) : " , game.current_turn);
        if (scanf("%d %d %d %d", &from_row, &from_col, &to_row, &to_col) != 4) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        MovePiece(&game, from_row, from_col, to_row, to_col);


        if (CountBits(game.player1_pieces) == 0) {
            PrintBoard(&game);
            printf("Player 2 wins!\n");
            break;
        }
        if (CountBits(game.player2_pieces) == 0) {
            PrintBoard(&game);
            printf("Player 1 wins!\n");
            break;
        }
    }

    return 0;
}
