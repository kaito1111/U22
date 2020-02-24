/// <summary>
/// 各種ライト
/// <remarks>ライトの構造体はここに定義</remarks>
/// </summary>

#pragma once

#include "math/Vector.h"

namespace myEngine {
	/// <summary>
	/// ディレクションライト
	/// </summary>
	struct SDirectionLight {
		CVector4 color;		//ライトの色
		CVector3 direction;	//ライトの向き
	};
}