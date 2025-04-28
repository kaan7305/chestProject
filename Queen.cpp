#include "Queen.h"
#include "Board.h"
#include <cmath>

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
  
    // We will be checking if the move is horizontal, vertical, or diagonal and if it is so
    // we will be returning true value otherwise we will be returning false


    int dx = end.first  - start.first;
    int dy = end.second - start.second;

    // We are checkingg if the move is horizontal, vertical, or diagonal
    if (dx != 0 && dy != 0 && std::abs(dx) != std::abs(dy))
    {
      return false;
    }
      
    if (dx > 0)
    {
        dx = 1;
    }
    else if (dx < 0)
    {
        dx = -1;
    }
    else
    {
        dx = 0;
    }
    
    if (dy > 0)
    {
        dy = 1;
    }
    else if (dy < 0)
    {
        dy = -1;
    }
    else
    {
        dy = 0;
    }

    char x = start.first + dx;
    char y = start.second + dy;
    
    while (x != end.first || y != end.second) 
    {
      if (board->isOccupied(Position(x, y))){
        return false;
      } 
      x += dx;
      y += dy;
    }
  
    if (board->isOccupied(end)) 
    {
      const Piece* target = board->operator()(end);
      return target && (target->is_white() != this->is_white());
    }
    return true;
  }

  int Queen::point_value() const {
    return 9;
  }
}
