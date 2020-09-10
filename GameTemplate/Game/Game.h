#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"
#include "stageObject/Goal.h"
#include "PlayerData.h"
class KaitoTask;
class PlayerData;
class Stage;
class Game : public PlayerData
{
public:
	Game();
	~Game();
	void SetStage(int num) {
		StageNum = num;
	}
	void setCon(bool con)
	{
		Continue = con;
	}
	void setAll(CVector3 pl1, CVector3 pl2, int sNum) {
		player1Pos = pl1;
		player2Pos = pl2;
		StageNum = sNum;
	}
private:
	/// <summary>
	/// �X�^�[�g
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;
	/// <summary>
	/// �T���v��
	/// <para>�������ς��A�T���v�������ς�</para>
	/// </summary>
	void Sample();	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �|�X�g�����_�[
	/// </summary>
	void PostRender();
private:
	bool Continue = false;
	CVector3 player1Pos = CVector3::Zero();
	CVector3 player2Pos = CVector3::Zero();
	int StageNum = 0;
	SpriteRender* m_test = nullptr;							//�X�v���C�g�����_�[
	Sprite m_copyMainRtToFrameBufferSprite;					//���C��RTV�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
	SoundSource	m_se;										//�T�E���h�\�[�X
	Effect* effect = nullptr;								//�G�t�F�N�g
	RenderTarget m_mainRenderTarget;						//���C�������_�[�^�[�Q�b�g
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[��RTV
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[��DSV
	D3D11_VIEWPORT m_frameBufferViewports;					//�t���[���r���[�|�[�g
	myEngine::PostEffect m_postEffect;								//�u���[��
	KaitoTask* m_task = nullptr;
};