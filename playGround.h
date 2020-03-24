#pragma once
#include "gameNode.h"

class playGround : public gameNode
{
private:
	RECT player;
	RECT* temp2;
	int _x, _y;
	int score;
	int randomYsize;

	bool _isGameStart, _isDead, _getScore;
	float _jumpPower;
	float _gravity;
	float _scrollingSpeed;

	RECT topPipe[4];
	RECT bottomPipe[4];
	RECT invisiblePipe[4];
	RECT getScoreRect;

	image* _bg;
	image* _birdImg;
	image* _topPipe[4];
	image* _bottomPipe[4];
	image* _scoreText;
	image* _scoreNum[10];
	image* _gameOver;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render(HDC hdc);	//그리기 전용 함수
};