#include "Rook.h"
#include "Board.h"

namespace Chess
{
    // Checks if the rook's move from 'start' to 'end' is a legal non-capturing move
    // Returns true if the move is legal, false otherwise
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    // How much the pawn moved
    int col_move = end.first  - start.first;
    int row_move = end.second - start.second;

    // Rook cannot move horizontally or vertically when not capturing
    if (col_move != 0 && row_move != 0) {
      return false;
    }

    // Determines direction of movement
    int dx = 0, dy = 0;
    if (col_move > 0)      dx =  1;
    else if (col_move < 0) dx = -1;
    else if (row_move > 0) dy =  1;
    else if (row_move < 0) dy = -1;

    // Checks if there are blocking pieces in the path
    char x = start.first + dx;
    char y = start.second + dy;
    while (x != end.first || y != end.second) {
      if (board->isOccupied(Position(x, y))) {
        return false;  // blocked in the path
      }
      x += dx;
      y += dy;
    }

    // If the end position is occupied, checks if it's an enemy piece
    if (board->isOccupied(end)) {
      const Piece* target = board->operator()(end);
      return target && (target->is_white() != this->is_white());
    }

    return true;
  }

  // Number of points rook is worth
  int Rook::point_value() const {
    return 5;
  }
}
