#ifndef _GAME_DATA_MANAGER_H
#define _GAME_DATA_MANAGER_H

#include <map>

struct SpritesheetDef;

class GameDataManager
{
public:
	GameDataManager();
	~GameDataManager();

	void Initialise();

	void AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef);
	SpritesheetDef* GetSpritesheetDef(const char* filename);

	bool LoadSpritesheetDefFromFile(const char* filename);

	int m_health;
	int m_PistolAmmo;
	int m_MaxPistolAmmo;
	int m_BlitzAmmo;
	int m_MaxBlitzAmmo;
	int m_Score = 0;

	bool m_enemyAttacking = true; //Only set to true to test player health damage and game lost state
	bool m_playerAttacking = false;

private:

	std::map<int, SpritesheetDef*> m_SpritesheetDefs;
public: 

};

#endif
