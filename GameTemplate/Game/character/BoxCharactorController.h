#pragma once

#include "physics/BoxCollider.h"
#include "physics/RigidBody.h"
class BoxCharactorController
{
public:
	~BoxCharactorController() {
		RemoveRigidBody();
	}

	/*!
	* @brief	�������B
	*@param[in]	wide		�{�b�N�X�R���C�_�[�̕��B
	*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
	*@param[in] depth      �@�{�b�N�X�R���C�_�[�̉��䂫
	*@param[in]	position	�����ʒu�B
	*/
	void Init(float wide, float height, float depth, const CVector3& position);

	/*!
		* @brief	���s�B
		*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		*@return �ړ���̃L�����N�^�[�̍��W�B
		*/
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed);

	//���W���擾�B
	const CVector3 GetPosition() {
		return m_position;
	}

	//���W��ݒ�B
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	//�W�����v��������
	bool IsJump() const
	{
		return m_isJump;
	}

	//�n�ʏ�ɂ��邩����B
	bool IsOnGround() const
	{
		return m_isOnGround;
	}

	//�R���C�_�[���擾�B
	BoxCollider* GetCollider() {
		return &m_collider;
	}

	//���̂��擾�B
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}

	//���̂𕨗��G���W������폜�B�B
	void RemoveRigidBody();

private:
	CVector3 m_position = CVector3::Zero();
	bool m_isJump = false;				//�W�����v���H
	bool m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	BoxCollider	m_collider;						//�R���C�_�[�B
	float m_wide = 0.0f;
	float m_height = 0.0f;
	float m_depth = 0.0f;
	float m_Bottom = 0.0f;
	RigidBody m_rigidBody;					//���́B

};