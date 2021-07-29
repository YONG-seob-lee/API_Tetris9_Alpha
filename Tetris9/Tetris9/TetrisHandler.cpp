#include "TetrisHandler.h"
#include "framework.h"

TetrisHandler::TetrisHandler()
{
	mode = PLAYER_COM;
	pvc = new PlayerVsCom;
	pvp = new PlayerVsPlayer;
	pvm = new PlayerVsMany;

	InitMode();
}

TetrisHandler::~TetrisHandler()
{
	delete pvc;
	delete pvp;
	delete pvm;
}

void TetrisHandler::DrawAll(HDC hdc, HANDLES h_Base, RECT m_rtClient)
{
	switch (mode)
	{
	case PLAYER_COM:
		// 1 vs COM  mode
		DrawMenuBG(h_Base);
		DrawVS(h_Base, m_rtClient);
		DrawPlayer(h_Base, m_rtClient);
		DrawPVC(h_Base, m_rtClient);
		DrawPVP(h_Base, m_rtClient);
		DrawPVM(h_Base, m_rtClient);
		DrawBPvc(h_Base, m_rtClient);
		break;

	case PLAYER_PLAYER:
		// 1 vs 1 mode
		DrawMenuBG(h_Base);
		DrawVS(h_Base, m_rtClient);
		DrawPlayer(h_Base, m_rtClient);
		DrawPVC(h_Base, m_rtClient);
		DrawPVP(h_Base, m_rtClient);
		DrawPVM(h_Base, m_rtClient);
		DrawBPvp(h_Base, m_rtClient);
		break;

	case PLAYER_MANY:
		// 1 vs Many(8) mode
		DrawMenuBG(h_Base);
		DrawVS(h_Base, m_rtClient);
		DrawPlayer(h_Base, m_rtClient);
		DrawPVC(h_Base, m_rtClient);
		DrawPVP(h_Base, m_rtClient);
		DrawPVM(h_Base, m_rtClient);
		DrawBPvm(h_Base, m_rtClient);
		break;

	case GAME_PLAY:
		DrawPlay(h_Base, m_rtClient);
		break;

	default:
		break;
	}
}

void TetrisHandler::DrawMenuBG(HANDLES h_Base)
{
	StretchBlt(h_Base.dc, 0, 0, XRES, YRES, h_MenuBG.dc, h_MenuBG.pt.x, 0, XRES, YRES, SRCCOPY);
}

void TetrisHandler::InitMode()
{

	h_MenuBG.pt.x = XRES * 2;
	h_MenuBG.pt.y = 0;

	u_BPvc.bTrigger = FALSE;
	u_BPvp.bTrigger = FALSE;
	u_BPvm.bTrigger = FALSE;

	u_PVC.bTrigger = FALSE;
	u_PVP.bTrigger = FALSE;
	u_PVM.bTrigger = FALSE;

	pvc->InitData();
	pvp->InitData();
	pvm->InitData();
}

void TetrisHandler::InitTetrisResource(HANDLES h_Base)
{
	Load(h_MenuBG, L"image/menubg.bmp", h_Base);
	Load(h_VS, L"image/vs.bmp", h_Base);
	Load(h_Player, L"image/player.bmp", h_Base);
	Load(h_Pvc, L"image/com.bmp", h_Base);
	Load(h_Pvp, L"image/vsplayer.bmp", h_Base);
	Load(h_Pvm, L"image/many.bmp", h_Base);
	Load(h_BPvc, L"image/bcom.bmp", h_Base);
	Load(h_BPvp, L"image/bvsplayer.bmp", h_Base);
	Load(h_BPvm, L"image/bmany.bmp", h_Base);

	pvc->LoadAll(h_Base);
	pvp->LoadAll(h_Base);
	pvm->LoadAll(h_Base);
}

void TetrisHandler::UpdateAll()
{
	switch (mode)
	{
	case PLAYER_COM:
		UpdateMenuBG();
		UpdateBmode();
		break;
	case PLAYER_PLAYER:
		UpdateMenuBG();
		UpdateBmode();
		break;

	case PLAYER_MANY:
		UpdateMenuBG();
		UpdateBmode();
		break;

	case GAME_PLAY:
		UpdatePlay();
		break;

	default:
		break;
	}
}

void TetrisHandler::DrawVS(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 - h_VS.bit.bmWidth / 2;
	int y = m_rtClient.bottom / 2 - h_VS.bit.bmHeight / 2;
	TransparentBlt(h_Base.dc, x, y, h_VS.bit.bmWidth, h_VS.bit.bmHeight, h_VS.dc, 0, 0, h_VS.bit.bmWidth, h_VS.bit.bmHeight, RGB(255, 0, 255));
}

