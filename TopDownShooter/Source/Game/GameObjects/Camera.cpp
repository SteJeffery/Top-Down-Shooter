#include "Camera.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"



Camera::Camera()
{
}


Camera::~Camera()
{
	this->RemoveCamera();
}

void Camera::Initialise()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();

	this->m_view = pWindowManager->GetWindow()->getDefaultView();
}

void Camera::Update()
{
	//Get the Current Game State
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
	GameObject* PlayerCamera = pCurrentGameState->GetPlayer();

	//Get the Player's Position from the Player Game Object
	if (PlayerCamera)
	{
		//Use the GetPosition function of the Game Object
		int positionX = 0;
		int positionY = 0;
		PlayerCamera->GetPosition(positionX, positionY);
		m_view.setCenter(sf::Vector2f(positionX, positionY));
	}
	if (this->m_Active)
	{
		this->SetAsCurrentCamera();
	}

}
void Camera::SetAsCurrentCamera()
{
	m_Active = true;
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(m_view);
}

void Camera::RemoveCamera()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(pWindowManager->GetWindow()->getDefaultView());

	m_Active = false;
}

void Camera::GetPosition(int & x, int & y)
{
}
