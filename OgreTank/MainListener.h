#ifndef __MainListener_h_
#define __MainListener_h_

#include "Ogre.h"
#include "OgreFrameListener.h"
#include "InputHandler.h"
#include "World.h"
#include "TankCamera.h"
#include "UserInput.h"

#include <ois.h>



class MainListener : public Ogre::FrameListener
{
public:
	MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputHandler, World *world, TankCamera *cam, UserInput *userInput);

	bool frameStarted(const Ogre::FrameEvent &evt);


protected:
	InputHandler *mInputHandler;
	World *mWorld;
    TankCamera *mTankCamera;
	Ogre::RenderWindow *mRenderWindow;
	UserInput *mUserInput;
	
	
};

#endif