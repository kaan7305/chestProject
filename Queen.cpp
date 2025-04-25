#include "Queen.h"
#include "Board.h"
#include <cmath>

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
  
    // We will be checking if the move is horizontal, vertical, or diagonal and if it is so
    // we will be returning true value otherwise we will be returning false

  int dx = abs(end.first - start.first);
  int dy = abs(end.second - start.second);

  if (start.first == end.first || start.second == end.second ||
    abs(start.first - end.first) == abs(start.second - end.second))
  {
    if ((board->isOccupied(Position(end.first,end.second)))) 
    {
      const Piece* target = board->operator()(Position(end.first, end.second));
      // checks if target is an enemy
      if (target && (this->is_white() != target->is_white())) 
      {
        return true;
      }
      return false;
    }
    return true;
  }

  return false;
  }
}
