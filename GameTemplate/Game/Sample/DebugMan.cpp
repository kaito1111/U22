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
		//移動量
		CVector3 moveSpeed;
		moveSpeed.x = g_Pad[0].GetLStickXF() * m_moveSpeed;
		moveSpeed.z = g_Pad[0].GetLStickYF() * m_moveSpeed;
		//重力
		moveSpeed.y = GRAVITY;

		//移動
		m_pos = m_charaCon.Execute(1.0f, moveSpeed);

		//向き計算
		if (moveSpeed.Length() > 0.0f) {
			//動いてる
			//アニメーションながすおー
			m_animation.Play(enAnimClip_walk, 0.2f);
			//向き計算するおー
			float t = atan2(moveSpeed.x, moveSpeed.z);
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