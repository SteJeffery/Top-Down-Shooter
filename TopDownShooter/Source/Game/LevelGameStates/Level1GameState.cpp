#include "Level1GameState.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"

#include "../GameObjects/Camera.h"
#include "../GameObjects/PlayerCharacter.h"

#include "../Enemies/EnemyType1.h"

#include "../UI/UISprite.h"
#include "../UI/UIText.h" 

#include "../GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"

#include "../MenuGameStates/PauseMenuGameState.h"
#include "../LevelGameStates/Level2GameState.h"

#include <SFML/Graphics.hpp>


//---------CONSTRUCTOR/DESTRUCTOR---------------------------

//////////////////////////////
// Constructor for Class
//////////////////////////////
Level1GameState::Level1GameState():GameState()
{
	pGameDataStorage->m_Score = 0;
}

//////////////////////////////
// Destructor for Class
//////////////////////////////
Level1GameState::~Level1GameState()
{
}

//---------CLASS FUNCTIONS---------------------------

//////////////////////////////
// Initialise the Game State
//////////////////////////////
void Level1GameState::Initialise()
{
	
	//----Load the Level Data First - this is our Tile Map
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef = pGameDataManager->GetSpritesheetDef("backgrounds/bg_desert.xml");

	m_pTileMapBase = new TileMap();
	m_pTileMapBase->Initialise();
	m_pTileMapBase->LoadFromSpriteSheetDef(pSpriteSheetDef, levelbase, 56, 22);
	m_GameObjects.push_back(m_pTileMapBase);

	TileMap* pForeground = new TileMap();
	pForeground->Initialise();
	pForeground->LoadFromFile("levels/Level1.txt");
	m_GameObjects.push_back(pForeground);
	
	UISprite* MainObj = new UISprite();
	MainObj->setSprite("sprites/hud/spr_hud_main_0.png");
	MainObj->setScale(2, 2);
	MainObj->SetPosition(75, 665);
	MainObj->Initialise();
	this->m_GameObjects.push_back(MainObj);
	

	UISprite* HealthOBJ = new UISprite();
	HealthOBJ->setSprite("sprites/hud/spr_icon_health_0.png");
	HealthOBJ->setScale(1.3, 1.3);
	HealthOBJ->SetPosition(180, 727);
	HealthOBJ->Initialise();
	this->m_GameObjects.push_back(HealthOBJ);

	UISprite* HealthOBJ2 = new UISprite();
	HealthOBJ2->setSprite("sprites/hud/spr_icon_health_0.png");
	HealthOBJ2->setScale(1.3, 1.3);
	HealthOBJ2->SetPosition(220, 727);
	HealthOBJ2->Initialise();
	this->m_GameObjects.push_back(HealthOBJ2);

	UISprite* HealthOBJ3 = new UISprite();
	HealthOBJ3->setSprite("sprites/hud/spr_icon_health_0.png");
	HealthOBJ3->setScale(1.3, 1.3);
	HealthOBJ3->SetPosition(260, 727);
	HealthOBJ3->Initialise();
	this->m_GameObjects.push_back(HealthOBJ3);
	
	
	UISprite* CharBox = new UISprite();
	CharBox->setSprite("sprites/hud/spr_char_playerCard_0.png");
	CharBox->setScale(1.2, 1.2);
	CharBox->SetPosition(-210, 635);
	CharBox->Initialise();
	this->m_GameObjects.push_back(CharBox);

	UISprite* HeadObj = new UISprite();
	HeadObj->setSprite("sprites/hud/spr_hud_face_biu_0.png");
	HeadObj->SetPosition(15, 670);
	HeadObj->Initialise();
	this->m_GameObjects.push_back(HeadObj);

	BlitzObj = new UIWeapon();
	BlitzObj->setSprite("sprites/weapons/spr_blitz_0.png");
	BlitzObj->SetPosition(18, 632);
	BlitzObj->Initialise();
	this->m_GameObjects.push_back(BlitzObj);

	PlayerCharacter* t_PC = new PlayerCharacter();
	t_PC->SetPosition(pForeground->MapData.playerPosX, pForeground->MapData.playerPosY);
	t_PC->Initialise();
	this->m_PlayerCharacter = t_PC;
	this->m_GameObjects.push_back(t_PC);

	EnemyType1* t_EC = new EnemyType1();
	t_EC->SetPosition(550, 550);
	t_EC->Initialise();
	this->m_GameObjects.push_back(t_EC);

	//Create a Blitz Ammo Ui Object
	m_UIAmmo = new UIText();
	m_UIAmmo->setText(std::to_string(pGameDataStorage->m_BlitzAmmo) + " / " + std::to_string(pGameDataStorage->m_MaxBlitzAmmo));
	m_UIAmmo->setUI(true);
	m_UIAmmo->setPosition(178, 673);
	m_UIAmmo->Initialise();
	this->m_GameObjects.push_back(m_UIAmmo);

	t_score = new UIElements();
	t_score->setSprite("backgrounds/spr_dynamic_bounty_0.png");
	t_score->setFont("fonts/Grand9K Pixel_0.ttf");
	t_score->setText("Score: " + std::to_string(pGameDataStorage->m_Score));
	t_score->setPosition(90, 34);
	t_score->setSpritePosition(10, 10);
	t_score->setScale(1.2, 1.2);
	t_score->Initialise();
	this->m_GameObjects.push_back(t_score);

	Camera* m_Camera = new Camera();
	m_Camera->Initialise();
	m_GameObjects.push_back(m_Camera);
}

//////////////////////////////
// Main Update Loop for Class
//////////////////////////////
void Level1GameState::Update()
{	
	GameState::Update();
	
	m_UIAmmo->setText(std::to_string(pGameDataStorage->m_BlitzAmmo) + " / " + std::to_string(pGameDataStorage->m_MaxBlitzAmmo));
	t_score->setText("Score: " + std::to_string(pGameDataStorage->m_Score));

	if (m_PlayerCharacter->currentWeapon == 1)
	{
		BlitzObj->setSprite("sprites/weapons/spr_blitz_0.png");
		BlitzObj->SetPosition(18, 632);
		m_UIAmmo->setText(std::to_string(pGameDataStorage->m_BlitzAmmo) + " / " + std::to_string(pGameDataStorage->m_MaxBlitzAmmo));
	}
	else if (m_PlayerCharacter->currentWeapon == 2)
	{
		BlitzObj->setSprite("sprites/weapons/spr_pistol_blast_0.png");
		BlitzObj->SetPosition(18, 642);
		m_UIAmmo->setText(std::to_string(pGameDataStorage->m_PistolAmmo) + " / " + std::to_string(pGameDataStorage->m_MaxPistolAmmo));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		PauseMenuGameState* pPause = new PauseMenuGameState();
		pGameStateManager->QueueGameState(pPause);
	}

	if (pGameDataStorage->m_Score == 40)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		Level2GameState* pLevel2 = new Level2GameState();
		pGameStateManager->QueueGameState(pLevel2);
	}
}

//////////////////////////////
// Implementation of Get Player
//////////////////////////////
GameObject* Level1GameState::GetPlayer()
{
	return m_PlayerCharacter;
}
