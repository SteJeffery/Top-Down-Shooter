#pragma once

#include <SFML/Graphics.hpp>

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

#include "../GameData/GameDataManager.h"

struct SpritesheetDef;

struct MapVariables
{
	int mapWidth;
	int mapHeight;
	int playerPosX;
	int playerPosY;
};

class TileMap : public sf::Drawable, public sf::Transformable, public GameObject
{
public:
	TileMap();
	~TileMap();
	
	bool LoadFromSpriteSheetDef(SpritesheetDef* pSpriteSheetDef, const int* tiles, const int width, unsigned int height);
	
	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int & y);
	virtual void LoadFromFile(const char* filename);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 

public: 
	MapVariables MapData; 

private:
	sf::VertexArray m_vertices;
	sf::Texture* m_pTileset;
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef;
};

