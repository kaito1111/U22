#include "stdafx.h"
#include "Game.h"
#include"Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"

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
	//NewGO< KaitoTask>(3, "kaito");
	//Stage* stage = NewGO<Stage>(2, "stage");

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
		//ex2D* ex2d = NewGO<ex2D>(4, "ex2D");

		//�G�t�F�N�g�̍쐬
		Effect* effect = NewGO<Effect>(1);
		effect->Play(L"Assets/effect/test.efk");
		effect->SetPosition({ 0,0, 0 });
		effect->SetScale(CVector3::One() * 20);

		//�T�E���h�̍Đ�
		m_se.Play(false);
	}
}