/// <summary>
/// �e�탉�C�g
/// <remarks>���C�g�̍\���̂͂����ɒ�`</remarks>
/// </summary>

#pragma once

#include "math/Vector.h"

namespace myEngine {
	/// <summary>
	/// �f�B���N�V�������C�g
	/// </summary>
	struct SDirectionLight {
		CVector4 color;		//���C�g�̐F
		CVector3 direction;	//���C�g�̌���
	};
}