#pragma once

#include "Skeleton.h"
#include "Shader.h"

/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	
	/// <summary>
	/// �����f���`��i���Ƃ��炱�̃G���W���ɂ�������j
	/// <para>---!!CAUTION!!---</para>
	/// <para>����Draw�֐��͏����\�肪����̂Ŏg��Ȃ��ł��������B</para>
	/// <para>������̊֐����g���Ă���N���X������Ȃ�A�����Е���Draw�Ɉ����z�������肢���܂��B</para>
	/// <para>---!!CAUTION!!---</para>
	/// </summary>
	/// <remarks>
	/// ����Draw�֐������ɔ����폜����\�肪����֐��ł��B
	/// �����@�\�Ƃ��Ă̓V���G�b�g�`�悪�ł��邩�ۂ��̍������Ȃ��̂ŁA
	/// �C�ɂ����������Draw�֐����g���Ă��������B
	/// </remarks>
	/// <param name="viewMatrix"></param>
	/// <param name="projMatrix"></param>
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );
	/// <summary>
	/// �V���G�b�g�`��or�`��
	/// <para>0���ʏ�`��A1���V���G�b�g�`��</para>
	/// <para>�V���G�b�g�`��̏ڍׂ͂��̊֐���Remarks�ɏ����Ă���̂ŁA</para>
	/// <para>������Q�l�ɃV���G�b�g�`����������Ă��������B</para>
	/// </summary>
	/// <remarks>
	/// -----�V���G�b�g�`��̕��@�ɂ���-----
	/// 1.�V���G�b�g���f�������I�u�W�F�N�g��`��i�ǌn)
	/// 2.�V���G�b�g�ɂȂ�I�u�W�F�N�g(Player�n)���V���G�b�g�`��i RenderMode = 1 �j
	/// 3.2�̃I�u�W�F�N�g��ʏ�`��i RenderMode = 0 �j
	/// ���Ԃ��ԈႦ���肷��ƃV���G�b�g���f��Ȃ�������A�ςȂƂ���ɃV���G�b�g���f��̂�
	/// ��������`�揇�Ԃ��m�F���Ă����Ă��������B
	/// --------------------------------------
	/// </remarks>
	/// <param name="viewMatrix">�J�����s��</param>
	/// <param name="projMatrix">�v���W�F�N�V�����s��</param>
	/// <param name="RenderMode">/�`�惂�[�h/ 0->�ʏ�`�� 1->�V���G�b�g�`��</param>
	void Draw(CMatrix viewMatrix, CMatrix projMatrix, int RenderMode);
	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};
private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	
private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
};

