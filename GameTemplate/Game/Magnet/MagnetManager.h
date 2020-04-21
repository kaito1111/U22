#pragma once
#include "Magnet.h"

namespace MyMagnet {
	class MagnetManager
	{
		typedef std::list < Magnet* > MagnetList;
		MagnetList m_MagnetList;
	public:
		/*¥Î‚ÆˆÊ’u‚ğƒ}ƒl[ƒWƒƒ[‚É“o˜^*/
		void LearnMagetObject(Magnet* magnetObject)
		{
			m_MagnetList.push_back(magnetObject);
		}

		/*IGameObject‚ÌFindGOs‚Æˆê*/
		void FindMagnetObject(std::function<bool(Magnet* mag)>func)
		{
			for (auto MagnetList : m_MagnetList) {
				if (func(MagnetList) == false)
				{
					return;
				}
			}
		}
		/*IGameObject‚Æˆê*/
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

	//¥—Í‚Ì“o˜^B‰Šú‰»
	static inline void LearnMO(Magnet* magnetObject) {
		return MagnetManeger().LearnMagetObject(magnetObject);
	}

	static inline void FindMO(std::function<bool(Magnet* mag)> func) {
		return MagnetManeger().FindMagnetObject(func);
	}

	static inline void QueryMO(std::function<bool(Magnet* mag)> func) {
		return MagnetManeger().QueryMagnetObject(func);
	}
};
