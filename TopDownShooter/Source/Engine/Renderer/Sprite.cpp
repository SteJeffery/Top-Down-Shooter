#include "Sprite.h"
#include "../System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "RenderManager.h"

Sprite::Sprite()
:m_bInitialised(false)
,UIObject(false)
{
}

Sprite::~Sprite()
{
	if (UIObject)
	{
		C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(this);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
	}
}

void Sprite::Initialise(const char* filename, const int x, const int y, const int sizeX, const int sizeY,bool UIObject)
{
	AssetManager* pAssetManager = C_SysContext::Get<AssetManager>();
	setTexture(pAssetManager->GetTexture(filename));
	m_bInitialised = true;
	
	if (UIObject)
	{
		C_SysContext::Get<RenderManager>()->AddUIRenderObject(this);
	}
	else
	{
		C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	}
}
