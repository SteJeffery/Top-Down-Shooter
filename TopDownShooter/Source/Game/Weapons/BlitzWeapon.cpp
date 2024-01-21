#include "BlitzWeapon.h"

#include "../GameData/SpritesheetDef.h"
#include "../GameData/GameDataManager.h"

#include "../GameObjects/Bullet.h"

#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/Context/SysContextProvider.h"

BlitzWeapon::BlitzWeapon()
{
}


BlitzWeapon::~BlitzWeapon()
{
}

void BlitzWeapon::Initialise()
{
	m_FireRate = 8.0f;
	m_Ammo = 100;
	m_MagazineSize = 5;
	m_AmmoInMagazine = m_MagazineSize;

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_blitz.xml");

	pGameDataStorage->m_BlitzAmmo = m_AmmoInMagazine;
	pGameDataStorage->m_MaxBlitzAmmo = m_Ammo;

	m_animatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_blitz", 24, false);
	m_animatedSprite.SetCurrentAnimation(0);
	m_animatedSprite.Pause();

	m_BarrelOffsetX = 60;
	m_BarrelOffsetY = -5;
}

void BlitzWeapon::Fire()
{
	if (!canFire())
		return;

	WeaponBase::Fire();

	//generate bullet
	Bullet* bullet = new Bullet();
	bullet->Initialise();

	//create a bullet spawn offset
	sf::Vector2f bulletSpawnOffset(m_BarrelOffsetX, m_BarrelOffsetY);

	//rotate it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_animatedSprite.getRotation());
	transform.scale(m_animatedSprite.getScale());
	bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

	bullet->SetPosition(m_animatedSprite.getPosition().x + bulletSpawnOffset.x, m_animatedSprite.getPosition().y + bulletSpawnOffset.y);
	bullet->SetRotation(m_animatedSprite.getRotation());
	bullet->SetScale(m_animatedSprite.getScale().x, m_animatedSprite.getScale().y);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	//add it to the current game state
	if (pGameState)
		pGameState->AddGameObject(bullet);

	m_animatedSprite.Play();
}

void BlitzWeapon::Reload()
{
	m_AmmoDifference = m_MagazineSize - m_AmmoInMagazine;
	m_AmmoInMagazine = m_MagazineSize;
	m_Ammo = m_Ammo - m_AmmoDifference;
}

void BlitzWeapon::Update()
{
	pGameDataStorage->m_BlitzAmmo = m_AmmoInMagazine;
	pGameDataStorage->m_MaxBlitzAmmo = m_Ammo;
	WeaponBase::Update();
}