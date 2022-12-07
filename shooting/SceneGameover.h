#pragma once
#include "SceneBase.h"

class SceneGameover : public SceneBase
{
public:
	SceneGameover()
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~SceneGameover() {}


	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:
	// �e�L�X�g�\���ʒu�ύX
	int m_textPosY;
	int m_textVecY;


	bool m_isEnd;

};

