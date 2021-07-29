#pragma once
#include "framework.h"

class Block
{
private:
	int BLock[4][4];

public:
	Block();
	~Block();

	void CopyBlock(int copy[4][4]);
	int getBpart(int x, int y);

	void rotate();
	void reverserotate();
};

