#ifndef __PIECES_H_INCLUDED__
#define __PIECES_H_INCLUDED__

class Pieces {
public:
	virtual bool move(int, int) = 0;
	int dist(int, int);
	float direction(int, int);
};

class King : public Pieces {
public:
	bool move(int, int);
};

class Queen : public Pieces {
	public:
	bool move(int, int);
};

class Rook : public Pieces {
	public:
	bool move(int, int);
};

class Bishop : public Pieces {
	public:
	bool move(int, int);
};
/*
class Knight : public Pieces {
};

class Pawn : public Pieces {
};
*/
#endif