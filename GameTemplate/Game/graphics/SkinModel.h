#pragma once

#include "Skeleton.h"
#include "Shader.h"

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	
	/// <summary>
	/// 旧モデル描画（もとからこのエンジンにあったやつ）
	/// <para>---!!CAUTION!!---</para>
	/// <para>このDraw関数は消す予定があるので使わないでください。</para>
	/// <para>こちらの関数を使っているクラスがあるなら、もう片方のDrawに引っ越しをお願いします。</para>
	/// <para>---!!CAUTION!!---</para>
	/// </summary>
	/// <remarks>
	/// 下のDraw関数実装に伴い削除する予定がある関数です。
	/// 正直機能としてはシルエット描画ができるか否かの差しかないので、
	/// 気にせずもう一つのDraw関数を使ってください。
	/// </remarks>
	/// <param name="viewMatrix"></param>
	/// <param name="projMatrix"></param>
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );
	/// <summary>
	/// シルエット描画or描画
	/// <para>0が通常描画、1がシルエット描画</para>
	/// <para>シルエット描画の詳細はこの関数のRemarksに書いてあるので、</para>
	/// <para>それを参考にシルエット描画を実装してください。</para>
	/// </summary>
	/// <remarks>
	/// -----シルエット描画の方法について-----
	/// 1.シルエットを映したいオブジェクトを描画（壁系)
	/// 2.シルエットになるオブジェクト(Player系)をシルエット描画（ RenderMode = 1 ）
	/// 3.2のオブジェクトを通常描画（ RenderMode = 0 ）
	/// 順番を間違えたりするとシルエットが映らなかったり、変なところにシルエットが映るので
	/// しっかり描画順番を確認しておいてください。
	/// --------------------------------------
	/// </remarks>
	/// <param name="viewMatrix">カメラ行列</param>
	/// <param name="projMatrix">プロジェクション行列</param>
	/// <param name="RenderMode">/描画モード/ 0->通常描画 1->シルエット描画</param>
	void Draw(CMatrix viewMatrix, CMatrix projMatrix, int RenderMode);
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	
private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
};

