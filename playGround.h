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

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render(HDC hdc);	//�׸��� ���� �Լ�
};