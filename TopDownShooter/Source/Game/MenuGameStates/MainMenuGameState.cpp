#include "MainMenuGameState.h"

#include "../UI/UIText.h"
#include "../UI/UISprite.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"

#include "../GameData/SpritesheetDef.h"

#include "../LevelGameStates/Level1GameState.h"
#include "HowToPlayScreen.h"


//---------CONSTRUCTOR/DESTRUCTOR---------------------------

//////////////////////////////
// Constructor for Class
//////////////////////////////
MainMenuGameState::MainMenuGameState():GameState()
{
	m_prevReturnKeyPressed = true;
}

//////////////////////////////
// Destructor for Class
//////////////////////////////
MainMenuGameState::~MainMenuGameState()
{
	m_GameObjects.clear();
}

//---------CLASS FUNCTIONS---------------------------

//////////////////////////////
// Initialise the Game State
//////////////////////////////
void MainMenuGameState::Initialise()
{
	pAudio->PlayMusic("sounds/bgm_main.wav", true);
	pAudio->SetMusicVolume(5.0f);

	UISprite* t_SGO = new UISprite();
	t_SGO->setSprite("backgrounds/bg_menu_main.png");
	t_SGO->setScale(1.1,1.1);
	t_SGO->SetPosition(-10, 0);
	t_SGO->Initialise();
	this->m_GameObjects.push_back(t_SGO);


	UISprite* t_MMU = new UISprite();
	t_MMU->setSprite("sprites/spr_logo_41.png");
	t_MMU->setScale(0.9, 0.9);
	t_MMU->SetPosition(-50, 300);
	t_MMU->Initialise();
	this->m_GameObjects.push_back(t_MMU);

    t_TGA = new UIElements();
	t_TGA->setText("Play");
	t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
	t_TGA->setPosition(10, 35);
	t_TGA->setSpritePosition(0, 30);
	t_TGA->Initialise();
	this->m_GameObjects.push_back(t_TGA);

	t_TGC = new UIElements();
	t_TGC->setText("Controls");
	t_TGC->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
	t_TGC->setPosition(10, 105);
	t_TGC->setSpritePosition(0, 100);
	t_TGC->Initialise();
	this->m_GameObjects.push_back(t_TGC);

	t_TGB = new UIElements();
	t_TGB->setText("Exit");
	t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
	t_TGB->setPosition(10, 175);
	t_TGB->setSpritePosition(0, 170);
	t_TGB->Initialise();
	this->m_GameObjects.push_back(t_TGB);
}

//////////////////////////////
// Main Update Loop for Class
//////////////////////////////
void MainMenuGameState::Update()
{
	GameState::Update();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	bool m_currentDownKeyPressed = pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown();
	bool m_currentUpKeyPressed = pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown();
	bool m_currentReturnKeyPressed = pInputDevice->GetButtonInput(E_DigitalInput_A).IsDown();

	switch (selection)
	{
	case 0:
	{
		if (m_currentDownKeyPressed && !m_prevDownKeyPressed)
		{
			selection = 1;
			pAudio->PlaySoundFX("sounds/sfx_menu_mouse.wav", false);
		}
	}
	break;
	case 1:
	{
		if (m_currentUpKeyPressed && !m_prevUpkeyPressed)
		{
			selection = 0;
			pAudio->PlaySoundFX("sounds/sfx_menu_mouse.wav", false);
		}
		else if (m_currentDownKeyPressed && !m_prevDownKeyPressed)
		{
			selection = 2;
			pAudio->PlaySoundFX("sounds/sfx_menu_mouse.wav", false);
		}
	}
		break;
	case 2:
	{
		if (m_currentUpKeyPressed && !m_prevUpkeyPressed)
		{
			selection = 1;
			pAudio->PlaySoundFX("sounds/sfx_menu_mouse.wav", false);
		}
	}
	}

	m_prevDownKeyPressed = m_currentDownKeyPressed;
	m_prevUpkeyPressed = m_currentUpKeyPressed;

	switch (selection)
	{
	case 0:
	{
		if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		{
			pAudio->PlaySoundFX("sounds/sfx_menu_click.wav", false);
			pAudio->RemoveAllMusicObjects();
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			Level1GameState* pLevel1 = new Level1GameState();
			pGameStateManager->QueueGameState(pLevel1);
		}
	}
	break;
	case 1:
	{
		if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		{
			pAudio->PlaySoundFX("sounds/sfx_menu_click.wav", false);
			pAudio->RemoveAllMusicObjects();
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			HowToPlayScreen* pControls = new HowToPlayScreen();
			pGameStateManager->QueueGameState(pControls);
		}
	}
	break;
	case 2:
	{
		if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		{
			pAudio->PlaySoundFX("sounds/sfx_menu_click.wav", false);
			pAudio->RemoveAllMusicObjects();
			WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
			pWindowManager->GetWindow()->close();
		}
	}
	}

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;

	switch (selection)
	{
	case 0:
	{
		t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
		t_TGC->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
		t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
		
	}
	break;
	case 1:
	{
		t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
		t_TGC->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
		t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
	}
	break;
	case 2:
	{
		t_TGA->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
		t_TGC->setSprite("sprites/menu/spr_menu_buttonMain_0.png");
		t_TGB->setSprite("sprites/menu/spr_menu_buttonMain_1.png");
	}
	}
}

GameObject * MainMenuGameState::GetPlayer()
{
	return nullptr;
}
