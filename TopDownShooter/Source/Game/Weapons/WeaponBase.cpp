#include "WeaponBase.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/FrameTimer.h"


WeaponBase::WeaponBase()
:m_Ammo(0)
,m_AmmoInMagazine(0)
,m_MagazineSize(0)
,m_AmmoDifference(0)
,m_FireRate(0.0f)
,m_FireTimer(0.0f)
{
}


WeaponBase::~WeaponBase()
{
}

void WeaponBase::Initialise()
{
}

void WeaponBase::Fire()
{
	if (m_FireRate > 0.0f)
	{
		m_FireTimer = 1.0f / m_FireRate;
		m_AmmoInMagazine = m_AmmoInMagazine - 1;
	}
}

void WeaponBase::Update()
{
	m_animatedSprite.Animate();

	if (m_animatedSprite.AnimationFinished())
	{
		m_animatedSprite.SetCurrentAnimation(0);
		m_animatedSprite.Pause();
	}

	if (m_FireTimer >= 0.0f)
	{
		FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
		m_FireTimer -= pFrameTimer->DeltaTime();
	}
}

bool WeaponBase::canFire()
{
	if (m_AmmoInMagazine > 0)
	{
		return m_FireTimer <= 0.0f;
	}
	return false;
}

void WeaponBase::SetPosition(int posx, int posy)
{
	m_animatedSprite.setPosition(posx, posy);
}

void WeaponBase::SetScale(float scalex, float scaley)
{
	m_animatedSprite.setScale(scalex, scaley);
}

void WeaponBase::SetRotation(float angle)
{
	m_animatedSprite.setRotation(angle);
}
