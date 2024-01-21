#pragma once
#include "../../Engine/Core/GameObject.h"

#include <SFML\Graphics.hpp>

class Camera : public GameObject
{
public:
	Camera();
	~Camera();


	virtual void Initialise();
	virtual void Update();

	void SetAsCurrentCamera();
	void RemoveCamera();

	virtual void GetPosition(int& x, int & y);

private:

	sf::View m_view;
	bool m_Active;
};

