#ifndef __OgreTank_h_
#define __OgreTank_h_
#include "World.h"
#include "InputHandler.h"
#include "MainListener.h"
#include "TankCamera.h"
#include "TankManager.h"
#include "Geometry.h"
#include "ProjectileManager.h"
#include "UserInput.h"
#include "Tank.h"
#include "Ogre.h"
#include "OgreConfigFile.h"
#include "OgreFontManager.h"
#include "OgreOverlaySystem.h"
#include "include/irrKlang.h"
using namespace irrklang;

////#pragma comment(lib, "irrKlang.lib")




class OgreTank :  public Ogre::WindowEventListener
{
public:
    OgreTank();
    ~OgreTank();

    // Do all the application setup
    bool setup(void);

    // Start to run
    void go(void);

	static int gameState;
	static int level;
	static Ogre::Real halfSize;


protected:

    ///////////////////////////////////////////////////
    /// The following methods are all called by the public
    ///   setup method, to handle various initialization tasks
    //////////////////////////////////////////////////

    //  Load all the requrired resources (Mostly reading the file paths
    //  of various resources from the .cfg files)
    void setupResources(void);

    // Invoke the startup window for all of the Ogre settings (resolution, etc)
    bool configure(void);

    // Create all of the required classes and do setup for all non-rendering tasks
    void createScene(void);

    // Free up all memory & resources created in createScene
    void destroyScene(void);

    // Create the rendering camera (separate from the game camera -- the game camera
    //   contains the logic of how the camera should be translated, the rendering camera
    //   is used by the rendering system to render the scene.  So, the game camera 
    //   decides where the camera should be, and then makes calls to the rendering camera
    //   to translate the camera
	void createCamera(void);

	void createViewports(void);

    // The FrameListener is what receives callbacks from the rendering loop to handle 
    //  game logic
	void createFrameListener(void);
	
	

	




	MainListener *mTankFrameListener;
	InputHandler *mInputHandler;
	World *mWorld;
	Geometry *mGeometry;
    TankCamera *mTankCamera;
	TankManager *mTankManager;
	ProjectileManager *mProjectileManager;
	UserInput *mUserInput;
	
    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
	Ogre::Camera* mCamera2;
    Ogre::SceneManager* mSceneManager;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcePath;
	Ogre::OverlaySystem *translaterlaySystem;
	//sound engine
	ISoundEngine* soundEngine; 
	ISound* BGM;
	std::string bgmfile;


};

#endif // #ifndef __OgreTank_h_