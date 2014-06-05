#ifndef __AIManager_h_
#define __AIManager_h_


class World;
class Tank;
class TankAI;


class AIManager 
{

public:
    // You may want to add parameters to the AI Manager constructor
	AIManager(World *world);
	~AIManager();
	void AddAI(Tank AITank);
	void RemoveAI(Tank AITank);

    // Go through all of the AIs, and call think on each one
    void Think(float time);

protected:
	World *mWorld;
	TankAI *AIlist;
};

#endif