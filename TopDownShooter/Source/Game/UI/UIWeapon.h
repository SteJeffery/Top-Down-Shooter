#ifndef _UI_WEAPON_H_
#define _UI_WEAPON_H_

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/System/Context/SysContextProvider.h"

#include "../GameData/GameDataManager.h"


class UIWeapon : public GameObject
{
public:
	UIWeapon();
	~UIWeapon();

	virtual void Initialise()override;
	virtual void Update() override;

	virtual void GetPosition(int& x, int & y) override;

	virtual void SetPosition(int x, int y);

	void setSprite(std::string psprite);

	std::string m_SpriteFile;

private:
	Sprite m_sprite;
};
#endif