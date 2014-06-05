#include "ProjectileManager.h"
#include "TankManager.h"



ProjectileManager::ProjectileManager( Ogre::SceneManager *sceneManager, ISoundEngine* soundEngine, Geometry* geometry):
	mSceneManager(sceneManager),mSoundEngine(soundEngine),mGeometry(geometry)
{
	Ogre::ParticleSystem::setDefaultNonVisibleUpdateTimeout(1);  // set nonvisible timeout
	
	
}

void
ProjectileManager::Spawn(Tank *fromTank)
{
	if (fromTank->getBulletN() == 3)
	{
		Ogre::Quaternion rotLeft = Ogre::Quaternion(Ogre::Degree(-10), Ogre::Vector3::UNIT_Y);
		Ogre::Quaternion rotRight = Ogre::Quaternion(Ogre::Degree(10), Ogre::Vector3::UNIT_Y);
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, rotLeft*fromTank->getBulletOrientation()));
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, rotRight*fromTank->getBulletOrientation()));
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, fromTank->getBulletOrientation()));
	}
	else if (fromTank->getBulletN() == 5)
	{
		Ogre::Real degree = 5 * (Ogre::Math::PI / 180.0f)/2;
		Ogre::Quaternion rotLeft = Ogre::Quaternion(cos(degree), 0, sin(degree), 0);
		Ogre::Quaternion rotRight = Ogre::Quaternion(cos(-degree), 0, sin(-degree), 0);
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, rotLeft*rotLeft*fromTank->getBulletOrientation()));
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, rotRight*rotRight*fromTank->getBulletOrientation()));
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, rotLeft*fromTank->getBulletOrientation()));
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, rotRight*fromTank->getBulletOrientation()));
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, fromTank->getBulletOrientation()));
	}
	else
		mProjectileList.push_back(new Projectile( mSceneManager,  this , fromTank, mSoundEngine, fromTank->getBulletOrientation()));
	
}


void
ProjectileManager::Think(float time)
{
	bool collision = false;

	for (std::size_t i = 0; i < mProjectileList.size(); i++ )
   {
	   collision = mProjectileList[i]->Think(time);
	   if (collision)
	   {
		   explosion++;
		   mExplosionList.push_back(new Explosion(mSceneManager, explosion, mProjectileList[i]->getBulletPosition()));
		   delete mProjectileList[i];
		   mProjectileList.erase(mProjectileList.begin()+i);
	   }
   }

	if (explosion > 10000000)
		explosion = 0;

	for (std::size_t i = 0; i < mExplosionList.size(); i++ )
	{
		mExplosionList[i]->Think(time);
		if (mExplosionList[i]->getTime() < 0)
		{
			delete mExplosionList[i];
			mExplosionList.erase(mExplosionList.begin()+i);
		}
	}

}



Tank*
ProjectileManager::CheckCollision(Projectile* pro1)		//return hit tank pointer
{
	Tank *t = pro1->getfromTank();
	if (t->getType() != 0)
	{
		if (mTankManager->calc_distance( pro1->getBulletPosition(), mTankManager->myTank()->getTankPosition())<25)
		{
			return mTankManager->myTank();
		}
	}

	for (std::size_t i = 0; i < mTankManager->getEnemyList().size(); i++ )
   {
	   if (mTankManager->getEnemyList()[i] == t)
		   continue;
	   if (mTankManager->calc_distance( pro1->getBulletPosition(), mTankManager->getEnemyList()[i]->getTankPosition())<25)
	   {
		   return mTankManager->getEnemyList()[i];
	   }
   }
	return NULL;
	
}




void
ProjectileManager::reset()
{
	for (std::size_t i = 0; i < mProjectileList.size(); i++ )
   {
	   delete mProjectileList[i];
   }
	mProjectileList.clear();
}

bool
ProjectileManager::hitTree(Ogre::Vector3 pos)
{
	for ( std::size_t i = 0; i< mGeometry->getTreePos().size() ; i++)
	{
		if (mTankManager->calc_distance( mGeometry->getTreePos()[i], pos) < 10)
			return true;
	}
	return false;
}