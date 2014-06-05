#include "Explosion.h"


Explosion::Explosion(Ogre::SceneManager *sceneManager, int explosion, Ogre::Vector3 pos):
	mSceneManager(sceneManager)
{
	ps = mSceneManager->createParticleSystem(Ogre::StringConverter::toString(explosion), "Examples/Explosion");
	sn = mSceneManager->getRootSceneNode()->createChildSceneNode(pos);
	sn->attachObject(ps);
	mtime = 1.0;
}


Explosion::~Explosion(void)
{
	sn->detachAllObjects();
	mSceneManager->destroyParticleSystem(ps);
	mSceneManager->destroySceneNode(sn);
}


void 
	Explosion::Think(float time)
{
	mtime -= time;
}