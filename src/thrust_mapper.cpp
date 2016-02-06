/* Put all of your #includes and #defines up here   */

#include "thrust_mapper.h"


/*Put all function definitions here. Do not forget the 
  classname:: part before the function name! */

/* Second note, each class must have a constructor. This
   is a function that is called when you create the object 
   (just like creating a variable) of the class. This function
   will have no return type. */


ThrustMapper::ThrustMapper(void)
{
	/*
	 *	Initialize mapper matrices here
	 */
	mapper_matrices.currentMapperMatrix = ALL;

	mapper_matrices.matrices[0] = mapper_matrices.all;
	mapper_matrices.matrices[1] = mapper_matrices.minus_t1;
	mapper_matrices.matrices[2] = mapper_matrices.minus_t2;
	mapper_matrices.matrices[3] = mapper_matrices.minus_t3;
	mapper_matrices.matrices[4] = mapper_matrices.minus_t4;
	mapper_matrices.matrices[5] = mapper_matrices.minus_t5;
	mapper_matrices.matrices[6] = mapper_matrices.minus_t6;
	mapper_matrices.matrices[7] = mapper_matrices.minus_t7;
	mapper_matrices.matrices[8] = mapper_matrices.minus_t8;

	mapper_matrices.matrices[0].t1 = vect6Make(  732,     0,   269,     0, -1311,     0);
	mapper_matrices.matrices[0].t2 = vect6Make( -732,     0,   276,     0,  1311,     0);
	mapper_matrices.matrices[0].t3 = vect6Make(  765,     0,  -269,     0,  1311,     0);
	mapper_matrices.matrices[0].t4 = vect6Make( -765,     0,  -276,     0, -1311,     0);
	mapper_matrices.matrices[0].t5 = vect6Make(   14,   223,   -19,  2364,     0,  1809);
	mapper_matrices.matrices[0].t6 = vect6Make(  -14,   232,   -19,  2364,     0, -1809);
	mapper_matrices.matrices[0].t7 = vect6Make(   14,   280,    19, -2364,     0,  1809);
	mapper_matrices.matrices[0].t8 = vect6Make(  -14,   289,    19, -2364,     0, -1809);

	mapper_matrices.matrices[1].t1 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[1].t2 = vect6Make(-1465,     0,     7,     0,  2621,     0);
	mapper_matrices.matrices[1].t3 = vect6Make(   32,     0,  -538,     0,  2621,     0);
	mapper_matrices.matrices[1].t4 = vect6Make(-1497,     0,  -545,     0,     0,     0);
	mapper_matrices.matrices[1].t5 = vect6Make(   14,   223,   -19,  2364,     0,  1809);
	mapper_matrices.matrices[1].t6 = vect6Make(  -14,   232,   -19,  2364,     0, -1809);
	mapper_matrices.matrices[1].t7 = vect6Make(   14,   280,    19, -2364,     0,  1809);
	mapper_matrices.matrices[1].t8 = vect6Make(  -14,   289,    19, -2364,     0, -1809);

	mapper_matrices.matrices[2].t1 = vect6Make( 1465,     0,    -7,     0, -2621,     0);
	mapper_matrices.matrices[2].t2 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[2].t3 = vect6Make( 1497,     0,  -545,     0,     0,     0);
	mapper_matrices.matrices[2].t4 = vect6Make(  -32,     0,  -551,     0, -2621,     0);
	mapper_matrices.matrices[2].t5 = vect6Make(   14,   223,   -19,  2364,     0,  1809);
	mapper_matrices.matrices[2].t6 = vect6Make(  -14,   232,   -19,  2364,     0, -1809);
	mapper_matrices.matrices[2].t7 = vect6Make(   14,   280,    19, -2364,     0,  1809);
	mapper_matrices.matrices[2].t8 = vect6Make(  -14,   289,    19, -2364,     0, -1809);

	mapper_matrices.matrices[3].t1 = vect6Make(  -32,     0,   538,     0, -2621,     0);
	mapper_matrices.matrices[3].t2 = vect6Make(-1497,     0,   545,     0,     0,     0);
	mapper_matrices.matrices[3].t3 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[3].t4 = vect6Make(-1529,     0,    -7,     0, -2621,     0);
	mapper_matrices.matrices[3].t5 = vect6Make(   14,   223,   -19,  2364,     0,  1809);
	mapper_matrices.matrices[3].t6 = vect6Make(  -14,   232,   -19,  2364,     0, -1809);
	mapper_matrices.matrices[3].t7 = vect6Make(   14,   280,    19, -2364,     0,  1809);
	mapper_matrices.matrices[3].t8 = vect6Make(  -14,   289,    19, -2364,     0, -1809);

	mapper_matrices.matrices[4].t1 = vect6Make( 1497,     0,   545,     0,     0,     0);
	mapper_matrices.matrices[4].t2 = vect6Make(   32,     0,   551,     0,  2621,     0);
	mapper_matrices.matrices[4].t3 = vect6Make( 1529,     0,     7,     0,  2621,     0);
	mapper_matrices.matrices[4].t4 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[4].t5 = vect6Make(   14,   223,   -19,  2364,     0,  1809);
	mapper_matrices.matrices[4].t6 = vect6Make(  -14,   232,   -19,  2364,     0, -1809);
	mapper_matrices.matrices[4].t7 = vect6Make(   14,   280,    19, -2364,     0,  1809);
	mapper_matrices.matrices[4].t8 = vect6Make(  -14,   289,    19, -2364,     0, -1809);

	mapper_matrices.matrices[5].t1 = vect6Make(  732,     0,   269,     0, -1311,     0);
	mapper_matrices.matrices[5].t2 = vect6Make( -732,     0,   276,     0,  1311,     0);
	mapper_matrices.matrices[5].t3 = vect6Make(  765,     0,  -269,     0,  1311,     0);
	mapper_matrices.matrices[5].t4 = vect6Make( -765,     0,  -276,     0, -1311,     0);
	mapper_matrices.matrices[5].t5 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[5].t6 = vect6Make(    0,   456,   -37,  4728,     0,     0);
	mapper_matrices.matrices[5].t7 = vect6Make(   28,   503,     0,     0,     0,  3618);
	mapper_matrices.matrices[5].t8 = vect6Make(  -28,    65,    37, -4728,     0, -3618);

	mapper_matrices.matrices[6].t1 = vect6Make(  732,     0,   269,     0, -1311,     0);
	mapper_matrices.matrices[6].t2 = vect6Make( -732,     0,   276,     0,  1311,     0);
	mapper_matrices.matrices[6].t3 = vect6Make(  765,     0,  -269,     0,  1311,     0);
	mapper_matrices.matrices[6].t4 = vect6Make( -765,     0,  -276,     0, -1311,     0);
	mapper_matrices.matrices[6].t5 = vect6Make(    0,   456,   -37,  4728,     0,     0);
	mapper_matrices.matrices[6].t6 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[6].t7 = vect6Make(   28,    47,    37, -4728,     0,  3618);
	mapper_matrices.matrices[6].t8 = vect6Make(  -28,   521,     0,     0,     0, -3618);

	mapper_matrices.matrices[7].t1 = vect6Make(  732,     0,   269,     0, -1311,     0);
	mapper_matrices.matrices[7].t2 = vect6Make( -732,     0,   276,     0,  1311,     0);
	mapper_matrices.matrices[7].t3 = vect6Make(  765,     0,  -269,     0,  1311,     0);
	mapper_matrices.matrices[7].t4 = vect6Make( -765,     0,  -276,     0, -1311,     0);
	mapper_matrices.matrices[7].t5 = vect6Make(   28,   503,     0,     0,     0,  3618);
	mapper_matrices.matrices[7].t6 = vect6Make(  -28,   -47,   -37,  4728,     0, -3618);
	mapper_matrices.matrices[7].t7 = vect6Make(    0,     0,     0,     0,     0,     0);
	mapper_matrices.matrices[7].t8 = vect6Make(    0,   568,    37, -4728,     0,     0);

	mapper_matrices.matrices[8].t1 = vect6Make(  732,     0,   269,     0, -1311,     0);
	mapper_matrices.matrices[8].t2 = vect6Make( -732,     0,   276,     0,  1311,     0);
	mapper_matrices.matrices[8].t3 = vect6Make(  765,     0,  -269,     0,  1311,     0);
	mapper_matrices.matrices[8].t4 = vect6Make( -765,     0,  -276,     0, -1311,     0);
	mapper_matrices.matrices[8].t5 = vect6Make(   28,   -65,   -37,  4728,     0,  3618);
	mapper_matrices.matrices[8].t6 = vect6Make(  -28,   521,     0,     0,     0, -3618);
	mapper_matrices.matrices[8].t7 = vect6Make(    0,   568,    37, -4728,     0,     0);
	mapper_matrices.matrices[8].t8 = vect6Make(    0,     0,     0,     0,     0,     0);





	/*
	 *	Other inits here
	 */
	// Desired force vector should start ROV stationary.
	desired_force_vector.L.x = 0;
	desired_force_vector.L.y = 0;
	desired_force_vector.L.z = 0;
	desired_force_vector.R.x = 0;
	desired_force_vector.R.y = 0;
	desired_force_vector.R.z = 0;
	// Init Pivot position at the center of mass.
	pivotPosition.x = 0;
	pivotPosition.y = 0;
	pivotPosition.z = 0;

}

