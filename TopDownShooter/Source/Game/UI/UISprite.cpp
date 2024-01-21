#include "UISprite.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

UISprite::UISprite()
{
}


UISprite::~UISprite()
{
}

void UISprite::Initialise()
{
	m_sprite.Initialise(m_SpriteFile.c_str(), 0, 0, 99, 87,true);
}

void UISprite::Update()
{
}

void UISprite::GetPosition(int & x, int & y)
{
	x = m_sprite.getPosition().x;
	y = m_sprite.getPosition().y;
}

void UISprite::SetPosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}

void UISprite::setSprite(std::string psprite)
{
	m_SpriteFile = psprite;
}

void UISprite::setScale(float x, float y)
{
	m_sprite.setScale(x, y);
}
