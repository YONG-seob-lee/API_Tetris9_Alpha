#include "PlayerVsMany.h"

PlayerVsMany::PlayerVsMany() : GameMode()
{
	for (int i = 0; i < 9; i++)
	{
		tetris[i] = new Tetris;
	}
}

PlayerVsMany::~PlayerVsMany()
{
	for (int i = 0; i < 9; i++)
	{
		delete tetris[i];
	}
}

void PlayerVsMany::LoadAll(HANDLES h_Base)
{
	ResourceMainBG(h_Base);
	Load(h_TetrisBoard, L"image/tetrisboard.bmp", h_Base);

	for (int i = 0; i < 9; i++)
	{
		tetris[i]->LoadTetris(h_Base);
	}
}

void PlayerVsMany::InitTetris()
{
	// UI part
	int part1_x = 60;
	int part1_y = 100;
	int part2_x = 60;
	int part2_y = YRES / 2 + 60;
	int part3_x = XRES / 2 + 330;
	int part3_y = 100;
	int part4_x = XRES / 2 + 330;
	int part4_y = YRES / 2 + 60;
	TX = XRES / 2 - BOARD_X / 2 + 60;
	TY = YRES / 2 - BOARD_Y / 2 - 40;


	// BLOCK part
	for (int i = 1; i < 3; i++)
	{
		tx[i] = part1_x + (i - 1) *(SMALL_BOARD_INTERVAL + SMALL_BOARD_X);
		ty[i] = part1_y;
	}
	for (int i = 3; i < 5; i++)
	{
		tx[i] = part2_x + (i - 3) *(SMALL_BOARD_INTERVAL + SMALL_BOARD_X);
		ty[i] = part2_y ;
	}
	for (int i = 5; i < 7; i++)
	{
		tx[i] = part3_x + (i - 5) *(SMALL_BOARD_INTERVAL + SMALL_BOARD_X);
		ty[i] = part3_y;
	}
	for (int i = 7; i < 9; i++)
	{
		tx[i] = part4_x + (i - 7) *(SMALL_BOARD_INTERVAL + SMALL_BOARD_X);
		ty[i] = part4_y;
	}
	tetris[0]->InitAll(TX, TY);
	for (int i = 1; i < 9; i++)
	{
		tetris[i]->InitAll(tx[i], ty[i]);
	}
}

void PlayerVsMany::InitData()
{
	u_Main.Frame = 0;
	u_Main.MaxFrame = MAIN_BG_FRAME;
	InitTetris();
}

void PlayerVsMany::ResourceMainBG(HANDLES h_Base)
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

void PlayerVsMany::DrawAll(HANDLES h_Base, RECT m_rtClient)
{
	DrawMain(h_Base);
	DrawTetrisBoard(h_Base);
	tetris[0]->DrawPersonal(h_Base);
	for (int i = 1; i < 9; i++)
	{
		tetris[i]->DrawSmall(h_Base);
	}
}

void PlayerVsMany::DrawMain(HANDLES h_Base)
{
	StretchBlt(h_Base.dc, 0, 0, XRES, YRES, h_Main[u_Main.Frame].dc, 0, 0, XRES, YRES, SRCCOPY);

}

void PlayerVsMany::DrawTetrisBoard(HANDLES h_Base)
{
	TransparentBlt(h_Base.dc, TX - 66, TY + 90, BOARD_X, BOARD_Y, h_TetrisBoard.dc, 0, 0, BOARD_X, BOARD_Y, RGB(255, 0, 255));
	for (int i = 1; i < 9; i++)
	{
		TransparentBlt(h_Base.dc, tx[i] - 35, ty[i] + 43, SMALL_BOARD_X, SMALL_BOARD_Y, h_TetrisBoard.dc, 0, 0, BOARD_X, BOARD_Y, RGB(255, 0, 255));
	}
}

void PlayerVsMany::UpdateAll()
{
	UpdateMain();
	tetris[0]->UpdateAutoDown();
	tetris[0]->UpdateMap();
	for (int i = 1; i < 9; i++)
	{
		tetris[i]->UpdateAutoDown();
		tetris[i]->UpdateMap();
		tetris[i]->Update_AI();
	}
}

void PlayerVsMany::UpdateMain()
{
	if (UpdateCheck(u_Main, 40) == TRUE)
	{
		u_Main.Frame++;
		if (u_Main.Frame >= u_Main.MaxFrame)
			u_Main.Frame = 1;
	}
}

BOOL PlayerVsMany::CheckOver()
{
	if (tetris[0]->UpdateGetOver() == FALSE)	return FALSE;

	return TRUE;
}

void PlayerVsMany::keyhandle(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:
		tetris[0]->Rotate();
		break;

	case VK_DOWN:
		tetris[0]->goDown();
		break;

	case VK_LEFT:
		tetris[0]->goLeft();
		break;

	case VK_RIGHT:
		tetris[0]->goRight();
		break;

	case VK_SPACE:
		tetris[0]->goStraightDown();
		break;

	case 'R':
		tetris[0]->Rotate();
		break;

	case VK_CONTROL:
		tetris[0]->SwapBlock();
		break;

	case 'E':
		tetris[0]->holdBlock();
		break;

	default:
		break;
	}
}
