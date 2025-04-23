#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
  
    // We will be checking if the move is horizontal, vertical, or diagonal and if it is so
    // we will be returning true value otherwise we will be returning false
    if (start.first == end.first || start.second == end.second ||
        abs(start.first - end.first) == abs(start.second - end.second)) {
      return true;
    }
    // If not, it's an illegal move
    return false;
  }
}
