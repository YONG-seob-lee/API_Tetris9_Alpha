#include "Block.h"

Block::Block()
{
	int BlockShape[7][4][4] =
	{
	{{0,2,0,0},{0,2,0,0},{0,2,0,0},{0,2,0,0}},
	{{0,0,0,0},{0,3,3,0},{0,3,3,0},{0,0,0,0}},
	{{0,4,0,0},{4,4,4,0},{0,0,0,0},{0,0,0,0}},
	{{0,0,5,0},{0,5,5,0},{0,5,0,0},{0,0,0,0}},
	{{0,6,0,0},{0,6,6,0},{0,0,6,0},{0,0,0,0}},
	{{0,7,0,0},{0,7,7,7},{0,0,0,0},{0,0,0,0}},
	{{0,0,0,0},{0,8,8,8},{0,8,0,0},{0,0,0,0}}
	};

	for (int i = 0; i < 4; i++)			// 4x4 블럭 멤버 변수 초기화
	{
		for (int j = 0; j < 4; j++)
		{
			BLock[i][j] = 0;
		}
	}

	//srand(unsigned(time(NULL)));		// 시간 난수 초기화

	//Random<int> gen(-1000, 1000);
	//auto num = gen();

	//mt19937 engine((unsigned int)time(NULL));			// MT19937 난수 엔진 초기화
	//uniform_int_distribution<int> distribution(0, 10000);	// 생성 범위
	//auto generator = bind(distribution, engine);			// 난수 변수 생성

	long sum = 0;
	chrono::system_clock::time_point start = chrono::system_clock::now();
	for (int i = 0; i < 1000000; i++) {
		sum += i;
	}
	chrono::system_clock::time_point end = chrono::system_clock::now();
	chrono::nanoseconds nano = end - start;

	switch (nano.count() % 7)
	{
	case 0:
		CopyBlock(BlockShape[0]);
		break;
	case 1:
		CopyBlock(BlockShape[1]);
		break;
	case 2:
		CopyBlock(BlockShape[2]);
		break;
	case 3:
		CopyBlock(BlockShape[3]);
		break;
	case 4:
		CopyBlock(BlockShape[4]);
		break;
	case 5:
		CopyBlock(BlockShape[5]);
		break;
	case 6:
		CopyBlock(BlockShape[6]);
		break;
	default:
		break;
	}
}

Block::~Block()
{
}

void Block::CopyBlock(int copy[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			BLock[i][j] = copy[i][j];
		}
	}
}

int Block::getBpart(int x, int y)
{
	return BLock[x][y];
}

void Block::rotate()
{
	int fix[4][4] = { 0, };

	for (int i = 0; i < 3; i++)
	{
		fix[i][3] = BLock[0][i];
		fix[3][3 - i] = BLock[i][3];
		fix[3 - i][0] = BLock[3][3 - i];
		fix[0][i] = BLock[3 - i][0];
	}
	for (int i = 1; i < 3; i++)
	{
		fix[i][2] = BLock[1][i];
		fix[3 - i][1] = BLock[2][3 - i];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			BLock[i][k] = fix[i][k];
		}
	}
}

void Block::reverserotate()
{
	int fix[4][4] = { 0, };

	for (int i = 0; i < 3; i++)
	{
		fix[3][i] = BLock[i][0];
		fix[3 - i][3] = BLock[3][i];
		fix[0][3 - i] = BLock[3 - i][3];
		fix[i][0] = BLock[0][3 - i];
	}
	for (int i = 1; i < 3; i++)
	{
		fix[2][i] = BLock[i][1];
		fix[1][3 - i] = BLock[3 - i][2];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			BLock[i][k] = fix[i][k];
		}
	}
}
