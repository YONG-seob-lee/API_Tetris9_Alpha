#pragma once
#include "GameMode.h"
#include "framework.h"

class PlayerVsPlayer :
	public GameMode
{
private:
	Tetris* t1;
	Tetris* t2;

	int t1x;
	int t1y;
	int t2x;
	int t2y;

	HANDLES h_Main[MAIN_BG_FRAME];
	HANDLES h_TetrisBoard;

	UPDATE u_Main;

public:
	PlayerVsPlayer();
	~PlayerVsPlayer();

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

