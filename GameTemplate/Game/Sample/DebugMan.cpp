#include "stdafx.h"
#include "DebugMan.h"
#include "SampleScene.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//アニメーションに上方向を合わせる。
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
		m_charaCon.Init(20.0f, 25.0f, m_pos);

		//アニメーション初期化
		AnimInit();
	
		//グラフィックスエンジンからシャドウマップを取得
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
		//移動処理
		Move();
		//アニメーションアップデート
		m_animation.Update(1.0f / 60.0f);
	}

	void DebugMan::PreRender()
	{
		//シャドウマップにレンダリング
		m_shadowMap->RegistShdowCaster(&m_skinModel);
	}

	void DebugMan::Draw()
	{
		//通常レンダリング
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			0
		);
	}

	void DebugMan::AnimInit()
	{
		//ファイル読み込み
		m_animClip[enAnimClip_idle].Load(L"Assets/animData/u_idle.tka");
		m_animClip[enAnimClip_idle].SetLoopFlag(true);
		m_animClip[enAnimClip_walk].Load(L"Assets/animData/u_walk.tka");
		m_animClip[enAnimClip_walk].SetLoopFlag(true);
		m_animClip[enAnimClip_run].Load(L"Assets/animData/u_run.tka");
		m_animClip[enAnimClip_run].SetLoopFlag(true);
		//アニメーション初期化
		m_animation.Init(
			m_skinModel,
			m_animClip,
			2
		);
	}

	void DebugMan::Move()
	{
		//加速度
		CVector3 acc;
		acc.x = g_Pad[0].GetLStickXF();
		acc.z = g_Pad[0].GetLStickYF();
		acc.y = 0.0f;

		//移動量加算
		m_moveSpeed += acc * PLAYER_MOVE_SPEED;

		//摩擦力
		m_moveSpeed -= m_moveSpeed * 0.1;

		//重力
		m_moveSpeed.y = GRAVITY;

		//移動
		m_pos = m_charaCon.Execute(1.0f, m_moveSpeed);

		//向き計算
		if (m_moveSpeed.Length() > 1.0f) {
			//走ってる
			//アニメーションながすお
			m_animation.Play(enAnimClip_run, 0.2f);
			//向き計算するおー
			float t = atan2(m_moveSpeed.x, m_moveSpeed.z);
			m_rot.SetRotation(CVector3::AxisY(), t);
		}
		else if (m_moveSpeed.Length() > 0.1f) {
			//動いてる
			//アニメーションながすおー
			m_animation.Play(enAnimClip_walk, 0.2f);
			//向き計算するおー
			float t = atan2(m_moveSpeed.x, m_moveSpeed.z);
			m_rot.SetRotation(CVector3::AxisY(), t);
		}
		else {
			//動いてない
			//アニメーションながすおー
			m_animation.Play(enAnimClip_idle, 0.2);
		}

		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}
}