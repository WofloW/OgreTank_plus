#include "TankManager.h"
#include "World.h"
#include "OgreTank.h"


TankManager::TankManager(Ogre::SceneManager *sceneManager,ProjectileManager *projectileManager, ISoundEngine* soundEngine, Geometry* geometry) :
	mSceneManager(sceneManager), mProjectileManager(projectileManager),mSoundEngine(soundEngine),mGeometry(geometry)
{
	srand ( (unsigned int)time(NULL) );
	spawnCD = 2;
	//reviveCD = 5;
	spawnTimer = 0;

	buffCD = 15;
	buffTimer = buffCD;

	buff = NULL;
	levelNum = 0;
	totalEnemyNum = 2;
	remainTank = totalEnemyNum ;
	levelupsound = "levelup.mp3";
	failsound = "fail.mp3";

	mTank = new Tank(Ogre::Vector3(0,0,0),this, mSceneManager,mProjectileManager, 0, 0);
}


void
TankManager::Think(float time)
{
	spawn(time);
	CheckHP(time);
	for (std::size_t i = 0; i < enemyTankList.size(); i++ )
	{
	   enemyTankList[i]->Think(time);
	}
	//calcScore();
	checkLevel();
	touchBuff();
	if (mTank->getBuff() != "")
	{
		buffTimer -= time;
		if (buff != NULL)
			buff->yaw(Ogre::Radian(time * 0.8));
		if (buffTimer <=0 )
		{
			deBuff();
			buffTimer = buffCD;
		}
	}
}



void
TankManager::spawn(float time)
{
	spawnTimer-= time;
	if (levelNum <totalEnemyNum && spawnTimer <= 0)
	{
		levelNum++;
		spawnTimer = spawnCD;
		float x;
		float z;
		do
		{
			Ogre::Real pos = OgreTank::halfSize-40;
			x = Ogre::Math::RangeRandom(-pos,pos);
			z = Ogre::Math::RangeRandom(-pos,pos);
		}while( notValidLoc(Ogre::Vector3(x,0,z)));
		enemyTankList.push_back(new Tank(Ogre::Vector3(x,0,z),this, mSceneManager,mProjectileManager, 1, 1));
	}
}

bool
TankManager::CheckCollision()		//if collision,return true
{
	Ogre::Real wall_position = OgreTank::halfSize - 22;
	for (std::size_t i = 0; i < enemyTankList.size(); i++ )
   {
	   if (calc_distance( mTank->getTankPosition() , enemyTankList[i]->getTankPosition())<30)			//mTank and enemyTank
		   return true;
	   if (abs(enemyTankList[i]->getTankPosition().x)>wall_position||abs(enemyTankList[i]->getTankPosition().z)>wall_position)		//enemytank and wall
		   return true;
	   if (enemyTankList.size()>2)		//enemyTank and enemyTank
	   {
		   for(std::size_t j = i+1; j < enemyTankList.size(); j++ )
			{
				if (calc_distance( enemyTankList[i]->getTankPosition() , enemyTankList[j]->getTankPosition())<30)
					return true;
			}
	   }
	   if (hitTree(enemyTankList[i]->getTankPosition()))		//enemy and tree
		   return true;

   }
	if (abs(mTank->getTankPosition().x)>wall_position||abs(mTank->getTankPosition().z)>wall_position)		//mtank and wall
		return true;
	
	if (hitTree(mTank->getTankPosition()))		//mTank and tree
		return true;

	return false;
	
}

bool
TankManager::notValidLoc(Ogre::Vector3 v)
{
	if (calc_distance(mTank->getTankPosition(), v)<35)
		return true;
	for (std::size_t i = 0; i < enemyTankList.size(); i++ )
	{
		if (calc_distance(enemyTankList[i]->getTankPosition(), v)<35)
		return true;
	}
	for ( std::size_t i = 0; i< mGeometry->getTreePos().size() ; i++)
	{
		if (calc_distance( mGeometry->getTreePos()[i], v) < 25)
			return true;
	}

	return false;
	
}


float
TankManager::calc_distance(Ogre::Vector3 v1, Ogre::Vector3 v2)
{
	float x1 = v1.x;
	float z1 = v1.z;
	float x2 = v2.x;
	float z2 = v2.z;
	return sqrt( pow((x1-x2),2) + pow(z1-z2,2));
}



void
TankManager::destroyTank(int num)		//for pvp mode
{
	if (num == 0)
	{
		myTank()->beDead();
	}
	else
	{
		enemyTankList[num-1]->beDead();
   }
}


/*
void		//only for pvp mode
TankManager::revive(float time)
{

	for (std::size_t i =0; i<enemyTankList.size(); i++)
	{
		if (enemyTankList[i]->getTankState() == 0)
		{
			if (reviveTimer[i]<=0)
			{
				if (i == 0)
					myTank()->beAlive();
				else
					enemyTankList[i-1]->beAlive();
				enemyTankList[i]->setTankState(1);
				reviveTimer[i] = reviveCD;
			}
			else
				reviveTimer[i] -= time;

		}
	}
}*/

