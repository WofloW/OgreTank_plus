#include "Tank.h"
#include "TankManager.h"
#include "ProjectileManager.h"
#include "OgreTank.h"

Tank::Tank(Ogre::Vector3 position, TankManager *tankManager,Ogre::SceneManager *sceneManager, ProjectileManager *projectileManager, int name, int type) : 
	mTankManager(tankManager),mSceneManager(sceneManager), mProjectileManager(projectileManager)
{
	srand ( (unsigned int)time(NULL) );
	mfireCD = 2;
	mtype = type;
	mname = name;
	playerFullHP = 100.0;
	enemyFullHP = 3.0;
	mbuff = "";
	disappearCD = 1;
	disappearTimer = disappearCD;
	kill = 0;
	mshield = false;
	mrecovery = false;
	mbulletN = 1;
	power = 10;

	
	mbulletRange = 1000;
	manglularV = 1.2;
	mBarrelAnglularV = 0.5;
	Tankstate = 1;
	mtankPosition = position;
	mbarrelPosition = Ogre::Vector3( 0, 8, 3 );
	mbarrelOrientation = Ogre::Quaternion(1,0,0,0);
	float degree = Ogre::Math::RangeRandom(0,360)*(Ogre::Math::PI / 180.0f)/2;
	mtankOrientation = Ogre::Quaternion(cos(degree), 0, sin(degree), 0);

	operationCD = 2;
	operationTimer = 0;
	oriBulletVelocity = 1000.0;
	
	if (type == 0)			//Player Tank
	{
		mbulletVelocity = oriBulletVelocity;
		mHealth = playerFullHP;
		mvelocity = 250;
		ent1 = mSceneManager->createEntity("player_tank.mesh");		
		ent2 = mSceneManager->createEntity("player_cannon.mesh");		
	}
	else if ( type==1 )		//AI Tank
	{
		mbulletVelocity = 600;
		mHealth = enemyFullHP*OgreTank::level;
		mvelocity = 25* (float) OgreTank::level;
		ent1 = mSceneManager->createEntity("ai_tank.mesh");		
		ent2 = mSceneManager->createEntity("ai_cannon.mesh");		
	}
	ent3 = mSceneManager->createEntity("dead_tank.mesh");		
	ent4 = mSceneManager->createEntity("dead_cannon.mesh");		
	ent3->setCastShadows(true);
	ent4->setCastShadows(true);
	ent5 = mSceneManager->createEntity("invulnerable_tank.mesh");	
	ent6 = mSceneManager->createEntity("invulnerable_cannon.mesh");
	
	ent1->setCastShadows(true);
	tank = mSceneManager->getRootSceneNode()->createChildSceneNode(mtankPosition);
	tank->attachObject(ent1);
	tank->setOrientation(mtankOrientation);
	ent2->setCastShadows(true);
	barrel = tank->createChildSceneNode(mbarrelPosition);
	barrel->attachObject(ent2);
	barrel->setOrientation(mbarrelOrientation);
}



void
Tank::Think(float time)
{
	operationTimer-= time;
	float TANK_SPEED = mvelocity;
	Ogre::Quaternion rotYaw;
	
	if (Tankstate == 1)
	{
		if (operationTimer<=0)
		{
			operationTimer = operationCD;
			operation1 = rand()%4+1;
			operation2 = rand()%2+1;
		}
	

		switch (operation1)
		{
		case 1:
			rotYaw = Ogre::Quaternion(Ogre::Degree(manglularV), Ogre::Vector3::UNIT_Y);
			rotateTank(rotYaw);
			break;
		case 2:
			rotYaw = Ogre::Quaternion(Ogre::Degree(manglularV), Ogre::Vector3::UNIT_Y);
			rotateTank(rotYaw);
			break;
		case 3:
			if (mbarrelOrientation.y<0.4)
			{
				rotYaw = Ogre::Quaternion(Ogre::Degree(mBarrelAnglularV), Ogre::Vector3::UNIT_Y);
				rotateBarrel(rotYaw);
			}
			break;
		case 4:
			if (mbarrelOrientation.y>-0.4)
			{
				rotYaw = Ogre::Quaternion(Ogre::Degree(-mBarrelAnglularV), Ogre::Vector3::UNIT_Y);
				rotateBarrel(rotYaw);
			}
			break;
		default:
			break;
		}

		switch(operation2)
		{
		case 1:
			moveRelative(Ogre::Vector3(0, 0, -time * TANK_SPEED));
			if (mTankManager->CheckCollision())
				moveRelative(Ogre::Vector3(0, 0, time * TANK_SPEED));
			break;
		case 2:
			moveRelative(Ogre::Vector3(0, 0, time * TANK_SPEED));
			if (mTankManager->CheckCollision())
				moveRelative(Ogre::Vector3(0, 0, -time * TANK_SPEED));
			break;
		default:
			break;
		
		
		}
	
		buttonTimer -= time;
		if (buttonTimer <= 0)
		{
			buttonTimer = getFireCD();
			mProjectileManager->Spawn(this);
		}
	}
}


void 
Tank::beDead()		
{
	Tankstate = 0;
	tank->detachAllObjects();
	tank->attachObject(ent3);
	barrel->detachAllObjects();
	barrel->attachObject(ent4);
}

void 
Tank::beShield()
{
	tank->detachAllObjects();
	tank->attachObject(ent5);
	barrel->detachAllObjects();
	barrel->attachObject(ent6);
}

void
Tank::beDamaged()
{
	ent7 = mSceneManager->createEntity("fired_ai_tank.mesh");		
	ent8 = mSceneManager->createEntity("fired_ai_cannon.mesh");		
	ent7->setCastShadows(true);
	ent8->setCastShadows(true);
	tank->detachAllObjects();
	tank->attachObject(ent7);
	barrel->detachAllObjects();
	barrel->attachObject(ent8);
	mvelocity = mvelocity *3/4;
}


Tank::~Tank()
{
	tank->detachAllObjects();
	barrel->detachAllObjects();
	mSceneManager->destroyEntity(ent1);
	mSceneManager->destroyEntity(ent2);
	mSceneManager->destroyEntity(ent3);
	mSceneManager->destroyEntity(ent4);
	mSceneManager->destroyEntity(ent5);
	mSceneManager->destroyEntity(ent6);
	mSceneManager->destroySceneNode(tank);
	mSceneManager->destroySceneNode(barrel);

}

void 
Tank::beAlive()		//for pvp mode
{
	Tankstate = 1;
	tank->detachAllObjects();
	tank->attachObject(ent1);
	barrel->detachAllObjects();
	barrel->attachObject(ent2);
}

void 
Tank::reset()
{
	mtankPosition = Ogre::Vector3(0,0,50);
	mHealth = playerFullHP;
	mvelocity = 250;
	tank->setPosition(mtankPosition);
	mfireCD = 2;
	mbuff = "";
	kill = 0;
	mbulletVelocity = oriBulletVelocity;
	mbulletRange = 1000;
	manglularV = 1.2;
	mBarrelAnglularV = 0.5;
	beAlive();
	mshield = false;
	mrecovery = false;
	mbulletN = 1;
	power = 10;

}

void 
Tank::buffHit()
{
	if (mbuff.compare("Fast Bullet") || mbuff.compare("Add Bullet Number")) 
		mTankManager->deBuff2();
}