#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include "pieces.h"
#include <string>

class Board {
	King k;
	Queen q;
	Rook r;
	Bishop b;
	//Knight wN[2], bN[2];
	//Pawn wP[8], bP[8];
	int block[128];

public:
	Board(); //Intializes the board by setting default positions
	int convert_to_0x88(std::string);
	void set_pos(int, int, int);
	bool is_valid(int); //Is the destination is valid
	int index_of(int);
	bool move(std::string, std::string);
	bool clear_path(short, short);
	void show_board();
	void update(int, int);
};

#endif