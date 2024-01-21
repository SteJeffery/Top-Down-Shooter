#ifndef _UI_SPRITE_H_
#define _UI_SPRITE_H_

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/System/Context/SysContextProvider.h"

#include "../GameData/GameDataManager.h"


class UISprite : public GameObject
{
public:
	UISprite();
	~UISprite();

	virtual void Initialise()override;
	virtual void Update() override;

	virtual void GetPosition(int& x, int & y) override;

	virtual void SetPosition(int x, int y);

	void setSprite(std::string psprite);

	void setScale(float x, float y);

private:
	Sprite m_sprite;
	std::string m_SpriteFile;
};
#endif