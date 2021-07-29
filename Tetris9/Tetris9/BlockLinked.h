#pragma once
#include "Block.h"
#include "BlockList.h"
#include "framework.h"

class BlockLinked
{
private:
	BlockList* MakeList;

public:
	BlockLinked();
	~BlockLinked();

	void Swap();		// 헤드데이터랑 두번째데이터 스왑
	void RotateH();		// 헤드데이터 시계방향으로 회전
	void CRotateH();	// 헤드데이터 반시계방향으로 회전
	void SetLinked();	// 헤드부분 빼고 다시 추가하기버전
	void SetData(Block* DaTa);		// 리스트안의 데이터 변경하기
	int getBpart(int x, int y);
	Block* getB();
	Block* getNextB(int count);
};

