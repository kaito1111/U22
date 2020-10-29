#pragma once
//class TitleStage;

#include "Player.h"
class GameCamera;
class KaitoTask : public IGameObject
{
public:
	KaitoTask();
	~KaitoTask();

	/// <summary>
	/// プレレンダー
	/// <para>shadowMap関連の処理</para>
	/// </summary>
	/// <remarks>
	/// PlayerクラスにかくとPlayer1側のSkinModelしかとれないので
	/// ここに書きます。
	/// </remarks>
	void PreRender();
	bool Start();
	void Update();
	void OnDestroy()override;
private:
	//TitleStage*7
	GameCamera* m_GameCamera = nullptr;
    GamePlayer* m_Player[2] = {};

};