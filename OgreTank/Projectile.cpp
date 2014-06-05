#include "Projectile.h"
#include "ProjectileManager.h"
#include "OgreTank.h"


Projectile::Projectile(Ogre::SceneManager *sceneManager,  ProjectileManager *projectileManager, Tank *fromTank, ISoundEngine* soundEngine, Ogre::Quaternion ori) :
	mSceneManager(sceneManager), mProjectileManager(projectileManager),mSoundEngine(soundEngine)
{
	mVelocity = fromTank->getBulletV();
	bulletPosition = fromTank->getBulletPosition();
	bulletOrientation = ori;
	destroyTank = NULL;
	mfromTank = fromTank;
	ent1 = mSceneManager->createEntity("bullet.mesh");
	ent1->setCastShadows(true);
	bullet = mSceneManager->getRootSceneNode()->createChildSceneNode(bulletPosition);
	bullet->attachObject(ent1);
	bullet->setOrientation(bulletOrientation);
	mbulletRange = fromTank->getBulletRange();
	power = fromTank->getPower();
	explosionSound = "explosion.mp3";
}


bool
Projectile::Think(float time)	//if collision,return true
{
	mbulletRange -= time*mVelocity;
	bulletPosition += bulletOrientation*Ogre::Vector3(0,0,mVelocity)*time;
	bullet->setPosition(bulletPosition);
	destroyTank = mProjectileManager->CheckCollision(this);
	/*		pvp mode
	if (destroyName != -1 && mProjectileManager->getTankState()[destroyName] == 1)
	{
		mProjectileManager->destroyTank(destroyName);
		mProjectileManager->calcScore(mfromTankName,destroyName);
	}
	*/

	if (destroyTank != NULL && destroyTank->getTankState() == 1 )
	{
		if (mfromTank->getType() == 0 || ((destroyTank->getType() == 0) && !destroyTank->getShield()))
		{
			if (destroyTank->getType() == 0)
			{
				destroyTank->setBulletN(1);
				destroyTank->setBulletV( destroyTank->getOriBulletV());
				destroyTank->setPower(10);
				destroyTank->buffHit();
			}
			
			mSoundEngine->play2D(explosionSound.c_str());
			float newHP = destroyTank->getHP() - power;
			destroyTank->setHP(newHP );
			if (mfromTank->getType() == 0)
			{
				if(newHP <= destroyTank->getFullEnemyHP()*OgreTank::level/2)
					destroyTank->beDamaged();
			}
			if (newHP <=0)
				mfromTank->setKill(mfromTank->getKill() + 1);
		}
	}

	if (mbulletRange <= 0 || abs(bulletPosition.x)> OgreTank::halfSize ||abs(bulletPosition.z)>OgreTank::halfSize || destroyTank != NULL || mProjectileManager->hitTree(bulletPosition))
	{
		return true;
	}

	return false;

}


Projectile::~Projectile()
{
	bullet->detachAllObjects();
	mSceneManager->destroyEntity(ent1);
	mSceneManager->destroySceneNode(bullet);
}





