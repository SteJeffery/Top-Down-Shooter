#include "HowToPlayScreen.h"



#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"

#include "../UI/UIElements.h"
#include "../UI/UISprite.h"
#include "../UI/UIText.h"

#include "../GameData/SpritesheetDef.h"

#include "../MenuGameStates/MainMenuGameState.h"


//---------CONSTRUCTOR/DESTRUCTOR---------------------------

//////////////////////////////
// Constructor for Class
//////////////////////////////
HowToPlayScreen::HowToPlayScreen():GameState()
{
}

//////////////////////////////
// Destructor for Class
//////////////////////////////
HowToPlayScreen::~HowToPlayScreen()
{
	m_GameObjects.clear();
}

//---------CLASS FUNCTIONS---------------------------

//////////////////////////////
// Initialise the Game State
//////////////////////////////
void HowToPlayScreen::Initialise()
{
	UISprite* t_Background = new UISprite;
	t_Background->setSprite("backgrounds/bg_menu_settings.png");
	t_Background->setScale(1.1, 1.1);
	t_Background->SetPosition(-150,-10);
	t_Background->Initialise();
	this->m_GameObjects.push_back(t_Background);

}

//////////////////////////////
// Main Update Loop for Class
//////////////////////////////
void HowToPlayScreen::Update()
{
	GameState::Update();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		MainMenuGameState* m_menu = new MainMenuGameState();
		pGameStateManager->QueueGameState(m_menu);
	}
}

GameObject * HowToPlayScreen::GetPlayer()
{
	return nullptr;
}
