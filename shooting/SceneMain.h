#pragma once
#include "SceneBase.h"
#include "ShotBase.h"
#include "enemy.h"
#include "Player.h"
#include "SceneTitle.h"
#include <vector>

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_textPosX = 0;
		m_textVecX = 0;
		m_isEnd = false;
		m_hPlayerGraohic = -1;
		m_hShotGraphic = -1;
		m_hEnemyGraphc = -1;
		m_hEnemySinGraphc = -1;
		m_hEnemyDesideGraphc = -1;
		m_hBackGraphic = -1;
		m_EnemyNum = 0;
		
	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();

	virtual bool Migration();

	// �e�̐���
	virtual bool createShotNormal(Vec2 pos);

	// �`�F�b�N��
	virtual bool isEnd() { return m_isEnd; }

	virtual bool isCol(); 

	virtual bool isPlayerCol();

private:
	// �e�L�X�g�\���ʒu�ύX
	int m_textPosX;
	int m_textVecX;

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraohic;
	int m_hShotGraphic;
	int m_hEnemyGraphc;
	int m_hEnemySinGraphc;
	int m_hEnemyDesideGraphc;
	int m_hBackGraphic;

	int m_EnemyNum;
	int m_EnemySinNum;
	int m_EnemyDesideNum;
	bool m_isEnd;
	

	Enemy m_enemy;
	EnemySin m_enemysin;
	EnemyDeside m_enemydeside;
	Player m_player;

	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
};