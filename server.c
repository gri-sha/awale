#include <stdio.h>
#include "awale.h"


// Main game loop
int main() {
    Board board;
    init_board(&board);
    
    printf("\n");
    printf("╔═══════════════════════════════════╗\n");
    printf("║     WELCOME TO AWALE GAME!        ║\n");
    printf("╚═══════════════════════════════════╝\n");
    printf("\n");
    printf("Awale is a traditional African strategy game.\n");
    printf("Capture more seeds than your opponent to win!\n");
    printf("\n");
    
    // Main game loop
    while (!is_game_over(&board)) {
        display_board(&board);
        int pit = get_player_input(&board);
        make_move(&board, pit);
        printf("\n");
    }
    
    // Game is over
    display_board(&board);
    display_winner(&board);
    
    return 0;
}