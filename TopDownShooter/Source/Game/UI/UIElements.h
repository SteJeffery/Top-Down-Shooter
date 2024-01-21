#ifndef _UI_ELEMENTS_H_
#define _UI_ELEMENTS_H_

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/UI/Text.h"

#include "../GameData/GameDataManager.h"




class UIElements : public GameObject
{
public:
	UIElements();
	virtual ~UIElements();

public:

	virtual void Initialise()override;
	virtual void Update() override;
	virtual void GetPosition(int& x, int & y) override;

public:
	void setColour(sf::Color pcolour);
	void setFont(std::string pfont);
	void setCharSize(int psize);
	void setText(std::string ptext);
	void setSprite(std::string psprite);
	void setScale(float x, float y);
	void setUI(bool UI);
	void setPosition(int px, int py);
	void setSpritePosition(int x, int y);

	bool m_Selected;
	std::string m_SpriteFile;

protected:
	Sprite m_sprite;
	Text m_Text;
	std::string m_TextString;
	bool m_UI;
	std::string m_FontName;
	sf::Color   m_Colour;
	int         m_CharSize;

	


};
#endif
