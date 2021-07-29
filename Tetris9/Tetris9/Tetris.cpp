#include "tetris.h"

Tetris::Tetris() : posX(5), posY(0)
{
	BLinked = new BlockLinked;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			BlockData[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			HBlock[i][j] = 0;
		}
	}
	InitMap();
}

Tetris::~Tetris()
{
	delete BLinked;
}


void Tetris::LoadTetris(HANDLES h_Base)
{
	Load(h_Block, L"image/pblock.bmp", h_Base);
	Load(h_TransBlock, L"image/transblock.bmp", h_Base);
}

void Tetris::InitAll(int x, int y)
{
	posX = 5;
	posY = 0;
	u_Block.mEndTick = u_Block.mStartTick = GetTickCount();
	InitPosition(x, y);

	HoldFirst = 0;
	u_Block.bTrigger = FALSE;		// 현재 화면에 블록이 없는 상태
	u_MAP.bTrigger = FALSE;			// 맵과 블록간의 충돌이 없는 상태
	u_CheckOver.bTrigger = TRUE;	// 게임 징행중인 상태
	u_AI.bTrigger = FALSE;
	u_TransBlock.bTrigger = FALSE;	// 홀드 사용 안한 상태
	InitBlock();
}

void Tetris::InitPosition(int x, int y)
{
	PositionX = x;
	PositionY = y;
}

void Tetris::InitMap()
{
	for (int h = 0; h < 24; h++)			// 벽 초기화를 위한 2중 for 문
	{													// 블록의 1값(블록) 과 벽의 1의 값이 같을때 그만 움직이도록 할 예정
		for (int w = 0; w < 12; w++)
		{
			if (w == 0 || h == 23 || w == 11)
				MapData[h][w] = 1;
			else
				MapData[h][w] = 0;
		}
	}
}

void Tetris::InitBlock()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			BlockData[i][j] = BLinked->getBpart(i, j);
		}
	}
	u_Block.bTrigger = TRUE;		// 블록 생성
}

void Tetris::InitCM()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			checkMap[i][j] = MapData[posY + i][posX + j];
		}
	}
}

void Tetris::SetBlock()
{
	u_MAP.bTrigger = FALSE;
	BLinked->SetLinked();		// 첫번째 블록 지우고 뒤에 새로운 블록 보충하기
	posX = 5;					// 블록 위치 조정
	posY = 0;
	InitCM();					// 맵데이터 초기화
	InitBlock();				// 블록 초기화
	
}

void Tetris::DrawPersonal(HANDLES h_Base)
{
	DrawMap(h_Base, 1);
	DrawHoldBlock(h_Base, 1);
	DrawNextBlock(h_Base, 1);
	DrawBlock(h_Base, 1);
	DrawBottomBlock(h_Base, 1);
}

void Tetris::DrawSmall(HANDLES h_Base)
{
	DrawMap(h_Base, 2);
	DrawSmallHoldBlock(h_Base);
	DrawSmallNextBlock(h_Base);
	DrawBlock(h_Base, 2);
	DrawBottomBlock(h_Base, 2);
}

void Tetris::DrawMap(HANDLES h_Base, int size)
{
	for (int h = 3; h < 24; h++)
	{
		for (int w = 0; w < 12; w++)
		{
			//if (MapData[h][w] == MAPBLOCK)		// UI 가 대체하므로 필요없음 ( 개발자 버전 )
			//{
			//	StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
			//		, h_Block.dc, PIECE_BLOCK_X * MAPBLOCK, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			//}
			if (MapData[h][w] == GREEN)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (MapData[h][w] == RED)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)),PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (MapData[h][w] == BLUE)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)),PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (MapData[h][w] == ORANGE)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (MapData[h][w] == PURPLE)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (MapData[h][w] == YELLOW)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (MapData[h][w] == SKY)
			{
				StretchBlt(h_Base.dc, (PositionX + (w*PIECE_BLOCK_X / size)), (PositionY + (h*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
		}
	}
}

void Tetris::DrawBlock(HANDLES h_Base, int size)
{
	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			if (BlockData[h][w] == GREEN)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == RED)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == BLUE)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == ORANGE)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == PURPLE)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == YELLOW)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == SKY)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_Block.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
		}
	}
}

