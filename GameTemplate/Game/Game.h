#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"
#include "stageObject/Goal.h"
#include "PlayerData.h"
class KaitoTask;
class PlayerData;
class Stage;
class Game : public PlayerData
{
public:
	Game();
	~Game();
	void SetStage(int num) {
		StageNum = num;
	}
	void setCon(bool con)
	{
		Continue = con;
	}
	void setAll(CVector3 pl1, CVector3 pl2, int sNum) {
		player1Pos = pl1;
		player2Pos = pl2;
		StageNum = sNum;
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
	bool Continue = false;
	CVector3 player1Pos = CVector3::Zero();
	CVector3 player2Pos = CVector3::Zero();
	int StageNum = 0;
	SpriteRender* m_test = nullptr;							//スプライトレンダー
	Sprite m_copyMainRtToFrameBufferSprite;					//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	SoundSource	m_se;										//サウンドソース
	Effect* effect = nullptr;								//エフェクト
	RenderTarget m_mainRenderTarget;						//メインレンダーターゲット
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームRTV
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームDSV
	D3D11_VIEWPORT m_frameBufferViewports;					//フレームビューポート
	myEngine::PostEffect m_postEffect;								//ブルーム
	KaitoTask* m_task = nullptr;
};