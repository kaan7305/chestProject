#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

namespace Chess
{
	class Bishop : public Piece {

	public:
	// returns true if the move is legal for this piece
    bool legal_move_shape(const Position& start, const Position& end) const override;

<<<<<<< HEAD
	    // ASCII representation of the piece
		char to_ascii() const override { return is_white() ? 'B' : 'b';	}
    
		// Unicode representation of the piece
		std::string to_unicode() const override { return is_white() ? "\u2657" : "\u265D"; }
		
		// returns piece's point value
		int point_value() const override;
	private:
		
		// Constructor
=======
		char to_ascii() const override { return is_white() ? 'B' : 'b';	}
		
		std::string to_unicode() const override { return is_white() ? "\u2657" : "\u265D"; }

		int point_value() const override;
	private:
>>>>>>> 23d544e547dd6022b3c6dfc461b95ee0d5a4eebf
		Bishop(bool is_white) : Piece(is_white) {}

		// creates a new piece
		// based on the piece designator
		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // BISHOP_H
