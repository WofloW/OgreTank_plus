#include "OgreParticleSystem.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"

class Explosion
{
public:
	Explosion(Ogre::SceneManager *sceneManager, int explosion, Ogre::Vector3 pos);
	~Explosion(void);
	void Think(float time);
	float getTime() {return mtime;}

protected:
	Ogre::SceneManager *mSceneManager;
	Ogre::ParticleSystem* ps;
	Ogre::SceneNode* sn;
	float mtime;
};

