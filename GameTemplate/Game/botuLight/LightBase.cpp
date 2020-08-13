/// <summary>
/// ライトの基底クラス
/// </summary>
/// <remarks>
/// ライトが作られたらリストに追加
/// ライトが消されたらリストから削除
/// するようにライトマネージャに指示を出す
/// </remarks>

#include "stdafx.h"
#include "LightBase.h"

bool LightBase::Start()
{
	Engine().GetGraphicsEngine().GetLightManager().AddLight(this);
	return true;//StartSub();
}

LightBase::~LightBase()
{
	Engine().GetGraphicsEngine().GetLightManager().RemoveLight(this);
}