void Tetris::DrawBottomBlock(HANDLES h_Base, int size)
{
	int y = posY;	// 현재 위치값 저장

	while (1)
	{
		posY++;		// 바닥에 닿을때까지 내리기
		if (CheckWall() == FALSE)		// 바닥에 다 닿으면
		{
			posY--;						// 한칸 올리고
			break;
		}
	}
	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			if (BlockData[h][w] == GREEN)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == RED)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == BLUE)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == ORANGE)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == PURPLE)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == YELLOW)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (BlockData[h][w] == SKY)
			{
				StretchBlt(h_Base.dc, (PositionX + ((w + posX)*PIECE_BLOCK_X / size)), (PositionY + ((h + posY)*PIECE_BLOCK_Y / size)), PIECE_BLOCK_X / size, PIECE_BLOCK_Y / size
					, h_TransBlock.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
		}
	}

	posY = y;		// 위치값 돌려놓기
}

void Tetris::DrawHoldBlock(HANDLES h_Base, int size)
{
	int Holdx = PositionX - 58;
	int Holdy = PositionY + 120;

	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			if (HBlock[h][w] == GREEN)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X- 12) / size, (PIECE_BLOCK_Y- 12) / size
					, h_Block.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == RED)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size
					, h_Block.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == BLUE)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size
					, h_Block.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == ORANGE)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size
					, h_Block.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == PURPLE)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size
					, h_Block.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == YELLOW)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size
					, h_Block.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == SKY)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12)) / size, Holdy + (h * (PIECE_BLOCK_Y - 12)) / size, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size
					, h_Block.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
		}
	}
}

void Tetris::DrawNextBlock(HANDLES h_Base, int size)
{
	int NextBx;
	int NextBy;
	int Interval = 0;
	for (int count = 1; count < 5; count++)		// count == 1 두번째 블록 , count == 2 세번째 블록
	{
		NextBx = PositionX + 356;
		NextBy = PositionY + 120 + count*3;
		for (int h = 0; h < 4; h++)
		{
			for (int w = 0; w < 4; w++)
			{
				if (BLinked->getNextB(count)->getBpart(h, w) == GREEN)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == RED)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == BLUE)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == ORANGE)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == PURPLE)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == YELLOW)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == SKY)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12)) / size, (NextBy + h * (PIECE_BLOCK_Y - 12) + Interval) / size
						, (PIECE_BLOCK_X - 12) / size, (PIECE_BLOCK_Y - 12) / size, h_Block.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
			}
		}
		Interval += 90;
	}
}

void Tetris::DrawSmallHoldBlock(HANDLES h_Base)
{
	int Holdx = PositionX - 31;
	int Holdy = PositionY + 58;

	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			if (HBlock[h][w] == GREEN)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == RED)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == BLUE)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == ORANGE)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == PURPLE)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == YELLOW)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
			if (HBlock[h][w] == SKY)
			{
				StretchBlt(h_Base.dc, Holdx + (w * (PIECE_BLOCK_X - 12) / 2), Holdy + (h * (PIECE_BLOCK_Y - 12) / 2), (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2
					, h_Block.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
			}
		}
	}
}

void Tetris::DrawSmallNextBlock(HANDLES h_Base)
{
	int NextBx;
	int NextBy;
	int Interval = 0;
	for (int count = 1; count < 5; count++)		// count == 1 두번째 블록 , count == 2 세번째 블록
	{
		NextBx = PositionX + 180;
		NextBy = PositionY + 53 + count * 3;
		for (int h = 0; h < 4; h++)
		{
			for (int w = 0; w < 4; w++)
			{
				if (BLinked->getNextB(count)->getBpart(h, w) == GREEN)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * GREEN, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == RED)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * RED, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == BLUE)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * BLUE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == ORANGE)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * ORANGE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == PURPLE)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * PURPLE, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == YELLOW)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * YELLOW, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
				if (BLinked->getNextB(count)->getBpart(h, w) == SKY)
				{
					StretchBlt(h_Base.dc, (NextBx + w * (PIECE_BLOCK_X - 12) / 2), (NextBy + h * (PIECE_BLOCK_Y - 12) / 2 + Interval / 2)
						, (PIECE_BLOCK_X - 12) / 2, (PIECE_BLOCK_Y - 12) / 2, h_Block.dc, PIECE_BLOCK_X * SKY, 0, PIECE_BLOCK_X, PIECE_BLOCK_Y, SRCCOPY);
				}
			}
		}
		Interval += 90;
	}
}

