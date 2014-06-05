#ifndef __TankAI_h_
#define __TankAI_h_


class World;

class TankAI 
{

public:
    
	TankAI(World *world);
	~TankAI();

    void Think(float time);

protected:
	World *mWorld;


};

#endif