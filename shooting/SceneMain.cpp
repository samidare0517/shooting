#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include <cassert>
#include "ShotNormal.h"
#include "enemy.h"
#include "SceneTitle.h"


namespace
{
	Enemy		enemy[7];
	EnemySin	enemysin[7];
	EnemyDeside enemydeside[7];
	Player player;

	bool kCheck;
	bool kPlayerCheck;

	int EnemyNum		= 7;
	int EnemySinNum		= 7;
	int EnemyDesideNum	= 7;

	// �V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
	bool kMigration = false;
}

void SceneMain::init()
{
	m_textPosX = 0;
	m_textVecX = 4;

	m_EnemyNum			= EnemyNum;
	m_EnemySinNum		= EnemySinNum;
	m_EnemyDesideNum	= EnemyDesideNum;
	
	m_isEnd				= false;
	
	// �摜�f�[�^
	m_hPlayerGraohic		= LoadGraph("data/player.png");
	m_hShotGraphic			= LoadGraph("data/shot.png");
	m_hEnemyGraphc			= LoadGraph("data/enemy.png");
	m_hEnemySinGraphc		= LoadGraph("data/enemy2.png");
	m_hEnemyDesideGraphc	= LoadGraph("data/enemy3.png");
	m_hBackGraphic			= LoadGraph("data/Back.png");
	
	m_player.setHandle(m_hPlayerGraohic);
	m_player.init();

	float posX = 400.0f;
	for (auto& m_enemy : enemy)
	{
		m_enemy.setHandle(m_hEnemyGraphc);
		m_enemy.init();
		m_enemy.setPos(posX, 160.0f);
		posX += 80.0f;
	}

	float posx = 300.0f;
	for (auto& m_enemysin : enemysin)
	{
		m_enemysin.setHandle(m_hEnemySinGraphc);
		m_enemysin.init();
		m_enemysin.setPos(posx, 300.0f);
		posx += 100.0f;

	}

	float posY = 580;
	for (auto& m_enemydeside : enemydeside)
	{
		m_enemydeside.setHandle(m_hEnemyDesideGraphc);
		m_enemydeside.init();
		m_enemydeside.setPos(1200,posY);
		posY -= 90.0f;
	}

	m_player.setMain(this);
	m_enemy.setMain(this);
}

