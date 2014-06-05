#ifndef __Projectile_h_
#define __Projectile_h_

#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "Ogre.h"
#include "Tank.h"

// sound system
#include "include/irrKlang.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")

class ProjectileManager;

class Projectile 
{

public:

	Projectile(Ogre::SceneManager *sceneManager,ProjectileManager *projectileManager, Tank *fromTank, ISoundEngine* soundEngine, Ogre::Quaternion ori);
	~Projectile();
	Ogre::Vector3 getBulletPosition() {return bulletPosition;}
    bool Think(float time);
	Tank* getfromTank() {return mfromTank;}


protected:

	Ogre::Vector3 bulletPosition;
	Ogre::Quaternion bulletOrientation;
	float mVelocity;
	
	Ogre::SceneNode *bullet;
	Ogre::Entity *ent1;
	Ogre::SceneManager *mSceneManager;
	ProjectileManager *mProjectileManager;
	ISoundEngine* mSoundEngine;
	float mbulletRange;
	Tank *destroyTank;
	Tank *mfromTank;

	int power;
	std::string explosionSound;

};

#endif