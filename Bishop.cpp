#include "Bishop.h"
#include "Board.h"
#include <utility>

namespace Chess
{

  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {

    // Checks if the move shape is Diagnonal
    if((abs(end.first - start.first) == abs(end.second - start.second))) {

      // moving foward/right = 1, moving back/left = -1
      int dx = (end.first > start.first) ? 1 : -1;
      int dy = (end.second > start.second) ? 1 : -1;

      // ensure there is no piece in the way of the path
      char x = start.first + dx; // add movement values
      char y = start.second + dy; 
      while ((x != end.first) && (y != end.second)) {
        if (board->isOccupied(Position(x, y))) return false;
        x += dx;
        y += dy;
      }

      // if it gets here, every other space was valid so check the last
      if (board->isOccupied(Position(end.first, end.second))) { // checks if capture move
        const Piece* target = board->operator()(Position(end.first, end.second));
        // checks if target is an enemy
        if ( target && ((this->is_white() && !(target->is_white()))
          || (!(this->is_white())) && (target->is_white()))) {
          return true;
        }
        return false;

      }
     
      return true;
    }
    return false;
  }


}
