#include "stdafx.h"
#include "Goal.h"
#include "Player.h"
#include "DirectionLight.h"

Goal::Goal(const wchar_t * modelName, CVector3 pos, CQuaternion rot)
{
	m_Skin.Init(modelName);
	m_Position = pos;
	m_rot = rot;
}

Goal::~Goal()
{
}

bool Goal::Start()
{
	m_Skin.Init(L"Assets/modelData/Goal.cmo");
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");
	return true;
}

void Goal::Update()
{
	const float Len = 50.0f;				//ÉSÅ[ÉãÇÃîºåa
	const int clearNum = 2;
	int i;
	for (i = 0; i < clearNum;) {
		CVector3 diff = m_player[i]->GetPosition() - m_Position;
		float playerLen = diff.Length();
		if (playerLen < Len) {
			i++;
		}
		else {
			break;
		}
	}
	if (i == clearNum) {
		Effect* effect = NewGO<Effect>(1);
		if (!effect->IsPlay()) {
			effect->Play(L"Assets/effect/hemohage.efk");
			effect->SetPosition(m_Position);
			effect->SetScale(CVector3::One() * 20);
		}
	}
	m_Skin.UpdateWorldMatrix(m_Position, CQuaternion::Identity(), CVector3::One());
}

void Goal::Draw()
{
	m_Skin.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
