#pragma once
#include "graphics/2D/SpriteRender.h"
namespace MyMagnet {
	class Magnet
	{
		CVector3* m_Position = nullptr;

		friend class MagnetManager;
	public:
		Magnet();
		~Magnet();
		CVector3 MagnetMove();
		enum State {
			NMode,
			SMode,
			NoMode,
			Num,
		};
		myEngine::SpriteRender* m_Sprite = nullptr;
	private:
		State state = NoMode;
	public:
		const void SetState(State s) {
			state = s;
		}
		const State GetState() {
			return state;
		}
		const CVector3 GetPosition() {
			return *m_Position;
		}
		const void SetPosition(CVector3* pos) {
			m_Position = pos;
		}
	};
}