#pragma once
//class TitleStage;
class GameCamera;
class Player;
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

private:
	//TitleStage*7
	GameCamera* m_GameCamera = nullptr;
	Player* m_Player[2] = {};
};