#pragma once

#include "Sample/DebugMan.h"

class SampleGround;

static const float GRAVITY = -1.0f;

class SampleScene : public IGameObject
{
public:
	SampleScene();		//�R���X�g���N�^
	~SampleScene();	//�f�X�g���N�^
	bool Start() override;		//�X�^�[�g
	void Update() override;							//�A�b�v�f�[�g
	//static const float GRAVITY;						//�d�͂͋���  �d�͂�Scene�̎����؂ꂽ�炢��Ȃ��B

private:
	SampleGround* m_ground = nullptr;		
	DebugMan* m_debugMan = nullptr;
	CVector3 Target = CVector3::Zero();
};
//const float SampleScene::GRAVITY = -1.0f;

