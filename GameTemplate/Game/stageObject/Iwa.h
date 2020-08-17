#pragma once
#include "character/CharacterController.h"
#include "Magnet/Magnet.h"
#include "character/BoxCharactorController.h"
class Iwa : public IGameObject
{
public:
	Iwa();
	~Iwa();

	bool Start();
	void Update();

	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}
private:
	Magnet* m_magnet = nullptr;
	SkinModelRender* m_model = nullptr;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	BoxCharactorController m_CharaCon;
	CVector3 m_moveSpeed = CVector3::Zero();
};