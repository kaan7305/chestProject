#include <cassert>
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
		if (start.first < 'A' || start.first > 'H' ||
			start.second < '1' || start.second > '8')
			throw Exception("start position is not on board");
		if (end.first < 'A' || end.first > 'H' ||
			end.second < '1' || end.second > '8')
			throw Exception("end position is not on board");
	
		const Piece* mover = board(start);
		if (!mover) throw Exception("no piece at start position");
	
		if (mover->is_white() != is_white_turn)
			throw Exception("piece color and turn do not match");

		bool destOcc = board.isOccupied(end);
		if (destOcc) {
			const Piece* victim = board(end);
			if (victim->is_white() == mover->is_white())
				throw Exception("cannot capture own piece");
			if (!mover->legal_capture_shape(start,end))
				throw Exception("illegal capture shape");
		} else {
			if (!mover->legal_move_shape(start,end))
				throw Exception("illegal move shape");
		}
	
		Game back = *this;

		board.move_piece(start,end);
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
	// Havent finished yet
	bool Game::in_mate(const bool& white) const {

		if (in_check(white) == false) 
		{
			return false;
			}
		// to gather all the pievces of color  by using vectors and pairs
		std::vector<std::pair<Position, const Piece*>> 
		colorGroup = board.piecesByColor(white);

		// we will try to move each piece to each square on the board
		// and check if the move is legal
		for (std::vector<std::pair<Position, const Piece*>>::const_iterator cit =
			colorGroup.begin(); cit != colorGroup.end(); ++cit) 
		{
			const Piece* p = cit->second;
			Position start = cit->first;

			for (char x = 'A'; x <= 'H'; x++) 
			{
				for (char y = '1'; y <= '8'; y++) 
				{
					Position to = std::make_pair(x, y);
							
					// we will decide which shape-checking function to use
					bool occupied = board.isOccupied(to);
					bool legalShape;
					if(occupied)
					{
						legalShape = p->legal_capture_shape(start, to);
					}
					else 
					{
						legalShape = p->legal_move_shape(start, to);
					}
					if(legalShape == false)
					{
						continue;
					}
					Game simulation = *this;
					simulation.is_white_turn = white;

					simulation.board.erase_piece(to);
					simulation.board.occ_to_from(start, to);
					
					// we will check if it is in check
					if (simulation.in_check(white) == false) 
					{
						return false; // if it is not in check, then it is not checkmate
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
						simulation.make_move(start, end);
						// if after legal move, and not in check, that means
						// there are valid moves left
						if (!simulation.in_check(white)) return false;
					}
				}
			}
		}
		return true; // no legal moves left because they would all result in a check
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
    }


      std::istream& operator>> (std::istream& is, Game& game) {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		game.board = Board();

		std::string line;
		for (int rank = 8; rank >= 1; rank--) {
			if (!std::getline(is, line) || line.size() < 8) {
				throw Exception("invalid file format");
			}

			for (int file = 0; file < 8; file++) {
				char piece_char = line[file];
				if (piece_char != '-') {
					Position pos (char ('A' + file), char ('1' + rank));
				game.board.add_piece(pos, piece_char);
				}
			}
		}

		char turn_char;
		if (!(is >> turn_char) || (turn_char != 'w' && turn_char != 'b')) {
			throw Exception("invalid file format");
		}

		return is;
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
