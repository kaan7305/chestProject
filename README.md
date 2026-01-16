# Chess Game - C++ Implementation

A fully-featured command-line chess game implemented in C++ with support for standard chess rules, move validation, check/checkmate detection, game saving/loading, and beautiful Unicode piece rendering.

## Quick Preview

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
```

**Interactive Visualizations**: Open `visualizations.html` in your browser for a beautifully styled interactive guide with multiple game scenarios!

## Table of Contents
- [Quick Preview](#-quick-preview)
- [Visualizations](#visualizations)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Compilation](#compilation)
- [How to Run](#how-to-run)
- [Game Commands](#game-commands)
- [Game Rules](#game-rules)
- [Example Games](#example-games)
- [Code Architecture](#code-architecture)
- [Testing](#testing)
- [Contributors](#contributors)

## Visualizations

This project includes multiple ways to visualize the chess game:

### Text-Based Display (Works Everywhere)
The game outputs beautiful Unicode chess boards directly in the terminal. All examples in this README use Unicode symbols that render perfectly on GitHub and any Markdown viewer.

### Interactive HTML Visualization
Open `visualizations.html` in your browser for a rich, interactive experience featuring:
- Beautiful dark-themed design
- Multiple game scenarios (initial position, check, checkmate)
- Piece legend with move descriptions
- Interactive how-to-use guide
- Color-coded status indicators

**To view**: Simply double-click `visualizations.html` or run:
```bash
open visualizations.html
```

### Screenshot Examples
Text-based board displays are available in the `screenshots/` folder:
- `initial_board.txt` - Starting position
- `check_position.txt` - Check scenario
- `checkmate_position.txt` - Checkmate scenario

## Features

### Core Features
- **Standard Chess Rules**: Implements all standard chess piece movements and captures
- **Turn-Based Gameplay**: Alternating turns between white and black players
- **Move Validation**: Comprehensive validation of legal moves for each piece type
- **Path Checking**: Ensures pieces cannot jump over other pieces (except knights)
- **Check Detection**: Automatically detects when a king is in check
- **Checkmate Detection**: Identifies checkmate conditions to end the game
- **Stalemate Detection**: Recognizes stalemate situations
- **Material Point Values**: Tracks and displays material point values for each player

### Advanced Features
- **Save/Load Games**: Save current game state to a file and load previously saved games
- **Unicode Display**: Beautiful chess board rendering with Unicode chess piece symbols (♔♕♖♗♘♙)
- **Alternating Board Colors**: Checkerboard pattern with alternating black and white squares
- **Mystery Piece**: Special piece type with unique properties (M/m)
- **Position Validation**: Validates all board positions and move specifications
- **Exception Handling**: Robust error handling with meaningful error messages

### Piece Types
- **King (K/k)**: Moves one square in any direction
- **Queen (Q/q)**: Moves any number of squares horizontally, vertically, or diagonally
- **Rook (R/r)**: Moves any number of squares horizontally or vertically
- **Bishop (B/b)**: Moves any number of squares diagonally
- **Knight (N/n)**: Moves in an L-shape (2 squares in one direction, 1 in perpendicular)
- **Pawn (P/p)**: Moves forward one square (or two from starting position), captures diagonally
- **Mystery (M/m)**: Special piece with 20 point value

## Project Structure

```
├── main.cpp              # Main game loop and user interface
├── Game.h/cpp           # Game state management and high-level logic
├── Board.h/cpp          # Chess board representation and piece management
├── Piece.h              # Abstract base class for all chess pieces
├── King.h/cpp           # King piece implementation
├── Queen.h/cpp          # Queen piece implementation
├── Rook.h/cpp           # Rook piece implementation
├── Bishop.h/cpp         # Bishop piece implementation
├── Knight.h/cpp         # Knight piece implementation
├── Pawn.h/cpp           # Pawn piece implementation
├── Mystery.h            # Mystery piece implementation
├── CreatePiece.h/cpp    # Factory pattern for piece creation
├── Exceptions.h         # Custom exception classes
├── Terminal.h           # Terminal display utilities
├── Makefile             # Build configuration
└── *.txt                # Sample game files for testing
```

## Requirements

- **Compiler**: g++ with C++11 support
- **Operating System**: Unix-like systems (Linux, macOS)
- **Terminal**: Terminal with Unicode support for proper piece rendering

## Compilation

### Build the Project
```bash
make
```

This will compile all source files and create an executable named `chess`.

### Clean Build Files
```bash
make clean
```

This removes all object files and the executable.

### Compilation Flags
The project is compiled with the following flags:
- `-std=c++11`: C++11 standard
- `-Wall -Wextra -pedantic`: Comprehensive warnings
- `-g -O0`: Debug symbols, no optimization (for development)

## How to Run

### Start a New Game
```bash
./chess
```

### Load a Saved Game
```bash
./chess output.txt
```
The game state will be saved to `output.txt` when the game ends.

## Game Commands

The game supports the following interactive commands:

### `?` - Show Help
Displays the list of available commands.
```
Next command: ?
```

### `Q` - Quit Game
Exits the game. If a filename was provided as a command-line argument, the final game state will be saved.
```
Next command: Q
```

### `L <filename>` - Load Game
Loads a previously saved game from the specified file.
```
Next command: L game.txt
```

**Game File Format:**
```
rnbqkbnr
pppppppp
--------
--------
--------
--------
PPPPPPPP
RNBQKBNR
w
```
- First 8 lines: Board state (row 8 to row 1)
- Last line: Current turn ('w' for white, 'b' for black)
- '-' represents empty squares
- Upper case = White pieces, Lower case = Black pieces

### `S <filename>` - Save Game
Saves the current game state to the specified file.
```
Next command: S saved_game.txt
```

### `M <move>` - Make a Move
Attempts to make a move. The move is specified as a 4-character string:
- Characters 1-2: Starting position (column A-H, row 1-8)
- Characters 3-4: Ending position (column A-H, row 1-8)

```
Next command: M E2E4
```

**Examples:**
- `M E2E4` - Move piece from E2 to E4
- `M G1F3` - Move piece from G1 to F3
- `M A7A8` - Move piece from A7 to A8 (pawn promotion context)

## Game Rules

### Turn Order
- White moves first
- Players alternate turns
- After a successful move, turn switches to the other player

### Move Validation
The game validates moves based on:
1. **Piece Movement Rules**: Each piece type has specific movement patterns
2. **Path Clearance**: Most pieces cannot jump over other pieces (knights excepted)
3. **Turn Order**: Can only move pieces of your own color
4. **King Safety**: Cannot make a move that leaves your king in check
5. **Position Validity**: All positions must be on the board (A-H, 1-8)

### Special Conditions

#### Check
When a king is under direct threat of capture, the player is in check and must:
- Move the king to a safe square, or
- Block the attack with another piece, or
- Capture the attacking piece

#### Checkmate
When a player is in check and has no legal moves to escape, the game ends in checkmate.

#### Stalemate
When a player has no legal moves but is not in check, the game ends in stalemate.

### Material Point Values
- **Pawn**: 1 point
- **Knight**: 3 points
- **Bishop**: 3 points
- **Rook**: 5 points
- **Queen**: 9 points
- **King**: No point value (invaluable)
- **Mystery**: 20 points

## Example Games

### Initial Board Position
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
```

