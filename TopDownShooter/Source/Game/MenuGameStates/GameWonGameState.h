#ifndef _GameWon_GAMESTATE_H_
#define _GameWon_GAMESTATE_H_

#include "../../Engine/System/GameState/GameState.h"

#include "../GameData/GameDataManager.h"

#include "../UI/UIElements.h"
#include "../UI/UIText.h"

class GameWonGameState : public GameState
{

public:
	//---CONSTRUCTORS/DESTRUCTORS------------
	GameWonGameState();
	virtual ~GameWonGameState();

	//---VIRTUAL FUNCTION OVERRIDES----------
	virtual void Initialise();
	virtual void Update();
	virtual GameObject* GetPlayer();

	int selection = 0;

private:
	UIElements* t_TGA;
	UIElements* t_TGB;

	GameDataManager* pGameDataStorage = C_SysContext::Get<GameDataManager>();

	bool m_prevDownKeyPressed;
	bool m_prevUpkeyPressed;
	bool m_prevReturnKeyPressed;
};
#endif