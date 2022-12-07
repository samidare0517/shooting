#pragma once
#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult()
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~SceneResult() {}


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
