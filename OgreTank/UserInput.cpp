#include "UserInput.h"
#include "World.h"
#include "OgreTank.h"



UserInput::UserInput(InputHandler * input, TankManager *tankManager, ProjectileManager *projectileManager, ISoundEngine* soundEngine) :
	mInputHandler(input), mTankManager(tankManager), mProjectileManager(projectileManager),mSoundEngine(soundEngine)
{
	buttonTimer = 0;
	moveState = false;
	moveSound = "track.wav";
	fireSound = "fire.wav";
	moveSoundE = mSoundEngine->play2D(moveSound.c_str(),true,false, true);
	moveSoundE->setIsPaused(true);
	moveSoundE->setVolume(0.5f);
}


void UserInput::Think(float time) {				//userinput.think() == myTank.think()
    float TANK_SPEED = mTankManager->myTank()->getVelocity();
	moveState = false;
	
	
	if (OgreTank::gameState == 0)		//game pause
	{
		moveSoundE->setIsPaused(true);
		if (mInputHandler->IsKeyDown(OIS::KC_RETURN))
		{
			OgreTank::gameState = 1;
			mTankManager->start();
		}
	}
	else{								//game running
		if (mTankManager->myTank()->getTankState() ==0)		//dead tank can't move, so pause movesound			for pvp mode, my tank can revive in a certain time
			moveSoundE->setIsPaused(true);

		if (mTankManager->myTank()->getTankState() ==1)		//alive tank can move
		{
			 if (mInputHandler->IsKeyDown(OIS::KC_A)) {
				Ogre::Quaternion rotYaw = Ogre::Quaternion(Ogre::Degree(mTankManager->myTank()->getanglularV()), Ogre::Vector3::UNIT_Y);
				mTankManager->myTank()->rotateTank(rotYaw);
				moveState = true;
			} 
			if (mInputHandler->IsKeyDown(OIS::KC_D)) {

				Ogre::Quaternion rotYaw = Ogre::Quaternion(Ogre::Degree(-mTankManager->myTank()->getanglularV()), Ogre::Vector3::UNIT_Y);
				mTankManager->myTank()->rotateTank(rotYaw);
				moveState = true;
			}
			if (mInputHandler->IsKeyDown(OIS::KC_Q)) {
				if (mTankManager->myTank()->barrelNode()->getOrientation().y<0.4)
				{
				//Ogre::Real degree = mTankManager->myTank()->getBarrelAnglularV() * (Ogre::Math::PI / 180.0f)/2;
				//Ogre::Quaternion rotYaw = Ogre::Quaternion(cos(degree), 0, sin(degree), 0);
				Ogre::Quaternion rotYaw = Ogre::Quaternion(Ogre::Degree( mTankManager->myTank()->getBarrelAnglularV()), Ogre::Vector3::UNIT_Y);
				mTankManager->myTank()->rotateBarrel(rotYaw);
				}
			}
			if (mInputHandler->IsKeyDown(OIS::KC_E)) {
				if (mTankManager->myTank()->barrelNode()->getOrientation().y>-0.4)
				{
					Ogre::Quaternion rotYaw = Ogre::Quaternion(Ogre::Degree( -mTankManager->myTank()->getBarrelAnglularV()), Ogre::Vector3::UNIT_Y);
					mTankManager->myTank()->rotateBarrel(rotYaw);
				}
			}
			if (mInputHandler->IsKeyDown(OIS::KC_W)) {
				mTankManager->myTank()->moveRelative(Ogre::Vector3(0, 0, -time * TANK_SPEED));
				if (mTankManager->CheckCollision())
					mTankManager->myTank()->moveRelative(Ogre::Vector3(0, 0, time * TANK_SPEED));
				moveState = true;
			}
			if (mInputHandler->IsKeyDown(OIS::KC_S)) {
				mTankManager->myTank()->moveRelative(Ogre::Vector3(0, 0, time * TANK_SPEED));
				if (mTankManager->CheckCollision())
					mTankManager->myTank()->moveRelative(Ogre::Vector3(0, 0, -time * TANK_SPEED));
				moveState = true;
			}

			if (moveState)		//move state
			{
				if (moveSoundE->getIsPaused() )	//if move state and no move sound, active move sound
					moveSoundE->setIsPaused(false);
			}
			else
				if(!moveSoundE->getIsPaused() )		//if !move state and move sound, deactive move sound
					moveSoundE->setIsPaused(true);



			buttonTimer -= time;
			if (mInputHandler->IsKeyDown(OIS::KC_J) && buttonTimer <= 0)
			{
				buttonTimer = mTankManager->myTank()->getFireCD();
				mProjectileManager->Spawn(mTankManager->myTank());
				mSoundEngine->play2D(fireSound.c_str());
			}

			if(mTankManager->myTank()->getRecovery() == true)
			{
				if (mTankManager->myTank()->getHP() <= mTankManager->myTank()->getFullHP())
					mTankManager->myTank()->setHP(mTankManager->myTank()->getHP() + time);
			}

		
		}
	}

}

UserInput::~UserInput()
{
	moveSoundE->drop();

}








