#pragma once
#include "WeaponBase.h"

#include "../GameData/GameDataManager.h"

#include "../../Engine/System/Context/SysContextProvider.h"

class BlitzWeapon : public WeaponBase
{
public:
	BlitzWeapon();
	virtual ~BlitzWeapon();

	virtual void Initialise();
	virtual void Fire();
	virtual void Reload();
	virtual void Update();


private:
	GameDataManager* pGameDataStorage = C_SysContext::Get<GameDataManager>();

	int m_BarrelOffsetX;
	int m_BarrelOffsetY;
};

