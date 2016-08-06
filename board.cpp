#include "board.h"
#include <algorithm>
#include <locale>
#include <iostream>

Board::Board()
{
	for (int i = 0; i < 128; ++i)
		block[i] = i;

	set_pos(1, 1, convert_to_0x88("1d")); // white king
	set_pos(1, 2, convert_to_0x88("1e")); // white queen
	set_pos(1, 3, convert_to_0x88("1c")); // white bishop
	set_pos(1, 3, convert_to_0x88("1f")); // white bishop
	set_pos(1, 4, convert_to_0x88("1b")); // white knight
	set_pos(1, 4, convert_to_0x88("1g")); // white knight
	set_pos(1, 5, convert_to_0x88("1a")); // white rook
	set_pos(1, 5, convert_to_0x88("1h")); // white rook
	for (int i = 0; i < 8; ++i)
		set_pos(1, 6, 16 + i);			// all white pawns
	
	set_pos(2, 1, convert_to_0x88("8d")); // black king
	set_pos(2, 2, convert_to_0x88("8e")); // black queen
	set_pos(2, 3, convert_to_0x88("8c")); // black bishop
	set_pos(2, 3, convert_to_0x88("8f")); // black bishop
	set_pos(2, 4, convert_to_0x88("8b")); // black knight
	set_pos(2, 4, convert_to_0x88("8g")); // black knight
	set_pos(2, 5, convert_to_0x88("8a")); // black rook
	set_pos(2, 5, convert_to_0x88("8h")); // black rook
	for (int i = 0; i < 8; ++i)
		set_pos(2, 6, 16*6 + i);		// all black pawns
}

void Board::set_pos(int col, int piece, int pos)
{
	block[index_of(pos)] = (col << 12) + (piece << 8) + pos;
}

int Board::convert_to_0x88(std::string pos)
{
	std::transform(pos.begin(), pos.end(), pos.begin(), ::tolower);
	return 16 * (int(pos[0]) - 49) + (int(pos[1]) - 97);
}

bool Board::move(std::string src, std::string dest)
{
	int s = convert_to_0x88(src);
	int d = convert_to_0x88(dest);
	
	if (!is_valid(s) || !is_valid(d) || s == d)
		return 0;

	/*
	 * Check that color of pieces are different
	 * in case of collison
	 */
	if (((block[index_of(d)] & 0xF000) & 
			(block[index_of(s)] & 0xF000)) != 0)
		return 0;
	int piece = (block[index_of(s)] & 0x0F00) >> 8;
	switch (piece) {
		case 1: if (k.move(s, d)) // no clear_path needed
					update(s, d);
				else
					return 0;
				break;
		case 2: if (q.move(s, d) && clear_path(s, d))
					update(s, d);
				else
					return 0;
				break;
		case 3: if (b.move(s, d) && clear_path(s, d))
					update(s, d);
				else
					return 0;
				break;
		case 4: if (n.move(s, d)) // no clear_path required for knight
					update(s, d);
				else
					return 0;
				break;
		case 5: if(r.move(s, d) && clear_path(s, d))
					update(s, d);
				else
					return 0;
				break;
		case 6: if (p.move(block[index_of(s)], block[index_of(d)]) 
						&& clear_path(s, d))		//clear_path in case of 2 step move
					update(s, d);
				else
					return 0;
				break;
		default:
			return 0;
	}
	return 1;
}

bool Board::is_valid(int pos)
{
	if (pos & 0x0088)
		return 0;
	return 1;
}

int Board::index_of(int pos)
{
	return (pos & 0x00F0) + (pos & 0x000F);  
}

bool Board::clear_path(short x, short y)
{
	int sign_x = (y & 0x0F) - (x & 0x0F);
	if (sign_x < 0)
		sign_x = -1;
	else if (sign_x > 0)
		sign_x = 1;
	else
		sign_x = 0;

	int sign_y = (y >> 4) - (x >> 4);
	if (sign_y < 0)
		sign_y = -1;
	else if (sign_y > 0)
		sign_y = 1;
	else
		sign_y = 0;
	int t = x;
	while (t != y) {
		t += (sign_y * 16 + sign_x);
		if ((block[t] & 0x0F00) != 0 && t!= y) {
			return 0;
		}
	}
	return 1;
}

void Board::show_board()
{
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; ++j) {
			std::cout << ((block[16*i + j] & 0x0F00)>> 8) << " ";
		}
		std::cout << std::endl;
	}
}

void Board::update(int s, int d)
{
	block[index_of(d)] =  index_of(d) + (block[index_of(s)] & 0xFF00);
	block[index_of(s)] = index_of(s);
}