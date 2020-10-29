#pragma once
#include "character/CharacterController.h"
class TitlePlayer : IGameObject
{
public:
	TitlePlayer();
	~TitlePlayer();

private:
	bool Start();
	void Update();
private:
	enum AnimationPattern {
		Idol,
		Run,
		AnimeNum
	};
	bool IsLeft = 0;
	SkinModelRender* m_PlayerSkin = nullptr;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();	
	float m_Angle = 0;
	Animation m_Anime;
	CharacterController m_CharaCon;
};