void
TankManager::CheckHP(float time)
{
	if (mTank->getHP()<=0)
	{
		mSoundEngine->play2D(failsound.c_str());
		OgreTank::gameState = 0;
		reset();
		mProjectileManager->reset();
		mGeometry->reset();
	}
	for (std::size_t i = 0; i < enemyTankList.size(); i++ )
	{

		if( enemyTankList[i]->getHP()<=0)
		{
			enemyTankList[i]->disappearTimerGo(time);		//first change mesh
			if (enemyTankList[i]->getDisappearTimer()>0)
				enemyTankList[i]->beDead();
			else{		
				delete enemyTankList[i];					//then disappear
				enemyTankList.erase(enemyTankList.begin()+i);
				remainTank -= 1;
			}
		}

	}
}



void
TankManager::reset()
{
	mTank->beDead();
	for (std::size_t i = 0; i<enemyTankList.size(); i++)
	{
		delete enemyTankList[i];
	}
	enemyTankList.clear();
	if (buff != NULL)
	{
		buff->detachAllObjects();
		mSceneManager->destroyEntity(ent1);
		mSceneManager->destroySceneNode(buff);
	}
	spawnTimer = 0;


}

void
TankManager::start()
{
	OgreTank::level = 1;
	levelNum = 0;
	mTank->reset();
	totalEnemyNum = 2;
	remainTank = totalEnemyNum;
}

void
TankManager::checkLevel()
{
	if(remainTank == 0)
	{
		OgreTank::level++;
		if (totalEnemyNum<=15)
			totalEnemyNum = 2 * OgreTank::level;
		remainTank = totalEnemyNum;
		mSoundEngine->play2D(levelupsound.c_str());
		levelNum = 0;
	}
}

void 
TankManager::touchBuff()
{
	if (mGeometry->getState() == 1 && calc_distance( mTank->getTankPosition() , mGeometry->getBuffPos())<25)
	{
		switch (mGeometry->getBonusNum())
		{
			case 0:
				meshName = "accelerate_bullet.mesh";				//accelerate bullets and increase power
				mTank->setBuff("Fast Bullet");
				mTank->setBulletV(1.5*mTank->getBulletV());
				mTank->setPower( mTank->getPower() + 10);
				ent1 = mSceneManager->createEntity(meshName);
				ent1->setCastShadows(true);
				buff = mTank->tankNode()->createChildSceneNode(Ogre::Vector3(0,20,0));
				buff->attachObject(ent1);
				break;
			case 1:													//HP potion
				meshName = "bottle.mesh";
				mTank->setBuff("HP Recovery");
				mTank->setRecovery(true);
				ent1 = mSceneManager->createEntity(meshName);	
				ent1->setCastShadows(true);
				buff = mTank->tankNode()->createChildSceneNode(Ogre::Vector3(0,22,0));
				buff->attachObject(ent1);
				break;
			case 2:
				meshName = "multiple_bullets.mesh";					//multiple bullets
				mTank->setBuff("Add Bullet Number");
				if (mTank->getBulletN()<5)
					mTank->setBulletN(mTank->getBulletN()+2);
				ent1 = mSceneManager->createEntity(meshName);	
				ent1->setCastShadows(true);
				buff = mTank->tankNode()->createChildSceneNode(Ogre::Vector3(0,20,0));
				buff->attachObject(ent1);
				break;
			case 3:														//invincible
				meshName = "shield.mesh";
				mTank->setBuff("Shield");
				ent1 = mSceneManager->createEntity(meshName);	
				ent1->setCastShadows(true);
				buff = mTank->tankNode()->createChildSceneNode(Ogre::Vector3(0,22,5));
				buff->attachObject(ent1);
				mTank->beShield();
				mTank->setShield(true);
				break;
			default:
				break;
		}
		mGeometry->takeBuff();
	}

}

void 
TankManager::deBuff()			//buff time over, remove all buff effects
{
	mTank->beAlive();
	mTank->setShield(false);
	mTank->setRecovery(false);
	mTank->setBuff("");
	if (buff != NULL)
	{
		buff->detachAllObjects();
		mSceneManager->destroyEntity(ent1);
		mSceneManager->destroySceneNode(buff);
		buff = NULL;
	}
	
}

bool
TankManager::hitTree(Ogre::Vector3 pos)
{
	for ( std::size_t i = 0; i< mGeometry->getTreePos().size() ; i++)
	{
		if (calc_distance( mGeometry->getTreePos()[i], pos) < 16)
			return true;
	}
	return false;
}

void 
TankManager::deBuff2()		//get hit, only remove buff 0 and 2 effect
{

	if (buff != NULL)
	{
		buff->detachAllObjects();
		mSceneManager->destroyEntity(ent1);
		mSceneManager->destroySceneNode(buff);
		buff = NULL;
	}
}