/// <summary>
/// ���C�g�̊��N���X
/// </summary>
/// <remarks>
/// ���C�g�����ꂽ�烊�X�g�ɒǉ�
/// ���C�g�������ꂽ�烊�X�g����폜
/// ����悤�Ƀ��C�g�}�l�[�W���Ɏw�����o��
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
