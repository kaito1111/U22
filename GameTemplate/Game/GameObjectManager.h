/// <summary>
/// GameObjectのマネージャー
/// </summary>
#pragma once
#include "IGameObject.h"
#include "util/Util.h"

namespace myEngine {
	typedef unsigned char	GameObjectPrio;
	class GameObjectManager
	{
	public:
		GameObjectManager()
		{
		};
		~GameObjectManager()
		{
		};
		/// <summary>
		/// ゲームオブジェクトの名前キーを作成
		/// </summary>
		/// <remarks>
		/// FindGOするときに使うよ
		/// Util::MakeHashで文字列を数列(hash)に変えています
		/// </remarks>
		/// <param name="objectName">オブジェクトの名前</param>
		/// <returns>ハッシュの値</returns>
		static unsigned int MakeGameObjectNameKey(const char* objectName)
		{
			//デフォルトネームを代入
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");
			unsigned int hash;
			//なにも入ってないなら
			if (objectName == nullptr) {
				//デフォルトネーム
				hash = defaultNameKey;
			}
			//なんか入ってたら
			else {
				//ハッシュの作成
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <returns>インスタンス</returns>
		static GameObjectManager& Instance()
		{
			static GameObjectManager instance;
			return instance;
		}
		/// <summary>
		/// <para>オブジェクトの作成</para>
		/// <para>この関数で作ったオブジェクトはDeleteGOで消すこと</para>
		/// </summary>
		/// <remarks>
		/// DeleteGOで消さなかった場合は、m_gameObjectListArrayからも消してね
		/// </remarks>
		/// <typeparam name="T"><para>新しく作るオブジェクト</para></typeparam>
		/// <param name="prio">優先度</param>
		/// <param name="objectName">オブジェクトの名前</param>
		/// <returns>オブジェクト</returns>
		template <class T>
		T* NewGameObject(GameObjPrio prio, const char* objectName)
		{
			(void*)objectName;
			//クラスの初期化
			T* newObject = new T();
			//優先度+ゲームオブジェクトをリストに積む
			m_gameObjectListArray.at(prio).push_back(newObject);
			//FindGOの為にハッシュを作成 hashについてはUtil.hを参照
			unsigned int hash = MakeGameObjectNameKey(objectName);
			//IGameObjectに積まれているprioを今回入ってきたprioで初期化
			newObject->m_priority = prio;
			//上と同じ感じでハッシュを代入
			newObject->m_nameKey = hash;
			return newObject;
		}
		/// <summary>
		/// オブジェクトの削除
		/// <para>オブジェクトを削除予定リストに積む</para>
		/// </summary>
		/// <remarks>
		/// 実際にはここでオブジェクトを消しているわけではありません。
		/// 毎フレームm_deleteObjectArrayに積まれてないか確認して
		/// ExecuteDeleteGameObjectsという関数で削除処理を行います
		/// </remarks>
		///	<param name="IGameObject">消したいオブジェクトのクラス</param>
		void DeleteGameObject(IGameObject* gameObject)
		{
			if (gameObject != nullptr)
			{
				//リストに追加
				m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;
			}
		}
		/// <summary>
		/// ゲームオブジェクトの検索 重いよ！
		/// <para>★エラーメッセージtrueにしても出ないので★</para>
		/// <para>★ブレイクポイントで対応をお願いします。★</para>
		/// </summary>
		/// <typeparam name="T">検索したいオブジェクト</typeparam>
		/// <param name="objectName">オブジェクトの名前</param>
		/// <param name="enableErrorMessage">エラー表示</param>
		template<class T>
		T* FindGameObject(const char* objectName, bool enableErrorMessage)
		{
			unsigned int nameKey = CUtil::MakeHash(objectName);
			//goListをm_gameObjectListArray回、回す
			for (auto goList : m_gameObjectListArray) {
				//goをgoList回
				for (auto go : goList) {
					//見つけた
					if (go->m_nameKey == nameKey) {
						//型変換
						T* p = dynamic_cast<T*>(go);
						//型変換に失敗
						if (p == nullptr && enableErrorMessage == true) {
							/*
							ここにブレークポイントを置いて止まった場合は
							型変換が原因でFindGOできてない場合があるので
							引数に渡したクラスの再確認をしてみてください。
							*/
						}
						//Find成功
						return p;
					}
				}
			}
			if (enableErrorMessage == true) {
				/*
				ここにブレークポイントを置いて止まった場合は
				FindGOに渡された名前が存在しないということなので
				FindGOとNewGOのオブジェクトネームを再確認してみてください。
				*/
			}
			//見つからなかった
			return nullptr;
		}

		void Start();
		void Update();
		void Draw();

		/// <summary>
		/// シングルトン　後でコメント増やします
		/// </summary>
		/// <returns></returns>
		static inline GameObjectManager& gameObjectManager()
		{
			return GameObjectManager::Instance();
		}
		/// <summary>
		/// ゲームオブジェクト作成関数	後でコメント増やす
		/// </summary>
		template<class T>
		static inline T* NewGO(int priority, const char* objectName = nullptr, typename T::IGameObjectIsBase* = nullptr)
		{
			return gameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
		}
		/// <summary>
		/// ゲームオブジェクト検索関数  後でコメント増やす
		/// </summary>
		template<class T>
		static inline T* FindGO(const char* objectName, bool enableErrorMessage = true)
		{
			return gameObjectManager().FindGameObject<T>(objectName, enableErrorMessage);
		}
		/// <summary>
		/// ゲームオブジェクト削除関数	後でコメント増やす
		/// </summary>
		/// <param name="go"></param>
		static inline void DeleteGO(IGameObject* go)
		{
			gameObjectManager().DeleteGameObject(go);
		}


	private:
		typedef std::list<IGameObject*>	GameObjectList;						//名前変更
		std::vector<GameObjectList>		m_gameObjectListArray;				//ゲームオブジェクトの優先度付きリスト		
		std::vector<GameObjectList>		m_deleteObjectArray[2];				//削除するオブジェクトのリスト	削除処理中に削除処理がよばれる可能性があるからダブルバッファ化
		int								m_currentDeleteObjectBufferNo = 0;	//削除中のバッファー番号

	};
}

