#pragma once

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"


class SceneManager
{
public:
	// シーンの種類定義
	typedef enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindResult,
	

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	void init(SceneKind kind = kSceneKindTitle);
	void end();

	void update();
	void draw();


private:
	SceneKind	m_kind;

	SceneTitle	m_title;
	SceneMain	m_main;
	SceneResult m_result;
};