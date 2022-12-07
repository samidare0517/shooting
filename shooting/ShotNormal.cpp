#include "ShotNormal.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 15.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;
}

void ShotNormal::update()
{
	// ��ʊO�ɏo����e�����
	if (!m_isExist) return;

	m_pos += m_vec;
	if (m_pos.x > Game::kScreenWindth)
	{
		m_isExist = false;
	}
}
