#ifndef _MainMenu_GAMESTATE_H_
#define _MainMenu_GAMESTATE_H_

#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Audio/AudioManager.h"

#include "../GameData/GameDataManager.h"

#include "../UI/UIElements.h"


class MainMenuGameState : public GameState
{

public:
	//---CONSTRUCTORS/DESTRUCTORS------------
	MainMenuGameState();
	virtual ~MainMenuGameState();

	//---VIRTUAL FUNCTION OVERRIDES----------
	virtual void Initialise();
	virtual void Update();
	virtual GameObject* GetPlayer();

	int selection = 0;

private:
	UIElements* t_TGA;
	UIElements* t_TGC;
	UIElements* t_TGB;

	AudioManager* pAudio = C_SysContext::Get<AudioManager>();

	bool m_prevDownKeyPressed;
	bool m_prevUpkeyPressed;
	bool m_prevReturnKeyPressed;
};
#endif