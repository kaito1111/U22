/// <summary>
/// �萔�o�b�t�@
/// </summary>
/// <remarks>
/// �Q�lURL�Q��
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
		/// �萔�o�b�t�@�̍쐬
		/// </summary>
		/// <param name="pInitData">�����f�[�^</param>
		/// <param name="bufferSize">�o�b�t�@�̃T�C�Y</param>
		/// <returns></returns>
		bool Create(const void*pInitData, int bufferSize);
	};

}

