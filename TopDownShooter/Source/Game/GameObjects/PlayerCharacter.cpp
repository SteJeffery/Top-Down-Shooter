#include "PlayerCharacter.h"

#include "../GameData/GameDataManager.h"

#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Utils/Utils.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../../Engine/Renderer/FrameTimer.h"

#include "../Weapons/WeaponBase.h"
#include "../Weapons/BlitzWeapon.h"
#include "../Weapons/PistolWeapon.h"

#include "../MenuGameStates/GameLostGameState.h"

#include "SFML/Graphics.hpp"

PlayerCharacter::PlayerCharacter()
:m_moving(false)
,m_health(3)
,m_IsHit(false)
,m_state(false)
{
}


PlayerCharacter::~PlayerCharacter()
{
	SAFE_DELETE_PTR(m_pWeapon);
}

void PlayerCharacter::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	SpritesheetDef* pSpritesheetDef;
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_biu.xml");

	if (pSpritesheetDef)
	{
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Dash, pSpritesheetDef, "spr_biu_dash", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Death, pSpritesheetDef, "spr_biu_death", 10, false);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Dig, pSpritesheetDef, "spr_biu_dig", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Hit, pSpritesheetDef, "spr_biu_hit", 10, false);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Holo, pSpritesheetDef, "spr_biu_holo", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpritesheetDef, "spr_biu_idle", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Melee, pSpritesheetDef, "spr_biu_melee", 10, false);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Sprint, pSpritesheetDef, "spr_biu_sprint", 10);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_TeleportIn, pSpritesheetDef, "spr_biu_teleport_in", 10, false);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_TeleportOut, pSpritesheetDef, "spr_biu_teleport_out", 10, false);
		m_animatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpritesheetDef, "spr_biu_walk", 10);
		m_animatedSprite.SetCurrentAnimation(E_AnimationState_TeleportIn);
	}

	m_CollisionRect = m_animatedSprite.getGlobalBounds();

	m_WeaponOffsetX = 0;
	m_WeaponOffsetY = 20;

	m_pWeapon = new BlitzWeapon();
	m_pWeapon->Initialise();
	currentWeapon = 1;
}

void PlayerCharacter::Update()
{
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
	
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	PlayerMovement();
	WeaponUpdate();
	WeaponControls();
	WeaponSwap();

	if (m_IsHit)
	{
		m_animatedSprite.SetCurrentAnimation(E_AnimationState_Hit);
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
	case E_AnimationState_Sprint:
	{
			
	}
	break;
	case E_AnimationState_Death:
	{
		if (m_animatedSprite.AnimationFinished())
		{
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameLostGameState* pLost = new GameLostGameState();
			pGameStateManager->QueueGameState(pLost);
		}
	}
	break;
	case E_AnimationState_Dig:
	{
		
	}
	break;
	case E_AnimationState_Hit:
	{
		if (m_animatedSprite.AnimationFinished())
		{
			m_animatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
	}
	break;
	case E_AnimationState_Holo:
	{
		
	}
	break;
	case E_AnimationState_TeleportIn:
	{
		if (m_animatedSprite.AnimationFinished())
		{
			m_animatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
	}
	break;
	case E_AnimationState_TeleportOut:
	{
		if (m_animatedSprite.AnimationFinished())
		{
			m_animatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
	}
	break;
	case E_AnimationState_Dash:
	{

	}
	break;
	case E_AnimationState_Melee:
	{
		pGameDataStorage->m_playerAttacking = true;

		if (m_animatedSprite.AnimationFinished())
		{
			pGameDataStorage->m_playerAttacking = false;
			m_animatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
	}
	break;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		WeaponReload();
	}

	m_animatedSprite.Animate();

	m_CollisionRect = m_animatedSprite.getGlobalBounds();
}

void PlayerCharacter::GetPosition(int & x, int & y)
{
	x = m_animatedSprite.getPosition().x; 
	y = m_animatedSprite.getPosition().y;
}

void PlayerCharacter::SetPosition(int x, int y)
{
	m_animatedSprite.setPosition(x, y);
}

int PlayerCharacter::GetHealth()
{
	return m_health;
}

void PlayerCharacter::SetHealth(int health)
{
	m_health = health;
}

void PlayerCharacter::Hit()
{
	m_IsHit = true;
}

void PlayerCharacter::OnCollision(Collider2D * pCollider2D)
{
	if (pGameDataStorage->m_enemyAttacking == true)
	{
		Hit();
	}
}

void PlayerCharacter::Dead()
{
	if (m_health <= 0)
	{
		m_animatedSprite.SetCurrentAnimation(E_AnimationState_Death);
	}
}

void PlayerCharacter::WeaponSwap()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		SAFE_DELETE_PTR(m_pWeapon);
		m_pWeapon = new BlitzWeapon();
		m_pWeapon->Initialise();
		currentWeapon = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		SAFE_DELETE_PTR(m_pWeapon);
		m_pWeapon = new PistolWeapon();
		m_pWeapon->Initialise();
		currentWeapon = 2;
	}
}

void PlayerCharacter::WeaponUpdate()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	float angle = 0.0f;

	if (pInputDevice)
	{
		float thumbXPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();
		float thumbYPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue();

		sf::Vector2f up(0.0f, -1.0f);
		sf::Vector2f forwards(thumbXPos, thumbYPos);

		angle = MathHelpers::AngleBetweenVectors(up, forwards) -90.0f;
	}

	//change angle relative to scale for when character flips in the x axis
	angle = m_animatedSprite.getScale().x < 0.0f ? -angle : angle;

	//follow the player position and scale
	m_pWeapon->SetPosition(m_animatedSprite.getPosition().x + m_WeaponOffsetX * m_animatedSprite.getScale().x, m_animatedSprite.getPosition().y + m_WeaponOffsetY * m_animatedSprite.getScale().y);
	m_pWeapon->SetRotation(angle);
	m_pWeapon->SetScale(m_animatedSprite.getScale().x, m_animatedSprite.getScale().y);
	m_pWeapon->Update();
}



void PlayerCharacter::WeaponReload()
{
	if (m_pWeapon)
	{
		m_pWeapon->Reload();
	}
}

void PlayerCharacter::WeaponControls()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_RightTrigger).GetValue() >= 0.1f)
	{
		WeaponFire();
	}

	if(pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_LeftShoulder).OnPressed())
	{
		m_animatedSprite.SetCurrentAnimation(E_AnimationState_Melee);
	}
}

void PlayerCharacter::WeaponFire()
{
	if (m_pWeapon)
	{
		m_pWeapon->Fire();
		pGameDataStorage->m_playerAttacking = true;
	}
}

void PlayerCharacter::PlayerMovement()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	m_moving = false;

	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
	{
		m_animatedSprite.move(sf::Vector2f(0.0f, -5.0f));
		m_moving = true;
	}

	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
	{
		m_animatedSprite.move(sf::Vector2f(0.0f, 5.0f));
		m_moving = true;
	}

	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
	{
		m_animatedSprite.move(sf::Vector2f(-5.0f, 0.0f));
		m_moving = true;
	}

	if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
	{
		m_animatedSprite.move(sf::Vector2f(5.0f, 0.0f));
		m_moving = true;
	}

	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() > 0.0f)
	{
		m_animatedSprite.setScale(1.0f, 1.0f);
	}
	else if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() < 0.0f)
	{
		m_animatedSprite.setScale(-1.0f, 1.0f);
	}
}
