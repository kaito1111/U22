/// <summary>
/// ライトの管理者
/// </summary>
/// <remarks>
/// 1.ライトのバッファーの初期化
/// 2.ライトのリスト管理
/// </remarks>

#include "stdafx.h"
#include "bLightManager.h"
#include "bDirectionLight.h"

namespace myEngine {
	LightManager::LightManager()
	{
	}
	LightManager::~LightManager()
	{
	}
	void LightManager::Init()
	{
		//平行ライトの構造体バッファーを初期化
		InitDirectionLightStructuredBuffer();
		//GPUBufferの作成
		m_lightParamCB.Create(&m_lightParam, sizeof(m_lightParam));
	}
	void LightManager::InitDirectionLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SDirectionLight);			//データの間隔

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド
		desc.ByteWidth = stride * MAX_DIRECTION_LIGHT;	//データ量
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_directionLightSB.Create(NULL, desc);			//ストラクチャーバッファの作成
	}
	void LightManager::AddLight(LightBase* light)
	{
		if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
			/*
			!!throw!!
			ディレクションライト作りすぎてない？？
			MAX_DIRECTION_LIGHTを参照して値を確認して
			!!throw!!
			*/
			throw;
		}
		//typeinfo = type_idの返却値を保存するクラス ※nullだと例外
		//typeid = 型の情報
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(myEngine::DirectionLight)) {
			//型がディレクションライトだった！

			//ディレクションライトリストに今回追加するライトが追加されいるかの検索
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light);
			if(findIt == m_directionLights.end()) {
				//登録されていないので新規登録
				//ディレクションライトへ型変換
				//reinterpret_cast = 引数をtemplateのクラスに強制的な型変換 
				m_directionLights.push_back(reinterpret_cast<DirectionLight*>(light));
			}
			else {
				/*
				!!thorw!!
				すでに登録されてる！！
				基本的に登録されてるのをもう一回登録するのはなんかのミスだと思うから
				throwするようにしてますが、仕様やねんワレィという方はthrowをコメントアウトしてください
				!!thorw!!
				*/
				throw;
				return;
			}
		}
	}
	void LightManager::RemoveLight(LightBase* light)
	{
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(DirectionLight)) {
			//ディレクションライトだ！
			m_directionLights.erase(
				//今回リストから削除するライトを検索して削除
				std::remove(m_directionLights.begin(), m_directionLights.end(), light),
				m_directionLights.end()
			);
		}
	}
	void LightManager::Update()
	{
		m_lightParam.eyePos = g_camera3D.GetPosition();
		//ディレクションライトのストラクチャーバッファの更新
		//ライトの数
		int ligNo = 0;
		//ディレクションライトの登録回数リストを更新
		for (auto lig : m_directionLights) {
			if (lig->IsActive() == false) {
				//アクティブじゃないのでスキップ
				continue;
			}
			//アクティブな奴はライトのデータをあげる
			m_rawDirectionLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		//ディレクションライトの数
		int numDirLig = ligNo;
		//ライトの数の初期化
		ligNo = 0;

		//安全な型変換
		m_lightParam.numDirectionLight = static_cast<int>(numDirLig);
	}
	void LightManager::SendLightParamToGPU()
	{
		//デバイスコンテキスト
		auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
		//ライトの基盤情報の送信。
		dc->UpdateSubresource(m_lightParamCB.GetBody(), 0, NULL, &m_lightParam, 0, 0);
		//ディレクションライトのパラメーターを送信。
		dc->UpdateSubresource(m_directionLightSB.GetBody(), 0, NULL, m_rawDirectionLights, 0, 0);
		//リソース設定。
		dc->PSSetShaderResources(enSkinModelSRVReg_Light, 1, &m_directionLightSB.GetSRV().GetBody());
		//定数バッファ設定。
		dc->PSSetConstantBuffers(enSkinModelCBReg_Light, 1, &m_lightParamCB.GetBody());
	}
	void LightManager::EndRender()
	{
		//デバイスコンテキスト
		auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
		//レンダー設定をもどす？
		dc->PSSetShaderResources(100, 1, NULL);
	}
}

