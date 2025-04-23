#include "Knight.h"
#include <cmath>
using std::abs;

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {

    int dx = abs(end.first - start.first);

    int dy = abs(end.second - start.second);

    // We know that knight moves in L shape
    
    return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
    
  }
}

