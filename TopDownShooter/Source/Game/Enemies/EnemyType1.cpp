#include "EnemyType1.h"

#include "../GameData/GameDataManager.h"

#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Utils/Utils.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../../Engine/Renderer/FrameTimer.h"

#include "SFML/Graphics.hpp"

EnemyType1::EnemyType1()
:m_moving(false)
, m_health(1)
, m_IsHit(false)
, m_state(false)
{
}


EnemyType1::~EnemyType1()
{
}

void EnemyType1::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	pGameDataStorage->m_health = m_health;

	SpritesheetDef* pSpritesheetDef;
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_worm.xml");

	if (pSpritesheetDef)
	{
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpritesheetDef, "spr_worm_idle", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpritesheetDef, "spr_worm_walk", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Death, pSpritesheetDef, "spr_worm_death1", 10, false);
		m_animatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
	}


    m_CollisionRect = m_animatedSprite.getGlobalBounds();
}

void EnemyType1::Update()
{
	m_CollisionRect = m_animatedSprite.getGlobalBounds();

	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	pGameDataStorage->m_health = m_health;

	if (m_IsHit)
	{
		m_IsHit = false;
		m_health = m_health - 1;
		Dead();
	}


	switch (m_animatedSprite.GetCurrentAnimation())
	{
	case E_AnimationState_Idle:
	{
		if (m_moving)
		{
			m_animatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
		}
	}
	break;
	case E_AnimationState_Walk:
	{
		if (!m_moving)
		{
			m_animatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
	}
	break;
	case E_AnimationState_Death:
	{
		if (m_animatedSprite.AnimationFinished())
		{
			pCurrentGameState->RemoveGameObject(this);
			pGameDataStorage->m_Score = pGameDataStorage->m_Score + 40;
		}
	};

     m_animatedSprite.Animate();
     m_CollisionRect = m_animatedSprite.getGlobalBounds();
	}
}

void EnemyType1::GetPosition(int & x, int & y)
{
	x = m_animatedSprite.getPosition().x;
	y = m_animatedSprite.getPosition().y;
}

void EnemyType1::SetPosition(int x, int y)
{
	m_animatedSprite.setPosition(x,y);
}

int EnemyType1::GetHealth()
{
	return m_health;
}

void EnemyType1::Hit()
{
	m_IsHit = true;
	pGameDataStorage->m_playerAttacking = false;
}

void EnemyType1::OnCollision(Collider2D * pCollider2D)
{
	if (pGameDataStorage->m_playerAttacking == true)
	{
		Hit();
	}
}

void EnemyType1::Dead()
{
	if (m_health <= 0)
	{
		m_animatedSprite.SetCurrentAnimation(E_AnimationState_Death);
	}
}