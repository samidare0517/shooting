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

	// 弾の生成
	virtual bool createShotNormal(Vec2 pos);

	// チェック類
	virtual bool isEnd() { return m_isEnd; }

	virtual bool isCol(); 

	virtual bool isPlayerCol();

private:
	// テキスト表示位置変更
	int m_textPosX;
	int m_textVecX;

	// プレイヤーのグラフィックハンドル
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

	// ショット
	std::vector<ShotBase*> m_pShotVt;
};