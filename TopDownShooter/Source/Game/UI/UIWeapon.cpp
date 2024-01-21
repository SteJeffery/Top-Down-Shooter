
#include "UIWeapon.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

UIWeapon::UIWeapon()
{
}


UIWeapon::~UIWeapon()
{
}

void UIWeapon::Initialise()
{
	m_sprite.Initialise(m_SpriteFile.c_str(), 0, 0, 99, 87,true);
	m_sprite.setScale(1.45, 1.45);
}

void UIWeapon::Update()
{
	m_sprite.Initialise(m_SpriteFile.c_str(), 0, 0, 99, 87, true);
}

void UIWeapon::GetPosition(int & x, int & y)
{
	x = m_sprite.getPosition().x;
	y = m_sprite.getPosition().y;
}

void UIWeapon::SetPosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}

void UIWeapon::setSprite(std::string psprite)
{
	m_SpriteFile = psprite;
}
