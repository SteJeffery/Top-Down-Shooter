#ifndef _UI_TEXT_H_
#define _UI_TEXT_H_

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"

#include "../GameObjects/PlayerCharacter.h"

#include <string>

class UIText :	public GameObject
{
public:
	//-------CONSTRUCTORS/DESTRUCTORS--------------
	UIText();
	virtual ~UIText();

public:
	//-------VIRTUAL FUNCTION OVERRIDES------------
	virtual void Initialise() override;
	virtual void Update();
	virtual void GetPosition(int& x, int & y);
	
public: 
	void setColour(sf::Color pcolour);
	void setFont(std::string pfont);
	void setCharSize(int psize);
	void setText(std::string ptext);
	void setUI(bool UI);
	void setPosition(int px, int py);
	void setPosition(sf::Vector2f ppos);

protected:
	Text m_Text;
	std::string m_TextString;
	bool m_UI;
	std::string m_FontName;
	sf::Color   m_Colour;
	int         m_CharSize;
};

#endif