#pragma once
#include "physics/PhysicsStaticObject.h"

class SampleGround : public IGameObject
{
public:
	SampleGround();
	~SampleGround();
private:
	bool Start() override;
	void Update() override;
private:
	CVector3 pos = CVector3::Zero();
	CVector3 scale = CVector3::One(); 
	CQuaternion qRot = CQuaternion::Identity();
	SkinModelRender* skin;						//�X�L�����f��
	PhysicsStaticObject physicsGround;			//�����蔻��
	Effect* m_effect1 = nullptr;				//�T���v���G�t�F�N�g1
	Effect* m_effect2 = nullptr;				//�T���v���G�t�F�N�g2
};

