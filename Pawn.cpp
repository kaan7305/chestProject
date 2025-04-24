#include "Pawn.h"
#include "Board.h"
#include <cmath>

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    // How much the pawn moved
    int col_move = end.first  - start.first;
    int row_move = end.second - start.second;

    // If the pawn is white
    if (is_white()) {
      if (col_move != 0) {
        return false;
      }

      if (row_move == 1) {
        if (board->isOccupied(end)) {
          return false;
        }
        return true;
      }

      if (start.second == '2' && row_move == 2) {
        Position mid(start.first, start.second + 1);
        if (board->isOccupied(mid)) {
          return false;
        }
        if (board->isOccupied(end)) {
          return false;
        }
        return true;
      }
    return false;
    }

    // BLACK pawn moves “down” the board
    // same logic, but row_move is negative
    if (col_move != 0) {
      return false;
    }

    if (row_move == -1) {
      if (board->isOccupied(end)) return false;
      return true;
    }

    if (start.second == '7' && row_move == -2) {
      Position mid(start.first, start.second - 1);
      if (board->isOccupied(mid)) return false;
      if (board->isOccupied(end)) return false;
      return true;
    }

    return false;
  }
    
  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    int col_move = end.first  - start.first;
    int row_move = end.second - start.second;

    // must be one diagonal step
    if (! (std::abs(col_move) == 1 && ((is_white() && row_move == 1) || (!is_white() && row_move == -1)) ) ){
      return false;
    }

    // target square must be occupied by an enemy
    if (! board->isOccupied(end)) {
      return false;
    }
    const Piece* target = board->operator()(end);
    if (target->is_white() == this->is_white()) {
      return false;
    }
    return true;
  }
}

