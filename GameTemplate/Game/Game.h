#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"

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
	SpriteRender* m_test=nullptr;		//スプライトレンダー
	SoundSource	m_se;					//サウンドソース
	Effect* effect = nullptr;			//エフェクト
};