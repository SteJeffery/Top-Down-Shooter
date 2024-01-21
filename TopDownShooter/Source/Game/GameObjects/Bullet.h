#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"

class Bullet : public GameObject, public BoxCollider2D
{
public:
	Bullet();
	 virtual ~Bullet();

	virtual void Initialise();
	virtual void Update();

	virtual void GetPosition(int& x, int & y);

	void SetPosition(int x, int  y);
	void SetRotation(float angle);
	void SetScale(int scaleX, int scaleY);

	virtual void OnCollision(Collider2D* pCollider2D);

private:

	AnimatedSprite m_animatedSprite;

	float m_Velocity;
	float m_Lifetime;
};