bool Tetris::CheckWall()		// 오로지 블록과 맵간의 충돌 확인 함수
{
	InitCM();								// 블럭이 움직이려는 방향에서 1:1매칭되는 4x4 맵데이터 초기화

	for (int i = 0; i < 4; i++)							// 블럭데이터값 가져오기
	{
		for (int j = 0; j < 4; j++)
		{
			if (checkMap[i][j] != 0 && BlockData[i][j] != 0)	// 체크맵에서 i,j 좌표의 값이 0이 아닌데 블록데이터 i,j 좌표의 값도 0이 아니면 
			{
				return FALSE;		// 4x4 맵데이터와 4x4 블럭데이터간의 충돌이 생기면	FALSE 반환
			}
		}
	}
	return TRUE;
}

void Tetris::CheckLine()
{
	int line = 0;		// 지우려고하는 줄의 최초 시작라인을 확인하기 위한 변수
	int count = 0;		// 지우고나서 위쪽 1로 저장되어있는 맵 데이터를 아래로 끌어내리려는 함수

	for (int h = 1; h < 23; h++)
	{
		if (MapData[h][1] != BLANK && MapData[h][2] != BLANK && MapData[h][3] != BLANK && MapData[h][4] != BLANK && MapData[h][5] != BLANK
			&& MapData[h][6] != BLANK && MapData[h][7] != BLANK && MapData[h][8] != BLANK && MapData[h][9] != BLANK && MapData[h][10] != BLANK)
		{
			line = h;			// 모든 데이터가 1인 최초라인 저장
			count++;			// h라인을 기준으로 몇줄까지 모든 데이터가 1인지 확인해서 저장
			for (int i = 1; i < 11; i++)		// h라인 데이터 0으로 초기화
				MapData[h][i] = 0;
		}
	}
	for (int h = line - count; h > 0; h--)	// h 라인에서 카운트된 라인부터 맨 위 라인까지
	{
		for (int w = 1; w < 11; w++)
		{
			MapData[h + count][w] = MapData[h][w];	// h라인에서 카운트된 라인부터 줄줄이 복사하기
		}
	}
	count = 0;	 // 카운트 다시 초기화
}

void Tetris::CheckDeadLine()
{
	for (int w = 1; w < 11; w++)
	{
		if (MapData[0][w] != BLANK)			// 맵 데이터 맨 윗줄에 '0' 이외의 데이터가 저장되면
			u_CheckOver.bTrigger = FALSE;			// 실패 트리거 발동
	}
}

void Tetris::goLeft()
{
	posX--;
	if (CheckWall() == FALSE)	posX++;			// 블럭이 움직였더니만 맵과 충돌이 생겨버려서 이전위치로 회귀
}

void Tetris::goRight()
{
	posX++;
	if (CheckWall() == FALSE)	posX--;
}

void Tetris::goDown()
{
	posY++;
	if (CheckWall() == FALSE)
	{
		u_MAP.bTrigger = TRUE;	// 맵데이터의 바닥과 블록이 충돌했으므로 트리거 발동
		u_Block.bTrigger = FALSE;	// 충돌하자마자 블럭 정지
		posY--;
	}
}

void Tetris::goStraightDown()
{
	while (1)
	{
		posY++;
		if (CheckWall() == FALSE)
		{
			u_MAP.bTrigger = TRUE;	// 맵데이터의 바닥과 블록이 충돌했으므로 트리거 발동
			u_Block.bTrigger = FALSE;	// 충돌하자마자 블럭 정지
			posY--;
			break;
		}
	}
}

void Tetris::Rotate()
{
	BLinked->RotateH();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			BlockData[i][j] = BLinked->getBpart(i, j);
		}
	}
	if (CheckWall() == FALSE)		// 벽체크를 했는데 걸리면 (기본값은 왼쪽에 걸리는것으로)
	{
		posX++;						// 오른쪽으로 한칸 이동
		if (CheckWall() == FALSE)	// 오른쪽으로 이동했는데도 불구하고 걸렸다면
		{
			posX++;					// 오른쪽으로 한칸 더 이동
			if (CheckWall() == FALSE)
			{
				posX -= 3;			// 왼쪽으로 한칸 이동(오른쪽에 걸리는것으로 판단)

				if (CheckWall() == FALSE)	// 왼쪽으로 이동했는데도 불구하고 걸렸다면
				{
					posX--;			// 왼쪽으로 한칸 더 이동
				}
			}
		}
	}
}
 
