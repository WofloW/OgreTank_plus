#include "MainListener.h"



MainListener::MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputManager,  World *world, TankCamera *cam, UserInput *userInput) :
mRenderWindow(mainWindow), mInputHandler(inputManager),  mWorld(world), mTankCamera(cam), mUserInput(userInput)
{

}


// On every frame, call the appropriate managers
bool 
	MainListener::frameStarted(const Ogre::FrameEvent &evt)
{
	
	float time = evt.timeSinceLastFrame;
	if (time > 0.5)
	{
		time = 0.5;
	}

	


    //  The only reason we have the Think method of the InputHandler return
    //   a value, is for the escape key to cause our application to end.
    //   Feel free to change this to something that makes more sense to you.
	mInputHandler->Think(time);
	mWorld->Think(time);
    mTankCamera->Think(time);
	mUserInput->Think(time);
	

	// Call think methods on any other managers / etc you want to add

	bool keepGoing = true;

	// Ogre will shut down if a listener returns false.  We will shut everything down if
	// either the user presses escape or the main render window is closed.  Feel free to 
	// modify this as you like.
	if (mInputHandler->IsKeyDown(OIS::KC_ESCAPE) || mRenderWindow->isClosed())
	{
		keepGoing = false;
	}

	return keepGoing;
}