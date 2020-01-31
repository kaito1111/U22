#pragma once
#include "Magnet.h"

namespace MyMagnet {
	class MagnetManager
	{
		typedef std::list < Magnet* > MagnetList;
		MagnetList m_MagnetList;
	public:
		/*磁石と位置をマネージャーに登録*/
		void LearnObject(Magnet* magnet, CVector3 pos);
		/*IGameObjectと一緒*/
		void FindObject(std::function<bool(Magnet* mag)>func);
		/*IGameObjectと一緒*/
		void QueryObject(std::function<bool(Magnet* mag)>func);
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

};
