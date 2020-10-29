#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"
#include "Sample/DebugMan.h"
#include "StageSelect/TitleStage.h"
#include "stageObject/Goal.h"
#include "level/Level.h"
#include "StageSelect/StageSelect.h"
#include "CheckPointgenerator.h"
#include "Player.h"
Game::Game()
{
	//�T�E���h�̏�����
	m_se.Init(L"Assets/sound/coinGet.wav");

	//���C�������_�[�^�[�Q�b�g�ɂ����ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂ɃX�v���C�g��������
	m_copyMainRtToFrameBufferSprite.Init(
		Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

}

Game::~Game()
{
	DeleteGO(m_task);//1��
}

bool Game::Start()
{
	//1�Ԗ�
	m_task = NewGO<KaitoTask>(2,"kaitoTask");

	//2�Ԗ�
	//StageSelect* stage = NewGO<StageSelect>(0, "stageselect");
	m_Stage = NewGO<Stage>(0, "stage");
	m_Stage->setStageNum(StageNum);
	//NewGO<DirectionLight>(3, "light");
	effect = NewGO<Effect>(1);		
	//CheckPointgenerator* PointGenerator = NewGO< CheckPointgenerator>(0, "checkpointgenerator");
	//PointGenerator->Load(L"Assets/level/Corse_Level_1.tkl");
	//if (Continue) {
	//	GamePlayer* pl1 = FindGO<GamePlayer>("player1");
	//	GamePlayer* pl2 = FindGO<GamePlayer>("player2");
	//	pl1->SetPosition(player1Pos);
	//	pl2->SetPosition(player2Pos);
	//}
	return true;
}

void Game::Update()
{
	//if (g_Pad[0].IsTrigger(enButtonDown)) {
	//	
	//	DeleteGO(this);
	//}
	Sample();
	m_postEffect.Update();
}

void Game::OnDestroy()
{
	DeleteGO(m_Stage);
}

//���낢��ȃT���v��
void Game::Sample()
{
	if (GetAsyncKeyState('H'))
	{
		//2D�̃T���v��
		//ex2D* ex2d = NewGO<ex2D>(4, "ex2D");
		
		//�f�o�b�O�pUnitychan��NewGO
		//NewGO<DebugMan>(0, "debugman");

		//�G�t�F�N�g�̍쐬
		if (!effect->IsPlay()) {
			effect = NewGO<Effect>(1);
			effect->Play(L"Assets/effect/SMode.efk");
			effect->SetPosition({ 100,0, 0 });
			effect->SetScale(CVector3::One() * 2);
		}
		//�T�E���h�̍Đ�
		m_se.Play(false);
	}
}

void Game::Draw()
{
	//~Draw����
}

void Game::PostRender()
{
	//�|�X�g�G�t�F�N�g�`��
	//m_postEffect.Draw();

	auto a = Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV();

	//�h���[
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}