#ifndef TYPEU_H
#define TYPEU_H

#include<vector>

struct TypeU {
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

	// equation of state variables
	std::vector<double> alpha;
	std::vector<double> beta;
};

#endif
