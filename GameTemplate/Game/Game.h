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
	/// サンプル
	/// <para>夢いっぱい、サンプルいっぱい</para>
	/// </summary>
	void Sample();	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ポストレンダー
	/// </summary>
	void PostRender();
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
	Sprite m_copyMainRtToFrameBufferSprite;					//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	SoundSource	m_se;										//サウンドソース
	Effect* effect = nullptr;								//エフェクト
	RenderTarget m_mainRenderTarget;						//メインレンダーターゲット
	ID3D11RenderTargetView* m_frameBufferRenderTargetView= nullptr;	//フレームRTV
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームDSV
	D3D11_VIEWPORT m_frameBufferViewports;					//フレームビューポート
	myEngine::PostEffect m_postEffect;								//ブルーム
	KaitoTask* m_task = nullptr;							//プレイヤー作ってるクラス。
	Stage* stage = nullptr;									//ステージ
};

static inline Game& GameObj()
{
	return Game::getGameInstance();
}