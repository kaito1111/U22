#pragma once
#include "Magnet.h"

namespace MyMagnet {
	class MagnetManager
	{
		typedef std::list < Magnet* > MagnetList;
		MagnetList m_MagnetList;
	public:
		/*磁石と位置をマネージャーに登録*/
		void LearnMagetObject(Magnet* magnetObject,CVector3 pos)
		{
			m_MagnetList.push_back(magnetObject);
			magnetObject->SetPosition(&pos);
		}

		/*IGameObjectのFindGOsと一緒*/
		void FindMagnetObject(std::function<bool(Magnet* mag)>func)
		{
			for (auto MagnetList : m_MagnetList) {

				if (func(MagnetList) == false)
				{
					return;
				}
			}
		}
		/*IGameObjectと一緒*/
		void QueryMagnetObject(std::function<bool(Magnet* mag)>func){
			FindMagnetObject(func);
		}
		MagnetManager();
		~MagnetManager();

		static MagnetManager& Instance() {
			static MagnetManager m_instance;
			return m_instance;
		}

	};
	static inline MagnetManager& MagnetManeger() {
		return MagnetManager::Instance();
	}

	static inline void LearnMO(Magnet* magnetObject,CVector3 pos) {
		return MagnetManeger().LearnMagetObject(magnetObject , pos);
	}

	static inline void FindMO(std::function<bool(Magnet* mag)> func) {
		return MagnetManeger().FindMagnetObject(func);
	}

	static inline void QueryMO(std::function<bool(Magnet* mag)> func) {
		return MagnetManeger().QueryMagnetObject(func);
	}
};