void TetrisHandler::DrawPlayer(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 - h_Player.bit.bmWidth / 2 - 470;
	int y = m_rtClient.bottom / 2 - h_Player.bit.bmHeight / 2;
	TransparentBlt(h_Base.dc, x, y, h_Player.bit.bmWidth, h_Player.bit.bmHeight, h_Player.dc, 0, 0, h_Player.bit.bmWidth, h_Player.bit.bmHeight, RGB(255, 0, 255));
}

void TetrisHandler::DrawPVC(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 + 250;
	int y = m_rtClient.bottom / 2 - h_Pvc.bit.bmHeight / 2 - 300;
	TransparentBlt(h_Base.dc, x, y, h_Pvc.bit.bmWidth, h_Pvc.bit.bmHeight, h_Pvc.dc, 0, 0, h_Pvc.bit.bmWidth, h_Pvc.bit.bmHeight, RGB(255, 0, 255));
}

void TetrisHandler::DrawPVP(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 + 250;
	int y = m_rtClient.bottom / 2 - h_Pvp.bit.bmHeight / 2;
	BitBlt(h_Base.dc, x, y, h_Pvp.bit.bmWidth, h_Pvp.bit.bmHeight, h_Pvp.dc, 0, 0, SRCCOPY);
}

void TetrisHandler::DrawPVM(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 + 250;
	int y = m_rtClient.bottom / 2 - h_Pvm.bit.bmHeight / 2 + 300;
	BitBlt(h_Base.dc, x, y, h_Pvm.bit.bmWidth, h_Pvm.bit.bmHeight, h_Pvm.dc, 0, 0, SRCCOPY);
}

void TetrisHandler::DrawBPvc(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 + 200;
	int y = m_rtClient.bottom / 2 - h_BPvc.bit.bmHeight / 2 - 300;
	TransparentBlt(h_Base.dc, x, y, h_BPvc.bit.bmWidth, h_BPvc.bit.bmHeight, h_BPvc.dc, 0, 0, h_BPvc.bit.bmWidth, h_BPvc.bit.bmHeight, RGB(255, 0, 255));
}

void TetrisHandler::DrawBPvp(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 + 200;
	int y = m_rtClient.bottom / 2 - h_BPvp.bit.bmHeight / 2;
	BitBlt(h_Base.dc, x, y, h_BPvp.bit.bmWidth, h_BPvp.bit.bmHeight, h_BPvp.dc, 0, 0, SRCCOPY);
}

void TetrisHandler::DrawBPvm(HANDLES h_Base, RECT m_rtClient)
{
	int x = m_rtClient.right / 2 + 200;
	int y = m_rtClient.bottom / 2 - h_BPvm.bit.bmHeight / 2 + 300;
	BitBlt(h_Base.dc, x, y, h_BPvm.bit.bmWidth, h_BPvm.bit.bmHeight, h_BPvm.dc, 0, 0, SRCCOPY);
}

void TetrisHandler::DrawPlay(HANDLES h_Base, RECT m_rtClient)
{
	if (u_PVC.bTrigger == TRUE)	pvc->DrawAll(h_Base, m_rtClient);
	if (u_PVP.bTrigger == TRUE)	pvp->DrawAll(h_Base, m_rtClient);
	if (u_PVM.bTrigger == TRUE)	pvm->DrawAll(h_Base, m_rtClient);
}

void TetrisHandler::UpdateMenuBG()
{
	if (UpdateCheck(u_MenuBG, 500) == TRUE)
	{
		h_MenuBG.pt.x -= 40;
		if (h_MenuBG.pt.x < 0)
		{
			h_MenuBG.pt.x = XRES * 2;
		}
	}
}

void TetrisHandler::UpdateBmode()
{
	switch (mode)
	{
	case PLAYER_COM:
		u_BPvc.bTrigger = TRUE;
		u_BPvp.bTrigger = FALSE;
		u_BPvm.bTrigger = FALSE;
		break;

	case PLAYER_PLAYER:
		u_BPvc.bTrigger = FALSE;
		u_BPvp.bTrigger = TRUE;
		u_BPvm.bTrigger = FALSE;
		break;

	case PLAYER_MANY:
		u_BPvc.bTrigger = FALSE;
		u_BPvp.bTrigger = FALSE;
		u_BPvm.bTrigger = TRUE;
		break;

	default:
		break;
	}
}
 
