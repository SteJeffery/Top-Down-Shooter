#ifndef _PauseMenu_GAMESTATE_H_
#define _PauseMenu_GAMESTATE_H_

#include "../../Engine/System/GameState/GameState.h"

#include "../UI/UIElements.h"

class PauseMenuGameState : public GameState
{

public:
	//---CONSTRUCTORS/DESTRUCTORS------------
	PauseMenuGameState();
	virtual ~PauseMenuGameState();

	//---VIRTUAL FUNCTION OVERRIDES----------
	virtual void Initialise();
	virtual void Update();
	virtual GameObject* GetPlayer();

	int selection = 0;

private:
	UIElements* t_TGA;
	UIElements* t_TGB;

	bool m_prevDownKeyPressed;
	bool m_prevUpkeyPressed;
	bool m_prevReturnKeyPressed;
};
#endif