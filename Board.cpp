#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  /**
   * Returns a const pointer to the piece at a prescribed location if it exists,
   * or nullptr if there is nothing there.
   * @param position The position on the board to check for a piece.
   * @return A const pointer to the piece at the specified position, or nullptr 
   *         if no piece exists.
   */
  const Piece* Board::operator()(const Position& position) const {
    std::map<Position, Piece*>::const_iterator it = occ.find(position);
    if (it != occ.end()) return it->second;
    return nullptr;
  }

  void Board::add_piece(const Position& position, const char& piece_designator) {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////
    
    // dont delete this code plz, it helps write legal move functions
    // for other pieces - Johnathan
    Piece* piece = create_piece(piece_designator);
    // Sets the board pointer within the Piece for move checks
    piece->setBoard(this);
    occ[position] = piece;
  }

  void Board::display() const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////

    std::cout << "  ABCDEFGH" << std::endl;
    
    for (char row = '8'; row >= '1'; row--) {
      std::cout << row << ' ';
      
      for (char col = 'A'; col <= 'H'; col++) {
        Position pos(col, row);
        const Piece* piece = (*this)(pos);
    
        bool is_dark = ((row - '1') + (col - 'A')) % 2;
        
        Terminal::Color bg;
        if (is_dark) {
          bg = Terminal::BLACK; // black on white
        } else {
          bg = Terminal::WHITE; // white on black
        }

        if (piece) {
          std::cout << piece->to_unicode();
        } else {
          std::cout << "-";
        }
  
        Terminal::set_default(); // reset after each square
      }  

      std::cout << ' ' << row << std::endl;
    }
    
    std::cout << "  ABCDEFGH" << std::endl;    
  }

  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();
	 it != occ.end();
	 it++) {
      if (it->second) {
	switch (it->second->to_ascii()) {
	case 'K':
	  white_king_count++;
	  break;
	case 'k':
	  black_king_count++;
	  break;
	}
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }

     /**
      * Checks if the specified position is occupied by a piece.
      * @param pos The position to check.
      * @return True if the position is occupied, false otherwise.
      */
     bool Board::isOccupied(const Position& pos) const {
      // if it's not nullptr, a piece is there so return true
      return (*this)(pos) != nullptr;
    }

}
