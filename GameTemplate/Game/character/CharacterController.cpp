/*!
* @brief	�L�����N�^�̃R���W�����R���g���[���B
*/

#include "stdafx.h"
#include "character/CharacterController.h"
#include "Physics/CollisionAttr.h"



namespace {
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;									//�Փ˃t���O�B
		CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
		CVector3 startPos = CVector3::Zero();					//���C�̎n�_�B
		CVector3 hitNormal = CVector3::Zero();				//�Փ˓_�̖@���B
		btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
		float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me
				) {
				//�����ɏՓ˂����B
				return 0.0f;
			}
			//�Փ˓_�̖@�������������Ă���B
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
				//�L�����N�^�����̃R���W�����ƏՓ˂����B
				) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				hitPos = hitPosTmp;
				hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
				return 0.0f;
			}
			//������Ɩ@���̂Ȃ��p�x�����߂�B
			float angle = hitNormalTmp.Dot(CVector3::Up());
			angle = fabsf(acosf(angle));
			if (angle < CMath::PI * 0.2f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //�������̓R���W�����������n�ʂƎw�肳��Ă���B
				) {
				//�Փ˂��Ă���B
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//�Փ˓_�̋��������߂�B�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp) {
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		CVector3 hitPos = CVector3::Zero();		//�Փ˓_�B
		CVector3 startPos = CVector3::Zero();		//���C�̎n�_�B
		float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
		CVector3 hitNormal = CVector3::Zero();	//�Փ˓_�̖@���B
		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
												//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me				//�����ɏՓ˂����B
				) {
				return 0.0f;
			}
			//�Փ˓_�̖@�������������Ă���B
			CVector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);
			//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
			float angle = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up())));
			if (angle >= CMath::PI * 0.3f && angle <= CMath::PI * 0.7f		//�n�ʂ̌X�΂�54�x�ȏ�A162�x�ȉ��Ȃ̂ŕǂƂ݂Ȃ��B
				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_BoxCharacter
				) {
				isHit = true;
				CVector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);
				//��_�Ƃ̋����𒲂ׂ�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				vDist.y = 0.0f;
				float distTmp = vDist.Length();
				if (distTmp < dist) {
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = hitNormalTmp;
				}
			}
			//if (
			//	//�R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B
			//	) {
			//	isHit = true;
			//	CVector3 hitPosTmp;
			//	hitPosTmp.Set(convexResult.m_hitPointLocal);
			//	//��_�Ƃ̋����𒲂ׂ�B
			//	CVector3 vDist;
			//	vDist.Subtract(hitPosTmp, startPos);
			//	vDist.y = 0.0f;
			//	float distTmp = vDist.Length();
			//	if (distTmp < dist) {
			//		//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
			//		hitPos = hitPosTmp;
			//		dist = distTmp;
			//		hitNormal = hitNormalTmp;
			//	}
			//}
			return 0.0f;
		}
	};

	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�V��p)
	struct SweepResultCeil : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;									//�Փ˃t���O�B
		CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
		CVector3 startPos = CVector3::Zero();					//���C�̎n�_�B
		CVector3 hitNormal = CVector3::Zero();				//�Փ˓_�̖@���B
		btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
		float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

															//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me
				) {
				//�����ɏՓ˂����Bor �L�����N�^�����̃R���W�����ƏՓ˂����B
				return 0.0f;
			}
			//�Փ˓_�̖@�������������Ă���B
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			hitNormalTmp.z = 0.0f;
			//������Ɩ@���̂Ȃ��p�x�����߂�B
			float angle = hitNormalTmp.Dot(CVector3::Up());
			angle = fabsf(acosf(angle));
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_BoxCharacter) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp) {
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
					dist = distTmp;
				}
				return 0.0f;
			}
			else if (angle > CMath::PI * 0.7f		//�V��̌X�΂�162�x���ł����̂œV��Ƃ݂Ȃ��B
				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //�������̓R���W�����������n�ʂƎw�肳��Ă���B
				)
			{
				//�Փ˂��Ă���B
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//�Փ˓_�̋��������߂�B�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp) {
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};
}

