#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * AWALE GAME (also known as Oware, Wari, or Mancala)
 * 
 * RULES:
 * 1. The board has 12 pits (6 per player) and each pit starts with 4 seeds
 * 2. Players alternate turns, selecting a pit on their side
 * 3. Seeds from the selected pit are sown counter-clockwise, one per pit
 * 4. The starting pit is left empty (seeds are distributed to following pits)
 * 5. CAPTURING: After sowing, if the last seed lands in an opponent's pit
 *    and that pit now has 2 or 3 seeds, those seeds are captured
 * 6. Continue capturing backwards if previous pits also have 2 or 3 seeds
 * 7. You cannot capture all opponent's seeds (must leave them with a move)
 * 8. If opponent has no seeds, you must give them seeds if possible
 * 9. Game ends when one player captures 25+ seeds or no more moves possible
 * 10. Player with most seeds wins
 */

#define PITS_PER_PLAYER 6
#define TOTAL_PITS 12
#define INITIAL_SEEDS 4
#define WINNING_SEEDS 25

// Structure to represent the game board
typedef struct {
    int pits[TOTAL_PITS];  // Pits 0-5: Player 1, Pits 6-11: Player 2
    int score[2];          // Captured seeds for each player
    int current_player;    // 0 for Player 1, 1 for Player 2
} Board;

// Function prototypes
void init_board(Board *board);
void display_board(const Board *board);
bool is_valid_move(const Board *board, int pit);
bool opponent_has_seeds(const Board *board, int player);
bool move_gives_seeds_to_opponent(const Board *board, int pit);
void make_move(Board *board, int pit);
bool is_game_over(const Board *board);
void display_winner(const Board *board);
int get_player_input(const Board *board);

// Initialize the board with starting position
void init_board(Board *board) {
    // Each pit starts with 4 seeds
    for (int i = 0; i < TOTAL_PITS; i++) {
        board->pits[i] = INITIAL_SEEDS;
    }
    // No seeds captured yet
    board->score[0] = 0;
    board->score[1] = 0;
    // Player 1 starts
    board->current_player = 0;
}

// Display the board in ASCII art
void display_board(const Board *board) {
    printf("\n");
    printf("=====================================\n");
    printf("         AWALE GAME BOARD\n");
    printf("=====================================\n");
    printf("\n");
    
    // Player 2's side (top, reversed for visual clarity)
    printf("Player 2 [Score: %2d]           <-- Direction\n", board->score[1]);
    printf("     ");
    for (int i = TOTAL_PITS - 1; i >= PITS_PER_PLAYER; i--) {
        printf("[%2d]", board->pits[i]);
    }
    printf("\n");
    
    // Pit numbers for Player 2
    printf("Pit:  ");
    for (int i = TOTAL_PITS - 1; i >= PITS_PER_PLAYER; i--) {
        printf(" %2d ", i);
    }
    printf("\n");
    
    printf("     ----------------------------------------\n");
    
    // Pit numbers for Player 1
    printf("Pit:  ");
    for (int i = 0; i < PITS_PER_PLAYER; i++) {
        printf(" %2d ", i);
    }
    printf("\n");
    
    // Player 1's side (bottom)
    printf("     ");
    for (int i = 0; i < PITS_PER_PLAYER; i++) {
        printf("[%2d]", board->pits[i]);
    }
    printf("\n");
    printf("Direction -->           Player 1 [Score: %2d]\n", board->score[0]);
    
    printf("\n");
    printf("=====================================\n");
    printf("Current turn: Player %d\n", board->current_player + 1);
    printf("=====================================\n\n");
}

// Check if a move is valid
bool is_valid_move(const Board *board, int pit) {
    // Check if pit is in valid range
    if (pit < 0 || pit >= TOTAL_PITS) {
        printf("Invalid pit number!\n");
        return false;
    }
    
    // Check if pit belongs to current player
    int player = board->current_player;
    int start_pit = player * PITS_PER_PLAYER;
    int end_pit = start_pit + PITS_PER_PLAYER;
    
    if (pit < start_pit || pit >= end_pit) {
        printf("You can only choose pits on your side!\n");
        return false;
    }
    
    // Check if pit has seeds
    if (board->pits[pit] == 0) {
        printf("This pit is empty!\n");
        return false;
    }
    
    // Check if opponent has seeds
    if (!opponent_has_seeds(board, player)) {
        // Must give seeds to opponent if possible
        if (!move_gives_seeds_to_opponent(board, pit)) {
            printf("You must give seeds to your opponent!\n");
            return false;
        }
    }
    
    return true;
}

// Check if opponent has any seeds
bool opponent_has_seeds(const Board *board, int player) {
    int opponent = 1 - player;
    int start_pit = opponent * PITS_PER_PLAYER;
    int end_pit = start_pit + PITS_PER_PLAYER;
    
    for (int i = start_pit; i < end_pit; i++) {
        if (board->pits[i] > 0) {
            return true;
        }
    }
    return false;
}

