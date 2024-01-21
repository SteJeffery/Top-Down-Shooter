#include "UIText.h"

//---------CONSTRUCTOR/DESTRUCTOR---------------------------

//////////////////////////////
// Constructor for Class
//////////////////////////////
UIText::UIText()
{
	this->m_FontName = "fonts/Grand9K Pixel_0.ttf"; 
	this->m_CharSize = 32;
	this->m_Colour = sf::Color::White;
}

//////////////////////////////
// Destructor for Class
//////////////////////////////
UIText::~UIText()
{
}

//---------CLASS FUNCTIONS---------------------------

//////////////////////////////
//Initialise the Text Game Object
//////////////////////////////
void UIText::Initialise()
{
	this->m_Text.Initialise(m_FontName.c_str(),m_TextString.c_str(),m_CharSize,m_Colour,m_UI);
}

//////////////////////////////
//Update Loop for the Text Game
//Object.
//////////////////////////////
void UIText::Update()
{
	if(this->m_TextString != "")
		this->m_Text.GetTextRW().setString(this->m_TextString);
}

//////////////////////////////
// Get the Position of the Text
// Game Object and store on 
// the two reference parameters
//////////////////////////////
void UIText::GetPosition(int& x, int & y)
{
	//Assign the Reference Variables the values from the Position
	x = this->m_Text.GetText().getPosition().x;
	y = this->m_Text.GetText().getPosition().y;
}

/////////////////////////////////
// Set the Colour on the Text
// Game Object.
/////////////////////////////////
void UIText::setColour(sf::Color pcolour)
{
	this->m_Colour = pcolour;
}

/////////////////////////////////
// Set the Name of the Font
/////////////////////////////////
void UIText::setFont(std::string pfont)
{
	this->m_FontName = pfont;
}

/////////////////////////////////
// Set the Scale of the Text
/////////////////////////////////
void UIText::setCharSize(int psize)
{
	this->m_CharSize = psize;
}

/////////////////////////////////
// Set the Value of the Text
/////////////////////////////////
void UIText::setText(std::string ptext)
{
	this->m_TextString = ptext;
}

void UIText::setUI(bool UI)
{
	m_UI = UI;
}

/////////////////////////////////
// Set the Position of the Text
/////////////////////////////////
void UIText::setPosition(int px, int py)
{
	m_Text.GetTextRW().setPosition(px, py);
}

/////////////////////////////////
// Set the Position of the Text
/////////////////////////////////
void UIText::setPosition(sf::Vector2f ppos)
{
	
}
