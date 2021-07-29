#include "TetrisManager.h"

TetrisManager::TetrisManager()
{
	// Frist of time initial
	InitFirst();
}

TetrisManager::~TetrisManager()
{
}

void TetrisManager::GameLoop(HDC hdc)
{
	DrawAll(hdc);		// Enter Draw Function
	Update();			// Enter Update Function
}

void TetrisManager::DrawAll(HDC hdc)
{
	switch (GameState)
	{
	case GAME_TITLE:
		DrawTitle();
		DrawNewBG();
		DrawFlash();
		DrawPressBig();
		break;

	case GAME_MODE:
		handle.DrawAll(hdc, h_Base, m_rtClient);
		DrawFade();
		break;
	case GAME_OVER:
		return;
	default:
		break;
	}

	BitBlt(hdc,	0, 0, h_Base.bit.bmWidth, h_Base.bit.bmHeight, h_Base.dc, 0, 0,	SRCCOPY);
}

void TetrisManager::Update()
{
	switch (GameState)
	{
	case GAME_TITLE:
		UpdateTitle();
		UpdateNewBG();
		UpdateFlash();
		UpdatePressBig();
		break;

	case GAME_MODE:
 		handle.UpdateAll();
		GetOver();
		UpdateFade();
		break;
	case GAME_OVER:
		return;
	default:
		break;
	}
}

void TetrisManager::setGameState()
{
	GameState = GAME_MODE;
}


void TetrisManager::InitFirst()
{
	GameState = GAME_TITLE;		// 게임의 큰 목차 설정을 위한 변수 초기화
}

