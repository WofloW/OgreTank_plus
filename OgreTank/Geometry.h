#ifndef __Geometry_h_
#define __Geometry_h_

#include "Ogre.h"
#include "OgreSceneNode.h"
// sound system
#include "include/irrKlang.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")

class Geometry 
{

public:

	Geometry(Ogre::SceneManager *sceneManager, ISoundEngine* soundEngine);
	~Geometry();
	void Think(float time);
	
	Ogre::Vector3 getBuffPos() {return pos;}
	int getBonusNum() {return bonusNum;}
	int getState() {return state;}
	void takeBuff();
	void reset();
	std::vector<Ogre::Vector3> getTreePos() {return treePos;}

protected:

	Ogre::SceneNode *wall1;
	Ogre::SceneNode *wall2;
	Ogre::SceneNode *wall3;
	Ogre::SceneNode *wall4;
	Ogre::SceneNode *treasure1;

	Ogre::SceneNode *tree1;
	Ogre::SceneNode *tree2;
	Ogre::SceneNode *tree3;
	Ogre::SceneNode *tree4;
	
	std::vector<Ogre::Vector3> treePos;
	//Ogre::SceneNode *buff;
	/*
	Ogre::SceneNode *treasure3;
	Ogre::SceneNode *treasure4;
	Ogre::SceneNode *treasure5;
	*/

	Ogre::Entity *ent1;		//wall1-wall4
	Ogre::Entity *ent2;
	Ogre::Entity *ent3;
	Ogre::Entity *ent4;

	Ogre::Entity *ent5;		//treasure
	
	Ogre::Entity *ent6;		//tree1-tree4
	Ogre::Entity *ent7;
	Ogre::Entity *ent8;
	Ogre::Entity *ent9;

	int bonusNum;
	Ogre::Vector3 pos;
	float bonusCD;
	float bonusTimer;

	int state;
	std::string treasureSound;
	
	
	Ogre::SceneManager *mSceneManager;
	ISoundEngine* mSoundEngine;

};

#endif