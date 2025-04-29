
#include <cassert>
#include <cstddef>
#include <utility>
#include "Game.h"
#include "Exceptions.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	void Game::make_move(const Position& start, const Position& end) {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////

		//I am checking if the start and end positions are valid
		if (start.first < 'A' || start.first > 'H' ||
			start.second < '1' || start.second > '8')
			{
				throw Exception("start position is not on board");
			}
		
		if (end.first < 'A' || end.first > 'H' ||
			end.second < '1' || end.second > '8')
			{
				throw Exception("end position is not on board");
			}
			
		// We are checking if the start and end positions are the same
		const Piece* mover = board(start);
		if (!mover) 
		{
			throw Exception("no piece at start position");
		}


		if (mover->is_white() != is_white_turn)
		{
			throw Exception("piece color and turn do not match");
		}

		// We are checking if the end position is occupied by a 
		// piece of the same color
		bool destOcc = board.isOccupied(end);
		if (destOcc) 
		{
			const Piece* victim = board(end);
			if (victim->is_white() == mover->is_white()){
				throw Exception("cannot capture own piece");
			}
				
			if (!mover->legal_capture_shape(start,end)){
				throw Exception("illegal capture shape");
			}
		} 
		else 
		{


    char pieceChar = mover->to_ascii();

	// We are checking if the move is legal
    int dx = end.first  - start.first;
    int dy = end.second - start.second;
    int adx = dx < 0 ? -dx : dx;
    int ady = dy < 0 ? -dy : dy;
	
    if ((pieceChar == 'P' && start.second == '2' && end.second == '4') ||
        (pieceChar == 'p' && start.second == '7' && end.second == '5'))
    {
        Position mid{ start.first,
                      static_cast<char>((start.second + end.second) / 2) };
        if (board.isOccupied(mid))
            throw Exception("path is not clear");
    }

	// We check for illegal moves
    if (pieceChar == 'R' || pieceChar == 'r' ||
        pieceChar == 'B' || pieceChar == 'b' ||
        pieceChar == 'Q' || pieceChar == 'q')
    {
        bool badShape =
           ((pieceChar == 'R' || pieceChar == 'r') && !(dx == 0 || dy == 0))    ||  
           ((pieceChar == 'B' || pieceChar == 'b') && !(adx == ady))            || 
           ((pieceChar == 'Q' || pieceChar == 'q') && !(dx == 0 || dy == 0 || adx == ady));
        if (badShape)
            throw Exception("illegal move shape");

        if (!mover->isPathClear(start, end))
            throw Exception("path is not clear");
    }
    else
    {
        if (!mover->legal_move_shape(start, end))
            throw Exception("illegal move shape");
    }
		}
		Game back = Game(*this);

		board.move_piece(start,end);

		const Piece* movedPiece = board(end);
		
		if (movedPiece) {
			char pieceChar = movedPiece->to_ascii();
			if ((pieceChar == 'P' && end.second == '8') || (pieceChar == 'p' && end.second == '1')) {
				board.erase_piece(end);
				board.add_piece(end, is_white_turn ? 'Q' : 'q');
			}
		}

		is_white_turn = !is_white_turn;
	
		if (board.checkChecker(!is_white_turn)) {
			*this = back;
			throw Exception("move exposes check");
		}
	}

	/**
	 * Checks if the king piece is in check.
	 * @param white True if the king is white, false if black.
	 * @return True if the king is in check, false otherwise.
	 */
	bool Game::in_check(const bool& white) const {
		return board.checkChecker(white);
	}

	// true is checkmate false is not checkmate
	bool Game::in_mate(const bool& white) const {	
		if (!in_check(white)) {
			return false;
		}
		
		std::vector<std::pair<Position, const Piece*>> colorGroup = board.piecesByColor(white);
		const Piece* p;
		Position start;
		// run through all pieces of the color
		// and check if there is a legal move for any of them
		// if there is a legal move then it is not checkmate
		// if there is no legal move then it is checkmate
		for (std::vector<std::pair<Position, const Piece*>>::const_iterator cit = colorGroup.begin(); 
			cit != colorGroup.end(); ++cit) {
			p = cit->second;
			start = cit->first;
	
			for (char x = 'A'; x <= 'H'; ++x) {
				for (char y = '1'; y <= '8'; ++y) {
					Position to = std::make_pair(x, y);
	
					bool occupied = board.isOccupied(to);
					bool legalShape;
					if (occupied) {
						legalShape = p->legal_capture_shape(start, to);
					} else {
						legalShape = p->legal_move_shape(start, to);
					}
					if (!legalShape) {
						continue;
					}
		
					Game simulation = *this;	
					try {
						simulation.make_move(start, to);
					} catch (const Exception& e) {
						continue;
					}
					if (!simulation.in_check(white)) {
						return false;
					}
				}
			}
	
		}
		return true;
	}
	
	


	/**
	 * Checks if the game is in stalemate.
	 * @param white True if the king is white, false if black.
	 * @return True if the game is in stalemate, false otherwise.
	 */
	 bool Game::in_stalemate(const bool& white) const {
        std::vector<std::pair<Position, const Piece*>> colorGroup =
        board.piecesByColor(white);
        const Piece* p;
        Position start;
        for (std::vector<std::pair<Position, const Piece*>>::const_iterator it =
            colorGroup.begin(); it != colorGroup.end(); ++it) {
            p = it->second;
            start = it->first;
            // run through all spots on the board
            for (char x = 'A'; x <= 'H'; ++x) {
                for (char y = '1'; y <= '8'; ++y) {
                    Position end(x, y);
                    // check if the moves would still be legal
                    if (p->legal_move_shape(start, end)) {
                        Game simulation = *this;

                        try {
                            simulation.make_move(start, end);
    
                            // If move succeeds and no check, it's NOT stalemate
                            if (!simulation.in_check(white)) {
                                return false;
                            }
                        } 
                        catch (const Exception& e) {
                            // move exposes check or invalid, ignore and continue
                        }
                    }
                }
            }
        }
        return true; // no legal moves left because they would all result in a check
    }



    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {

		// we will have the total value of each piece
		// then we have to get all the pieces from the given color
		// we will sum all these by using a switch or if statement
		int total = 0;
		std::vector<std::pair<Position, const Piece*>> colorGroup = board.piecesByColor(white);
		// we will iterate through the color group to get the value of each piece
		for (std::vector<std::pair<Position, const Piece*>>::const_iterator it = colorGroup.begin();
			it != colorGroup.end(); it++) 
		{
			const Piece* p = it->second;
			if (p != nullptr) 
			{	// add the value of the piece to the total
				total += p->point_value(); 
			}
		}
		return total;
	}


      std::istream& operator>> (std::istream& is, Game& game) {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		game.board = Board();

		std::string line;
		// Read the input board
		for (int rank = 8; rank >= 1; rank--) {
			if (!std::getline(is, line) || line.size() < 8) {
				throw Exception("invalid file format");
			}

			for (int file = 0; file < 8; file++) {
				char piece_char = line[file];
				// if the piece is not a placeholder
				if (piece_char != '-') {
					// Adds piece to the board based on file and rank
					Position pos (char ('A' + file), char ('0' + rank));
					game.board.add_piece(pos, piece_char);
				}
			}
		}
		// Read the turn character
		char turn_char;
		if (!(is >> turn_char) || (turn_char != 'w' && turn_char != 'b')) {
			throw Exception("invalid file format");
		}
		// Set the turn based on the character
		// 'w' for white and 'b' for black
		game.is_white_turn = (turn_char == 'w');
		return is;
	}

	// Game copy constructor
	Chess::Game::Game(const Game& other)
	// copies the board and is_white_turn from the other game
    : board(other.board), is_white_turn(other.is_white_turn) {}

	// Game assignment operator
	Chess::Game& Game::operator=(const Game& other) {
		// Check for self-assignment
		if (this != &other) {
			// Copy the board and is_white_turn from the other game
			board = other.board;
			is_white_turn = other.is_white_turn;
		}
		return *this;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}