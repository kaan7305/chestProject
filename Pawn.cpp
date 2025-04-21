#include "Pawn.h"
#include <cmath>

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    // How much the pawn moved
    int col_move = end.first - start.first;
    int row_move = end.second - start.second;

    // If the pawn is white
    if (is_white()) {
      // Must stay in the same column
      if (col_move != 0) {
        return false;
      }

      // If the pawn is on the starting row. If not, can only move 1 square
      if (start.second == '2') {
        return row_move == 1 || row_move == 2;
      } else {
        return row_move == 1;
      }
    }
    // If the pawn is black
    else {
      if (col_move != 0) {
        return false;
      }
      if (start.second == '7') {
        return row_move == -1 || row_move == -2;
      } else {
          return row_move == -1;
      }
    }
  }
    
  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    int col_move = end.first - start.first;
    int row_move = end.second - start.second;

    // If the pawn is white
    if (is_white()) {
      // Must move diagonally
      return row_move == 1 && (col_move == 1 || col_move == -1);
    } else {
      return row_move == -1 && (col_move == 1 || col_move == -1);
    }
  }
}

