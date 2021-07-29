#pragma once
#include "framework.h"
#include "Block.h"

class BlockList
{
private:
	BlockRail* CreateNode(Block* data);
	BlockRail* ptr;
	BlockRail* ptrHead;

public:
	BlockList();
	~BlockList();

	void InsertAddHead(Block* data);
	void InsertAddTail(Block* data);
	void DeleteHead();
	void SwapNode();		// 헤드랑 두번째꺼랑 바꾸는 스왑함수
	void DelNode();
	void SetData(Block* DaTa);

	Block* getBlock();	// 맨 앞쪽(헤드) 에 있는 데이터 보내기 함수
	Block* getNextBlock(int count);
};

