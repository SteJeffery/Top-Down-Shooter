#pragma once
#include "../../Engine/Renderer/AnimatedSprite.h"

class WeaponBase : public AnimatedSprite
{
public:
	WeaponBase();
	virtual ~WeaponBase();

	virtual void Initialise();
	virtual void Fire();
	virtual void Update();
	virtual void Reload() = 0;

	bool canFire();

	void SetPosition(int posx, int posy);
	void SetScale(float scalex, float scaley);
	void SetRotation(float angle);

protected:
	int m_Ammo;
	int m_AmmoInMagazine;
	int m_MagazineSize;
	int m_AmmoDifference;

	float m_FireRate;
	float m_FireTimer;

	AnimatedSprite m_animatedSprite;
};

