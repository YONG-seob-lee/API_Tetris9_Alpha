#include "PlayerVsPlayer.h"

PlayerVsPlayer::PlayerVsPlayer() : GameMode()
{
	t1 = new Tetris;
	t2 = new Tetris;
}

PlayerVsPlayer::~PlayerVsPlayer()
{
	delete t1;
	delete t2;
}

void PlayerVsPlayer::LoadAll(HANDLES h_Base)
{
	ResourceMainBG(h_Base);
	Load(h_TetrisBoard, L"image/tetrisboard.bmp", h_Base);

	t1->LoadTetris(h_Base);
	t2->LoadTetris(h_Base);
}

void PlayerVsPlayer::InitTetris()
{
	t1x = 200;
	t1y = 130;
	t2x = 1100;
	t2y = 130;
	t1->InitAll(t1x, t1y);
	t2->InitAll(t2x, t2y);
}

void PlayerVsPlayer::InitData()
{
	u_Main.Frame = 0;
	u_Main.MaxFrame = MAIN_BG_FRAME;
	InitTetris();
}

void PlayerVsPlayer::ResourceMainBG(HANDLES h_Base)
{
	WCHAR name[40];
	for (int i = 0; i < MAIN_BG_FRAME; i++)
	{
		wsprintf(name, L"image/main/main%d.bmp", i);
		h_Main[i].hbmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		h_Main[i].dc = CreateCompatibleDC(h_Base.dc);
		GetObject(h_Main[i].hbmp, sizeof(BITMAP), &h_Main[i].bit);

		h_Main[i].hOldbmp = (HBITMAP)SelectObject(h_Main[i].dc, h_Main[i].hbmp);
	}
}

void PlayerVsPlayer::DrawAll(HANDLES h_Base, RECT m_rtClient)
{
	DrawMain(h_Base);
	DrawTetrisBoard(h_Base);
	t1->DrawPersonal(h_Base);
	t2->DrawPersonal(h_Base);

}

void PlayerVsPlayer::DrawMain(HANDLES h_Base)
{
	StretchBlt(h_Base.dc, 0, 0, XRES, YRES, h_Main[u_Main.Frame].dc, 0, 0, XRES, YRES, SRCCOPY);
}

void PlayerVsPlayer::DrawTetrisBoard(HANDLES h_Base)
{
	TransparentBlt(h_Base.dc, t1x - 67, t1y + 91, BOARD_X, BOARD_Y, h_TetrisBoard.dc, 0, 0, BOARD_X, BOARD_Y, RGB(255, 0, 255));
	TransparentBlt(h_Base.dc, t2x - 67, t2y + 91, BOARD_X, BOARD_Y, h_TetrisBoard.dc, 0, 0, BOARD_X, BOARD_Y, RGB(255, 0, 255));
}

void PlayerVsPlayer::UpdateAll()
{
	UpdateMain();
	t1->UpdateAutoDown();
	t1->UpdateMap();
	t2->UpdateAutoDown();
	t2->UpdateMap();
}

void PlayerVsPlayer::UpdateMain()
{
	if (UpdateCheck(u_Main, 40) == TRUE)
	{
		u_Main.Frame++;
		if (u_Main.Frame >= u_Main.MaxFrame)
			u_Main.Frame = 1;
	}
}

BOOL PlayerVsPlayer::CheckOver()
{
	if (t1->UpdateGetOver() == FALSE)	return FALSE;

	return TRUE;
}

void PlayerVsPlayer::keyhandle(WPARAM wParam)
{
	switch (wParam)
	{
	// PLAYER1
	case 'W':
		t1->Rotate();
		break;

	case 'S':
		t1->goDown();
		break;

	case 'A':
		t1->goLeft();
		break;

	case 'D':
		t1->goRight();
		break;

	case VK_SPACE:
		t1->goStraightDown();
		break;

	case 'R':
		t1->Rotate();
		break;

	case VK_CONTROL:
		t1->SwapBlock();
		break;

	case 'E':
		t1->holdBlock();
		break;

	// PLAYER2
	case VK_UP:	
		t2->Rotate();
		break;

	case VK_DOWN:
		t2->goDown();
		break;

	case VK_LEFT:
		t2->goLeft();
		break;

	case VK_RIGHT:
		t2->goRight();
		break;

	case VK_NUMPAD0:
		t2->goStraightDown();
		break;

	case VK_LSHIFT:
		t2->SwapBlock();
		break;

	default:
		break;
	}
}