// Check if a move would give seeds to opponent
bool move_gives_seeds_to_opponent(const Board *board, int pit) {
    int seeds = board->pits[pit];
    int opponent = 1 - board->current_player;
    int opp_start = opponent * PITS_PER_PLAYER;
    int opp_end = opp_start + PITS_PER_PLAYER;
    
    // Simulate sowing
    int current_pit = pit;
    for (int i = 0; i < seeds; i++) {
        current_pit = (current_pit + 1) % TOTAL_PITS;
        // Check if we land in opponent's territory
        if (current_pit >= opp_start && current_pit < opp_end) {
            return true;
        }
    }
    return false;
}

// Make a move and handle capturing
void make_move(Board *board, int pit) {
    int seeds = board->pits[pit];
    board->pits[pit] = 0;  // Empty the selected pit
    
    int current_pit = pit;
    
    // Sow seeds counter-clockwise
    for (int i = 0; i < seeds; i++) {
        current_pit = (current_pit + 1) % TOTAL_PITS;
        board->pits[current_pit]++;
    }
    
    // Check for capturing
    int player = board->current_player;
    int opponent = 1 - player;
    int opp_start = opponent * PITS_PER_PLAYER;
    int opp_end = opp_start + PITS_PER_PLAYER;
    
    // Only capture if last seed landed in opponent's territory
    if (current_pit >= opp_start && current_pit < opp_end) {
        // Capture backwards while conditions are met
        int capture_pit = current_pit;
        int captured_total = 0;
        
        // First, count how many seeds would be captured
        int temp_pit = capture_pit;
        while (temp_pit >= opp_start && temp_pit < opp_end &&
               (board->pits[temp_pit] == 2 || board->pits[temp_pit] == 3)) {
            captured_total += board->pits[temp_pit];
            temp_pit--;
        }
        
        // Check if capturing would leave opponent with no seeds
        int opponent_remaining = 0;
        for (int i = opp_start; i < opp_end; i++) {
            opponent_remaining += board->pits[i];
        }
        
        // Only capture if opponent would still have seeds left
        if (opponent_remaining - captured_total > 0) {
            while (capture_pit >= opp_start && capture_pit < opp_end &&
                   (board->pits[capture_pit] == 2 || board->pits[capture_pit] == 3)) {
                board->score[player] += board->pits[capture_pit];
                printf("Player %d captures %d seeds from pit %d!\n", 
                       player + 1, board->pits[capture_pit], capture_pit);
                board->pits[capture_pit] = 0;
                capture_pit--;
            }
        }
    }
    
    // Switch player
    board->current_player = opponent;
}

// Check if game is over
bool is_game_over(const Board *board) {
    // Someone has won by capturing 25+ seeds
    if (board->score[0] >= WINNING_SEEDS || board->score[1] >= WINNING_SEEDS) {
        return true;
    }
    
    // Check if current player has any valid moves
    int player = board->current_player;
    int start_pit = player * PITS_PER_PLAYER;
    int end_pit = start_pit + PITS_PER_PLAYER;
    
    bool has_seeds = false;
    for (int i = start_pit; i < end_pit; i++) {
        if (board->pits[i] > 0) {
            has_seeds = true;
            break;
        }
    }
    
    if (!has_seeds) {
        return true;
    }
    
    // Check if opponent has seeds
    if (!opponent_has_seeds(board, player)) {
        // Check if current player can give seeds
        bool can_give_seeds = false;
        for (int i = start_pit; i < end_pit; i++) {
            if (board->pits[i] > 0 && move_gives_seeds_to_opponent(board, i)) {
                can_give_seeds = true;
                break;
            }
        }
        if (!can_give_seeds) {
            return true;
        }
    }
    
    return false;
}

// Display the winner
void display_winner(const Board *board) {
    printf("\n");
    printf("=====================================\n");
    printf("           GAME OVER!\n");
    printf("=====================================\n");
    printf("Player 1 Score: %d\n", board->score[0]);
    printf("Player 2 Score: %d\n", board->score[1]);
    
    if (board->score[0] > board->score[1]) {
        printf("\n🎉 Player 1 WINS! 🎉\n");
    } else if (board->score[1] > board->score[0]) {
        printf("\n🎉 Player 2 WINS! 🎉\n");
    } else {
        printf("\n🤝 It's a TIE! 🤝\n");
    }
    printf("=====================================\n\n");
}

// Get valid input from player
int get_player_input(const Board *board) {
    int pit;
    char input[100];
    
    while (true) {
        printf("Player %d, choose a pit (or 'q' to quit): ", board->current_player + 1);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }
        
        // Check for quit
        if (input[0] == 'q' || input[0] == 'Q') {
            printf("Thanks for playing!\n");
            exit(0);
        }
        
        // Try to parse as integer
        if (sscanf(input, "%d", &pit) != 1) {
            printf("Please enter a valid pit number!\n");
            continue;
        }
        
        // Validate the move
        if (is_valid_move(board, pit)) {
            return pit;
        }
    }
}

// Main game loop
int main() {
    Board board;
    init_board(&board);
    
    printf("\n");
    printf("╔═══════════════════════════════════╗\n");
    printf("║     WELCOME TO AWALE GAME!       ║\n");
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
