#pragma once
#include "gameNode.h"

class testRc : public gameNode
{
private:
	RECT _rc;

public:
	testRc();
	~testRc();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render(HDC hdc);	//�׸��� ���� �Լ�

};

