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

    if (piece == nullptr)
    {
      throw Exception("invalid  designator");
    }

    //  define pair of characters as a new type to represent a position on the board,
    // I take this fropm Piece.h which us typedef std::pair<char, char> Position;
    // .first refers to column, .second refers to row

    char column =  position.first;
    char row = position.second;
    // check if the position is valid
    if (column < 'A' || column > 'H' || row < '1' || row > '8') 
    {
      delete piece;
      throw Exception("invalid position");
    }

    // I am checking three different ways ti see there is no error also this will help me to understand
    // isOcccupied function works properly 
    if (isOccupied(position)) 
    {
      delete piece;
      throw Exception("position is occupied");
    }
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

  void Board::occ_to_from(const Position& from, const Position& to)
	{
		occ[from] = occ[to];
    occ.erase(from);
	}

	void Board::erase_piece(const Position& pos) 
	{
		occ.erase(pos);
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

    /**
     * Checks if the king piece is in check.
     * @param white True if the king is white, false if black.
     * @return True if the king is in check, false otherwise.
     * @note This helper function is in board because it requires
     *       piece positions and logic, which board already has.
     */
    bool Board::checkChecker (const bool& white) const {
      Position kingPos; // king's position
      const Piece* p;
      bool kingExists = false;

      // find the king's location
      for (std::map<Position, Piece*>::const_iterator it = occ.begin();
          it != occ.end(); ++it ) {  
          p = it->second;
          if ( p && (p->to_ascii() == (white ? 'K' : 'k')) ) {
            kingPos = it->first;
            kingExists = true;
            break; // got what we needed, loop no longer necessary
          }
      }

      if (!kingExists) return false;
        
      // find if the king is in danger
      for (std::map<Position, Piece*>::const_iterator it = occ.begin();
          it != occ.end(); ++it ) {
          p = it->second;
          if (p && (p->is_white() != white) ) { // piece is an enemy
            if (p->legal_capture_shape(it->first, kingPos)) return true;
          }
      }
      return false;
    }

    /**
     * Returns a vector of pairs containing the positions and pointers to pieces
     * of the specified color.
     * @param white True if the pieces are white, false if black.
     * @return A vector of pairs containing the positions and pointers to pieces
     *         of the specified color.
     */
    std::vector<std::pair<Position, const Piece*>> Board::piecesByColor (const bool& white) const {
      std::vector<std::pair<Position, const Piece*>> result;
      // collects all (avalible) pieces of the same color in one vector
      for (std::map<Position, Piece*>::const_iterator it = occ.begin();
          it != occ.end(); ++it ) {
          if (it->second && (it->second->is_white() == white) ) {
            result.push_back(std::make_pair(it->first, it->second));
          }
      }
      return result;
    }

    /**
     * Moves a piece from one square to another (possibly capturing).
     * @param from The position of the piece to move.
     * @param to The position to move the piece to.
     */
    void Board::move_piece(const Position& from, const Position& to) {
      // grabs and removes the pointer at "from"
      Piece* p = occ[from];
      occ.erase(from);
  
      // overwrites (captures if needed) at "to"
      occ[to] = p;
  
      // makes sure the piece knows its board
      p->setBoard(this);
  }  


}
