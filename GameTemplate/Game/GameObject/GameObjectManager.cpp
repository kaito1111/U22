#include "stdafx.h"
#include "GameObjectManager.h"
#include "Graphics/2D/Sprite.h"

namespace myEngine {
	/// <summary>
	/// リストに積まれているオブジェクトの個数分
	/// 優先度順(数字が若いほうが優先)で
	/// 各オブジェクトの関数をここで一気に呼び出す処理
	/// </summary>

	void GameObjectManager::Start()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
	}

	void GameObjectManager::Update()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
	}

	void GameObjectManager::PreRender()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreRenderWrapper();
			}
		}
	}

	void GameObjectManager::Draw()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->DrawWrapper();
			}
		}
	}
	
	void GameObjectManager::PostRender()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostRenderWrapper();
			}
		}
	}

	void GameObjectManager::ShadowDraw()
	{
		//レンダーターゲットのバックアップ
		g_graphicsEngine->GetShadowMap()->BiginRender();
		//描画
		g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
		//もとに戻す。
		g_graphicsEngine->GetShadowMap()->EndRender();
	}

	/// <summary>
	/// 更新処理、描画処理をまとめてしてくれるやつ
	/// </summary>
	void GameObjectManager::ExecuteFromGameThread()
	{
		/// 更新系処理
		{
			Update();
			g_graphicsEngine->GetShadowMap()->Update();
		}
		/// 描画系処理
		{
			//プレレンダー(シャドウマップのセットアップ)
			PreRender();
			//シャドウ描画
			ShadowDraw();
			//レンダーターゲットのバックアップ
			g_graphicsEngine->oldTarget();
			//フォワードレンダーターゲットに変える
			g_graphicsEngine->ForwardRenderTarget();
			//通常描画
			Draw();
			//ポストレンダーターゲットに変える
			g_graphicsEngine->PostRenderTarget();
			//ポストレンダー
			PostRender();
		}
		//削除
		ExcuteDeleteGameObject();
	}
	/// <summary>
	/// オブジェクトを消す処理
	/// </summary>
	/// <remarks>
	/// 削除予定リストに何のオブジェクトも登録されてないか確認
	/// 入ってたら、メモリの解放処理を開始します。
	/// </remarks>
	void GameObjectManager::ExcuteDeleteGameObject()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//バッファの切り替え　{01 ,10 = 1}  {00 ,11 = 0} ^→排他的論理和
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for (GameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
			for (IGameObject* go : goList) {
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_gameObjectListArray.at(prio);
				//Listからgoを検索 ※なかったらList.endを返すよ
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				//みつけたら
				if (it != goExecList.end()) {
					//削除リストから除外された。
					delete (*it);
				}
				//消す
				goExecList.erase(it);
			}
			//リスト自体の削除	
			goList.clear();
		}
	}
}