void TetrisManager::InitResource()
{
	h_Base.hbmp = (HBITMAP)LoadImage(NULL, L"image/base.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// HANDLES Base 에서 hbmp 핸들 사용하기 위한 초기화
	h_Base.dc = CreateCompatibleDC(NULL);
	// HANDLES Base 에서 DeviceContext 값 초기화 (base 이므로 디폴트값)
	h_Base.hOldbmp = (HBITMAP)SelectObject(h_Base.dc, h_Base.hbmp);
	// hbmp 와 dc 간의 동기화
	GetObject(h_Base.hbmp, sizeof(BITMAP), &h_Base.bit);

	h_Alpha.hbmp = (HBITMAP)LoadImage(NULL, L"image/base.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);//비트맵 핸들 얻어오는 과정 
	h_Alpha.dc = CreateCompatibleDC(NULL);//화면에 호환되는 DC 얻기 
	h_Alpha.hOldbmp = (HBITMAP)SelectObject(h_Alpha.dc, h_Alpha.hbmp);//dc 랑 비트맵이랑 연결
	GetObject(h_Alpha.hbmp, sizeof(BITMAP), &h_Alpha.bit);
	h_Alpha.bf.AlphaFormat = 0;
	h_Alpha.bf.BlendFlags = 0;
	h_Alpha.bf.BlendOp = 0;
	h_Alpha.bf.SourceConstantAlpha = 255;

	InitResourceTitleBG();

	Load(h_newBG, L"image/newBG.bmp");
	Load(h_PressSmall, L"image/presssmall.bmp");
	Load(h_PressBig, L"image/pressbig.bmp");
	Load(h_Flash, L"image/flash.bmp");

	Load(h_Fade, L"image/alpha.bmp");
	h_Fade.bf.AlphaFormat = 0;
	h_Fade.bf.BlendFlags = 0;
	h_Fade.bf.BlendOp = 0;
	h_Fade.bf.SourceConstantAlpha = 255;//불투명...0완전투명 반투명 127

	handle.InitTetrisResource(h_Base);
}

void TetrisManager::InitData()
{
	InitTick(u_TitleBG);
	u_TitleBG.MaxFrame = TITLE_BG_FRAME;		// 타이틀 배경의 최대 프레임 초기화
	u_TitleBG.Frame = 0;						// 타이틀 배경의 최초 프레임 초기화
	u_PressBig.bTrigger = TRUE;
	u_NewBG.bTrigger = FALSE;
	u_Flash.aEndTick = u_Flash.aStartTick = GetTickCount();
	u_Flash.bTrigger = FALSE;
	u_Flash.Frame = -1;
	u_Flash.MaxFrame = 7;
	u_Flash.size = FLASH_SIZE;
	u_Flash.tricnt = 0;
	
	handle.InitMode();

	InitTick(u_Fade);
	h_Fade.bf.SourceConstantAlpha = 255;

}

void TetrisManager::InitResourceTitleBG()
{
	WCHAR name[40];
	for (int i = 0; i < TITLE_BG_FRAME; i++)
	{
		wsprintf(name, L"image/title/title%d.bmp", i);
		h_TitleBG[i].hbmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		h_TitleBG[i].dc = CreateCompatibleDC(h_Base.dc);
		GetObject(h_TitleBG[i].hbmp, sizeof(BITMAP), &h_TitleBG[i].bit);

		h_TitleBG[i].hOldbmp = (HBITMAP)SelectObject(h_TitleBG[i].dc, h_TitleBG[i].hbmp);
	}
}

void TetrisManager::DrawTitle()
{
	StretchBlt(h_Base.dc, 0, 0, XRES, YRES, h_TitleBG[u_TitleBG.Frame].dc, 0, 0, XRES, YRES, SRCCOPY);
}

void TetrisManager::DrawNewBG()
{
	if (u_NewBG.bTrigger == FALSE)	return;

	int x = m_rtClient.right / 2 - h_newBG.bit.bmWidth / 2+30;
	int y = m_rtClient.bottom / 2 - h_newBG.bit.bmHeight / 2+60;
	BitBlt(h_Base.dc, x, y, h_Base.bit.bmWidth, h_Base.bit.bmHeight, h_newBG.dc, 0, 0, SRCCOPY);
}

void TetrisManager::DrawFlash()
{
	if (u_Flash.bTrigger == FALSE)	return;
	int x = m_rtClient.right / 2 - u_Flash.size / 2;
	int y = m_rtClient.bottom / 2;
	TransparentBlt(h_Base.dc, x, y, u_Flash.size, h_Flash.bit.bmHeight, h_Flash.dc, u_Flash.Frame * u_Flash.size, 0, u_Flash.size, h_Flash.bit.bmHeight, RGB(0, 0, 0));
}


void TetrisManager::DrawPressBig()
{
	if (u_PressBig.bTrigger == FALSE)
	{
		DrawPressSmall();
		return;
	}
	int x = m_rtClient.right / 2 - h_PressBig.bit.bmWidth / 2;
	int y = 800;
	TransparentBlt(h_Base.dc, x, y, h_PressBig.bit.bmWidth, h_PressBig.bit.bmHeight,h_PressBig.dc, 0, 0, h_PressBig.bit.bmWidth, h_PressBig.bit.bmHeight, RGB(255, 0, 255));
}

void TetrisManager::DrawPressSmall()
{
	int x = m_rtClient.right / 2 - h_PressSmall.bit.bmWidth / 2;
	int y = 820;
	TransparentBlt(h_Base.dc, x, y, h_PressSmall.bit.bmWidth, h_PressSmall.bit.bmHeight, h_PressSmall.dc, 0, 0, h_PressSmall.bit.bmWidth, h_PressSmall.bit.bmHeight, RGB(255, 0, 255));
}

void TetrisManager::DrawFade()
{
	//1. 알파dc 에다가 검은색찍고
	BitBlt(h_Alpha.dc, 0, 0, XRES, YRES, h_Fade.dc, 0, 0, SRCCOPY);
	//2. 알파 브렌드 함수로 베이스에다가 알파를찍기 
	AlphaBlend(h_Base.dc, 0, 0, XRES, YRES, h_Alpha.dc, 0, 0, XRES, YRES, h_Fade.bf);

}

void TetrisManager::DrawBlockAlpha()
{
}


void TetrisManager::UpdateTitle()
{
	if (UpdateCheck(u_TitleBG, 30) == TRUE)
	{
		u_TitleBG.Frame++;
		if (u_TitleBG.Frame >= u_TitleBG.MaxFrame)
			u_TitleBG.Frame = 0;
	}
	
}

void TetrisManager::UpdateNewBG()
{
	if (u_TitleBG.Frame == 120)
	{
		u_NewBG.bTrigger = TRUE;
	}
}

void TetrisManager::UpdateFlash()
{
	if (u_Flash.tricnt >= 15)	return;

	if (u_TitleBG.Frame == 115)
	{
		u_Flash.bTrigger = TRUE;
		u_Flash.tricnt++;
	}

	if (u_Flash.bTrigger == FALSE)	return;

	u_Flash.aEndTick = GetTickCount();
	if (u_Flash.aEndTick - u_Flash.aStartTick > 100)
	{
		u_Flash.aStartTick = u_Flash.aEndTick;
		u_Flash.Frame++;//
		if (u_Flash.Frame > u_Flash.MaxFrame)// 애니가 끝나면
		{
			u_Flash.bTrigger = FALSE;//폭발이 끝났음을 알림 
		}
	}
}


void TetrisManager::UpdatePressBig()
{
	if (UpdateCheck(u_PressBig, 210) == TRUE)
	{
		u_PressBig.bTrigger = !u_PressBig.bTrigger;
	}
}

void TetrisManager::GetOver()
{
	if (handle.Updateover() == FALSE)	GameState = GAME_OVER;
}

void TetrisManager::UpdateFade()
{
	if (UpdateCheck(u_Fade, 8) == TRUE)
	{
		h_Fade.bf.SourceConstantAlpha--;
		if (h_Fade.bf.SourceConstantAlpha <= 1)
			h_Fade.bf.SourceConstantAlpha = 1;
	}
}


void TetrisManager::Load(HANDLES & h, LPCWSTR name)
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

void TetrisManager::InitTick(UPDATE & up, int mode)
{
	switch (mode)
	{
	case 0://all
		up.mStartTick = up.mEndTick = up.aStartTick
			= up.aEndTick = GetTickCount();
		break;
	default:
		break;
	}
}

RECT & TetrisManager::GetRect()
{
	return m_rtClient;
}

void TetrisManager::GetFrame()
{
	Frame.sTick = Frame.eTick = GetTickCount();
	Frame.FrameCount = 0;
	Frame.StartFrameCount = 0;
	Frame.FrameRate = 0;
	Frame.bTrigger = TRUE;
}

BOOL TetrisManager::UpdateCheck(UPDATE & up, DWORD tick)
{
	up.mEndTick = GetTickCount();
	if (up.mEndTick - up.mStartTick > tick)
	{
		up.mStartTick = up.mEndTick;
		return TRUE;
	}
	return FALSE;
}

HANDLES TetrisManager::getbase()
{
	return h_Base;
}

BOOL TetrisManager::KeyCheck(WPARAM wparam)
{
	if (GameState == GAME_TITLE)
	{
		GameState = GAME_MODE;
		return TRUE;
	}
	handle.keyhandle(wparam);
	
	return FALSE;
}
