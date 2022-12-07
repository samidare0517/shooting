#include "DxLib.h"
#include "ShotBase.h"

namespace
{
	// �����蔼�a�̔��a
	constexpr float kColRadius = 16.0f;
}


ShotBase::ShotBase()
{

	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}

ShotBase::~ShotBase()
{

}



// �V���b�g�J�n
void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

// �X�V
void ShotBase::update()
{
	if (!m_isExist) return;
}


// �����蔻��̔��a�擾
float ShotBase::getRadius() const
{
	return kColRadius;
}

// �����蔻��̒��S�ʒu�擾
Vec2 ShotBase::getCenter() const
{
	int sizeX = 0;
	int sizeY = 0;

	if (GetGraphSize(m_handle, &sizeX, &sizeY) == -1)
	{
		// �T�C�Y���擾�ł��Ȃ������ꍇ�͍��ʒu��n���Ă���
		return m_pos;
	}

	Vec2 result = m_pos;
	result.x += sizeX / 2;
	result.y += sizeY / 2;

	return result;
}



// �\��
void ShotBase::draw()
{
	if (!m_isExist)return;
	DrawGraph(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}