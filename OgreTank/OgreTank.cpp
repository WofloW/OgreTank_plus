#include "OgreTank.h"




OgreTank::OgreTank()
{
    mTankFrameListener = 0;
    mRoot = 0;
    // Provide a nice cross platform solution for locating the configuration files
    // On windows files are searched for in the current working directory, on OS X however
    // you must provide the full path, the helper function macBundlePath does this for us.
	//  (Note:  This is not fully tested under IOS)
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    mResourcePath = macBundlePath() + "/Contents/Resources/";
#else
    mResourcePath = "";
#endif
}

int OgreTank::gameState = 1;		//static initialization
int OgreTank::level = 1;
Ogre::Real OgreTank::halfSize = 500;

/// Standard destructor
OgreTank::~OgreTank()
{
    if (mTankFrameListener)
        delete mTankFrameListener;
    if (mRoot)
        delete mRoot;
}



void
OgreTank::createCamera()
{
	mCamera = mSceneManager->createCamera("Cam_1");
	mCamera->setPosition(Ogre::Vector3(0,0,100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));

	mCamera2 = mSceneManager->createCamera("Cam_2");
	mCamera2->setPosition(Ogre::Vector3(0, 800, 100)); //800
	mCamera2->lookAt(0,0,0);


}



// We will create a single frame listener, to handle our main event loop.  While we could
// add as many frame listeners as we want (and let the main rendering loop call them),
// we would not have as much control over the order that the listeners are called --
//  so we will just have one listener and handle everything ourselves.
void 
OgreTank::createFrameListener(void)
{
	mTankFrameListener = new MainListener(mWindow, mInputHandler, mWorld, mTankCamera, mUserInput);
	mRoot->addFrameListener(mTankFrameListener);
}

// We will have a single viewport.  If you wanted splitscreen, or a rear-view mirror, then
// you may want multiple viewports.
void 
OgreTank::createViewports(void)
{
	    // Create one viewport, entire window
        Ogre::Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));    

		Ogre::Viewport* vp2 = mWindow->addViewport(mCamera2, 1, 0.03, 0.03, 0.3, 0.3);
        vp2->setBackgroundColour(Ogre::ColourValue(0,0,0));
		vp2->setOverlaysEnabled(false);
        mCamera->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));    

}

// Here is where we set up all of the non-rendering stuff (our world, various managers, etc)
void 
OgreTank::createScene() 
{
	bgmfile = "background.ogg";
	soundEngine = createIrrKlangDevice();
	BGM = soundEngine->play2D(bgmfile.c_str(),true, false, true);

    mInputHandler = new InputHandler(mWindow);
	mGeometry = new Geometry(mSceneManager, soundEngine);
	mProjectileManager = new ProjectileManager( mSceneManager, soundEngine, mGeometry);
	mTankManager = new TankManager(mSceneManager,mProjectileManager, soundEngine, mGeometry);
    mWorld = new World(mSceneManager, mInputHandler,mTankManager, mProjectileManager, mGeometry);
	
	mTankCamera = new TankCamera(mCamera, mCamera2, mWorld, mInputHandler, mTankManager);
	mUserInput = new UserInput(mInputHandler, mTankManager, mProjectileManager, soundEngine);
	mWorld->addCamera(mTankCamera);
	mProjectileManager->addTankManager(mTankManager);


}

bool 
OgreTank::setup(void)
{

    Ogre::String pluginsPath;
	Ogre::String configPath;
    // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB

#if OGRE_DEBUG_MODE == 1 && (OGRE_PLATFORM != OGRE_PLATFORM_APPLE && OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS)
	// add _d suffix to config files
	pluginsPath = mResourcePath + "plugins_d.cfg";
	configPath = mResourcePath + "ogre_d.cfg";
#else
	pluginsPath = mResourcePath + "plugins.cfg";
	configPath = mResourcePath + "ogre.cfg";

#endif


#endif
	
    mRoot = new Ogre::Root(pluginsPath, 
        configPath, mResourcePath + "Ogre.log");

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    // Create the SceneManager, in this case a generic one
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "TankSMInstance");
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);


	translaterlaySystem = new Ogre::OverlaySystem();
	mSceneManager->addRenderQueueListener(translaterlaySystem);


    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    createScene();


    // When we start the renderer, it will run forever, making callbacks every
    // frame to the frame listeners.  These listeners are where all of the non-
    // rendering work is done.  
    createFrameListener();

    return true;

}
/** Configures the application - returns false if the user chooses to abandon configuration. */
bool 
OgreTank::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true);
        return true;
    }
    else
    {
        return false;
    }
}

void
OgreTank::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;

	#if OGRE_DEBUG_MODE == 1 && (OGRE_PLATFORM != OGRE_PLATFORM_APPLE && OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS)
			// add _d suffix to config files
    cf.load(mResourcePath + "resources_d.cfg");
#else
	cf.load(mResourcePath + "resources.cfg");
#endif
		

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                String(macBundlePath() + "/" + archName), typeName, secName);
#else
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
#endif
        }
    }
}

void
OgreTank::destroyScene()
{
    delete mWorld;
    delete mTankCamera;
    delete mInputHandler;
	soundEngine->drop();
}

void 
OgreTank::go(void)
{
    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}

