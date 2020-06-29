#pragma once
#include "SampleGround.h"
#include "Sample/DebugMan.h"

static const float GRAVITY = -1.0f;

class SampleScene : public IGameObject
{
public:
	SampleScene();		//�R���X�g���N�^
	~SampleScene();	//�f�X�g���N�^
	bool Start() override { return true; } ;		//�X�^�[�g
	void Update() override;							//�A�b�v�f�[�g
	//static const float GRAVITY;						//�d�͂͋���  �d�͂�Scene�̎����؂ꂽ�炢��Ȃ��B

private:
	SampleGround* m_ground = nullptr;
	DebugMan* m_debugMan = nullptr;
	
};
//const float SampleScene::GRAVITY = -1.0f;