void CharacterController::Init(float radius, float height, const CVector3& position)
{
	m_position = position;
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(position.x, position.y + m_height * 0.5f + m_radius, position.z));
	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);
}
const CVector3& CharacterController::Execute(float deltaTime, CVector3& moveSpeed)
{
	//���̈ړ���ƂȂ���W���v�Z����B
	CVector3 nextPosition = m_position;
	//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
	CVector3 addPos = moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;

	if (moveSpeed.y > 0.0f) {
		//������ђ��ɂ���B
		m_isJump = true;
		m_isOnGround = false;
	}
	/*��������ǉ���
	������̈ړ�����*/
	{
		CVector3 addPos;
		addPos.Subtract(nextPosition, m_position);
		//���C���쐬����B
		//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
		//CVector3 posTmp = m_position;
		//posTmp.Subtract(addPos);
		//posTmp.y += m_height * 1.0f + m_radius *2.0f/*+ m_height * 0.1*/;
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
		start.setOrigin(btVector3(m_position.x, nextPosition.y + m_height * 0.5f + m_radius, m_position.z));
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�����B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		CVector3 endPos;
		endPos.Set(start.getOrigin());
		if (m_isOnGround == false) {
			if (addPos.y > 0.0f) {
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���Ă���ꍇ�͂��̂܂܏�𒲂ׂ�B
				//endPos.y += addPos.y * 0.01f;
				endPos.y += addPos.y;
			}
			else {
				//�������ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŏ�𒲂ׂ�B
				//endPos.y -= addPos.y;
				endPos.y -= addPos.y * 0.01f;
			}
		}
		else
		{
			//endPos.y += 1.0f;
		}
		//endPos.Add(addPos);
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultCeil callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//�Փˌ��o�B
		if (fabsf(endPos.y - callback.startPos.y) > FLT_EPSILON) {
			g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit) {
				//���������B
				moveSpeed.y = 0.0f;
				//float angle = callback.hitNormal.Dot(CVector3::Up());
				//angle = fabsf(acosf(angle));
				//CQuaternion m_Rot;
				//m_Rot.SetRotation(CVector3::Up(), -angle);
				//CVector3 sphereHitPos = callback.hitPos;
				//sphereHitPos.y - (m_radius + m_height);
				//CVector3 a = sphereHitPos;
				//m_Rot.Multiply(a);
				nextPosition.y = callback.hitPos.y - (m_height + m_radius + m_radius/* * 0.5*/);
				//nextPosition.y = a.y - (m_height + m_radius * 2.0f/*+ 8.0f*/);

			}
		}
	}

	//�������𒲂ׂ�B
	{
		CVector3 addPos;
		addPos.Subtract(nextPosition, m_position);
		//addPos = nextPosition - m_position;

		//m_position = nextPosition;	//�ړ��̉��m��B
									//���C���쐬����B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		/*�ύX�_
		start.setOrigin(btVector3(nextPosition.x, m_position.y + m_height * 0.5f + m_radius, nextPosition.z));*/
		start.setOrigin(btVector3(m_position.x, nextPosition.y + m_height * 0.5f + m_radius, m_position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		CVector3 endPos;
		endPos.Set(start.getOrigin());
		if (m_isOnGround == false) {
			if (addPos.y > 0.0f) {
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
				endPos.y -= addPos.y * 0.01f;
			}
			else {
				//�������Ă���ꍇ�͂��̂܂܉��𒲂ׂ�B
				endPos.y += addPos.y;
			}
		}
		else {
			//�n�ʏ�ɂ���ꍇ��1m��������B
			endPos.y -= 1.0f;
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultGround callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//�Փˌ��o�B
		if (fabsf(endPos.y - callback.startPos.y) > FLT_EPSILON) {
			g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit) {
				//�n�ʂɓ��������B
				m_isJump = false;
				m_isOnGround = true;
				//	btTransform start, end;
				//	CVector3 hitPos = callback.hitPos;
				//	start.setOrigin(btVector3(hitPos.x, hitPos.y, 0.0f));
				//	hitPos.x -= 1.0f;
				//	end.setOrigin(btVector3(hitPos.x, hitPos.y, 0.0f));
				//	SweepResultGround callBack;
				//	callBack.me = m_rigidBody.GetBody();
				//	callBack.startPos.Set(start.getOrigin());
				//	g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callBack);
				//	if (callBack.isHit) {
				//		//�E�ɏ�Q��������
				//		if (addPos.Length() > FLT_EPSILON) {//�����ĂȂ�
				//			nextPosition.x = 1.0f;
				//		}
				//		addPos *= 1.1f;
				//	}
				//	else {
				//		//���ɏ�Q��������
				//		if (addPos.Length() > FLT_EPSILON) {//�����ĂȂ�
				//			nextPosition.x = -1.0f;
				//		}
				//		addPos *= 1.1f;
				//	}
				nextPosition.y = callback.hitPos.y;

				moveSpeed.y = 0.0f;
				/*+ addPos.y * 0.01f*/
			}
			else {
				//�n�ʏ�ɂ��Ȃ��B
				m_isOnGround = false;
			}
		}
	}
	//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
	{
		int loopCount = 0;
		while (true) {
			//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
			CVector3 addPos;
			addPos.Subtract(nextPosition, m_position);
			float addPosX = addPos.x;

			if ((fabsf(addPosX) < FLT_EPSILON)) {
				//XZ���ʂœ������Ȃ��̂Œ��ׂ�K�v�Ȃ��B
				//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
				//�ƂĂ��������l�̂��Ƃł��B
				break;
			}
			//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
			CVector3 posTmp = m_position;
			posTmp.y += m_height * 0.5f + m_radius + m_height * 0.1f;
			//���C���쐬�B
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
			end.setOrigin(btVector3(nextPosition.x, posTmp.y, posTmp.z));

			SweepResultWall callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos.Set(posTmp);
			//�Փˌ��o�B
			g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

			if (callback.isHit) {
				//���������B
				//�ǁB
#if 1
				//�������L���ɂ���ƏՓˉ������Փ˓_�ɖ߂��ɂȂ�B
				nextPosition.x = callback.hitPos.x;
				//nextPosition.z = callback.hitPos.z;
				//�@���̕����ɔ��a�������߂��B
				nextPosition.x += callback.hitNormal.x * m_radius;
				//nextPosition.z += callback.hitNormal.z * m_radius;
#else
				CVector3 vT0, vT1;
				//XZ���ʏ�ł̈ړ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��B
				vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
				vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
				//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
				CVector3 vMerikomi;
				vMerikomi = vT0 - vT1;
				//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B�B
				CVector3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				hitNormalXZ.Normalize();
				//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
				float fT0 = hitNormalXZ.Dot(vMerikomi);
				//�����߂��Ԃ��x�N�g�������߂�B
				//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g��+���a�B
				CVector3 vOffset;
				vOffset = hitNormalXZ;
				vOffset *= -fT0 + m_radius;
				nextPosition += vOffset;
				CVector3 currentDir;
				currentDir = nextPosition - m_position;
				currentDir.y = 0.0f;
				currentDir.Normalize();
				if (currentDir.Dot(originalXZDir) < 0.0f) {
					//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
					//�ړ��悪�t�����ɂȂ�����ړ����L�����Z������B
					nextPosition.x = m_position.x;
					nextPosition.z = m_position.z;
					break;
				}
#endif
			}
			else {
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
	}
	//XZ�̈ړ��͊m��B
	m_position.x = nextPosition.x;
	m_position.z = nextPosition.z;
	//�ړ��m��B
	m_position = nextPosition;
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	//btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	return m_position;
}
/*!
* @brief	���S�������Ƃ�ʒm�B
*/
void CharacterController::RemoveRigidBoby()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
