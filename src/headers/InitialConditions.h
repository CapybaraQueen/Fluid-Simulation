#ifndef INITIALCONDITIONS_H
#define INITIALCONDITIONS_H

#include<vector>

struct InitialConditions {
	// density
	std::vector<double> rho;

	// x momentum
	std::vector<double> xMomentum;

	// y momentum
	std::vector<double> yMomentum;

	// z momentum
	std::vector<double> zMomentum;

	// total energy
	std::vector<double> E;

	// volume fraction
	std::vector<double> phi;
};

#endif
