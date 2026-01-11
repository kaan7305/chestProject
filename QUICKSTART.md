# Quick Start Guide

Get started with the Chess Game in 5 minutes!

## Step 1: Compile the Game

```bash
make
```

Expected output:
```
g++ -c main.cpp -std=c++11 -Wall -Wextra -pedantic -g -O0
g++ -c Board.cpp -std=c++11 -Wall -Wextra -pedantic -g -O0
...
g++ -o chess main.o Board.o Game.o CreatePiece.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o
```

## Step 2: Run the Game

```bash
./chess
```

You'll see the initial chess board:
```
  ABCDEFGH
  --------
8|♜♞♝♛♚♝♞♜|8
7|♟♟♟♟♟♟♟♟|7
6| · · · · |6
5|· · · · ·|5
4| · · · · |4
3|· · · · ·|3
2|♙♙♙♙♙♙♙♙|2
1|♖♘♗♕♔♗♘♖|1
  --------
  ABCDEFGH

White's move.
Material point value: 39
Next command:
```

## Step 3: Make Your First Move

Type `M E2E4` and press Enter to move the white pawn from E2 to E4.

```
Next command: M E2E4
```

The board updates:
```
  ABCDEFGH
  --------
8|♜♞♝♛♚♝♞♜|8
7|♟♟♟♟♟♟♟♟|7
6| · · · · |6
5|· · · · ·|5
4| · · ♙ · |4
3|· · · · ·|3
2|♙♙♙♙ ♙♙♙|2
1|♖♘♗♕♔♗♘♖|1
  --------
  ABCDEFGH

Black's move.
```

## Step 4: Continue Playing

Make Black's move:
```
Next command: M E7E5
```

Continue alternating between White and Black until checkmate or stalemate!

## Step 5: Useful Commands

### Save Your Game
```
Next command: S my_game.txt
```

### Load a Saved Game
```
Next command: L my_game.txt
```

### Get Help
```
Next command: ?
```

### Quit
```
Next command: Q
```

## Example Game Session

Here's a complete game showing Scholar's Mate (4-move checkmate):

```bash
./chess

# White opens with king's pawn
Next command: M E2E4

# Black responds with king's pawn
Next command: M E7E5

# White develops bishop
Next command: M F1C4

# Black develops knight
Next command: M B8C6

# White brings out queen
Next command: M D1H5

# Black moves pawn
Next command: M G8F6

# White delivers checkmate!
Next command: M H5F7

Checkmate! Game over.
```

## Try Pre-Made Scenarios

Load interesting positions:

### Check Position
```bash
./chess
L check.txt
```

### Checkmate Position
```bash
./chess
L checkmate.txt
```

### Stalemate Position
```bash
./chess
L stalemate.txt
```

## Tips for Beginners

1. **Notation**: Columns are A-H (left to right), Rows are 1-8 (bottom to top)
2. **Piece Symbols**:
   - ♔/♚ = King
   - ♕/♛ = Queen
   - ♖/♜ = Rook
   - ♗/♝ = Bishop
   - ♘/♞ = Knight
   - ♙/♟ = Pawn
3. **White pieces** (bottom) are shown in outline
4. **Black pieces** (top) are shown filled
5. **Material value** helps you track who's ahead
6. **Check** means your king is under attack - you must escape!
7. **Checkmate** means you have no legal moves to escape check - game over!

## Common Mistakes

### Invalid Position
```
Next command: M E2E9
ERROR: end position is not on board
```
→ Rows only go from 1-8!

### Wrong Turn
```
Next command: M E7E5
ERROR: piece has wrong color
```
→ You can only move your own pieces!

### Illegal Move
```
Next command: M E2F4
ERROR: illegal move shape
```
→ Pawns can't move diagonally unless capturing!

### Path Blocked
```
Next command: M F1C4
ERROR: path is not clear
```
→ Must move the pawn first!

## Next Steps

Ready to learn more? Check out the full [README.md](README.md) for:
- Complete rules and game mechanics
- Code architecture and design patterns
- Testing and debugging
- Advanced features

## Quick Reference Card

| Command | Description | Example |
|---------|-------------|---------|
| `M <move>` | Make a move | `M E2E4` |
| `L <file>` | Load game | `L game.txt` |
| `S <file>` | Save game | `S save.txt` |
| `?` | Show help | `?` |
| `Q` | Quit | `Q` |

## Have Fun!

Now you're ready to play chess! Remember:
- Practice makes perfect
- Study the example games
- Try loading different scenarios
- Challenge your friends!

**Good luck and enjoy the game!** ♔♕♖♗♘♙
