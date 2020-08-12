/// <summary>
/// ���C�g�̊Ǘ���
/// </summary>
/// <remarks>
/// 1.���C�g�̃o�b�t�@�[�̏�����
/// 2.���C�g�̃��X�g�Ǘ�
/// </remarks>

#include "stdafx.h"
#include "bLightManager.h"
#include "bDirectionLight.h"

namespace myEngine {
	LightManager::LightManager()
	{
	}
	LightManager::~LightManager()
	{
	}
	void LightManager::Init()
	{
		//���s���C�g�̍\���̃o�b�t�@�[��������
		InitDirectionLightStructuredBuffer();
		//GPUBuffer�̍쐬
		m_lightParamCB.Create(&m_lightParam, sizeof(m_lightParam));
	}
	void LightManager::InitDirectionLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SDirectionLight);			//�f�[�^�̊Ԋu

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h
		desc.ByteWidth = stride * MAX_DIRECTION_LIGHT;	//�f�[�^��
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_directionLightSB.Create(NULL, desc);			//�X�g���N�`���[�o�b�t�@�̍쐬
	}
	void LightManager::AddLight(LightBase* light)
	{
		if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
			/*
			!!throw!!
			�f�B���N�V�������C�g��肷���ĂȂ��H�H
			MAX_DIRECTION_LIGHT���Q�Ƃ��Ēl���m�F����
			!!throw!!
			*/
			throw;
		}
		//typeinfo = type_id�̕ԋp�l��ۑ�����N���X ��null���Ɨ�O
		//typeid = �^�̏��
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(myEngine::DirectionLight)) {
			//�^���f�B���N�V�������C�g�������I

			//�f�B���N�V�������C�g���X�g�ɍ���ǉ����郉�C�g���ǉ����ꂢ�邩�̌���
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light);
			if(findIt == m_directionLights.end()) {
				//�o�^����Ă��Ȃ��̂ŐV�K�o�^
				//�f�B���N�V�������C�g�֌^�ϊ�
				//reinterpret_cast = ������template�̃N���X�ɋ����I�Ȍ^�ϊ� 
				m_directionLights.push_back(reinterpret_cast<DirectionLight*>(light));
			}
			else {
				/*
				!!thorw!!
				���łɓo�^����Ă�I�I
				��{�I�ɓo�^����Ă�̂��������o�^����̂͂Ȃ񂩂̃~�X���Ǝv������
				throw����悤�ɂ��Ă܂����A�d�l��˂񃏃��B�Ƃ�������throw���R�����g�A�E�g���Ă�������
				!!thorw!!
				*/
				throw;
				return;
			}
		}
	}
	void LightManager::RemoveLight(LightBase* light)
	{
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(DirectionLight)) {
			//�f�B���N�V�������C�g���I
			m_directionLights.erase(
				//���񃊃X�g����폜���郉�C�g���������č폜
				std::remove(m_directionLights.begin(), m_directionLights.end(), light),
				m_directionLights.end()
			);
		}
	}
	void LightManager::Update()
	{
		m_lightParam.eyePos = g_camera3D.GetPosition();
		//�f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@�̍X�V
		//���C�g�̐�
		int ligNo = 0;
		//�f�B���N�V�������C�g�̓o�^�񐔃��X�g���X�V
		for (auto lig : m_directionLights) {
			if (lig->IsActive() == false) {
				//�A�N�e�B�u����Ȃ��̂ŃX�L�b�v
				continue;
			}
			//�A�N�e�B�u�ȓz�̓��C�g�̃f�[�^��������
			m_rawDirectionLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		//�f�B���N�V�������C�g�̐�
		int numDirLig = ligNo;
		//���C�g�̐��̏�����
		ligNo = 0;

		//���S�Ȍ^�ϊ�
		m_lightParam.numDirectionLight = static_cast<int>(numDirLig);
	}
	void LightManager::SendLightParamToGPU()
	{
		//�f�o�C�X�R���e�L�X�g
		auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
		//���C�g�̊�Տ��̑��M�B
		dc->UpdateSubresource(m_lightParamCB.GetBody(), 0, NULL, &m_lightParam, 0, 0);
		//�f�B���N�V�������C�g�̃p�����[�^�[�𑗐M�B
		dc->UpdateSubresource(m_directionLightSB.GetBody(), 0, NULL, m_rawDirectionLights, 0, 0);
		//���\�[�X�ݒ�B
		dc->PSSetShaderResources(enSkinModelSRVReg_Light, 1, &m_directionLightSB.GetSRV().GetBody());
		//�萔�o�b�t�@�ݒ�B
		dc->PSSetConstantBuffers(enSkinModelCBReg_Light, 1, &m_lightParamCB.GetBody());
	}
	void LightManager::EndRender()
	{
		//�f�o�C�X�R���e�L�X�g
		auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
		//�����_�[�ݒ�����ǂ��H
		dc->PSSetShaderResources(100, 1, NULL);
	}
}

