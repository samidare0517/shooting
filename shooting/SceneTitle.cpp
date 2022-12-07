#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

	m_menu.init();
	m_menu.addItem("�Q�[���X�^�[�g");


	m_menu.setPos(540, 360);

	m_menu.setupCursor();
}

void SceneTitle::end()
{
	m_menu.end();
}

void SceneTitle::update()
{
	m_menu.update();
	Fade();

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = true;
	}
}

void SceneTitle::Fade()
{
	fadeValue_ -= 5;
	if (fadeValue_ < 0)
	{
		fadeValue_ = 0;
	}
	if (fadeValue_ > 255)
	{
		fadeValue_ = 255;
	}
}

void SceneTitle::draw()
{
	m_menu.draw();

	
	// ������e�摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	// �u�����h�̎d�����w�肵�Ă���B
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	// ��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, 1280, 700, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	// �f�o�b�N�p
//	DrawFormatString(0, 100, GetColor(255,255,255), "%d", fadeValue_);

	// �f�o�b�N�p	
//	DrawString(400, 100, "�^�C�g�����", GetColor(255, 255, 255));
}

