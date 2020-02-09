/// <summary>
/// エフェクトのサンプルコード
/// </summary>

#pragma once

#include "Player.h"
class exEffect : public IGameObject
{
public:
	exEffect();
	~exEffect();
	void Update();
private:
	Player* player = FindGO<Player>("player", false);	//デバッグ時に使うだけなので通常は必要ないです。
	Effect* effect = NewGO<Effect>(0); 					//エフェクトの作成
	CVector3 m_pos = CVector3::Zero();					//座標
};

