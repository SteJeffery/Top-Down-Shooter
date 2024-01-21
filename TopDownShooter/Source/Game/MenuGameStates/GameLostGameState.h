#ifndef _GameLost_GAMESTATE_H_
#define _GameLost_GAMESTATE_H_

#include "../../Engine/System/GameState/GameState.h"

#include "../GameData/GameDataManager.h"

#include "../UI/UIText.h"
#include "../UI/UIElements.h"


class GameLostGameState : public GameState
{

public:
	//---CONSTRUCTORS/DESTRUCTORS------------
	GameLostGameState();
	virtual ~GameLostGameState();

	//---VIRTUAL FUNCTION OVERRIDES----------
	virtual void Initialise();
	virtual void Update();
	virtual GameObject* GetPlayer();

	int selection = 0;

private:
	
	UIElements* t_TGA;
	UIElements* t_TGB;
	UIText* m_UIScore;
	GameDataManager* pGameDataStorage = C_SysContext::Get<GameDataManager>();
	bool m_prevDownKeyPressed;
	bool m_prevUpkeyPressed;
	bool m_prevReturnKeyPressed;
};
#endif