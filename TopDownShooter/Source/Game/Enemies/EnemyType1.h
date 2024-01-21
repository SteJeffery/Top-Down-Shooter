#pragma once
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/System/Animation/AnimationStateMachine.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

#include "../GameData/GameDataManager.h"

#include <vector>

class EnemyType1 : public GameObject, public BoxCollider2D      
{
public:
	EnemyType1();
	virtual ~EnemyType1();

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);
	virtual void SetPosition(int x, int y);
	virtual int GetHealth();

	virtual void Hit();
	virtual void OnCollision(Collider2D* pCollider2D);
	virtual void Dead();

private:
	GameDataManager* pGameDataStorage = C_SysContext::Get<GameDataManager>();
	AnimatedSprite m_animatedSprite;
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Death,
		E_AnimationState_Hit,
	};


	bool m_moving;
	bool m_IsHit;
	bool m_state;
	int m_health;

};
