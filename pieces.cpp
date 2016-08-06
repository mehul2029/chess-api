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
	return float(sign_y)/float(sign_x);
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
	int drc = fabs(direction(s, dest));
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