#include "King.h"
#include "Board.h"
#include <cmath>

namespace Chess
{
  /**
   * Class to check if the move shape is valid for a King. Also checks if,
   * if the move is a capture move, it's valid.
   * @param start The starting position of the piece
   * @param end The ending position of the piece
   * @return true if the move shape is valid, false otherwise
   * @note The move shape is valid if the piece moves one space in any direction
   *       and there are no pieces in the way
   */
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    
    int dx = abs(end.first - start.first);
    int dy = abs(end.second - start.second);
    // keeps dx and dy in the range of 0 - 1 as thats how far the king can
    // move x and y. And if both dy and dx are 0, then the king didnt move
    if (dx <= 1 && dy <=1 && (dy != 0 || dx != 0)) {
      if ((board->isOccupied(Position(end.first,end.second)))) {
        const Piece* target = board->operator()(Position(end.first, end.second));
        // checks if target is an enemy
        if ( target && (this->is_white() != target->is_white()) ) {
          return true;
        }
        return false;
      }
      return true;
    }

    return false;
  }

  int King::point_value() const {
    return 0;
  }

}
