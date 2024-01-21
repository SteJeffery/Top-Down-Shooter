#include "Bullet.h"

#include "../GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"

#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/Context/SysContextProvider.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/bullets/spr_bullet.xml");

	m_animatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_bullet", 24, false);
	m_animatedSprite.SetCurrentAnimation(0);

	m_Velocity = 1500.0f;
	m_Lifetime = 1.0f;

	m_CollisionRect = m_animatedSprite.getGlobalBounds();
}

void Bullet::Update()
{
	m_CollisionRect = m_animatedSprite.getGlobalBounds();

	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	m_animatedSprite.Animate();

	if (m_animatedSprite.GetCurrentFrame() == 0)
		return;

	sf::Vector2f movement(1.0f, 0.0f);

	movement *= (m_Velocity * pFrameTimer->DeltaTime());

	sf::Transform transform;
	transform.rotate(m_animatedSprite.getRotation());
	transform.scale(m_animatedSprite.getScale());
	movement = transform.transformPoint(movement);

	m_animatedSprite.move(movement);

	m_Lifetime -= pFrameTimer->DeltaTime();
	if (m_Lifetime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();

		
		//remove from to the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);
	}

	m_CollisionRect = m_animatedSprite.getGlobalBounds();
	
}

void Bullet::GetPosition(int& x, int & y)
{
	x = m_animatedSprite.getPosition().x;
	y = m_animatedSprite.getPosition().y;
}

void Bullet::SetPosition(int x, int y)
{
	m_animatedSprite.setPosition(x, y);
}

void Bullet::SetRotation(float angle)
{
	m_animatedSprite.setRotation(angle);
}

void Bullet::SetScale(int scaleX, int scaleY)
{
	m_animatedSprite.setScale(scaleX, scaleY);
}

void Bullet::OnCollision(Collider2D* pCollider2D)
{
}
