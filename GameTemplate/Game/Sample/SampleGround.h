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
	SkinModelRender* skin;						//スキンモデル
	PhysicsStaticObject physicsGround;			//当たり判定
	Effect* m_effect1 = nullptr;				//サンプルエフェクト1
	Effect* m_effect2 = nullptr;				//サンプルエフェクト2
};

