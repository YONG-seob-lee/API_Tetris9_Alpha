#include "BlockList.h"



BlockList::BlockList()
{
	ptr = NULL;
	ptrHead = NULL;
}

BlockList::~BlockList()
{
}

BlockRail * BlockList::CreateNode(Block* data)
{
	BlockRail* ptr = new BlockRail;		// ptr 포인터 생성후 힙변수 저장
	ptr->data = data;		// 새로만든 포인터의 데이터 초기화
	ptr->pNode = NULL;		// 새로만든 포인터의 pNode 초기화
	return ptr;				// 포인터(주소값) 반환
}

void BlockList::InsertAddHead(Block* data)
{
	BlockRail* ptr;
	if (ptrHead == NULL)	ptrHead = CreateNode(data);	// 헤드ptr 이 가리키는것이 없으면(NULL) 새로 노드 생성

	else
	{
		ptr = CreateNode(data);		// ptr 생성하고
		ptr->pNode = ptrHead;		// ptr의 노드가 ptrHead 포인터를 가리키게 하고
		ptrHead = ptr;				// ptrHead 포인터를 ptr이 가리키는곳으로 옮김
	}
}

void BlockList::InsertAddTail(Block* data)
{
	BlockRail* ptr;

	if (ptrHead == NULL)	ptrHead = CreateNode(data);	// 헤드ptr 이 가리키는것이 없으면(NULL) 새로 노드 생성

	else
	{
		ptr = ptrHead;						// 일단 ptr포인터를 Head 포인터로 옮겨두고
		while (ptr->pNode != NULL)			// ptr이 pNode를 따라 노드의 마지막값이 null 이 되는곳까지 이동
		{
			ptr = ptr->pNode;				// 다 이동한 뒤에 마지막 노드를 ptr포인터에 연결
		}
		ptr->pNode = CreateNode(data);				// 연결 후에 ptr 노드 생성
	}
}

void BlockList::DeleteHead()
{
	BlockRail* ptr;
	BlockRail* ptr2;
	if (ptrHead == NULL)	return;

	ptr = ptr2 = ptrHead;		// ptr 초기화
	ptr2 = ptr2->pNode;			// ptr2 한 칸 움직이기
	ptrHead = ptr2;				// ptrHead 한 칸 움직이기
	delete ptr;
}

void BlockList::SwapNode()
{
	BlockRail* ptr;
	BlockRail* ptr2;
	ptr = ptr2 = ptrHead;	//ptr들 초기화
	ptr2 = ptr2->pNode;	// ptr2 한칸 전진
	ptr->pNode = ptr2->pNode;	// ptr의 노드가 ptr2가 가리키는 포인터로 설정
	ptr2->pNode = ptr;	// ptr2의 노드를 이전 노드를 가리키게 설정
	ptrHead = ptr2;	// 헤드 옮기기
}

void BlockList::DelNode()
{
	BlockRail* ptr;
	for (ptr = ptrHead; ptrHead != NULL; ptr = ptrHead)
	{
		ptrHead = ptrHead->pNode;
		if (ptr != NULL)
			delete ptr;
	}
}

void BlockList::SetData(Block* DaTa)
{
	ptrHead->data = DaTa;
}

Block * BlockList::getBlock()
{
	BlockRail* ptr;
	ptr = ptrHead;
	return ptr->data;
}

Block * BlockList::getNextBlock(int count)
{
	BlockRail* ptr;
	ptr = ptrHead;
	for (int i = 0; i < count; i++)
	{
		ptr = ptr->pNode;
	}
	return ptr->data;
}
