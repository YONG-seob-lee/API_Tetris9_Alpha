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
	u_Block.bTrigger = FALSE;		// ���� ȭ�鿡 ����� ���� ����
	u_MAP.bTrigger = FALSE;			// �ʰ� ��ϰ��� �浹�� ���� ����
	u_CheckOver.bTrigger = TRUE;	// ���� ¡������ ����
	u_AI.bTrigger = FALSE;
	u_TransBlock.bTrigger = FALSE;	// Ȧ�� ��� ���� ����
	InitBlock();
}

void Tetris::InitPosition(int x, int y)
{
	PositionX = x;
	PositionY = y;
}

void Tetris::InitMap()
{
	for (int h = 0; h < 24; h++)			// �� �ʱ�ȭ�� ���� 2�� for ��
	{													// ����� 1��(���) �� ���� 1�� ���� ������ �׸� �����̵��� �� ����
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
	u_Block.bTrigger = TRUE;		// ��� ����
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
	BLinked->SetLinked();		// ù��° ��� ����� �ڿ� ���ο� ��� �����ϱ�
	posX = 5;					// ��� ��ġ ����
	posY = 0;
	InitCM();					// �ʵ����� �ʱ�ȭ
	InitBlock();				// ��� �ʱ�ȭ
	
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
			//if (MapData[h][w] == MAPBLOCK)		// UI �� ��ü�ϹǷ� �ʿ���� ( ������ ���� )
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
	int y = posY;	// ���� ��ġ�� ����

	while (1)
	{
		posY++;		// �ٴڿ� ���������� ������
		if (CheckWall() == FALSE)		// �ٴڿ� �� ������
		{
			posY--;						// ��ĭ �ø���
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

	posY = y;		// ��ġ�� ��������
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
	for (int count = 1; count < 5; count++)		// count == 1 �ι�° ��� , count == 2 ����° ���
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
	for (int count = 1; count < 5; count++)		// count == 1 �ι�° ��� , count == 2 ����° ���
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

bool Tetris::CheckWall()		// ������ ��ϰ� �ʰ��� �浹 Ȯ�� �Լ�
{
	InitCM();								// ���� �����̷��� ���⿡�� 1:1��Ī�Ǵ� 4x4 �ʵ����� �ʱ�ȭ

	for (int i = 0; i < 4; i++)							// �������Ͱ� ��������
	{
		for (int j = 0; j < 4; j++)
		{
			if (checkMap[i][j] != 0 && BlockData[i][j] != 0)	// üũ�ʿ��� i,j ��ǥ�� ���� 0�� �ƴѵ� ��ϵ����� i,j ��ǥ�� ���� 0�� �ƴϸ� 
			{
				return FALSE;		// 4x4 �ʵ����Ϳ� 4x4 �������Ͱ��� �浹�� �����	FALSE ��ȯ
			}
		}
	}
	return TRUE;
}

void Tetris::CheckLine()
{
	int line = 0;		// ��������ϴ� ���� ���� ���۶����� Ȯ���ϱ� ���� ����
	int count = 0;		// ������� ���� 1�� ����Ǿ��ִ� �� �����͸� �Ʒ��� ��������� �Լ�

	for (int h = 1; h < 23; h++)
	{
		if (MapData[h][1] != BLANK && MapData[h][2] != BLANK && MapData[h][3] != BLANK && MapData[h][4] != BLANK && MapData[h][5] != BLANK
			&& MapData[h][6] != BLANK && MapData[h][7] != BLANK && MapData[h][8] != BLANK && MapData[h][9] != BLANK && MapData[h][10] != BLANK)
		{
			line = h;			// ��� �����Ͱ� 1�� ���ʶ��� ����
			count++;			// h������ �������� ���ٱ��� ��� �����Ͱ� 1���� Ȯ���ؼ� ����
			for (int i = 1; i < 11; i++)		// h���� ������ 0���� �ʱ�ȭ
				MapData[h][i] = 0;
		}
	}
	for (int h = line - count; h > 0; h--)	// h ���ο��� ī��Ʈ�� ���κ��� �� �� ���α���
	{
		for (int w = 1; w < 11; w++)
		{
			MapData[h + count][w] = MapData[h][w];	// h���ο��� ī��Ʈ�� ���κ��� ������ �����ϱ�
		}
	}
	count = 0;	 // ī��Ʈ �ٽ� �ʱ�ȭ
}

void Tetris::CheckDeadLine()
{
	for (int w = 1; w < 11; w++)
	{
		if (MapData[0][w] != BLANK)			// �� ������ �� ���ٿ� '0' �̿��� �����Ͱ� ����Ǹ�
			u_CheckOver.bTrigger = FALSE;			// ���� Ʈ���� �ߵ�
	}
}

void Tetris::goLeft()
{
	posX--;
	if (CheckWall() == FALSE)	posX++;			// ���� ���������ϸ� �ʰ� �浹�� ���ܹ����� ������ġ�� ȸ��
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
		u_MAP.bTrigger = TRUE;	// �ʵ������� �ٴڰ� ����� �浹�����Ƿ� Ʈ���� �ߵ�
		u_Block.bTrigger = FALSE;	// �浹���ڸ��� �� ����
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
			u_MAP.bTrigger = TRUE;	// �ʵ������� �ٴڰ� ����� �浹�����Ƿ� Ʈ���� �ߵ�
			u_Block.bTrigger = FALSE;	// �浹���ڸ��� �� ����
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
	if (CheckWall() == FALSE)		// ��üũ�� �ߴµ� �ɸ��� (�⺻���� ���ʿ� �ɸ��°�����)
	{
		posX++;						// ���������� ��ĭ �̵�
		if (CheckWall() == FALSE)	// ���������� �̵��ߴµ��� �ұ��ϰ� �ɷȴٸ�
		{
			posX++;					// ���������� ��ĭ �� �̵�
			if (CheckWall() == FALSE)
			{
				posX -= 3;			// �������� ��ĭ �̵�(�����ʿ� �ɸ��°����� �Ǵ�)

				if (CheckWall() == FALSE)	// �������� �̵��ߴµ��� �ұ��ϰ� �ɷȴٸ�
				{
					posX--;			// �������� ��ĭ �� �̵�
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
	if (CheckWall() == FALSE)		// ��üũ�� �ߴµ� �ɸ��� (�⺻���� ���ʿ� �ɸ��°�����)
	{
		posX++;						// ���������� ��ĭ �̵�
		if (CheckWall() == FALSE)	// ���������� �̵��ߴµ��� �ұ��ϰ� �ɷȴٸ�
		{
			posX++;					// ���������� ��ĭ �� �̵�
			if (CheckWall() == FALSE)
			{
				posX -= 3;			// �������� ��ĭ �̵�(�����ʿ� �ɸ��°����� �Ǵ�)

				if (CheckWall() == FALSE)	// �������� �̵��ߴµ��� �ұ��ϰ� �ɷȴٸ�
				{
					posX--;			// �������� ��ĭ �� �̵�
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
	if (u_TransBlock.bTrigger == TRUE)	return;	// Ȧ�� �ѹ� ��������� �ٷ� ����

	if (HoldFirst < 1)			// Ȧ�带 �ѹ��� ������� �ʾ�����
	{
		HoldBlock = BLinked->getB();		// ���� ��� ��������
		for (int i = 0; i < 4; i++)			// ��ü �� ������ ����
		{
			for (int j = 0; j < 4; j++)
			{
				HBlock[i][j] = HoldBlock->getBpart(i, j);	// Ȧ��� ��� ������ �����ϱ�
			}
		}
		BLinked->SetLinked();				// ����Ʈ ��ĭ �о��
		for (int i = 0; i < 4; i++)			// ��ü �� ������ ����
		{
			for (int j = 0; j < 4; j++)
			{
				BlockData[i][j] = BLinked->getBpart(i, j);	// ���� ������ ��� ������ �����ϱ�
			}
		}
		u_TransBlock.bTrigger = TRUE;		// Ȧ�� �����
		HoldFirst++;
		return;
	}
	else
	{

		Block* temp;
		temp = HoldBlock;
		HoldBlock = BLinked->getB();		// Ȧ����� ���� �������� �� ����

		for (int i = 0; i < 4; i++)			// ��ü �� Ȧ�� �����Ϳ� ������ ����
		{
			for (int j = 0; j < 4; j++)
			{
				HBlock[i][j] = BlockData[i][j];	// hblock �� ���̿� ������ �ǵ���� ��
			}
		}
		BLinked->SetData(temp);		// ���� �������� ���� Ȧ����� ����

		for (int i = 0; i < 4; i++)			// ��ü �� Ȧ��� �����͸� �� �����Ϳ� ����
		{
			for (int j = 0; j < 4; j++)
			{
				BlockData[i][j] = BLinked->getBpart(i, j);	// ��ü�� ��� ������ �����ϱ�
			}
		}
		posX = 5;
		posY = 0;
		u_TransBlock.bTrigger = TRUE;		// Ȧ�� �����
	}
}

void Tetris::UpdateAutoDown()
{
	u_Block.mEndTick = GetTickCount();
	if (u_Block.mEndTick - u_Block.mStartTick > 1500)	// ���� �ð� ������
	{
		goDown();				// ��ĭ ������
		u_Block.mStartTick = u_Block.mEndTick;	// startTick �ʱ�ȭ
	}
}

void Tetris::UpdateMap()
  {
	if (u_MAP.bTrigger == FALSE)	return;	// ������ �浹�� �Ȼ���� ��ȯ

	if (u_MAP.bTrigger == TRUE)	// ������ �浹�� ����� ���̻� �� ���� �������θ���
	{
		InitCM();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (checkMap[i][j] == MAPBLOCK)		MapData[posY + i][posX + j] = MAPBLOCK;	// ��üũ �迭�� ���κ� ����
				if (BlockData[i][j] == GREEN)		MapData[posY + i][posX + j] = GREEN;
				if (BlockData[i][j] == RED)			MapData[posY + i][posX + j] = RED;
				if (BlockData[i][j] == BLUE)		MapData[posY + i][posX + j] = BLUE;
				if (BlockData[i][j] == ORANGE)		MapData[posY + i][posX + j] = ORANGE;
				if (BlockData[i][j] == PURPLE)		MapData[posY + i][posX + j] = PURPLE;
				if (BlockData[i][j] == YELLOW)		MapData[posY + i][posX + j] = YELLOW;
				if (BlockData[i][j] == SKY)			MapData[posY + i][posX + j] = SKY;	// �� �����Ϳ� ������ 1~8�� �κ��� ������ �� �����Ϳ� ����
			}
		}
		u_TransBlock.bTrigger = FALSE;	// ��� �ٽ� ��������� ���� Ȧ�� �ѹ� ��� ����
		CheckDeadLine();
 		CheckLine();				// ���� �ϼ��Ǿ����� Ȯ���� �� �ִ� �Լ�
		SetBlock();
	}
}

BOOL Tetris::UpdateGetOver()
{
	if (u_CheckOver.bTrigger == TRUE)	return TRUE;	// ������ ���� ������¶�� ��ȯ

	return FALSE;		// ������ ����Ǿ����� FALSE ��ȯ
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
	int LongTimeTick = u_Block.aStartTick;				// �������� �� ���� ������ �ٷ� ������ �Ϸ��� ����
	u_Block.aEndTick = GetTickCount();
	u_AI.bTrigger = FALSE;
	
	if (u_Block.aEndTick - u_Block.aStartTick > 1000)	// ���� �ð� ������
	{
		UpdateRandomMove();		// �����ϰ� ��ĭ �����̱�
		if (CheckFillLine() == TRUE)		// �ٴڿ� ���������߷����� ������ �ϼ��� �� �ִٸ� ( 1���� )
		{
			goDown();		// �ٷ� �ٴ����� ���Ź�����
		}
		if (CheckFillBlock() == TRUE)		// �ٴڿ� ����� ����߷����� 4x4 ũ���� ������ ���� BLANK ���� ���ٸ�
		{
			if (u_AI.bTrigger == FALSE)
			{
				goDown();
				u_AI.bTrigger = TRUE;
			}
		}
		u_Block.aStartTick = u_Block.aEndTick;	// startTick �ʱ�ȭ
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
			&& MapData[h][6] != BLANK && MapData[h][7] != BLANK && MapData[h][8] != BLANK && MapData[h][9] != BLANK && MapData[h][10] != BLANK) // �� ����߷����� �� �ϼ��� �ȴٸ�
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
			if (BlockData[h][w] != BLANK)	temp[h][w] = BlockData[h][w]; // �� ������ �ƴ� ���� ����
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
	if (count <= 3)		// �� ������ 3�� ���ϸ�
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
		MessageBox(NULL, name, L"��Ʈ�� �ε� ����", MB_OK);
	} 
	h.dc = CreateCompatibleDC(h_Base.dc);//���̽��� ȣȯ�Ǵ� DC ��� 
	h.hOldbmp = (HBITMAP)SelectObject(h.dc, h.hbmp);//dc �� ��Ʈ���̶� ����

	GetObject(h.hbmp, sizeof(BITMAP), &h.bit);
}