### Opening Moves - Italian Game
```bash
./chess
M E2E4    # White moves pawn to E4
M E7E5    # Black moves pawn to E5
M G1F3    # White develops knight to F3
M B8C6    # Black develops knight to C6
M F1C4    # White develops bishop to C4 (Italian Game)
```

**Board after these moves:**
```
  ABCDEFGH
  --------
8|♜ ♝♛♚♝♞♜|8
7|♟♟♟♟ ♟♟♟|7
6| ·♞· · · |6
5|· · · ♟· ·|5
4| ·♗· ♙ · |4
3|· · · · ♘·|3
2|♙♙♙♙ ♙♙♙|2
1|♖♘♗♕♔ ·♖|1
  --------
  ABCDEFGH

Black's move.
Material point value: 39
```

### Check Position
A position where Black is in check:
```
  ABCDEFGH
  --------
8|♜♞♝♛♚♝ ♜|8
7|♟♟♟♟ ♕♟♟|7
6| · · · · |6
5|·♗· ·♟· ·|5
4| · · ♞ · |4
3|· · · · ·|3
2|♙♙♙♙ ♙♙♙|2
1|♖♘♗ ♔ ♘♖|1
  --------
  ABCDEFGH

Black's move.
Material point value: 38
You are in check!
```

**To load this position:**
```bash
./chess
L check.txt
```

### Checkmate Position
A position resulting in checkmate:
```
  ABCDEFGH
  --------
8|♜♞♝♛♚♝ ♜|8
7|♟♟♟♟ ♕♟♟|7
6| · · · · |6
5|· · · ♟· ·|5
4| ·♗· ♞ · |4
3|· · · · ·|3
2|♙♙♙♙ ♙♙♙|2
1|♖♘♗ ♔ ♘♖|1
  --------
  ABCDEFGH

Black's move.
Material point value: 38
Checkmate! Game over.
```

**To load this position:**
```bash
./chess
L checkmate.txt
```

## Code Architecture

### Design Patterns

