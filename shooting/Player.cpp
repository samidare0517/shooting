#include "DxLib.h"
#include "game.h"
#include "Player.h"
#include "SceneMain.h"

namespace
{
	// �����蔼�a�̔��a
	constexpr float kColRadius = 20.0f;

	// X�����AY�����̍ő呬�x
	constexpr float kSpeedMax = 8.0f;
	constexpr float kAcc	  = 0.4f;

	// �V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 20.0f;
}

Player::Player()
{
	m_handle	   = -1;
	m_pMain		   = nullptr;
	m_shotInterval = 0;
}

Player::~Player()
{

}

// �v���C���[�̏�����
void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_shotInterval = 0;
}

// ����
void Player::update()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �V���b�g��ł���
	m_shotInterval--;
	if (m_shotInterval < 0)
	{
		m_shotInterval = 0;
	}
	
	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	// Player�̃p�b�h�ړ�����

	if (padState & PAD_INPUT_UP)
	{
		m_vec.y -= kAcc;
		if (m_vec.y < -kSpeedMax)
		{
			m_vec.y = -kSpeedMax;
		}
	}
	else if (padState & PAD_INPUT_DOWN)
	{
		m_vec.y += kAcc;

		if (m_vec.y > kSpeedMax)
		{
			m_vec.y = kSpeedMax;
		}

	}
	else
	{
		m_vec.y *= 0.9f;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		m_vec.x -= kAcc;

		if (m_vec.x < kSpeedMax)
		{
			m_vec.x = -kSpeedMax;
		}
		
	}
	else if (padState & PAD_INPUT_RIGHT)
	{
		m_vec.x += kAcc;
		
		if (m_vec.x > kSpeedMax)
		{
			m_vec.x = kSpeedMax;
		}
	}
	else
	{
		m_vec.x *= 0.9f;
	}
	m_pos += m_vec;
	
	// player���O�ɏo�����ɂȂ������ʓ��ɖ߂�
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}
	if (m_pos.x > Game::kScreenWindth -118)
	{
		m_pos.x = Game::kScreenWindth -118;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}
	if (m_pos.y > Game::kScreenHeight -118)
	{
		m_pos.y = Game::kScreenHeight -118;
	}
}

// �`��
void Player::draw()
{
	if (m_isDead) return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}

// �����蔻��̔��a�擾
float Player::getRadius() const
{
	return kColRadius;
}

// �����蔻��̒��S�ʒu�擾
Vec2 Player::getCenter() const
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
