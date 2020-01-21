/// <summary>
/// 定数バッファ
/// </summary>
/// <remarks>
/// 参考URL参照
/// </remarks>

#pragma once

#include "GPUBuffer/GPUBuffer.h"

namespace myEngine {
	class ConstantBuffer : public GPUBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();
		/// <summary>
		/// 定数バッファの作成
		/// </summary>
		/// <param name="pInitData">初期データ</param>
		/// <param name="bufferSize">バッファのサイズ</param>
		/// <returns></returns>
		bool Create(const void*pInitData, int bufferSize);
	};

}

