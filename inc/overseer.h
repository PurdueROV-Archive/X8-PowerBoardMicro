
#ifndef OVERSEER
#define OVERSEER

// INCLUDES:
#include <stdint.h>
#include "matrices.h"
#include "thrust_mapper.h"


// STRUCTS:

typedef struct {

	int powers[8];
	int currents[8];
	int voltages[8];
	// Contains 1/0 depending on whether each motor 1-8 is 'enabled' or 'not disabled.'
	uint8_t enabled[8];

} ThrustersContainer;

// DEFINES:

#define NO_NEW_DATA 0
#define NEW_DATA 1

#define MAX(x,y) (x > y) ? x : y
#define MIN(x,y) (x > y) ? y : x

// OVERSEER CLASS

class Overseer
{
	public:
		Overseer();
		void update(vect6 force, vect3 pivotPos, char on_off);
		int checkForUpdate(void);
		void calculateAndPush(void);
		void updateFromThrusters(void);
        void doRamping(void);
		int flag_NewData;

	private:
		ThrustersContainer thrusters;
		ThrustMapper thrustMapper;
		vect6 target_force;
        vect6 Tset;
        vect6 Tcurrent;
        

};

#endif