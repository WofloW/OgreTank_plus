#ifndef __TankCamera_h_
#define __TankCamera_h_
#include "OgreCamera.h"

#include "World.h"
#include "TankManager.h"
#include "OgreVector3.h"
#include "Tank.h"
// IOS (Input system) header files
#include <ois/ois.h>

// Other input files for my project
#include "InputHandler.h"



class TankCamera
{

public:
    TankCamera(Ogre::Camera *renderCamera, Ogre::Camera *renderCamera2, World *world, InputHandler *input, TankManager *tankManager); 
    void Think(float time);
    // If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could retranslate this class entirely

protected:

    Ogre::Camera *mRenderCamera; 
	Ogre::Camera *mRenderCamera2; 
	InputHandler *mInputHandler;
    World *mWorld;
	TankManager *mTankManager;
	Ogre::SceneNode *mcameraNode;
	Ogre::SceneNode *mcameraNode2;
};

#endif