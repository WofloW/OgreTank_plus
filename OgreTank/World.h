#ifndef __World_h_
#define __World_h_
#include <string>


// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"

// IOS (Input system) header files
#include <ois/ois.h>

// Other input files for my project
#include "InputHandler.h"
#include "TankManager.h"
#include "Tank.h"
#include "ProjectileManager.h"
#include "Geometry.h"



class World
{
public:
	
	World(Ogre::SceneManager *sceneManager, InputHandler *input, TankManager *tankManager, ProjectileManager *projectileManager, Geometry* geometry);

    // You'll want various methods to access & change your world here
    
    void Think(float time);
	
	void addCamera(TankCamera *c) { mCamera = c; }


	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	void debugDisplay();


	
protected:


	Ogre::SceneManager *mSceneManager;
	ProjectileManager *mProjectileManager;
	InputHandler *mInputHandler;
	TankCamera *mCamera;
	TankManager *mTankManager;
	Geometry* mGeometry;


	std::string hudText1;		//HP
	std::string hudText2;		//BUFF
	std::string hudText3;		//Kill
	std::string hudText4;		//Level
	std::string hudText5;		//Remaining Enemy
	std::string hudText6;		//Enemy HP

	

};


#endif