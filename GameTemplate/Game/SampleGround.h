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
	SkinModelRender* skin;						//ƒXƒLƒ“ƒ‚ƒfƒ‹
	PhysicsStaticObject physicsGround;			//“–‚½‚è”»’è
};

