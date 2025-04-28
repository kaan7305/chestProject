#include "Pawn.h"
#include "Board.h"
#include <cmath>

namespace Chess
{
    // Checks if the pawn's move from 'start' to 'end' is a legal non-capturing move
    // Returns true if the move is legal, false otherwise
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    // How much the pawn moved
    int col_move = end.first  - start.first;
    int row_move = end.second - start.second;

    // If the pawn is white
    if (is_white()) {
      // Pawn cannot move horizontally when not capturing
      if (col_move != 0) {
        return false;
      }

      // Moves white pawn forward if not occupied
      if (row_move == 1) {
        if (board->isOccupied(end)) {
          return false;
        }
        return true;
      }

      // Moves white pawn forward if on starting row and not occupied
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

    // If the pawn is black
    else {
      // Pawn cannot move horizontally when not capturing
      if (col_move != 0) {
        return false;
      }

      // Moves black pawn forward if not occupied
      if (row_move == -1) {
        if (board->isOccupied(end)) return false;
        return true;
      }

      // Moves black pawn forward if on starting row and not occupied
      if (start.second == '7' && row_move == -2) {
        Position mid(start.first, start.second - 1);
        if (board->isOccupied(mid)) return false;
        if (board->isOccupied(end)) return false;
        return true;
      }
    }

    return false;
   
  }


  

  // Checks if the pawn's move from 'start' to 'end' is a legal capturing move
  // Returns true if the move is legal, false otherwise
  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
    // How much the pawn moved
    int col_move = end.first  - start.first;
    int row_move = end.second - start.second;

    // Capture is only sequare diagonally forward
    if (! (std::abs(col_move) == 1 && ((is_white() && row_move == 1) || (!is_white() && row_move == -1)) ) ){
      return false;
    }

    // If the target square is occipied
    if (! board->isOccupied(end)) {
      return false;
    }

    // If the piece on the target square is the opposite color
    const Piece* target = board->operator()(end);
    if (target->is_white() == this->is_white()) {
      return false;
    }
    
    return true;
  }
  int Pawn::point_value() const {
    return 1;
  }
}

