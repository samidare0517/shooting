#include "SceneResult.h"
#include "DxLib.h"
#include "Pad.h"
#include "SceneManager.h"

void SceneResult::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

}

void SceneResult::end()
{

}

void SceneResult::update()
{

	if (Pad::isTrigger(PAD_INPUT_4))
	{
		m_isEnd = false;
	}
}

void SceneResult::draw()
{
	SceneMain scenemain;
	if (scenemain.Migration() == false)
	{
		DrawString(615, 360, "�Q�[���N���A", GetColor(255, 255, 255));
	}
	else if (scenemain.Migration() == true)
	{
		DrawString(615, 360, "�Q�[���I�[�o�[", GetColor(255, 255, 255));
	}
	DrawString(540, 400, "ESC�������ƃQ�[�����I�����܂��B", GetColor(225, 225, 225));
}