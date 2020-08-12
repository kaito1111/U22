#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"
#include "Stage.h"
class KaitoTask;

class Game : public IGameObject
{
public:
	Game();
	~Game();
private:
	/// <summary>
	/// スタート
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
public:
	/// <summary>
	/// ゲームのインスタンス取得
	/// </summary>
	/// <returns></returns>
	static Game& getGameInstance()
	{
		static Game Instance;
		return Instance;
	}
private:
	SpriteRender* m_test = nullptr;							//スプライトレンダー
	KaitoTask* m_task = nullptr;							//プレイヤー作ってるクラス。
	Stage* stage = nullptr;									//ステージ
};

static inline Game& GameObj()
{
	return Game::getGameInstance();
}