void Tetris::CRotate()
{
	BLinked->CRotateH();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			BlockData[i][j] = BLinked->getBpart(i, j);
		}
	}
	if (CheckWall() == FALSE)		// 벽체크를 했는데 걸리면 (기본값은 왼쪽에 걸리는것으로)
	{
		posX++;						// 오른쪽으로 한칸 이동
		if (CheckWall() == FALSE)	// 오른쪽으로 이동했는데도 불구하고 걸렸다면
		{
			posX++;					// 오른쪽으로 한칸 더 이동
			if (CheckWall() == FALSE)
			{
				posX -= 3;			// 왼쪽으로 한칸 이동(오른쪽에 걸리는것으로 판단)

				if (CheckWall() == FALSE)	// 왼쪽으로 이동했는데도 불구하고 걸렸다면
				{
					posX--;			// 왼쪽으로 한칸 더 이동
				}
			}
		}
	}
}

void Tetris::SwapBlock()
{
	BLinked->Swap();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			BlockData[i][j] = BLinked->getBpart(i, j);
		}
	}
}

void Tetris::holdBlock()
{
	if (u_TransBlock.bTrigger == TRUE)	return;	// 홀드 한번 사용했으면 바로 퇴출

	if (HoldFirst < 1)			// 홀드를 한번도 사용하지 않았으면
	{
		HoldBlock = BLinked->getB();		// 현재 블록 가져오기
		for (int i = 0; i < 4; i++)			// 교체 후 데이터 저장
		{
			for (int j = 0; j < 4; j++)
			{
				HBlock[i][j] = HoldBlock->getBpart(i, j);	// 홀드된 블록 데이터 저장하기
			}
		}
		BLinked->SetLinked();				// 리스트 한칸 밀어내기
		for (int i = 0; i < 4; i++)			// 교체 후 데이터 저장
		{
			for (int j = 0; j < 4; j++)
			{
				BlockData[i][j] = BLinked->getBpart(i, j);	// 새로 생성된 블록 데이터 저장하기
			}
		}
		u_TransBlock.bTrigger = TRUE;		// 홀드 사용함
		HoldFirst++;
		return;
	}
	else
	{

		Block* temp;
		temp = HoldBlock;
		HoldBlock = BLinked->getB();		// 홀드블럭에 현재 진행중인 블럭 넣음

		for (int i = 0; i < 4; i++)			// 교체 전 홀드 데이터에 데이터 저장
		{
			for (int j = 0; j < 4; j++)
			{
				HBlock[i][j] = BlockData[i][j];	// hblock 는 더미에 들어갔으니 건드려도 됨
			}
		}
		BLinked->SetData(temp);		// 현재 진행중인 블럭에 홀드블럭을 넣음

		for (int i = 0; i < 4; i++)			// 교체 전 홀드블럭 데이터를 블럭 데이터에 저장
		{
			for (int j = 0; j < 4; j++)
			{
				BlockData[i][j] = BLinked->getBpart(i, j);	// 교체한 블록 데이터 저장하기
			}
		}
		posX = 5;
		posY = 0;
		u_TransBlock.bTrigger = TRUE;		// 홀드 사용함
	}
}

void Tetris::UpdateAutoDown()
{
	u_Block.mEndTick = GetTickCount();
	if (u_Block.mEndTick - u_Block.mStartTick > 1500)	// 일정 시간 지나면
	{
		goDown();				// 한칸 떨구기
		u_Block.mStartTick = u_Block.mEndTick;	// startTick 초기화
	}
}

