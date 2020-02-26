/// <summary>
/// ディレクションライト
/// </summary>
/// <remarks>カメラのカラー、方向、生データを返す程度のクラス</remarks>

#include "stdafx.h"
#include "DirectionLight.h"
#include "light.h"

namespace myEngine {
	DirectionLight::DirectionLight()
	{
		//初期化
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