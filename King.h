#ifndef KING_H
#define KING_H

#include "Piece.h"

namespace Chess
{
	class King : public Piece {

	public:
		// returns true if the move is legal for this piece
    	bool legal_move_shape(const Position& start, const Position& end) const override;

		// ASCII representation of the piece
		char to_ascii() const override { return is_white() ? 'K' : 'k';	}

		// Unicode representation of the piece
		std::string to_unicode() const override { return is_white() ? "\u2654" : "\u265A"; }

		// returns piece's point value
		int point_value() const override;
    
	private:

		// Constructor
		King(bool is_white) : Piece(is_white) {}

		// creates a new piece
		friend Piece* create_piece(const char& piece_designator);
	};

}
#endif // KING_H
