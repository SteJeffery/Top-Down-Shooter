#pragma once
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/System/Animation/AnimationStateMachine.h"
#include "../../Engine/System/Context/SysContextProvider.h"

#include "../GameData/GameDataManager.h"

#include <vector>

class WeaponBase;

class PlayerCharacter : public GameObject, public BoxCollider2D
{
public:
	PlayerCharacter();
	virtual ~PlayerCharacter();

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);
	virtual void SetPosition(int x, int y);
	virtual int GetHealth();
	virtual void SetHealth(int health);

	virtual void Hit();
	virtual void OnCollision(Collider2D* pCollider2D);
	virtual void Dead();
	virtual void WeaponSwap();

	int currentWeapon;

private:
	GameDataManager* pGameDataStorage = C_SysContext::Get<GameDataManager>();
	AnimatedSprite m_animatedSprite;

	virtual void WeaponUpdate();
	virtual void WeaponFire();
	virtual void WeaponReload();
	virtual void WeaponControls();
	virtual void PlayerMovement();


	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Sprint,
		E_AnimationState_Death,
		E_AnimationState_Dig,
		E_AnimationState_Holo,
		E_AnimationState_Melee,
		E_AnimationState_TeleportIn,
		E_AnimationState_TeleportOut,
		E_AnimationState_Dash,
		E_AnimationState_Hit,
	};

	WeaponBase* m_pWeapon;

	int m_WeaponOffsetX;
	int m_WeaponOffsetY;
	bool m_moving;
	bool m_IsHit;
	bool m_state;
	int m_health;
};


