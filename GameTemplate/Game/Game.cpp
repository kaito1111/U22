#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"
#include "DebugMan.h"
#include "GameCamera.h"

Game::Game()
{
	//�T�E���h�̏�����
	m_se.Init(L"Assets/sound/coinGet.wav");
}

Game::~Game()
{
}

bool Game::Start()
{
	//Stage* stage = NewGO<Stage>(0, "stage");
	NewGO< KaitoTask>(2, "kaito");
	//NewGO<DirectionLight>(3, "light");

	effect = NewGO<Effect>(1);

	return true;
}

void Game::Update()
{
	Sample();
}

//���낢��ȃT���v��
void Game::Sample()
{
	if (GetAsyncKeyState('H'))
	{
		//2D�̃T���v��
		ex2D* ex2d = NewGO<ex2D>(4, "ex2D");
		
		//�f�o�b�O�pUnitychan��NewGO
		NewGO<DebugMan>(0, "debugman");

		//�G�t�F�N�g�̍쐬
		if (!effect->IsPlay()) {
			effect = NewGO<Effect>(1);
			effect->Play(L"Assets/effect/test.efk");
			effect->SetPosition({ 0,0, 0 });
			effect->SetScale(CVector3::One() * 20);
		}
		//�T�E���h�̍Đ�
		m_se.Play(false);
	}
}