void TetrisHandler::UpdatePVC()
{
	if (u_BPvc.bTrigger == TRUE)
	{
		u_PVC.bTrigger = TRUE;
		mode = GAME_PLAY;
	}
	else
	{
		return;
	}
}

void TetrisHandler::UpdatePVP()
{
	if (u_BPvp.bTrigger == TRUE)
	{
		u_PVP.bTrigger = TRUE;
		mode = GAME_PLAY;
	}
	else
	{
		return;
	}
}

void TetrisHandler::UpdatePVM()
{
	if (u_BPvm.bTrigger == TRUE)
	{
		u_PVM.bTrigger = TRUE;
		mode = GAME_PLAY;
	}
	else
	{
		return;
	}
}

void TetrisHandler::UpdatePlay()
{
	if (u_PVC.bTrigger == TRUE)	pvc->UpdateAll();

	if (u_PVP.bTrigger == TRUE)	pvp->UpdateAll();

	if (u_PVM.bTrigger == TRUE)	pvm->UpdateAll();
}

BOOL TetrisHandler::Updateover()
{
	if (pvc->CheckOver() == FALSE)	return FALSE;
	if (pvp->CheckOver() == FALSE)	return FALSE;
	if (pvm->CheckOver() == FALSE)	return FALSE;
	return TRUE;
}


void TetrisHandler::setModeUP()
{
	mode--;
	if (mode < 1)	mode = 3;
}

void TetrisHandler::setModeDown()
{
	mode++;
	if (mode > 3)	mode = 1;
}

void TetrisHandler::keyhandle(WPARAM wParam)
{
	switch (mode)
	{
	case PLAYER_COM:
		switch (wParam)
		{
		case VK_UP:
			setModeUP();
			break;

		case VK_DOWN:
			setModeDown();
			break;

		case 'W':
			setModeUP();
			break;

		case 'S':
			setModeDown();
			break;

		case VK_SPACE:
			UpdatePVC();
			UpdatePVP();
			UpdatePVM();
			break;
		case VK_RETURN:
			UpdatePVC();
			UpdatePVP();
			UpdatePVM();
			break;

		default:
			break;
		}
		break;
	case PLAYER_PLAYER:
		switch (wParam)
		{
		case VK_UP:
			setModeUP();
			break;

		case VK_DOWN:
			setModeDown();
			break;

		case 'W':
			setModeUP();
			break;

		case 'S':
			setModeDown();
			break;

		case VK_SPACE:
			UpdatePVC();
			UpdatePVP();
			UpdatePVM();
			break;
		case VK_RETURN:
			UpdatePVC();
			UpdatePVP();
			UpdatePVM();
			break;

		default:
			break;
		}
		break;

	case PLAYER_MANY:
		switch (wParam)
		{
		case VK_UP:
			setModeUP();
			break;

		case VK_DOWN:
			setModeDown();
			break;

		case 'W':
			setModeUP();
			break;

		case 'S':
			setModeDown();
			break;

		case VK_SPACE:
			UpdatePVC();
			UpdatePVP();
			UpdatePVM();
			break;
		case VK_RETURN:
			UpdatePVC();
			UpdatePVP();
			UpdatePVM();
			break;

		default:
			break;
		}
		break;

	case GAME_PLAY:
		if (u_PVC.bTrigger == TRUE)				pvc->keyhandle(wParam);
		else if (u_PVP.bTrigger == TRUE)		pvp->keyhandle(wParam);
		else if (u_PVM.bTrigger == TRUE)		pvm->keyhandle(wParam);
		else
		{
			break;
		}	

		break;
	default:
		break;
	}
}

void TetrisHandler::Load(HANDLES & h, LPCWSTR name, HANDLES h_Base)
{
	h.hbmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (h.hbmp == NULL)
	{
		MessageBox(NULL, name, L"비트맵 로딩 에러", MB_OK);
	}
	h.dc = CreateCompatibleDC(h_Base.dc);//베이스에 호환되는 DC 얻기 
	h.hOldbmp = (HBITMAP)SelectObject(h.dc, h.hbmp);//dc 랑 비트맵이랑 연결

	GetObject(h.hbmp, sizeof(BITMAP), &h.bit);
}

BOOL TetrisHandler::UpdateCheck(UPDATE & up, DWORD tick)
{
	up.mEndTick = GetTickCount();
	if (up.mEndTick - up.mStartTick > tick)
	{
		up.mStartTick = up.mEndTick;
		return TRUE;
	}
	return FALSE;
}