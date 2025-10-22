# Awale Game

A terminal-based implementation of the traditional African strategy game Awale (also known as Oware, Wari, or Mancala) written in pure C.

## Game Rules

1. **Setup**: The board has 12 pits (6 per player), each starting with 4 seeds
2. **Turns**: Players alternate turns, selecting a pit on their side
3. **Sowing**: Seeds from the selected pit are sown counter-clockwise, one per pit
4. **Empty Start**: The starting pit is left empty (seeds go to following pits)
5. **Capturing**: After sowing, if the last seed lands in an opponent's pit and that pit now has 2 or 3 seeds, those seeds are captured
6. **Chain Capturing**: Continue capturing backwards if previous opponent pits also have 2 or 3 seeds
7. **Feeding Rule**: If your opponent has no seeds, you must give them seeds if possible
8. **Protection**: You cannot capture all of your opponent's seeds
9. **Winning**: Game ends when one player captures 25+ seeds or no more moves are possible
10. **Victory**: Player with the most seeds wins

## How to Compile

```bash
make
```

Or manually:
```bash
gcc -Wall -Wextra -std=c99 -o awale awale.c
```

## How to Play

```bash
make run
```

Or:
```bash
./awale
```

## Game Instructions

- The board shows pits numbered 0-5 for Player 1 (bottom) and 6-11 for Player 2 (top)
- On your turn, enter the number of the pit you want to select
- Seeds will be distributed counter-clockwise
- Watch for capturing opportunities!
- Type 'q' at any time to quit

## Example Gameplay

```
=====================================
         AWALE GAME BOARD
=====================================

Player 2 [Score:  0]           <-- Direction
     [ 4][ 4][ 4][ 4][ 4][ 4]
Pit:  11  10   9   8   7   6 
     ----------------------------------------
Pit:   0   1   2   3   4   5 
     [ 4][ 4][ 4][ 4][ 4][ 4]
Direction -->           Player 1 [Score:  0]

=====================================
Current turn: Player 1
=====================================

Player 1, choose a pit (or 'q' to quit): 
```

## Features

- ✅ Pure C implementation
- ✅ Structured with clear data structures and functions
- ✅ Comprehensive rule comments
- ✅ ASCII art board representation
- ✅ Input validation
- ✅ Two-player hot-seat gameplay
- ✅ Automatic win detection
- ✅ Feeding rule enforcement

## Structure

The implementation uses:
- **Board structure**: Stores the game state (pits, scores, current player)
- **Functions**: Modular functions for initialization, display, validation, and game logic
- **Clear comments**: Detailed rule explanations throughout the code

Enjoy playing Awale!