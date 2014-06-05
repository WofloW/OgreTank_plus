#ifndef __Terrain_h_
#define __Terrain_h_
#include "Ogre.h"
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

class Terrain 
{

public:
    Terrain(Ogre::SceneManager* SceneMgr, Ogre::Camera* Camera);
    ~Terrain(void);

private:
    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
 
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

};

#endif

