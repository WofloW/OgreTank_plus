#ifndef __Tank_h_
#define __Tank_h_
#include <string>

// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
// IOS (Input system) header files
#include <ois/ois.h>
// Other input files for my project
#include "InputHandler.h"


class TankManager;
class ProjectileManager;

class Tank
{

public:

	Tank(Ogre::Vector3 position, TankManager *tankManager, Ogre::SceneManager *sceneManager, ProjectileManager *projectileManager, int name, int type);		//type = 0 my tank; =1 enemy tank
	~Tank();

	void setPositon(Ogre::Vector3 pos) {mtankPosition = pos; tank->setPosition(mtankPosition);}
	void moveRelative(Ogre::Vector3 pos) {mtankPosition = mtankOrientation*pos+mtankPosition; tank->setPosition(mtankPosition);}
	void setTankOrientation(Ogre::Quaternion orientation) {mtankOrientation = orientation; tank->setOrientation(mtankOrientation);}
	void setBarrelOrientation(Ogre::Quaternion orientation) {mbarrelOrientation = orientation; barrel->setOrientation(mbarrelOrientation);}
	void rotateTank(Ogre::Quaternion orientation) {mtankOrientation = orientation*mtankOrientation; tank->setOrientation(mtankOrientation);}
	void rotateBarrel(Ogre::Quaternion orientation) {mbarrelOrientation = orientation*mbarrelOrientation; barrel->setOrientation(mbarrelOrientation); }
	void fire();
	void Think(float time);


	float getHP() {return mHealth;}
	void setHP(float HP) {mHealth = HP;}
	float getFireCD() {return mfireCD;}
	void setFireCD(float newCD) {mfireCD = newCD;}
	float getVelocity() {return mvelocity;}
	void setVelocity(float velocity) {mvelocity = velocity;}
	float getBulletV() {return mbulletVelocity;}
	void setBulletV(float bv) {mbulletVelocity = bv;}
	float getBulletRange() {return mbulletRange;}
	Ogre::Real getanglularV() {return manglularV;}
	Ogre::Real getBarrelAnglularV() {return mBarrelAnglularV;}

	Ogre::Vector3 getBarrelPosition() {return mbarrelPosition;}
	Ogre::Vector3 getTankPosition() {return mtankPosition;}

	Ogre::Quaternion getTankOrientation() {return mtankOrientation;}
	Ogre::Vector3 getBulletPosition() {return mtankOrientation*(mbarrelOrientation*Ogre::Vector3( 0, 4, -6)+mbarrelPosition)+mtankPosition;}
	Ogre::Quaternion getBulletOrientation() {return mtankOrientation*mbarrelOrientation*Ogre::Quaternion(0,0,1,0);}
	
	Ogre::SceneNode *tankNode() { return tank;} 
	Ogre::SceneNode *barrelNode() { return barrel;} 

	void setName(int num) {mname = num;}
	int getName() {return mname;}
	int getType() {return mtype;}
	void setBuff(std::string buff) {mbuff = buff;}
	std::string getBuff() {return mbuff;}

	void beDead();
	void beAlive();
	void beDamaged();

	int getTankState() {return Tankstate;}
	void setTankState(int state) {Tankstate = state;}
	float getDisappearTimer() {return disappearTimer;}
	void disappearTimerGo(float time) {disappearTimer -= time;}

	int getKill() {return kill;}
	void setKill(int k) {kill = k;}
	void reset();
	void beShield();

	void setShield(bool set) {mshield = set;}
	bool getShield() {return mshield;}
	bool getRecovery() {return mrecovery;}
	void setRecovery(bool rec) {mrecovery = rec;}
	int getBulletN() {return mbulletN;}
	void setBulletN(int bulletN) {mbulletN = bulletN;}

	float getFullHP() {return playerFullHP;}
	float getFullEnemyHP() {return enemyFullHP;}
	float getOriBulletV() {return oriBulletVelocity;}
	float getOriFireCD() {return 2.0;}

	int getPower() {return power;}
	void setPower(int p) {power = p;}

	void buffHit() ;
	

protected:
	Ogre::SceneNode *tank;
	Ogre::SceneNode *barrel;

	

	Ogre::Entity *ent1;	//normal tank
	Ogre::Entity *ent2;	//normal barrel
	Ogre::Entity *ent3;	//dead tank
	Ogre::Entity *ent4;	//dead barrel
	Ogre::Entity *ent5;	//shield tank
	Ogre::Entity *ent6;	//shield barrel
	Ogre::Entity *ent7;	//damaged tank
	Ogre::Entity *ent8; //damaged barrel

	Ogre::SceneManager *mSceneManager;
	TankManager *mTankManager;
	ProjectileManager *mProjectileManager;

	float mHealth;
	float playerFullHP;
	float enemyFullHP;
	float mbulletVelocity;
	float oriBulletVelocity;
	float mvelocity;
	float mbulletRange;
	Ogre::Real manglularV;
	Ogre::Real mBarrelAnglularV;
	Ogre::Quaternion  mtankOrientation;
	Ogre::Quaternion  mbarrelOrientation;
	Ogre::Vector3 mtankPosition;
	Ogre::Vector3 mbarrelPosition;
	float mfireCD;
	float buttonTimer;

	int mname;
	int mtype;		//0 mytank  1 enemy

	float operationCD;
	float operationTimer;

	int operation1;
	int operation2;
	int Tankstate;		//0 dead 1 alive
	int power;

	std::string mbuff;
	float disappearCD;
	float disappearTimer;

	int kill;
	bool mshield;
	bool mrecovery;
	int mbulletN;
};

#endif