#ifndef __UserInput_h_
#define __UserInput_h_


#include "TankManager.h"
#include "Tank.h"
#include "ProjectileManager.h"
#include "OgreVector3.h"

#include <string>
// sound system
#include "include/irrKlang.h"
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")

// IOS (Input system) header files
#include <ois/ois.h>

// Other input files for my project
#include "InputHandler.h"




class UserInput 
{

public:

	UserInput(InputHandler *input, TankManager *tankManager, ProjectileManager *projectileManager,ISoundEngine* soundEngine);
	~UserInput();


    void Think(float time);

protected:
	InputHandler *mInputHandler;
	TankManager *mTankManager;
	ProjectileManager *mProjectileManager;
	float buttonTimer;
	ISoundEngine* mSoundEngine;
	ISound* moveSoundE;


	bool moveState;
	std::string moveSound;
	std::string fireSound;


};

#endif