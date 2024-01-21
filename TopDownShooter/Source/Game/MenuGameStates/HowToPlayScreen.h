#ifndef _HOW_TO_PLAY_SCREEN_H_
#define _HOW_TO_PLAY_SCREEN_H_

#include "../../Engine/System/GameState/GameState.h"

class HowToPlayScreen : public GameState
{

public:
	//---CONSTRUCTORS/DESTRUCTORS------------
	HowToPlayScreen();
	virtual ~HowToPlayScreen();

	//---VIRTUAL FUNCTION OVERRIDES----------
	virtual void Initialise();
	virtual void Update();
	virtual GameObject* GetPlayer();

	int selection = 0;

private:
	bool m_prevDownKeyPressed;
	bool m_prevUpkeyPressed;
	bool m_prevReturnKeyPressed;
};
#endif