#include "Rook.h"
#include "Board.h"

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    int col_move = end.first  - start.first;
    int row_move = end.second - start.second;
    if (col_move != 0 && row_move != 0) {
      return false;  // diagonal or no movement - illegal
    }

    int dx = 0, dy = 0;
    if (col_move > 0)      dx =  1;
    else if (col_move < 0) dx = -1;
    else if (row_move > 0) dy =  1;
    else if (row_move < 0) dy = -1;

    char x = start.first + dx;
    char y = start.second + dy;
    while (x != end.first || y != end.second) {
      if (board->isOccupied(Position(x, y))) {
        return false;  // blocked in the path
      }
      x += dx;
      y += dy;
    }

    if (board->isOccupied(end)) {
      const Piece* target = board->operator()(end);
      return target && (target->is_white() != this->is_white());
    }

    return true;
  }
}
