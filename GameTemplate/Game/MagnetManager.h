#pragma once
#include "Magnet.h"

namespace MyMagnet {
	class MagnetManager
	{
		typedef std::list < Magnet* > MagnetList;
		MagnetList m_MagnetList;
	public:
		/*���΂ƈʒu���}�l�[�W���[�ɓo�^*/
		void LearnObject(Magnet* magnet, CVector3 pos);
		/*IGameObject�ƈꏏ*/
		void FindObject(std::function<bool(Magnet* mag)>func);
		/*IGameObject�ƈꏏ*/
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