#### 1. Factory Pattern (CreatePiece)
The `create_piece()` function uses the Factory pattern to instantiate the correct piece type based on a designator character:
```cpp
Piece* create_piece(const char& piece_designator);
```

#### 2. Inheritance Hierarchy
All piece types inherit from the abstract `Piece` base class:
```
Piece (abstract base class)
├── King
├── Queen
├── Rook
├── Bishop
├── Knight
├── Pawn
└── Mystery
```

#### 3. Polymorphism
Virtual functions in the `Piece` class allow polymorphic behavior:
- `legal_move_shape()`: Piece-specific movement rules
- `legal_capture_shape()`: Piece-specific capture rules
- `to_ascii()`: ASCII representation
- `to_unicode()`: Unicode representation
- `point_value()`: Material point value

### Key Classes

#### Game Class (Game.h/cpp)
**Responsibilities:**
- Manages overall game state
- Tracks whose turn it is
- Validates and executes moves
- Detects check, checkmate, and stalemate
- Calculates material point values
- Handles game serialization (save/load)

**Key Methods:**
```cpp
Game();                                          // Initialize new game
void make_move(const Position& start, const Position& end);  // Execute move
bool in_check(const bool& white) const;         // Check detection
bool in_mate(const bool& white) const;          // Checkmate detection
bool in_stalemate(const bool& white) const;     // Stalemate detection
int point_value(const bool& white) const;       // Material calculation
```

#### Board Class (Board.h/cpp)
**Responsibilities:**
- Maintains the 8x8 chess board
- Manages piece positions using a sparse map
- Provides piece lookup by position
- Handles piece addition, removal, and movement
- Validates board positions
- Renders the board display

**Key Methods:**
```cpp
Board();                                         // Initialize empty board
const Piece* operator()(const Position& position) const;  // Get piece at position
void add_piece(const Position& pos, const char& designator);  // Add piece
void move_piece(const Position& from, const Position& to);    // Move piece
void display() const;                            // Render board
bool has_valid_kings() const;                    // Validate king count
```

**Data Structure:**
```cpp
std::map<Position, Piece*, PositionCompare> occ;  // Sparse map of occupied positions
```

#### Piece Class (Piece.h)
**Responsibilities:**
- Abstract base class for all piece types
- Defines interface for piece behavior
- Provides color information (white/black)
- Supports path clearance checking

**Pure Virtual Methods:**
```cpp
virtual bool legal_move_shape(const Position& start, const Position& end) const = 0;
virtual char to_ascii() const = 0;
virtual std::string to_unicode() const = 0;
virtual int point_value() const = 0;
```

### Position Type
Positions are represented as pairs of characters:
```cpp
typedef std::pair<char, char> Position;
```
- First char: Column ('A' through 'H')
- Second char: Row ('1' through '8')

Example: `Position('E', '4')` represents square E4

### Exception Handling
Custom exceptions are defined in `Exceptions.h`:
```cpp
class Exception {
    std::string message;
public:
    Exception(const std::string& msg) : message(msg) {}
    const std::string& what() const { return message; }
};
```

**Common exception messages:**
- "invalid designator" - Invalid piece character
- "invalid position" - Position not on board
- "position is occupied" - Square already has a piece
- "start position is not on board"
- "end position is not on board"
- "no piece at start position"
- "piece has wrong color"
- "illegal move shape"
- "path is not clear"
- "move exposes check"

## Testing

### Provided Test Files

The project includes several test scenarios:

1. **game.txt** - Standard game in progress
2. **check.txt** - Position where Black is in check
3. **checkmate.txt** - Checkmate position
4. **mate_in_two.txt** - Tactical puzzle (mate in 2 moves)
5. **stalemate.txt** - Stalemate position
6. **pre_promotion.txt** - Position before pawn promotion
7. **promotion_to_mate.txt** - Promotion leading to mate

### Running Tests

**Test loading a game:**
```bash
./chess < test_load_check.txt
```

**Test a sequence of moves:**
```bash
./chess < test_game_moves.txt
```

**Interactive testing:**
```bash
./chess
# Enter commands interactively
```

### Validation Tests

The code includes several validation mechanisms:

1. **Move Validation**: `Game::make_move()` validates all aspects of moves
2. **Board Validation**: `Board::has_valid_kings()` ensures valid game state
3. **Position Validation**: Checks all positions are within bounds
4. **Path Clearance**: Verifies pieces don't jump over others (except knights)
5. **Check Detection**: Prevents moves that leave king in check

### Creating Custom Test Files

Create your own test scenarios:

```bash
# Create a custom board position
cat > custom_game.txt << 'EOF'
r---k--r
pppppppp
--------
--------
--------
--------
PPPPPPPP
R---K--R
w
EOF

# Load and test
./chess
L custom_game.txt
```

