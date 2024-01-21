#include "GameLostGameState.h"

#include "../UI/UIText.h"
#include "../UI/UISprite.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"

#include "../GameData/SpritesheetDef.h"

#include "../MenuGameStates/MainMenuGameState.h"

//---------CONSTRUCTOR/DESTRUCTOR---------------------------

//////////////////////////////
// Constructor for Class
//////////////////////////////
GameLostGameState::GameLostGameState():GameState()
{
}

//////////////////////////////
// Destructor for Class
//////////////////////////////
GameLostGameState::~GameLostGameState()
{
	m_GameObjects.clear();
}

//---------CLASS FUNCTIONS---------------------------

//////////////////////////////
// Initialise the Game State
//////////////////////////////
void GameLostGameState::Initialise()
{
	
	UISprite* t_SGO = new UISprite();
	t_SGO->setSprite("backgrounds/bg_menu_nested.png");
	t_SGO->setScale(1.1, 1.1);
	t_SGO->SetPosition(0, -20);
	t_SGO->Initialise();
	this->m_GameObjects.push_back(t_SGO);

	t_TGA = new UIElements();
	t_TGA->setText("Main Menu");
	t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
	t_TGA->setPosition(10, 35);
	t_TGA->setSpritePosition(0, 30);
	t_TGA->Initialise();
	this->m_GameObjects.push_back(t_TGA);

	t_TGB = new UIElements();
	t_TGB->setText("Exit");
	t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
	t_TGB->setPosition(10, 105);
	t_TGB->setSpritePosition(0, 100);
	t_TGB->Initialise();
	this->m_GameObjects.push_back(t_TGB);

	UIElements* t_score = new UIElements();
	t_score->setSprite("backgrounds/spr_dynamic_bounty_0.png");
	t_score->setFont("fonts/Grand9K Pixel_0.ttf");
	t_score->setText("Score: " + std::to_string(pGameDataStorage->m_Score));
	t_score->setPosition(480, 382);
	t_score->setSpritePosition(300, 330);
	t_score->setScale(2, 2);
	t_score->Initialise();
	this->m_GameObjects.push_back(t_score);

}

//////////////////////////////
// Main Update Loop for Class
//////////////////////////////
void GameLostGameState::Update()
{
	GameState::Update();

	m_prevReturnKeyPressed = false;

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	bool m_currentDownKeyPressed = pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown();
	bool m_currentUpKeyPressed = pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown();
	bool m_currentReturnKeyPressed = pInputDevice->GetButtonInput(E_DigitalInput_A).IsDown();

	if (m_currentDownKeyPressed && !m_prevDownKeyPressed && selection == 0)
	{
		selection = 1;
		m_prevDownKeyPressed = m_currentDownKeyPressed;
	}
	else if(m_currentUpKeyPressed && !m_prevUpkeyPressed && selection == 1)
	{
		selection = 0;
		m_prevUpkeyPressed = m_currentUpKeyPressed;
	}
	m_prevDownKeyPressed = false;
	m_prevUpkeyPressed = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed && selection == 0)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		MainMenuGameState* pMainMenu = new MainMenuGameState();
		pGameStateManager->QueueGameState(pMainMenu);
		m_prevReturnKeyPressed = m_currentReturnKeyPressed;
	}
	else if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed && selection == 1)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		pWindowManager->GetWindow()->close();
		m_prevReturnKeyPressed = m_currentReturnKeyPressed;
	}

	switch (selection)
	{
	case 0:
	{
		t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
		t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
	}
	break;
	case 1:
	{
		t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
		t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
	}
	break;
	}
}

GameObject * GameLostGameState::GetPlayer()
{
	return nullptr;
}
