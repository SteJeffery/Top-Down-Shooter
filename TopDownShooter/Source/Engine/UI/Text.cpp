#include "Text.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"

Text::Text()
	:m_Initialised(false)
	,m_UIObject(false)
{

}

Text::~Text()
{
	if (m_UIObject)
	{
		C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_Text);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->RemoveRenderObject(&m_Text);
	}
}

void Text::Initialise(const char* filename, const char* text,int psize,sf::Color pcolour, bool UIObject)
{
	AssetManager* pAssetManager = C_SysContext::Get<AssetManager>();
	m_Text.setFont(*pAssetManager->GetFont(filename));
	m_UIObject = UIObject;

	m_Text.setString(text);
	m_Text.setCharacterSize(psize); // in pixels, not points!
	m_Text.setFillColor(pcolour);
	//m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	if (UIObject)
	{
		C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_Text);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->AddRenderObject(&m_Text);
	}


	m_Initialised = true;
}