void ThrustMapper::calcZeroForceVector(void)
{
	desired_force_vector.L.x = 0;
	desired_force_vector.L.y = 0;
	desired_force_vector.L.z = 0;
	desired_force_vector.R.x = 0;
	desired_force_vector.R.y = 0;
	desired_force_vector.R.z = 0;
	calculateThrustMap();
}

void ThrustMapper::adjustPivotPosition(vect3 loc)
{
	pivotPosition = loc;
}

void ThrustMapper::calculateThrustMap(void)
{
	// Calculations:
	vect3 cross_result = cross(pivotPosition, desired_force_vector.R);
	desired_force_vector.L.x += cross_result.x;
	desired_force_vector.L.y += cross_result.y;
	desired_force_vector.L.z += cross_result.z;
	thrust_map = matMul_86x61(mapper_matrices.matrices[mapper_matrices.currentMapperMatrix], desired_force_vector);
}

void ThrustMapper::calculateThrustMap(vect6 target_vector)
{
	desired_force_vector = div6(target_vector,1024);

	// Calculations:
	vect3 cross_result = cross(pivotPosition, desired_force_vector.R);
	desired_force_vector.L.x += cross_result.x;
	desired_force_vector.L.y += cross_result.y;
	desired_force_vector.L.z += cross_result.z;
	thrust_map = matMul_86x61(mapper_matrices.matrices[mapper_matrices.currentMapperMatrix], desired_force_vector);
}

void scaleNewtonsToInt()
{
	//thrust_map
}

// Only accepts an array of 8 ints. These ints correspond to whether each of the 8 thrusters are enabled.
void ThrustMapper::changeMapperMatrix(char enabled_thrusters)
{
	switch(enabled_thrusters)
	{
		case 255:
			mapper_matrices.currentMapperMatrix = ALL;
			break;
		case 254:
			mapper_matrices.currentMapperMatrix = T1;
			break;	
		case 253:
			mapper_matrices.currentMapperMatrix = T2;
			break;
		case 251:
			mapper_matrices.currentMapperMatrix = T3;
			break;
		case 247:
			mapper_matrices.currentMapperMatrix = T4;
			break;
		case 239:
			mapper_matrices.currentMapperMatrix = T5;
			break;
		case 223:
			mapper_matrices.currentMapperMatrix = T6;
			break;
		case 191:
			mapper_matrices.currentMapperMatrix = T7;
			break;
		case 127:
			mapper_matrices.currentMapperMatrix = T8;
			break;
		default:
			mapper_matrices.currentMapperMatrix = ALL;
 	}
}

vect6 ThrustMapper::getCurrentForceVector(void)
{
	return desired_force_vector;
}

