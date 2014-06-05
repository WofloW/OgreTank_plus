#include "TankCamera.h"



TankCamera::TankCamera(Ogre::Camera *renderCamera, Ogre::Camera *renderCamera2, World *world, InputHandler *input, TankManager *tankManager) :
	mRenderCamera(renderCamera), mRenderCamera2(renderCamera2) , mWorld(world), mInputHandler(input), mTankManager(tankManager)
{
 mRenderCamera->setNearClipDistance(2);
 mcameraNode = mTankManager->myTank()->barrelNode()->createChildSceneNode(Ogre::Vector3( 0, 40, 30 ));
 //mcameraNode = mTankManager->myTank()->barrelNode()->createChildSceneNode(Ogre::Vector3( 0, 40, 150 ));
 mcameraNode->attachObject(mRenderCamera);

 mcameraNode2 = mTankManager->myTank()->tankNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
 mcameraNode2->attachObject(mRenderCamera2);
 mRenderCamera2->setNearClipDistance(5);

}


void
TankCamera::Think(float time)
{
 /*
 const float CAMERA_SPEED = 30;
 // Any code needed here to translate the camera about per frame
 //  (use mRenderCamera to get the actual render camera, of course!)
 if (mInputHandler->IsKeyDown(OIS::KC_A))
  {
  
  if (mInputHandler->IsKeyDown( OIS::KC_LSHIFT ))
  //mRenderCamera->setPosition(mRenderCamera->getPosition() + Ogre::Vector3(time * CAMERA_SPEED, 0, 0));
 mRenderCamera->translate(Ogre::Vector3(time * CAMERA_SPEED,0,0));
  else
  mRenderCamera->yaw(Ogre::Degree(0.5));
  }
  else if (mInputHandler->IsKeyDown(OIS::KC_D))
  {
  
  if (mInputHandler->IsKeyDown( OIS::KC_LSHIFT ))
  //mRenderCamera->setPosition(mRenderCamera->getPosition() - Ogre::Vector3(time * CAMERA_SPEED, 0, 0));
 mRenderCamera->translate(Ogre::Vector3(-time * CAMERA_SPEED,0,0));
  else
  mRenderCamera->yaw(Ogre::Degree(-0.5));
  }
 else if (mInputHandler->IsKeyDown(OIS::KC_W))
  {
  if (mInputHandler->IsKeyDown( OIS::KC_LSHIFT ))
  //mRenderCamera->setPosition(mRenderCamera->getPosition() + Ogre::Vector3(0, time * CAMERA_SPEED, 0));
  mRenderCamera->translate(Ogre::Vector3(0,time * CAMERA_SPEED,0));
  else
  mRenderCamera->pitch(Ogre::Degree(0.5));


  }
 else if (mInputHandler->IsKeyDown(OIS::KC_S))
  {
  if (mInputHandler->IsKeyDown( OIS::KC_LSHIFT ))
  //mRenderCamera->setPosition(mRenderCamera->getPosition() - Ogre::Vector3(0, time * CAMERA_SPEED, 0));
   mRenderCamera->translate(Ogre::Vector3(0,-time * CAMERA_SPEED,0));
  else
 mRenderCamera->pitch(Ogre::Degree(-0.5));
  }
  */
  

}








