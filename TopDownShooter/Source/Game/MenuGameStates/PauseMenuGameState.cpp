#include "PauseMenuGameState.h"


#include "../UI/UIText.h"
#include "../UI/UISprite.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"

#include "../GameData/SpritesheetDef.h"

//---------CONSTRUCTOR/DESTRUCTOR---------------------------

//////////////////////////////
// Constructor for Class
//////////////////////////////
PauseMenuGameState::PauseMenuGameState():GameState()
{
}

//////////////////////////////
// Destructor for Class
//////////////////////////////
PauseMenuGameState::~PauseMenuGameState()
{
	m_GameObjects.clear();
}

//---------CLASS FUNCTIONS---------------------------

//////////////////////////////
// Initialise the Game State
//////////////////////////////
void PauseMenuGameState::Initialise()
{
	
	UISprite* t_SGO = new UISprite();
	t_SGO->setSprite("backgrounds/bg_pause.png");
	t_SGO->setScale(1.1, 1.1);
	t_SGO->SetPosition(-200, -20);
	t_SGO->Initialise();
	this->m_GameObjects.push_back(t_SGO);

	UISprite* t_Char = new UISprite();
	t_Char->setSprite("sprites/hud/spr_card_biu_0.png");
	t_Char->SetPosition(765, 0);
	t_Char->Initialise();
	this->m_GameObjects.push_back(t_Char);

	UISprite* t_Char2 = new UISprite();
	t_Char2->setSprite("sprites/hud/spr_card_jimmy_0.png");
	t_Char2->SetPosition(0, 479);
	t_Char2->Initialise();
	this->m_GameObjects.push_back(t_Char2);


	t_TGA = new UIElements();
	t_TGA->setText("Resume");
	t_TGA->setPosition(450, 285);
	t_TGA->setSprite("sprites/menu/spr_menu_button_1.png");
	t_TGA->setSpritePosition(300, 280);
	t_TGA->Initialise();
	this->m_GameObjects.push_back(t_TGA);

	t_TGB = new UIElements();
	t_TGB->setText("Exit");
	t_TGB->setPosition(480, 385);
	t_TGB->setSprite("sprites/menu/spr_menu_button_0.png");
	t_TGB->setSpritePosition(300, 380);
	t_TGB->Initialise();
	this->m_GameObjects.push_back(t_TGB);

}

//////////////////////////////
// Main Update Loop for Class
//////////////////////////////
void PauseMenuGameState::Update()
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
		pGameStateManager->QueuePop();
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
		t_TGA->setSprite("sprites/menu/spr_menu_button_1.png");
		t_TGB->setSprite("sprites/menu/spr_menu_button_0.png");
	}
	break;
	case 1:
	{
		t_TGA->setSprite("sprites/menu/spr_menu_button_0.png");
		t_TGB->setSprite("sprites/menu/spr_menu_button_1.png");
	}
	break;
	}
}

GameObject * PauseMenuGameState::GetPlayer()
{
	return nullptr;
}
