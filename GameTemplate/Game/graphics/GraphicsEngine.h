#pragma once

/// <summary>
/// �����_�����O���[�h
/// </summary>
enum EnRenderMode {
	enRenderMode_Normal,			//�ʏ�`��
	enRenderMode_CreateSilhouette,	//�V���G�b�g�`��
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v����
	enRenderMode_Num				//�����_�����O���[�h�̐�
};	

/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */

#include "light/LightManager.h"
#include "Shadow/ShadowMap.h"
#include "2D/Sprite.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/// <summary>
	/// �G�t�F�N�T�[�̏�����
	/// </summary>
	void InitEffekseer();
	/*!
	 *@brief	����B
	 */
	void Release();
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ� '�[�x�X�e���V���r���[�͕ύX���Ȃ�Ver'
	/// <para>�r���[�|�[�g���w�肵�Ȃ��ꍇ��nullptr�𑗂��Ă�������</para>
	/// </summary>
	/// <param name="dc">�f�o�R��</param>
	/// <param name="rtv">�����_�����O�^�[�Q�b�g�r���[</param>
	/// <param name="dsv">�[�x�X�e���V���r���[</param>
	/// <param name="vp">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* dc, RenderTarget* rtv, D3D11_VIEWPORT* vp);
	/// <summary>
	/// �����_�[�^�[�Q�b�g��ύX '�[�x�X�e���V���r���[���ύX����Ver' 
	/// <para>�r���[�|�[�g���w�肵�Ȃ��ꍇ��nullptr�𑗂��Ă�������</para>
	/// </summary>
	/// <param name="dc">�f�o�R��</param>
	/// <param name="rtv">�����_�[�^�[�Q�b�g�r���[</param>
	/// <param name="dsv">�f�v�X�X�e���V���r���[</param>
	/// <param name="vp">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* dc, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv, D3D11_VIEWPORT* vp);
	/// <summary>
	/// �����_�[�^�[�Q�b�g�Ƃ��̃o�b�N�A�b�v
	/// </summary>
	void oldTarget();
	/// /// <summary>
	/// �t�H���[�h�����_�[�^�[�Q�b�g
	/// </summary>
	void OffScreenRenderTarget();
	/// <summary>
	/// �|�X�g�����_�[�^�[�Q�b�g
	/// </summary>
	void PostRenderTarget();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice() const
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// �o�b�N�o�b�t�@�[���擾
	/// </summary>
	/// <returns></returns>
	ID3D11RenderTargetView* GetBuckBuffer()
	{
		return m_backBuffer;
	}
	/// <summary>
	/// ���C�g�}�l�[�W���[�̎擾
	/// </summary>
	/// <returns></returns>
	myEngine::LightManager* GetLigManager()
	{
		return m_ligManager;
	}
	/// <summary>
	/// �V���h�E�}�b�v���擾
	/// </summary>
	/// <returns></returns>
	myEngine::ShadowMap* GetShadowMap()
	{
		return m_shadowMap;
	}
	/// <summary>
	/// �I�t�X�N���[�������_�[�^�[�Q�b�g���擾
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetOffScreenRenderTarget()
	{
		return m_mainRenderTarget;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;								//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;						//D3D11�f�o�C�X�B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;					//D3D11�f�o�C�X�R���e�L�X�g�B		
	IDXGISwapChain*			m_pSwapChain = NULL;						//�X���b�v�`�F�C���B
	ID3D11RenderTargetView* m_backBuffer = NULL;						//�o�b�N�o�b�t�@�B
	RenderTarget* m_mainRenderTarget = NULL;							//���C�������_�[�^�[�Q�b�g
	ID3D11RenderTargetView* m_frameBufferRenderTargetView;				//�t���[��RTV
	ID3D11DepthStencilView* m_frameBufferDepthStencilView;				//�t���[��DSV
	ID3D11BlendState*		m_blendState = nullptr;								//�u�����h�X�e�[�g�i�e�X�g�j
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���r���[�|�[�g
	ID3D11RasterizerState*	m_rasterizerState = NULL;					//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;						//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;					//�f�v�X�X�e���V���r���[�B
	myEngine::Sprite* m_copyMainRtToFrameBufferSprite;					//�I�t�X�N���[�������_�����O�p�̃X�v���C�g
	myEngine::LightManager* m_ligManager = nullptr;						//���C�g�}�l�[�W���[ �O���t�B�b�N�G���W����NewGO���Ă�
	myEngine::ShadowMap* m_shadowMap;									//�V���h�E�}�b�v

	//���������O���t�B�b�N�G���W�������菜�����ϐ��ꗗ
	/*
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�r���[�|�[�g
	ID3D11DeviceContext*	m_pImmediateContext = NULL;					//�����R���e�L�X�g
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	D3D11_FEATURE_DATA_THREADING m_featureDataThreading;
	*/
};