## Implementation Highlights

### Check Detection Algorithm
The `in_check()` method:
1. Finds the king of the specified color
2. Gets all opponent pieces
3. Checks if any opponent piece can legally capture the king
4. Returns true if king is under attack

### Checkmate Detection Algorithm
The `in_mate()` method:
1. Verifies the king is in check
2. Iterates through all pieces of the player's color
3. For each piece, tries all possible moves
4. Creates a hypothetical board state for each move
5. Checks if the move resolves check
6. Returns true only if no move can escape check

### Stalemate Detection Algorithm
The `in_stalemate()` method:
1. Verifies the king is NOT in check
2. Iterates through all pieces of the player's color
3. For each piece, tries all possible moves
4. Checks if any legal move exists
5. Returns true if no legal moves available

### Path Clearance Algorithm
The `isPathClear()` method:
1. Determines the direction of movement
2. Iterates from start to end position
3. Checks each intermediate square
4. Returns false if any square is occupied
5. Does not check start/end squares (handled separately)

### Board Display
The `display()` method:
1. Prints column headers
2. Iterates from row 8 to row 1 (top to bottom)
3. Alternates background colors (checkerboard pattern)
4. Uses Unicode symbols for pieces
5. Prints row numbers on both sides

## Advanced Features

### Pawn Special Moves

#### Two-Square Initial Move
Pawns can move two squares forward from their starting position:
- White pawns: From row 2
- Black pawns: From row 7

#### Diagonal Capture
Pawns capture diagonally (different from normal movement).

### King Safety
The game prevents moves that would leave the king in check:
1. Hypothetically makes the move
2. Checks if king is in check in resulting position
3. Rejects move if king becomes exposed
4. Restores original board state

### Material Calculation
The `point_value()` method sums the point values of all pieces of a given color, providing tactical information to players.

## Memory Management

### Resource Management
- Uses smart pointers and proper destructors
- Board class manages piece lifetimes
- Copy constructor and assignment operator properly handle deep copying
- Destructor ensures all dynamically allocated pieces are deleted

### Copy Semantics
```cpp
Board(const Board& other);               // Deep copy constructor
Board& operator=(const Board& other);    // Deep copy assignment
```

## Building and Debugging

### Debug Build (default)
```bash
make
```
Includes debug symbols (`-g`) and no optimization (`-O0`).

### Running with GDB
```bash
gdb ./chess
(gdb) run
```

### Checking for Memory Leaks
```bash
valgrind --leak-check=full ./chess
```

## Future Enhancements

Potential improvements for future versions:

1. **En Passant**: Special pawn capture move
2. **Castling**: King and rook special move
3. **Pawn Promotion**: Promote pawns reaching the opposite end
4. **Move History**: Track and display move history
5. **Undo/Redo**: Ability to undo and redo moves
6. **AI Opponent**: Computer player with various difficulty levels
7. **Time Controls**: Chess clock functionality
8. **PGN Support**: Import/export games in standard notation
9. **Move Suggestions**: Hint system for beginners
10. **Network Play**: Multiplayer over network

## Troubleshooting

### Common Issues

**Issue**: Unicode symbols don't display correctly
**Solution**: Ensure your terminal supports Unicode (UTF-8 encoding)

**Issue**: Compilation errors with C++11 features
**Solution**: Verify g++ version supports C++11 (`g++ --version`)

**Issue**: "Failed to open" error when loading game
**Solution**: Check file path and permissions

**Issue**: Move rejected without clear reason
**Solution**: The move likely exposes your king to check

## Code Style

The codebase follows these conventions:
- **Naming**: PascalCase for classes, camelCase for methods/variables
- **Indentation**: Tabs/spaces consistent throughout
- **Comments**: Descriptive comments for complex logic
- **Headers**: Include guards in all header files
- **Namespace**: All chess-related code in `Chess` namespace

## Documentation

### Code Documentation
- Header files contain interface documentation
- Complex algorithms are documented inline
- Public methods have clear descriptions
- Pre/post-conditions specified where relevant

### Project Documentation
- This README provides comprehensive project overview
- Example files demonstrate usage
- Comments in code explain implementation details

## Contributors

This project was developed as a final project for a programming course, demonstrating:
- Object-oriented design principles
- C++ language features
- Data structure usage
- Algorithm implementation
- Software engineering best practices

## License

This is an educational project. Please refer to your institution's policies regarding code sharing and reuse.

## Acknowledgments

- Chess rules and conventions from FIDE (World Chess Federation)
- Unicode chess symbols from Unicode Standard
- Terminal display techniques from ANSI/VT100 standards

---

**Enjoy playing chess!** ♔♕♖♗♘♙

For questions or issues, please refer to the source code comments or contact the project maintainers.
