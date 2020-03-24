#pragma once
#include"physics/PhysicsStaticObject.h"
class Floor : public IGameObject
{
public:
	Floor();
	~Floor();
	bool Start();
	void Update();
	void setPos(const CVector3& pos) {
		m_pos = pos;
	}
private:
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject atariHantei;
};

