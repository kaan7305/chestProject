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
  // Default constructor
  Board::Board(){}

  // Destructor: deletes all dynamically allocated pieces
  Board::~Board() {
    for (auto &it : occ) {
      delete it.second;
    }
    occ.clear();
  }
  
  // Deep‐copy constructor
  Board::Board(const Board& other) {
    std::map<Position, Piece*, PositionCompare> temp_occ;

    try {
      // Copies pieces from the other board
      for (const auto& kv : other.occ) {
        if (kv.second) {
          char designator = kv.second->to_ascii();
          Piece* new_piece = create_piece(designator);
          new_piece->setBoard(this);
          temp_occ[kv.first] = new_piece;
        }
      }
    } catch (...) {
        // If any exception occurs, delete created pieces
        for (auto& kv : temp_occ) {
            delete kv.second;
        }
        temp_occ.clear();
        throw;  // rethrow original exception
    }

    // Swaps if successful
    occ.swap(temp_occ);
  }
  
  // Assignment operator
  Board& Board::operator=(const Board& other) {
    if (this != &other) {
      // Deletes existing pieces
      for (auto &kv : occ) {
        delete kv.second;
      }
      occ.clear();
  
      // Deep-copies pieces from other board
      for (auto &kv : other.occ) {
        char designator = kv.second->to_ascii();
        Piece* newp = create_piece(designator);
        newp->setBoard(this);
        occ[kv.first] = newp;
      }
    }
    return *this;
  }

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

  /**
   * Attempts to add a new piece with the specified designator, at the given position.
   * @param position The position on the board to add the piece.
   * @param piece_designator The designator for the piece to be added.
   * @throws Exception if the designator is invalid, the position is not on the board,
   *                   or if the specified position is occupied.
   */
  void Board::add_piece(const Position& position, const char& piece_designator) {
    // Creates a new piece based on designator
    Piece* piece = create_piece(piece_designator);

    if (piece == nullptr) {
      throw Exception("invalid  designator");
    }

    // Defines pair of characters as new type to represent position on board,
    // .first refers to column, .second refers to row
    char column =  position.first;
    char row = position.second;

    // Checks if the position is valid
    if (column < 'A' || column > 'H' || row < '1' || row > '8') {
      delete piece;
      throw Exception("invalid position");
    }

    // Checks if position is not already occupied
    if (isOccupied(position)) {
      delete piece;
      throw Exception("position is occupied");
    }

    // Sets the board pointer within the Piece for move checks
    piece->setBoard(this);
    occ[position] = piece;
  }

  /**
   * Prints the board state
   */
  void Board::display() const {
    // Labels at top
    std::cout << "  ABCDEFGH" << std::endl;
    std::cout << "  --------" << std::endl;
    
    // Loops through board top to bown row
    for (char row = '8'; row >= '1'; row--) {
      std::cout << row << '|';
      
      for (char col = 'A'; col <= 'H'; col++) {
        Position pos(col, row);
        const Piece* piece = (*this)(pos);
    
        // Alternates background color for each square
        bool is_white = ((row - '1') + (col - 'A')) % 2;
        
        Terminal::Color bg;
        if (is_white) {
            bg = Terminal::WHITE;
        } else {
            bg = Terminal::BLACK;
        }
        Terminal::color_bg(bg);

        // Displays piece if exists, otherwise displays empty square
        if (piece) {
          std::cout << piece->to_unicode();
        } else {
          std::cout << " ";
        }
        
        // Resets background color for next square
        Terminal::set_default();
      }  

      std::cout << '|' << row << std::endl;
    }

    // Labels at bottom
    std::cout << "  --------" << std::endl;
    std::cout << "  ABCDEFGH" << std::endl;    
  }

  /**
   * Moves a piece from one square to another.
   * @param from The position of the piece to move.
   * @param to The position to move the piece to.
   */
  void Board::occ_to_from(const Position& from, const Position& to)
	{
		occ[from] = occ[to];
    occ.erase(from);
	}

  /**
   * Erases a piece from the board at the specified position.
   * @param pos The position of the piece to erase.
   */
  void Board::erase_piece(const Position& pos) {
    auto it = occ.find(pos);
    if (it != occ.end()) {
      delete it->second;
      occ.erase(it);     
    }
  }

  /**
   * Checks if the board has the right number of kings on it.
   * @return True if the board has exactly one white king and one black king, false otherwise.
   */
  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;

    // Counts number of kings on the board
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

    // Must have 1 white and 1 black king
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /**
   * Overloaded operator to print the board state.
   * @param os The output stream to print to.
   * @param board The board to print.
   * @return The output stream.
   */
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
    Position kingPos;
    const Piece* p;
    bool kingExists = false;

    // Finds the king's position
    for (std::map<Position, Piece*>::const_iterator it = occ.begin();
        it != occ.end(); ++it ) {  
      p = it->second;
      if ( p && (p->to_ascii() == (white ? 'K' : 'k')) ) {
        kingPos = it->first;
        kingExists = true;
        break;
      }
    }

    // Not in check if no king exists
    if (!kingExists) return false;

    // Checks if any enemy piece can capture king
    for (std::map<Position, Piece*>::const_iterator it = occ.begin();
      it != occ.end(); ++it ) {
      p = it->second;
      if (p && (p->is_white() != white) ) {
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
    // Collects all avalible pieces of same color in one vector
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
    // Gets piece pointer from original position
    Piece* p = occ[from];
    occ.erase(from); // and gets rid of it from previous spot

    // Deletes target if already occupied
    auto it = occ.find(to);
    if (it != occ.end()) {
      delete it->second;
      occ.erase(it);
    }

    // Moves piece to target destination and updates board pointer
    occ[to] = p;
    p->setBoard(this);
  }  

  /**
   * Sets the board pointer within the Piece for move checks.
   */
  void Board::fix_pieces_board() {
    for (auto& kv : occ) {
      if (kv.second) {
        kv.second->setBoard(this);
      }
    }
  }

  /**
   * Checks if the path between two positions is clear.
   * @param start The starting position.
   * @param end The ending position.
   * @return True if the path is clear, false otherwise.
   */
  bool Piece::isPathClear(const Position& start, const Position& end) const {
    // Calculates step direction
    int dx = (end.first  > start.first)  ? 1 :
             (end.first  < start.first)  ? -1 : 0;
    int dy = (end.second > start.second) ? 1 :
             (end.second < start.second) ? -1 : 0;

    Position cur{ char(start.first + dx), char(start.second + dy) };

    // Walks through the path from start to end, returns false if blocked
    while (cur != end) {
      if (board->isOccupied(cur)) return false;
      cur.first  += dx;
      cur.second += dy;
    }

    // Path is clear
    return true;
  }

}
