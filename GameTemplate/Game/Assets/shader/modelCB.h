/*
	<Sum>
	モデル用定数バッファ
	<Rem>
	スロット番号をいじったら
	　→CPU側のスロット番号を、SkinModelShaderConst.hを参照しつつ直すこと。
	変数をいじったら
	　→CPU側、各定数バッファが送られている(UpdateSubResources)されている場所も調整すること。
*/

//ライトの数
static const int NUM_DIRECTION_LIG = 4;

//注意シャドウマップの枚数増やしたら、shadowCbのメンバを割り当てている
//レジスタ番号を再調整する必要があります。
static const int NUM_SHADOW_MAP = 3;

/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0) {
	float4x4 mWorld;		//ワールド行列
	float4x4 mView;			//ビュー行哲
	float4x4 mProj;			//プロジェクション行列
	//シャドウ関連//
	float4x4 mLightView;	//ライトビュー行列
	float4x4 mLightProj;	//ライトプロジェクション行列
	int isShadowReciever;	//シャドウレシーバーフラグ 0->OFF 1->ON
};

/*
	ライト用定数バッファ
*/
cbuffer LightCb : register(b1) {
	float3		Direction[NUM_DIRECTION_LIG];	//カメラの方向
	float4		Color[NUM_DIRECTION_LIG];		//カラー
	float3		eyePos;							//視点の座標
	bool		active = true;					//アクティブ
	float		specPow/*[NUM_DIRECTION_LIG]*/;		//鏡面反射の絞り 最後に書いて！
};

/*
	シャドウマップ用の定数バッファ
*/
cbuffer ShadowCb : register(b3) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//ライトビュープロジェクション行列
	float4 shadowAreaDepthInViewSapce;	//カメラ空間で影を落とすエリア x = shadow0 y = shadow1 z= shadow2
}
