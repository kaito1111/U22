/// <summary>
/// 2Dサンプルコード
/// </summary>
/// <remarks>
/// 2Dのサンプルコードです。
/// NewGOするとUnitychanの皮がでます
/// </remarks>

#include "stdafx.h"
#include "GameCamera.h"
#include "ex2D.h"

namespace myEngine {
	ex2D::ex2D()
	{
		//スプライトレンダーのポインタ
		spriteRender = NewGO<SpriteRender>(0);
		//ファイルパスの読み込み
		spriteRender->Init(L"Assets/sprite/utc_all2.dds", 200.0f, 200.0f, false);
		//透明度の設定
		spriteRender->SetW(0.5f);
	}


	ex2D::~ex2D()
	{
	}

	void ex2D::Update()
	{
		//ワールド座標の更新
		spriteRender->Update();
	}

	void ex2D::Draw()
	{
		//描画
		spriteRender->Draw();
	}
}
