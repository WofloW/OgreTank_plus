#ifndef __TankManager_h_
#define __TankManager_h_
#include "OgreSceneNode.h"
#include "Tank.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Geometry.h"


// sound system
#include "include/irrKlang.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")

class TankManager
{

public:
	TankManager(Ogre::SceneManager *sceneManager,ProjectileManager *mProjectileManager, ISoundEngine* soundEngine, Geometry* geometry);
	~TankManager();
	void Think(float time);
	Tank *myTank() { return mTank; }
	void spawn(float time);
	bool CheckCollision();
	bool notValidLoc(Ogre::Vector3 v);
	float calc_distance(Ogre::Vector3 v1, Ogre::Vector3 v2);
	std::vector<Tank*> getEnemyList() {return enemyTankList;}
	void destroyTank(int num);
	int getTotalEnemyNum() {return totalEnemyNum;}
	void revive(float time);		//only for pvp mode, automatic reviving after certain time
	void CheckHP(float time);
	void reset();
	void checkLevel();
	void setRemainTank(int n) {remainTank = n;}
	int getRemainTank() {return remainTank;}
	void start();
	void touchBuff();
	void deBuff();
	bool hitTree(Ogre::Vector3 pos);
	void deBuff2();


protected:
	Tank *mTank;
	std::vector<Tank*> enemyTankList;
	Ogre::SceneManager *mSceneManager;
	ProjectileManager *mProjectileManager;
	ISoundEngine* mSoundEngine;
	Geometry* mGeometry;
	int totalEnemyNum;
	int levelNum;
	int remainTank;
	float spawnCD;
	float spawnTimer;

	//float reviveCD;
	//float reviveTimer[10];

	std::string levelupsound;
	std::string failsound;

	std::string meshName;
	Ogre::SceneNode *buff;
	Ogre::Entity *ent1;
	float buffCD;
	float buffTimer;

};

#endif