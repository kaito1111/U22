#pragma once

#include "Physics/ICollider.h"

class BoxCollider : public ICollider  
{
public :
	//デストラクタ
	~BoxCollider();

	void Init(float wide,float height, float depth) {
		btVector3 BoxScale(wide, height, depth);
		shepe = new btBoxShape(BoxScale);
		this->height = height;
		this->wide = wide;
		this->depth = depth;
	}
	btCollisionShape* GetBody()const override
	{
		return shepe;
	}
	float GetWide()const
	{
		return wide;
	}
	float GetHeight()const
	{
		return height;
	}
	float GetDepth()const
	{
		return depth;
	}
private:
	btBoxShape* shepe = nullptr;
	float wide = 0.0f;
	float height = 0.0f;
	float depth = 0.0f;
};

