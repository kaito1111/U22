#pragma once
class stageObjectShuriken : public IGameObject
{
	class Player;
		//サイズ200*200*20
	public:
		stageObjectShuriken();
		//stageObjectShuriken(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
		~stageObjectShuriken();

		void Draw();
		bool Start();
		void Update();
	private:
		SkinModel m_model;								//スキンモデル
		CVector3 m_pos = CVector3::Zero();				//座標
		CQuaternion m_rot = CQuaternion::Identity();	//回転
		bool UDPos = false;								//右端左端
		bool speedDown = false;							//スピードを上げたり下げたりする
		float moveSpeed = 0;                            //速度。左右に動く
		bool sLimit = false;		    				//動いた量


};

