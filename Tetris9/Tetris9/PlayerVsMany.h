#pragma once
#include "GameMode.h"
#include "framework.h"

class PlayerVsMany :
	public GameMode
{
private:
	Tetris* tetris[9];

	int TX;			// Player Point
	int TY;
	int tx[8];		// Computers Point
	int ty[8];

	HANDLES h_Main[MAIN_BG_FRAME];
	HANDLES h_TetrisBoard;

	UPDATE u_Main;


public:
	PlayerVsMany();
	~PlayerVsMany();

	void LoadAll(HANDLES h_Base);
	void InitTetris();
	void InitData();
	void ResourceMainBG(HANDLES h_Base);


	void DrawAll(HANDLES h_Base, RECT m_rtClient);
	void DrawMain(HANDLES h_Base);
	void DrawTetrisBoard(HANDLES h_Base);

	void UpdateAll();
	void UpdateMain();
	BOOL CheckOver();

	void keyhandle(WPARAM wParam);
};

