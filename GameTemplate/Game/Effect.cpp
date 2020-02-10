/// <summary>
/// エフェクト
/// DirectXⅢを参考に作成
/// </summary>

#include "stdafx.h"
#include "Effect.h"

namespace myEngine {
	Effect::Effect()
	{
		//エフェクサーの初期化
		g_graphicsEngine->InitEffekseer();
	}
	Effect::~Effect()
	{
		//解放
		Release();
	}
	
	void Effect::Release()
	{
		if (m_handle != -1) {
			g_graphicsEngine->GetEffekseerManager()->StopEffect(m_handle);
			m_handle = -1;
		}
	}

	void Effect::Play(const wchar_t* filePath)
	{
		//ハッシュの作成
		int nameKey = Util::MakeHash(filePath);
		m_effect = GetResource(nameKey);
		if (m_effect == nullptr) {
			//エフェクトの作成
			m_effect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)filePath );
			//ロード失敗！！
			//？？ファイルパス間違えてない？？
			if (m_effect == nullptr) {
				throw;
			}
			//これいる？
			RegistResource(nameKey, m_effect);
		}
		m_handle = g_graphicsEngine->GetEffekseerManager()->Play(m_effect, 0, 0, 0);
	}

	void Effect::Update()
	{
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		g_graphicsEngine->GetEffekseerRenderer()->SetCameraMatrix(efCameraMat);
		g_graphicsEngine->GetEffekseerRenderer()->SetProjectionMatrix(efProjMat);
		
		//Effekseerを更新。
		g_graphicsEngine->GetEffekseerManager()->Update();

		//各行列定義
		CMatrix mTrans, mRot, mScale, mBase;
		mTrans.MakeTranslation(m_position);
		mRot.MakeRotationFromQuaternion(m_rotation);
		mScale.MakeScaling(m_scale);
		//ワールド行列に変換
		mBase = mScale * mRot;
		mBase = mBase * mTrans;
		
		//CMatrixいじって変換できるようにしてるよ
		g_graphicsEngine->GetEffekseerManager()->SetBaseMatrix(m_handle, mBase);

		if (IsPlay() == false) {
			//再生が終了したら削除
			DeleteGO(this);
		}

	}

	void Effect::PostDraw()
	{
		//描画
		g_graphicsEngine->GetEffekseerManager()->Draw();
	}
}