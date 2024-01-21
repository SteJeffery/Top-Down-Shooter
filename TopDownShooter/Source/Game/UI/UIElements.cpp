#include "UIElements.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"



UIElements::UIElements()
	:m_Selected(false)
{
	this->m_FontName = "fonts/8-BIT WONDER.TTF";
	this->m_CharSize = 32;
	this->m_Colour = sf::Color::Black;
}


UIElements::~UIElements()
{
}

void UIElements::Initialise()
{
	this->m_sprite.Initialise(m_SpriteFile.c_str(), 0, 0, 100, 100, true);
	this->m_Text.Initialise(m_FontName.c_str(), m_TextString.c_str(), m_CharSize, m_Colour, m_UI);;

	this->m_Text.GetTextRW().getPosition();
	
}

void UIElements::Update()
{
	this->m_sprite.Initialise(m_SpriteFile.c_str(), 0, 0, 100, 100, true);
	this->m_Text.Initialise(m_FontName.c_str(), m_TextString.c_str(), m_CharSize, m_Colour, m_UI);;
	
	this->m_Text.GetTextRW().getPosition();
}

void UIElements::GetPosition(int & x, int & y)
{
	x = m_sprite.getPosition().x;
	y = m_sprite.getPosition().y;
}

void UIElements::setColour(sf::Color pcolour)                                 
{
	this->m_Colour = pcolour;
}

void UIElements::setFont(std::string pfont)  
{
	this->m_FontName = pfont;
}

void UIElements::setCharSize(int psize)
{
	this->m_CharSize = psize;
}

void UIElements::setText(std::string ptext)
{
	this->m_TextString = ptext;
}

void UIElements::setSprite(std::string psprite)
{
	m_SpriteFile = psprite;
}

void UIElements::setScale(float x, float y)
{
	m_sprite.setScale(x, y);
}

void UIElements::setUI(bool UI)
{
	m_UI = UI;
}

void UIElements::setPosition(int px, int py)
{
	m_Text.GetTextRW().setPosition(px,py);
}

void UIElements::setSpritePosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}