#include <algorithm>
#include "pieces.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

int Pieces::dist(int a, int b)
{
	a = a & 0x00FF;
	b = b & 0x00FF;
	int x = abs((a & 0x000F) - (b & 0x000F));
	int y = abs((a >> 4) - (b >> 4));
	return std::max(x, y);
}

float Pieces::direction(int x, int y)
{
	int sign_x = (y & 0x000F) - (x & 0x000F);
	int sign_y = ((y & 0x00F0) >> 4) - ((x & 0x00F0) >> 4);
	if (sign_x == 0 && sign_y >= 0)
		return 8;
	else if (sign_x == 0 && sign_y < 0)
		return -8;
	return float(sign_y)/sign_x;
}

bool King::move(int src, int dest)
{
	//Check if move is legal for king
	
	int s = (src & 0x00FF);
	int length = dist(s, dest);
	if (length == 1)
		return 1;
	else
		return 0;
}

bool Queen::move(int src, int dest)
{
	//Check if move is legal for Queen
	int s = (src & 0x00FF);
	int drc = fabs(direction(s, dest));
	int length = dist(s, dest);
	if (!(drc == 0 || drc == 1 || drc == 8)) // Six directions allowed
		return 0;
	if (length <= 7)
		return 1;
	else
		return 0;
}

bool Rook::move(int src, int dest)
{
	int s = (src & 0x00FF);
	float drc = fabs(direction(s, dest));
	int length = dist(s, dest);
	if (!(drc == 0 || drc == 8)) // Four directions are allowed
		return 0;
	if (length <= 7)
		return 1;
	else
		return 0;
}


bool Bishop::move(int src, int dest)
{
	int s = (src & 0x00FF);
	int drc = fabs(direction(s, dest));
	int length = dist(s, dest);
	if (!(drc == 1)) // Four directions are allowed
		return 0;
	if (length <= 7)
		return 1;
	else
		return 0;
}

bool Knight::move(int src, int dest)
{
	int s = (src & 0x00FF);
	if(dist(s, dest) != 2)
		return 0;
	float drc = fabs(direction(s, dest));
	if (drc == 8 || drc == 0)
		return 0;
	return 1;
}

bool Pawn::move(int src, int dest)
{
	int s = (src & 0x00FF);
	int col = (src & 0xF000) >> 12;
	if(dist(s, dest) != 1) {
		if (dist(s, dest) == 2) {
			for (int i = 0; i < 8; ++i) {
				if (s == (16 + i)) {
					if (direc == 8 || -8) {
						; // Add for special move
					}
				}
			}
		}
		else
			return 0;
	}
	if (col == 2)
		col = -1;
	if (col != (((dest & 0x00F0) >> 4) - ((s & 0x00F0) >> 4)))
		return 0;
	/*
	 * In case pawn is taking a diagonal move
	 * there should be a piece of different color.
	 */

	if (fabs(direction(s, dest)) == 1)
		if (((dest & 0xF000) == (s & 0xF000)) || (dest & 0x0F00 == 0))
			return 0;
	return 1;
}
