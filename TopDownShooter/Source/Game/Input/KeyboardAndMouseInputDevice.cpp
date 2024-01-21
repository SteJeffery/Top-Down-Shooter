#include <iostream>

#include "KeyboardAndMouseInputDevice.h"

#include <SFML\Graphics.hpp>

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Core/MathHelpers.h"





KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{
}


KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{
}

void KeyboardAndMouseInputDevice::ProcessInputs()
{

	//This code is setting the Digital input, of the D-pad to the corresponding Keyboard keys.
	m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
	m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
	m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
	m_DigitalInputs[E_DigitalInput_LeftShoulder].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::V));
	m_DigitalInputs[E_DigitalInput_A].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));

	m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0.0f);
	m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0.0f);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	GameObject* pPlayer = pGameState->GetPlayer();
	if (pPlayer)
	{
		int posX = 0;
		int posY = 0;

		pPlayer->GetPosition(posX, posY);

		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		sf::RenderWindow* pWindow = pWindowManager->GetWindow();

		const sf::View view = pWindow->getView();

		//get the mouse position relative to the window
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);

		//get the mouse world position
		sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

		sf::Vector2f distance((float)mouseWorldPos.x - (float)posX, (float)mouseWorldPos.y - (float)posY);

		distance = MathHelpers::Normalise(distance);

		m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(distance.x);
		m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(distance.y);
	}
	else
	{
		m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0.0f);
		m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0.0f);
	}

	//This is setting the Left and Right Tricker on an Analogue Controller to the Mouse 1 and Mouse 2 buttons.
	m_AnalogueInputs[E_AnalogueInput_LeftTrigger].SetValue(sf::Mouse::isButtonPressed(sf::Mouse::Right) ? 1.0f : 0.0f);
	m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? 1.0f : 0.0f);
}