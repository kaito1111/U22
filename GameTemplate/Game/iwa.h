#pragma once
#include "Magnet.h"
class Iwa : public IGameObject ,public Magnet
{ 
public:
	Iwa(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
	~Iwa();

	void Draw();
	void Update();

private:
	SkinModel * m_model = nullptr;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

