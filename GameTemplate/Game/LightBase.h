/// <summary>
/// ライトの基底クラス
/// </summary>
/// <remarks>
/// ライトが作られたらリストに追加
/// ライトが消されたらリストから削除
/// するようにライトマネージャに指示を出す
/// </remarks>

#pragma once

namespace myEngine {
	class LightBase : public IGameObject
	{
	public:
		bool Start() override final;
		/// <summary>
		/// デストラクタ
		/// </summary>
		LightBase::~LightBase();
	private:
		virtual bool StartSub() = 0;
	};
}

