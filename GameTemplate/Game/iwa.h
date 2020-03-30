#pragma once
#include "Magnet/Magnet.h"
class Iwa : public IGameObject
{ 
public:
	Iwa();
	~Iwa();

	void Draw();
	void Update();

private:
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

