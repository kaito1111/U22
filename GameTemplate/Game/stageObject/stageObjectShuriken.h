#pragma once
class stageObjectShuriken : public IGameObject
{
	class Player;
		//�T�C�Y200*200*20
	public:
		stageObjectShuriken();
		//stageObjectShuriken(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
		~stageObjectShuriken();

		void Draw();
		bool Start();
		void Update();
	private:
		SkinModel m_model;								//�X�L�����f��
		CVector3 m_pos = CVector3::Zero();				//���W
		CQuaternion m_rot = CQuaternion::Identity();	//��]
		bool UDPos = false;								//�E�[���[
		bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
		float moveSpeed = 0;                            //���x�B���E�ɓ���
		bool sLimit = false;		    				//��������


};

