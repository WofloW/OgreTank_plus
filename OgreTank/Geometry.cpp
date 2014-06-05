#include "Geometry.h"
#include "OgreTank.h"


Geometry::Geometry(Ogre::SceneManager *sceneManager, ISoundEngine* soundEngine):mSceneManager(sceneManager),mSoundEngine(soundEngine)

{
	state = 0;
	bonusCD = 15;
	bonusTimer = bonusCD;
	bonusNum = -1;
	treasure1 = NULL;
	treasureSound = "treasure.mp3";

	srand ( (unsigned int)time(NULL) );
	ent1 = mSceneManager->createEntity("wall.mesh");		
	ent1->setCastShadows(true);
	wall1 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -3, 500));
	wall1->scale(13.4, 1, 1);
	wall1->attachObject(ent1);

	ent2 = mSceneManager->createEntity("wall.mesh");		
	ent2->setCastShadows(true);
	wall2 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -3, -500));
	wall2->scale(13.4, 1, 1);
	wall2->attachObject(ent2);

	ent3 = mSceneManager->createEntity("wall.mesh");		
	ent3->setCastShadows(true);
	wall3 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(500, -3, 0));
	wall3->scale(13.4, 1, 1);
	wall3->yaw(Ogre::Degree(90.0f));
	wall3->attachObject(ent3);

	ent4 = mSceneManager->createEntity("wall.mesh");		
	ent4->setCastShadows(true);
	wall4 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-500, -3, 0));
	wall4->scale(13.4, 1, 1);
	wall4->yaw(Ogre::Degree(90.0f));
	wall4->attachObject(ent4);

	ent6 =  mSceneManager->createEntity("tree.mesh");
	ent6->setCastShadows(true);
	tree1 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-250, -3, 250));
	tree1->attachObject(ent6);

	ent7 =  mSceneManager->createEntity("tree.mesh");
	ent7->setCastShadows(true);
	tree2 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(250, -3, 250));
	tree2->attachObject(ent7);

	ent8 =  mSceneManager->createEntity("tree.mesh");
	ent8->setCastShadows(true);
	tree3 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-250, -3, -250));
	tree3->attachObject(ent8);

	ent9 =  mSceneManager->createEntity("tree.mesh");
	ent9->setCastShadows(true);
	tree4 = mSceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(250, -3, -250));
	tree4->attachObject(ent9);


	treePos.push_back(Ogre::Vector3(-250,-3,250));
	treePos.push_back(Ogre::Vector3(250,-3,250));
	treePos.push_back(Ogre::Vector3(-250,-3,-250));
	treePos.push_back(Ogre::Vector3(250,-3,-250));


}



void Geometry::Think(float time) {
	if (state == 0)
		bonusTimer -= time;
	if (bonusTimer <= 0)
	{
		mSoundEngine->play2D(treasureSound.c_str());
		bonusNum = (int) floor( Ogre::Math::RangeRandom(0.0001,3.9999));
		std::string meshName;
		switch (bonusNum)
		{
		case 0:
			meshName = "treasure_blue.mesh";
			break;
		case 1:
			meshName = "treasure_green.mesh";
			break;
		case 2:
			meshName = "treasure_red.mesh";
			break;
		case 3:
			meshName = "treasure_yellow.mesh";
			break;
		default:
			break;
		}

		ent5 = mSceneManager->createEntity(meshName);		
		ent5->setCastShadows(true);
		int maxPos = OgreTank::halfSize - 30;
		pos.x = Ogre::Math::RangeRandom(-maxPos,maxPos);
		pos.y = -3;
		pos.z = Ogre::Math::RangeRandom(-maxPos,maxPos);
			
		treasure1 = mSceneManager->getRootSceneNode()->createChildSceneNode(pos);
		treasure1->attachObject(ent5);
		state = 1;
		bonusTimer = bonusCD;
	}

}

Geometry::~Geometry()
{
	if (treasure1 != NULL)
	{
		treasure1->detachAllObjects();
		mSceneManager->destroyEntity(ent5);
		mSceneManager->destroySceneNode(treasure1);
		treasure1 = NULL;
	}
	treePos.clear();
}

void 
	Geometry::reset()
{
	if (treasure1 != NULL)
	{
		treasure1->detachAllObjects();
		mSceneManager->destroyEntity(ent5);
		mSceneManager->destroySceneNode(treasure1);
		treasure1 = NULL;
	}
	state = 0;
}


void 
	Geometry::takeBuff()
{
	state = 0;
	reset();
}



