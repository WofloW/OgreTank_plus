#ifndef __ProjectileManager_h_
#define __ProjectileManager_h_

#include "Ogre.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "Projectile.h"
#include "Tank.h"
#include "Geometry.h"

// sound system
#include "include/irrKlang.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")
//particle system
#include "OgreParticleSystem.h"
#include "Explosion.h"

class TankManager;



class ProjectileManager 
{

public:

	ProjectileManager( Ogre::SceneManager *sceneManager, ISoundEngine* soundEngine, Geometry* geometry);
	Tank* CheckCollision(Projectile* pro);
	
	void Spawn(Tank *fromTank);
    void Think(float time);
	void addTankManager(TankManager *c) { mTankManager = c; }
	void reset();
	bool hitTree(Ogre::Vector3 pos);


protected:
	std::vector<Projectile*> mProjectileList;
	Ogre::SceneManager *mSceneManager;
	TankManager *mTankManager;
	ISoundEngine* mSoundEngine;
	Geometry* mGeometry;
	int explosion;
	std::vector<Explosion*> mExplosionList;
};

#endif