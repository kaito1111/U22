/// <summary>
/// �f�B���N�V�������C�g
/// </summary>
/// <remarks>�J�����̃J���[�A�����A���f�[�^��Ԃ����x�̃N���X</remarks>

#include "stdafx.h"
#include "DirectionLight.h"
#include "light.h"

namespace myEngine {
	DirectionLight::DirectionLight()
	{
		//������
		m_lig.color = CVector3::One();
		m_lig.direction = CVector3::Down();
	}
	DirectionLight::~DirectionLight()
	{

	}
	bool DirectionLight::StartSub()
	{
		return true;
	}
	void DirectionLight::Update()
	{
	}
	void DirectionLight::SetDirection(const CVector3& direction)
	{
		m_lig.direction = direction;
	}
	void DirectionLight::SetColor(const CVector4& color)
	{
		m_lig.color = color;
	}
}