void SceneMain::end()
{
	// �摜�̊J��
	DeleteGraph(m_hPlayerGraohic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphc);
	DeleteGraph(m_hEnemySinGraphc);
	DeleteGraph(m_hEnemyDesideGraphc);
	DeleteGraph(m_hBackGraphic);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

void SceneMain::update()
{
	m_player.update();

	for (auto& m_enemy : enemy)
	{
		m_enemy.update();
	}
	for (auto& m_enemysin : enemysin)
	{
		m_enemysin.update();
	}
	for (auto& m_enemydeside : enemydeside)
	{
		m_enemydeside.update();
	}

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();

	// enemy�o�E���h����
	for (int i = 0; i < EnemyNum; i++)
	{
		for (int j = i + 1; j < EnemyNum; j++)
		{
			if (enemy[i].isDead())continue;

			// enemy[i]��enemy[j]�̓����蔻����Ƃ�
			Vec2  dist = enemy[i].getCenter() - enemy[j].getCenter();
			float radiusAdd = enemy[i].getRadius() + enemy[j].getRadius();
			if (dist.length() < radiusAdd)
			{
				// ���������ꍇ�̏���
				enemy[i].bound(enemy[j].getCenter());
				enemy[j].bound(enemy[i].getCenter());
			}
		}
	}

	// enemy��player�̓����蔻��
	for (int i = 0; i < EnemyNum; i++)
	{
		// Player��flag (false = ����)
		m_isEnd = false;
		if (player.isDead())continue;

		// enemy������ł����玀��enemy�\�����Ȃ�
		if (enemy[i].isDead())continue;		
		
		Vec2  dist = m_player.getCenter() - enemy[i].getCenter();
		float radiusAdd = enemy[i].getRadius() + m_player.getRadius();
		if (dist.length() < radiusAdd)
		{
			// ���������ꍇ�̏���
		//	DrawFormatString(400, 0, GetColor(255, 0, 0), "�Ԃ����Ă��܂���!");
			kPlayerCheck = true;
		}
		else
		{
			kPlayerCheck = false;
		}
		if (isPlayerCol() == true)
		{
			player.setDead();
			m_isEnd = true;
		}
	}

	// enemysin��player�̓����蔻��
	for (int i = 0; i < EnemySinNum; i++)
	{
		// player�����t���O
		m_isEnd = false;
		if (player.isDead())continue;

		// enemysin������ł����玀��enemysin�͕\�����Ȃ�
		if (enemysin[i].isDead())continue;

		Vec2 dist = m_player.getCenter() - enemysin[i].getCenter();
		float radiusAdd = enemysin[i].getRadius() + m_player.getRadius();
		if(dist.length() < radiusAdd)
		{
			// �f�o�b�N�p�F���������ꍇ�̏���
		//	DrawFormatString(800, 0, GetColor(225, 255, 0), "�Ԃ����Ă��܂����B");
			kPlayerCheck = true;
		}
		else
		{
			kPlayerCheck = false;
		}
		if (isPlayerCol() == true)
		{
			player.setDead();
			m_isEnd = true;
		}
	}

	for (int i = 0; i < EnemyDesideNum; i++)
	{
		// Player�����t���O
		m_isEnd = false;
		if (player.isDead())continue;

		//�@EnemyDeside������ł����玀��EnemyDeside�͕\�����Ȃ�
		if (enemydeside[i].isDead())continue;

		Vec2 dist = m_player.getCenter() - enemydeside[i].getCenter();
		float radiusAdd = enemydeside[i].getRadius() + m_player.getRadius();
		if (dist.length() < radiusAdd)
		{
			// �f�o�b�N�p�F���������ꍇ�̏���
		//	DrawFormatString(900, 0, GetColor(225, 225, 225), "�Ԃ����Ă��܂����B");
			kPlayerCheck = true;
		}
		else
		{
			kPlayerCheck = false;
		}
		if (isPlayerCol() == true)
		{
			player.setDead();
		}
	}

	
	while (it != m_pShotVt.end())
	{

		auto& pShot = (*it);

		assert(pShot);

		pShot->update();

		// enemy�ƒe�̓����蔻��
		for (int i = 0; i < EnemyNum; i++)
		{
			
			if (enemy[i].isDead())continue;

			Vec2 dist = (*pShot).getCenter() - enemy[i].getCenter();
			float radiusAdd = enemy[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
				// �f�o�b�N�p�F�e�����������ꍇ�̏���
			//	DrawFormatString(200, 0, GetColor(225, 0, 0), "�q�b�g�I");
				kCheck = true;
			}
			else
			{
				kCheck = false;
			}
			if (isCol() == true)
			{
				enemy[i].setDead();
				m_EnemyNum--;
			}
		}
	
		// enemysin�Ƌʂ̓����蔻��
		for (int i = 0; i < EnemySinNum; i++)
		{
			if (enemysin[i].isDead())continue;

			Vec2 dist = (*pShot).getCenter() - enemysin[i].getCenter();
			float radiusAdd = enemysin[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
				// �f�o�b�N�p�F�e�����������ꍇ�̏���
			//	DrawFormatString(800, 100, GetColor(225, 225, 0), "�q�b�g");
				kCheck = true;
			}
			else
			{
				kCheck = false;
			}
			if (isCol() == true)
			{
				enemysin[i].setDead();
				m_EnemySinNum--;
			}
		}

		// enemydeside�Ƌʂ̓����蔻��
		for (int i = 0; i < EnemyDesideNum; i++)
		{
			if (enemydeside[i].isDead())continue;

			Vec2 dist = (*pShot).getCenter() - enemydeside[i].getCenter();
			float radiusAdd = enemydeside[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
				// �f�o�b�N�p�F�e�����������ꍇ�̏���
			//	DrawFormatString(900, 100, GetColor(225, 225, 225), "�q�b�g");
				kCheck = true;
			}
			else
			{
				kCheck = false;
			}
			if (isCol() == true)
			{
				enemydeside[i].setDead();
				m_EnemyDesideNum--;
			}
		}

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			// vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}

		it++;
	}

	// ��ʂ���G�l�~�[or�v���C���[�����񂾂�I��
	if (m_EnemyNum == 0 && m_EnemySinNum == 0 && m_EnemyDesideNum == 0
		|| player.isDead())
	{
		if (player.isDead())
		{
			kMigration = true;
		}
		m_isEnd = true;
	}
}

void SceneMain::draw()
{
	DrawGraph(0,0,m_hBackGraphic,false);
	m_player.draw();
	for (auto& m_enemy : enemy)
	{
		m_enemy.draw();
	}
	for (auto& m_enemysin : enemysin)
	{
		m_enemysin.draw();
	}
	for (auto& m_enemydeside : enemydeside)
	{
		m_enemydeside.draw();
	}

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
}

// Enemy�̐�������̃`�F�b�N
bool SceneMain::isCol()
{
	if(kCheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Player�̐�������̃`�F�b�N
bool SceneMain::isPlayerCol()
{
	if (kPlayerCheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SceneMain::Migration()
{
	bool check;
	check = kMigration;
	return check;
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

