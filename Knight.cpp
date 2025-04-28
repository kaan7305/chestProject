#include "Knight.h"
#include "Board.h"
#include <cmath>
using std::abs;

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

    // we are checking if tge move is in the board and valid
    int dx = abs(end.first - start.first);

    int dy = abs(end.second - start.second);

    // We know that knight moves in L shape 
    // so we can check if the move is valid
    // Also we have to chec if the move is legit by checking if it is white or black
    
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
    {
      // this will help us to see if the move is occupied or not
      if ((board->isOccupied(Position(end.first,end.second)))) 
      {
        const Piece* target = board->operator()(Position(end.first, end.second));
        // we are checking if target is an enemy one
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

  int Knight::point_value() const {
    return 3;
}
}
    

