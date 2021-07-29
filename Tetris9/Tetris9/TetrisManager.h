#pragma once
#include "TetrisHandler.h"

class TetrisManager
{
private:
	int GameState;
	int AttackLine;

	TetrisHandler handle;
	FRAME Frame;

	// HANDLES
	HANDLES h_Base;
	HANDLES h_TitleBG[TITLE_BG_FRAME];			// 타이틀 배경
	HANDLES h_newBG;							// 뉴 타이틀 배경 덧붙이기
	HANDLES h_Flash;							// 뉴 타이틀 배경으로 바뀌는 과정
	HANDLES h_PressBig;							// 큰 버튼
	HANDLES h_PressSmall;						// 작은 버튼
	HANDLES h_Alpha;
	HANDLES h_Fade;

	// UPDATE
	UPDATE u_TitleBG;							// 타이틀 배경 애니메이션을 위한 업데이트
	UPDATE u_NewBG;								// 틱 딜레이를 위한 추가
	UPDATE u_Flash;								// 섬광 애니메이션
	UPDATE u_PressBig;							// 작은 버튼에서 큰 버튼으로 전환을 위한 업데이트
	UPDATE u_Fade;

	// UTIL
	RECT m_rtClient;							// 크기를 위한 그렇쿵

public:
	TetrisManager();
	~TetrisManager();

	// Basic
	void GameLoop(HDC hdc);		// 게임 전반을 총괄하는 루프
	void DrawAll(HDC hdc);		// 게임 그림을 총괄하는 함수
	void Update();				// 게임 업데이트를 총괄하는 함수
	void setGameState();		// 

	// Init
	void InitFirst();				// 가장 최초로 초기화하는 함수
	void InitResource();			// Bace.dc 버퍼 생성 함수
	void InitData();				// 리소스를 제외한 멤버변수등을 초기화 하는 함수
	void InitResourceTitleBG();		// 타이틀배경 리소스 초기화

	// Draw
	void DrawTitle();			// 타이틀 찍기
	void DrawNewBG();			// 뉴 타이틀
	void DrawFlash();			// 섬광
	void DrawPressBig();		// 큰 버튼
	void DrawPressSmall();		// 작은 버튼
	void DrawFade();
	void DrawBlockAlpha();

	// Update
	void UpdateTitle();
	void UpdateNewBG();
	void UpdateFlash();
	void UpdatePressBig();
	void GetOver();
	void UpdateFade();


	// Util
	void Load(HANDLES& h, LPCWSTR name);
	void InitTick(UPDATE& up, int mode = 0);	// '0' 이면 all, '1' 이면 move, '2' 이면 animate
	RECT& GetRect();
	void GetFrame();
	BOOL UpdateCheck(UPDATE& up, DWORD tick);
	HANDLES getbase();
	BOOL KeyCheck(WPARAM wparam);

};

