#include "stdafx.h"

#include "Game.h"
#include "Player.h"
#include"Stage.h"
#include"stageObject1.h"
#include "GameCamera.h"
#include "graphics/Shader.h"
#include "graphics/2D/ex2D.h"
#include "GPUView/ShaderResourceView.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	NewGO< GameCamera>(1, "camera");
	Player* player = NewGO<Player>(1, "player");
	Stage* stage = NewGO<Stage>(1, "stage");
	//ex2D* ex2d = NewGO<ex2D>(1, "ex2D");
	stageObject1* UpDownToge = NewGO<stageObject1>(1, "upDownToge");
	ShaderResourceView m_shader;
	m_shader.CreateFromDDSTextureFromFile(L"Assets/sprite/titletest.dds");
	m_test.Init(m_shader.GetBody(), 500.0, 500.0f);

	return true;
}

void Game::Update()
{
	m_test.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Game::Draw()
{
	m_test.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
