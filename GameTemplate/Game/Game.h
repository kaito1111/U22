#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"
#include "stageObject/Goal.h"

class KaitoTask;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void SetStage(int num) {
		StageNum = num;
	}
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
private:
	Goal* goalPtr = nullptr;
	int StageNum = 0;
	SpriteRender* m_test = nullptr;							//スプライトレンダー
	Sprite m_copyMainRtToFrameBufferSprite;					//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	SoundSource	m_se;										//サウンドソース
	Effect* effect = nullptr;								//エフェクト
	RenderTarget m_mainRenderTarget;						//メインレンダーターゲット
	ID3D11RenderTargetView* m_frameBufferRenderTargetView;	//フレームRTV
	ID3D11DepthStencilView* m_frameBufferDepthStencilView;	//フレームDSV
	D3D11_VIEWPORT m_frameBufferViewports;					//フレームビューポート
	myEngine::PostEffect m_postEffect;								//ブルーム
	KaitoTask* m_task = nullptr;
};