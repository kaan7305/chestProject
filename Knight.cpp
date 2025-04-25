#include "Knight.h"
#include "Board.h"
#include <cmath>
using std::abs;

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

    int dx = abs(end.first - start.first);

    int dy = abs(end.second - start.second);

    // We know that knight moves in L shape 
    // so we can check if the move is valid
    // Also we have to chec if the move is legit by checking if it is white or black
    
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
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
    

