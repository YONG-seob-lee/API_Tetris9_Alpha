// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

extern HWND hWnd;		// 윈도우 핸들
//우리가 추가할거 
#pragma comment(lib,"Msimg32.lib")  //투명 으로찍는 함수 추가하기 위한 프라그마 라이브러리 추가
#pragma comment(lib,"vfw32.lib")	// .mp4 확장자를 사용하기 위한 프라그마 라이브러리 추가
#pragma comment(lib,"winmm.lib")

#include <strsafe.h>//DrawScore 
#include "g_Defines.h"
#include <mmsystem.h>
#include <ctime>
#include <random>
#include <functional>
#include <chrono>
using namespace std;
