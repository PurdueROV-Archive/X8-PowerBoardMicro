#ifndef THRUST_MAPPER
#define THRUST_MAPPER

#include "matrices.h"




typedef enum {
	ALL = 0,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7,
	T8
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

	// Array for the above matrices:
	matrix8_6 matrices[9];

} ThrustMapperMatrices;


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
		void calcZeroForceVector(void);
		vect8 thrust_map;

	private:
		vect6 desired_force_vector;
		vect3 pivotPosition;
		ThrustMapperMatrices mapper_matrices;

};


#endif