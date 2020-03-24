#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}

playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init();
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	player = RectMakeCenter(_x - 300, _y, 50, 35);
	_getScore = score = _scrollingSpeed = _gravity = _jumpPower = _isDead = _isGameStart = 0;
	temp2 = nullptr;

	for (int i = 0; i < 4; i++)
	{
		randomYsize = RND->gerFrom1IntTo(4);
		topPipe[i] = RectMakeCenter(512 + (256 * i), 0, 100, 200 + (100 * randomYsize));
		_topPipe[i] = new image;
		_topPipe[i]->init("pipe_1.bmp", 100, 200 + (100 * randomYsize), true, RGB(255, 0, 255));

		bottomPipe[i] = RectMakeCenter(512 + (256 * i), WINSIZEY, 100, WINSIZEY - (100 * randomYsize) + 200);
		_bottomPipe[i] = new image;
		_bottomPipe[i]->init("pipe_0.bmp", 100, WINSIZEY - (100 * randomYsize) + 200, true, RGB(255, 0, 255));
		invisiblePipe[i] = RectMakeCenter(512 + (256 * i) + 48, (topPipe[i].bottom + bottomPipe[i].top) / 2, 2, 100 + 80);
	}

	// 이미지 생성
	_bg = new image;
	_bg->init("bg.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	_birdImg = new image;
	_birdImg->init("bird_0.bmp", 50, 35, true, RGB(255, 0, 255));

	_scoreText = new image;
	_scoreText->init("score.bmp", 88, 24, true, RGB(255, 0, 255));

	_gameOver = new image;
	_gameOver->init("gameover.bmp", 192, 42, true, RGB(255, 0, 255));
	
	for (int i = 0; i < 10; i++)
	{
		char buff[64];
		sprintf_s(buff, sizeof(buff), "%d.bmp", i);
		_scoreNum[i] = new image;
		if (i == 1 || i == 4 || i == 7)
		{
			_scoreNum[i]->init(buff, 12, 14, true, RGB(255, 0, 255));
			continue;
		}
		_scoreNum[i]->init(buff, 12, 14, false, RGB(0, 0, 0));
	}
	
	return S_OK;
}

void playGround::release()
{
	gameNode::release();

}

void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (!_isGameStart)
		{
			_scrollingSpeed = 3.5;
			_gravity = 0.2;
			_isGameStart = true;
			_isDead = false;
		}
		else
		{
			if (!_isDead)
			{
				_jumpPower = 4.5;
			}
		}
	}

	if (_isGameStart)
	{
		if (!_isDead)
		{
			_y += _gravity;
			_y -= _jumpPower;
			_jumpPower -= _gravity;
			player = RectMakeCenter(_x - 300, _y, 50, 35);

			for (int i = 0; i < 4; i++)
			{
				RECT temp;
				topPipe[i].left -= _scrollingSpeed, topPipe[i].right -= _scrollingSpeed;
				bottomPipe[i].left -= _scrollingSpeed, bottomPipe[i].right -= _scrollingSpeed;
				invisiblePipe[i].left -= _scrollingSpeed, invisiblePipe[i].right -= _scrollingSpeed;
				if (topPipe[i].right < 0)
				{
					int randomYsize = RND->gerFrom1IntTo(4);
					topPipe[i] = RectMakeCenter(1024, 0, 100, 200 + (100 * randomYsize));
					_topPipe[i] = new image;
					_topPipe[i]->init("pipe_1.bmp", 100, 200 + (100 * randomYsize), true, RGB(255, 0, 255));

					bottomPipe[i] = RectMakeCenter(1024, WINSIZEY, 100, WINSIZEY - (100 * randomYsize) + 200);
					_bottomPipe[i] = new image;
					_bottomPipe[i]->init("pipe_0.bmp", 100, WINSIZEY - (100 * randomYsize) + 200, true, RGB(255, 0, 255));
					invisiblePipe[i] = RectMakeCenter(1024 + 48, (topPipe[i].bottom + bottomPipe[i].top) / 2, 2, 100 + 80);
				}

				if (IntersectRect(&temp, &player, &topPipe[i]))
				{
					_isDead = true;
				}
				if (IntersectRect(&temp, &player, &bottomPipe[i]))
				{
					_isDead = true;
				}
				if (IntersectRect(&temp, &player, &invisiblePipe[i]))
				{
					temp2 = &invisiblePipe[i];
					_getScore = true;
				}
			}
			if (_getScore)
			{
				if (temp2->right < player.left)
				{
					++score;
					_getScore = false;
				}
			}
			if (player.top > WINSIZEY)
			{
				_isDead = true;
			}
		}
	}
}

void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	_bg->render(backDC, 0, 0);
	_birdImg->render(backDC, player.left, player.top);

	for (int i = 0; i < 4; i++)
	{
		_topPipe[i]->render(backDC, topPipe[i].left, topPipe[i].top);
		_bottomPipe[i]->render(backDC, bottomPipe[i].left, bottomPipe[i].top);
	}

	if (!_isGameStart)
		TextOut(backDC, WINSTARTX, WINSTARTY, "<게임을 시작하려면 스페이스를 누르세요>", strlen("<게임을 시작하려면 스페이스를 누르세요>"));
	else
	{
		_scoreText->render(backDC, 10, 10);
		int fDigit = score % 10;
		int sDigit = score / 10;
		int tDigit = score / 100;

		for (int i = 0; i < 10; i++)
		{
			if (fDigit == i)
			{
				_scoreNum[i]->render(backDC, 150, 15);
			}
			if (sDigit == i)
			{
				_scoreNum[i]->render(backDC, 140, 15);
			}
			if (tDigit == i)
			{
				_scoreNum[i]->render(backDC, 130, 15);
			}
		}
	}

	if (_isDead)
	{
		_gameOver->render(backDC, WINSIZEX / 2 - 80, WINSIZEY / 2 - 25);
	}
	//===================================================
	this->getBackBuffer()->render(hdc, 0, 0);
}