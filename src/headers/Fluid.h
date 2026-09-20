#ifndef FLUID_H
#define FLUID_H

#include<vector>

struct Fluid {
	int xVolume, yVolume, zVolume;
	int volume;
	float totalEnergy;
	float totalPressure;
	float avgDensity;
	float avgTemperature;

	std::vector<float> density;
	std::vector<float> pressure;
	std::vector<float> velocity;
	std::vector<float> energy;

	Fluid(int x, int y, int z) {
		xVolume = x;
		yVolume = y;
		zVolume = z;

		volume = x*y*z;

		density.resize(volume);
		pressure.resize(volume);
		velocity.resize(volume);
		energy.resize(volume);
	}
};

#endif
