// My header file.  This should go first!
#include "World.h"
#include "OgreTank.h"





World::World(Ogre::SceneManager *sceneManager, InputHandler *input, TankManager *tankManager, ProjectileManager *projectileManager, Geometry* geometry)  : 
	mSceneManager(sceneManager), mInputHandler(input), mTankManager(tankManager),mProjectileManager(projectileManager),mGeometry(geometry)
{
	


	// Yeah, this should be done automatically for all fonts referenced in an overlay file.
	//  But there is a bug in the OGRE code so we need to do it manually.
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
	{ 
		iter.getNext()->load(); 
	}

	

	mSceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);

 
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -3);
 
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,		//ground x:-750~750 y:-3 z:-750~750
        plane, (OgreTank::halfSize)*2, (OgreTank::halfSize)*2, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
    Ogre::Entity* entGround = mSceneManager->createEntity("GroundEntity", "ground");
    mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
    entGround->setMaterialName("Examples/Floor");		//grass
    entGround->setCastShadows(false);
 
    Ogre::Light* directionalLight = mSceneManager->createLight("directionalLight");			//light1
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue::White);
    directionalLight->setSpecularColour(Ogre::ColourValue::White);
    directionalLight->setDirection(Ogre::Vector3( -1, -1, 1 )); 

	
	Ogre::Light* directionalLight2 = mSceneManager->createLight("directionalLight2");			//light2
    directionalLight2->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight2->setDiffuseColour(Ogre::ColourValue::White);
    directionalLight2->setSpecularColour(Ogre::ColourValue::White);
    directionalLight2->setDirection(Ogre::Vector3( 1, -1, -1 )); 
	

	mSceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);					//sky
 

}




void 
World::Think(float time)
{
	if (OgreTank::gameState == 1)
	{
		mProjectileManager->Think(time);
		mTankManager->Think(time);
		mGeometry->Think(time);

	}
	debugDisplay();
	
}

void
World::debugDisplay()
{
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();

	Ogre::Overlay *hud = om.getByName("Hud");

	hudText1 = Ogre::StringConverter::toString((int)mTankManager->myTank()->getHP());
	Ogre::TextAreaOverlayElement *hud1 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Hud/Panel/Text1");
	hud1->setCaption("HP:  "+hudText1);

	hudText2 = Ogre::StringConverter::toString(mTankManager->myTank()->getBulletN());
	Ogre::TextAreaOverlayElement *hud2 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Hud/Panel/Text2");
	hud2->setCaption("Bullet Num:   "+ hudText2);

	hudText3 = Ogre::StringConverter::toString(mTankManager->myTank()->getPower());
	Ogre::TextAreaOverlayElement *hud3 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Hud/Panel/Text3");
	hud3->setCaption("Bullet Power: "+hudText3);

	Ogre::Overlay *hud_2 = om.getByName("Hud2");
	hudText4 = Ogre::StringConverter::toString(OgreTank::level);
	Ogre::TextAreaOverlayElement *hud4 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Hud2/Panel/Text4");
	hud4->setCaption("Level:  "+hudText4);
	
	hudText5 = Ogre::StringConverter::toString(mTankManager->getRemainTank());
	Ogre::TextAreaOverlayElement *hud5 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Hud2/Panel/Text5");
	hud5->setCaption("Remaining:  "+hudText5);

	hudText6 = Ogre::StringConverter::toString(mTankManager->myTank()->getFullEnemyHP()*OgreTank::level);
	Ogre::TextAreaOverlayElement *hud6 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Hud2/Panel/Text6");
	hud6->setCaption("Enemy HP:  "+hudText6);


	hud->show();
	hud_2->show();

	Ogre::Overlay *gameover = om.getByName("GameOver");

	if(OgreTank::gameState == 0)
		gameover->show();
	else
		gameover->hide();
	Ogre::Overlay *minimap = om.getByName("MiniMap");
	minimap->show();

}


