#include "TileMap.h"

#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/RenderManager.h"

#include "../GameData/SpritesheetDef.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

bool TileMap::LoadFromSpriteSheetDef(SpritesheetDef * pSpriteSheetDef, const int * tiles, const int width, unsigned int height)
{
	if (!pSpriteSheetDef)
		return false;

	AssetManager* pAssetManager = C_SysContext::Get<AssetManager>();
	m_pTileset = &(pAssetManager->GetTexture(pSpriteSheetDef->m_Filename.c_str()));

	std::vector<sf::IntRect> frames;
	for (std::vector<SpritesheetSpriteDef>::iterator iter = pSpriteSheetDef->m_pSpriteDefs.begin(); iter != pSpriteSheetDef->m_pSpriteDefs.end(); iter++)
	{
		sf::IntRect rect((*iter).m_PosX, (*iter).m_PosY, (*iter).m_Width, (*iter).m_Height);
		frames.push_back(rect);
	}

	int numTiles = 0;

	for (int i = 0; i < width * height; i++)
	{
		int tileNumber = tiles[i];

		if (tileNumber < 0 || tileNumber >= frames.size())
			continue;

		numTiles++;
	}

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(numTiles * 4);

	int quadNum = 0;

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * width];

			//If the tile number is outside the range of valid tiles, leave it as a blank space
			if (tileNumber < 0 || tileNumber >= frames.size())
				continue;

			int tu1 = frames[tileNumber].left;
			int tv1 = frames[tileNumber].top;
			int tu2 = tu1 + frames[tileNumber].width;
			int tv2 = tv1 + frames[tileNumber].height;

			sf::Vertex* quad = &m_vertices[(quadNum) * 4];

			// define its 4 corners (Geometric Position
			quad[0].position = sf::Vector2f(i * frames[tileNumber].width, j * frames[tileNumber].height);
			quad[1].position = sf::Vector2f((i + 1) * frames[tileNumber].width, j * frames[tileNumber].height);
			quad[2].position = sf::Vector2f((i + 1) * frames[tileNumber].width, (j + 1) * frames[tileNumber].height);
			quad[3].position = sf::Vector2f(i * frames[tileNumber].width, (j + 1) * frames[tileNumber].height);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu1, tv1);
			quad[1].texCoords = sf::Vector2f(tu2, tv1);
			quad[2].texCoords = sf::Vector2f(tu2, tv2);
			quad[3].texCoords = sf::Vector2f(tu1, tv2);
			quadNum++;
		}
	C_SysContext::Get<RenderManager>()->AddRenderObject(this);

	return true;
}

void TileMap::Initialise()
{
}

void TileMap::Update()
{
}

void TileMap::GetPosition(int & x, int & y)
{
}

void TileMap::LoadFromFile(const char* filename)
{

	//read file and store value
	ifstream file;
	string str;

	file.open(filename);

	if (file.is_open())
	{
		string width;
		string height;

		string posX;
		string posY;

		getline(file, str);
		istringstream stringStream2(str);
		stringStream2 >> posX;
		stringStream2 >> posY;

		MapData.playerPosX = stoi(posX);
		MapData.playerPosY = stoi(posY);

		getline(file, str);
		istringstream stringStream(str);
		stringStream >> width;
		stringStream >> height;

		this->MapData.mapWidth = stoi(width);
		this->MapData.mapHeight = stoi(height);

		int* pMap = new int[MapData.mapWidth*MapData.mapHeight];
		int input;

		getline(file, str);
		pSpriteSheetDef = pGameDataManager->GetSpritesheetDef(str.c_str());

		for (int i = 0; i < MapData.mapWidth * MapData.mapHeight; i++)
		{
			file >> input;
			pMap[i] = input;
		}

		file.close();

		LoadFromSpriteSheetDef(pSpriteSheetDef, pMap, MapData.mapWidth, MapData.mapHeight);

		delete[] pMap;
	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cout << "Error: " << message;
	}

}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	//Apply the transform
	states.transform *= getTransform();

	//Apply the tile set texture
	states.texture = m_pTileset;

	//Draw the vertex array
	target.draw(m_vertices, states);
}
