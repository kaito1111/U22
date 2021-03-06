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
	* @brief	初期化。
	*@param[in]	wide		ボックスコライダーの幅。
	*@param[in]	height		カプセルコライダーの高さ。
	*@param[in] depth      　ボックスコライダーの奥ゆき
	*@param[in]	position	初期位置。
	*/
	void Init(float wide, float height, float depth, const CVector3& position);

	/*!
		* @brief	実行。
		*@param[in]	deltaTime		経過時間。単位は秒。
		*@param[in, out]	moveSpeed		移動速度。内部で重力加速が計算され、その結果がmoveSpeedに反映されます。
		*@return 移動後のキャラクターの座標。
		*/
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed);

	//座標を取得。
	const CVector3 GetPosition() {
		return m_position;
	}

	//ジャンプ中か判定
	bool IsJump() const
	{
		return m_isJump;
	}

	//地面上にいるか判定。
	bool IsOnGround() const
	{
		return m_isOnGround;
	}

	//コライダーを取得。
	BoxCollider* GetCollider() {
		return &m_collider;
	}

	//剛体を取得。
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}

	//剛体を物理エンジンから削除。。
	void RemoveRigidBody();

	float GetWide() {
		return m_wide;
	}
	float GetHight() {
		return m_height;
	}
	float GetDepth() {
		return m_depth;
	}
	void SetAffected(bool af) {
		IsAffected = af;
	}
private:
	CVector3 m_position = CVector3::Zero();
	bool m_isJump = false;				//ジャンプ中？
	bool m_isOnGround = true;			//地面の上にいる？
	BoxCollider	m_collider;						//コライダー。
	float m_wide = 0.0f;
	float m_height = 0.0f;
	float m_depth = 0.0f;
	float m_Bottom = 0.0f;
	RigidBody m_rigidBody;					//剛体。
	bool IsAffected = true;				//ほかのキャラコンから影響を受けるかどうか
};