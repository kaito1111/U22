#include "stdafx.h"
#include "DebugMan.h"
#include "SampleScene.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//�A�j���[�V�����ɏ���������킹��B
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
		m_charaCon.Init(20.0f, 25.0f, m_pos);

		//�A�j���[�V����������
		AnimInit();
	
		//�O���t�B�b�N�X�G���W������V���h�E�}�b�v���擾
		m_shadowMap = Engine().GetGraphicsEngine().GetShadowMap();

	}
	
	bool DebugMan::Start()
	{
		return true;
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//�ړ�����
		Move();
		//�A�j���[�V�����A�b�v�f�[�g
		m_animation.Update(1.0f / 60.0f);
	}

	void DebugMan::PreRender()
	{
		//�V���h�E�}�b�v�Ƀ����_�����O
		m_shadowMap->RegistShdowCaster(&m_skinModel);
	}

	void DebugMan::Draw()
	{
		//�ʏ탌���_�����O
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			0
		);
	}

	void DebugMan::AnimInit()
	{
		//�t�@�C���ǂݍ���
		m_animClip[enAnimClip_idle].Load(L"Assets/animData/u_idle.tka");
		m_animClip[enAnimClip_idle].SetLoopFlag(true);
		m_animClip[enAnimClip_walk].Load(L"Assets/animData/u_walk.tka");
		m_animClip[enAnimClip_walk].SetLoopFlag(true);
		m_animClip[enAnimClip_run].Load(L"Assets/animData/u_run.tka");
		m_animClip[enAnimClip_run].SetLoopFlag(true);
		//�A�j���[�V����������
		m_animation.Init(
			m_skinModel,
			m_animClip,
			2
		);
	}

	void DebugMan::Move()
	{
		//�����x
		CVector3 acc;
		acc.x = g_Pad[0].GetLStickXF();
		acc.z = g_Pad[0].GetLStickYF();
		acc.y = 0.0f;

		//�ړ��ʉ��Z
		m_moveSpeed += acc * PLAYER_MOVE_SPEED;

		//���C��
		m_moveSpeed -= m_moveSpeed * 0.1;

		//�d��
		m_moveSpeed.y = GRAVITY;

		//�ړ�
		m_pos = m_charaCon.Execute(1.0f, m_moveSpeed);

		//�����v�Z
		if (m_moveSpeed.Length() > 1.0f) {
			//�����Ă�
			//�A�j���[�V�����Ȃ�����
			m_animation.Play(enAnimClip_run, 0.2f);
			//�����v�Z���邨�[
			float t = atan2(m_moveSpeed.x, m_moveSpeed.z);
			m_rot.SetRotation(CVector3::AxisY(), t);
		}
		else if (m_moveSpeed.Length() > 0.1f) {
			//�����Ă�
			//�A�j���[�V�����Ȃ������[
			m_animation.Play(enAnimClip_walk, 0.2f);
			//�����v�Z���邨�[
			float t = atan2(m_moveSpeed.x, m_moveSpeed.z);
			m_rot.SetRotation(CVector3::AxisY(), t);
		}
		else {
			//�����ĂȂ�
			//�A�j���[�V�����Ȃ������[
			m_animation.Play(enAnimClip_idle, 0.2);
		}

		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}
}