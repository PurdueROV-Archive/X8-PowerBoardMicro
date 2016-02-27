#ifndef THRUST_MAPPER
#define THRUST_MAPPER

#include "matrices.h"



// MapperMatrixIndex is used to give significance to the index of mapper_matrices.matrices
typedef enum {
	ALL = 0,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7,
	T8,
	NONE
} MapperMatrixIndex;

typedef struct {

	MapperMatrixIndex currentMapperMatrix;

	matrix8_6 all;
	matrix8_6 minus_t1;
	matrix8_6 minus_t2;
	matrix8_6 minus_t3;
	matrix8_6 minus_t4;
	matrix8_6 minus_t5;
	matrix8_6 minus_t6;
	matrix8_6 minus_t7;
	matrix8_6 minus_t8;
	matrix8_6 none;

	// Array for the above matrices:
	matrix8_6 matrices[10];

} ThrustMapperMatrices;


/*
 *	How to Use thrust_mapper
 *
 *	1. Make One ThrustMapper Object.

 *	On each update, set as necessary:
 *	2. pivotPosition via adjustPivotPosition() and what motors are online which changes the mapper matrix via changeMapperMatrix().

 *	When Control changes the force/direction of the ROV, set as necessary:
 *	3. desired_force_vector via calculateThrustMap().
 
 *	When the thrusters power should be changed (due to ramping timer, etc.):
 *	4. Get the most recent thrust_map via getThrustMap().
 */

class ThrustMapper
{	
	public:
		ThrustMapper(void);
		void adjustPivotPosition(vect3 loc);
		void calculateThrustMap(void);
		void calculateThrustMap(vect6 target_vector);
		void scaleNewtonsToInt(void);
		void changeMapperMatrix(char enabled_thrusters);
		vect6 getCurrentForceVector(void);
		vect8 getThrustMap(void);
		vect3 getPivotPosition(void);
		void calcZeroForceVector(void);
		vect8 thrust_map;

	private:
		vect6 desired_force_vector;
		vect3 pivotPosition;
		ThrustMapperMatrices mapper_matrices;

};


#endif