void Tetris::UpdateMap()
  {
	if (u_MAP.bTrigger == FALSE)	return;	// 벽간의 충돌이 안생기면 반환

	if (u_MAP.bTrigger == TRUE)	// 벽간의 충돌이 생기고 더이상 갈 곳이 없어져부리면
	{
		InitCM();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (checkMap[i][j] == MAPBLOCK)		MapData[posY + i][posX + j] = MAPBLOCK;	// 맵체크 배열에 벽부분 저장
				if (BlockData[i][j] == GREEN)		MapData[posY + i][posX + j] = GREEN;
				if (BlockData[i][j] == RED)			MapData[posY + i][posX + j] = RED;
				if (BlockData[i][j] == BLUE)		MapData[posY + i][posX + j] = BLUE;
				if (BlockData[i][j] == ORANGE)		MapData[posY + i][posX + j] = ORANGE;
				if (BlockData[i][j] == PURPLE)		MapData[posY + i][posX + j] = PURPLE;
				if (BlockData[i][j] == YELLOW)		MapData[posY + i][posX + j] = YELLOW;
				if (BlockData[i][j] == SKY)			MapData[posY + i][posX + j] = SKY;	// 맵 데이터와 블럭에서 1~8인 부분이 있으면 맵 데이터에 저장
			}
		}
		u_TransBlock.bTrigger = FALSE;	// 블록 다시 만들어지는 순간 홀드 한번 사용 가능
		CheckDeadLine();
 		CheckLine();				// 줄이 완성되었는지 확인할 수 있는 함수
		SetBlock();
	}
}

BOOL Tetris::UpdateGetOver()
{
	if (u_CheckOver.bTrigger == TRUE)	return TRUE;	// 게임이 아직 진행상태라면 반환

	return FALSE;		// 게임이 종료되었으면 FALSE 반환
}

void Tetris::UpdateRandomMove()
{
	srand(unsigned(time(NULL)));
	int move = rand() % 3;
	switch (move)
	{
	case 0:
		goLeft();
		break;
	case 1:
		goRight();
		break;
	case 2:
		Rotate();
	default:
		break;
	}
}

void Tetris::Update_AI()
{
	int LongTimeTick = u_Block.aStartTick;				// 오래도록 둘 곳이 없으면 바로 떨구게 하려는 변수
	u_Block.aEndTick = GetTickCount();
	u_AI.bTrigger = FALSE;
	
	if (u_Block.aEndTick - u_Block.aStartTick > 1000)	// 일정 시간 지나면
	{
		UpdateRandomMove();		// 랜덤하게 한칸 움직이기
		if (CheckFillLine() == TRUE)		// 바닥에 블록을떨어뜨렸을때 한줄이 완성될 수 있다면 ( 1순위 )
		{
			goDown();		// 바로 바닥으로 떨궈버리기
		}
		if (CheckFillBlock() == TRUE)		// 바닥에 블록을 떨어뜨렸을때 4x4 크기의 데이터 안의 BLANK 수가 적다면
		{
			if (u_AI.bTrigger == FALSE)
			{
				goDown();
				u_AI.bTrigger = TRUE;
			}
		}
		u_Block.aStartTick = u_Block.aEndTick;	// startTick 초기화
	}
}


BOOL Tetris::CheckFillLine()
{
	int y = posY;
	while (1)
	{
		posY++;
		if (CheckWall() == FALSE)
		{
			posY--;
			break;
		}
	}
	for (int h = 1; h < 23; h++)
	{
		if (MapData[h][1] != BLANK && MapData[h][2] != BLANK && MapData[h][3] != BLANK && MapData[h][4] != BLANK && MapData[h][5] != BLANK
			&& MapData[h][6] != BLANK && MapData[h][7] != BLANK && MapData[h][8] != BLANK && MapData[h][9] != BLANK && MapData[h][10] != BLANK) // 다 떨어뜨렸을때 줄 완성이 된다면
		{
			posY = y;
			return TRUE;
		}
	}
	posY = y;
	return FALSE;
}

BOOL Tetris::CheckFillBlock()
{
	int y = posY;
	int temp[4][4] = { 0, };
	int count = 0;
	while (1)
	{
		posY++;
		if (CheckWall() == FALSE)
		{
			posY--;
			break;
		}
	}
	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			if (BlockData[h][w] != BLANK)	temp[h][w] = BlockData[h][w]; // 빈 공간이 아닐 때만 저장
			if(checkMap[h][w] != BLANK)		temp[h][w] = checkMap[h][w];
		}
	}
	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			if (temp[h][w] == BLANK)	count++;
		}
	}
	if (count <= 3)		// 빈 공간이 3개 이하면
	{
		count = 0;
		posY = y;
		return TRUE;	
	}
	posY = y;
	return FALSE;
}

void Tetris::Load(HANDLES & h, LPCWSTR name, HANDLES h_Base)
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