#pragma once
#include "Tetris.h"
#include "framework.h"

class GameMode
{
private:

public:
	GameMode();
	~GameMode();

	virtual void LoadAll(HANDLES h_Base);
	virtual void InitTetris();
	virtual void InitData();
	virtual void ResourceMainBG(HANDLES h_Base);

	virtual void DrawAll(HANDLES h_Base, RECT m_rtClient);
	virtual void DrawMain(HANDLES h_Base);
	virtual void DrawTetrisBoard(HANDLES h_Base);

	virtual void UpdateAll();
	virtual void UpdateMain();
	virtual BOOL CheckOver();

	virtual void keyhandle(WPARAM wParam);
	virtual void Load(HANDLES& h, LPCWSTR name, HANDLES h_Base);
	virtual BOOL UpdateCheck(UPDATE& up, DWORD tick);
};
