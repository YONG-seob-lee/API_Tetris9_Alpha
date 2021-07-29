#pragma once
#include "BlockLinked.h"
#include "framework.h"

class Tetris
{
private:
	BlockLinked* BLinked;
	Block* HoldBlock;		// 홀드 블럭을 저장할 공간
	int PositionX;			// 테트리스의 시작포인트 x
	int PositionY;			// 테트리스의 시작 포인트 y
	int MapData[24][12];
	int BlockData[4][4];	// 블럭 데이터 삽입
	int checkMap[4][4];		// 블럭과 맵간의 충돌을 확인할 블럭배열
	int HBlock[4][4];		// 홀드블럭 데이터를 저장할 변수
	int HoldFirst;		// 홀드블럭 최초 사용했는지 확인하기 위한 변수
	int posX;				// 블럭 데이터와 맵 데이터의 좌표
	int posY;				// 블럭 데이터와 맵 데이터의 좌표

	// Handles
	HANDLES h_Block;
	HANDLES h_TransBlock;

	// Update
	UPDATE u_Block;
	UPDATE u_MAP;
	UPDATE u_AI;
	UPDATE u_CheckOver;
	UPDATE u_TransBlock;

public:
	Tetris();
	~Tetris();

	// init
	void LoadTetris(HANDLES h_Base);
	void InitAll(int x, int y);
	void InitPosition(int x, int y);
	void InitMap();
	void InitBlock();
	void InitCM();
	void SetBlock();			// 블럭 생성 및 위치 초기화

	// draw
	void DrawPersonal(HANDLES h_Base);
	void DrawSmall(HANDLES h_Base);

	void DrawMap(HANDLES h_Base, int size);
	void DrawBlock(HANDLES h_Base, int size);
	void DrawBottomBlock(HANDLES h_Base, int size);
	void DrawHoldBlock(HANDLES h_Base, int size);		// 홀드한 블록 그리기 함수
	void DrawNextBlock(HANDLES h_Base, int size);
	void DrawSmallHoldBlock(HANDLES h_Base);
	void DrawSmallNextBlock(HANDLES h_Base);

	// check util
	bool CheckWall();
	void CheckLine();
	void CheckDeadLine();

	// block move
	void goLeft();
	void goRight();
	void goDown();
	void goStraightDown();
	void Rotate();
	void CRotate();
	void SwapBlock();
	void holdBlock();

	void UpdateAutoDown();
	void UpdateMap();
	BOOL UpdateGetOver();

	//////////// AI	/////////////
	void UpdateRandomMove();
	void Update_AI();
	BOOL CheckFillLine();
	BOOL CheckFillBlock();

	void Load(HANDLES& h, LPCWSTR name, HANDLES h_Base);
};

