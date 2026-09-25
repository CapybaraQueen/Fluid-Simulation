#include<iostream>
#include<sstream>
#include<string>
#include<vector>

#include "Physics.h"
#include "Fluid.h"
#include "Simulation.h"

int main() {
	int x,y,z;
	double h;
	double dt,iTol,epsilon;

	double tmpGamma,tmpPiInf;

	std::string dummy;

	std::cout << "Enter the volume coordinates and grid resolution as x y z h: ";
	getline(std::cin, dummy);

	auto streamedString = std::istringstream(dummy);

	streamedString >> x >> y >> z >> h;

	Simulation simulation(x,y,z,h);

	std::cout << "Enter the deltaTime, interface tolerance, and epsilon as dt iTol epsilon: ";
	getline(std::cin, dummy);

	streamedString = std::istringstream(dummy);

	streamedString >> dt >> iTol >> epsilon;

	Physics physics(dt,iTol,epsilon);

	std::cout << "How many fluids are in this simulation? ";
	getline(std::cin, dummy);

	streamedString = std::istringstream(dummy);
	int dummyInt;
	streamedString >> dummyInt;
	for (int i = 0; i < dummyInt; i++) {
		std::cout << "Enter gamma and piInf as gamma piInf: ";
		getline(std::cin, dummy);
		streamedString = std::istringstream(dummy);
		streamedString >> tmpGamma >> tmpPiInf;

		simulation.AddFluid(tmpGamma, tmpPiInf);
	}

	std::cout << "You entered " << simulation.GetNx() << ", " << simulation.GetNy() << ", " << simulation.GetNz() << ", " << simulation.GetGridResolution() << "\n";

	std::cout << "The fluid volume is " << simulation.GetSize() * h << "\n";

	std::cout << "Time = " << physics.GetTime() << "\n";

	std::cout << "DeltaTime = " << physics.GetDeltaTime() << "\n";

	std::cout << "You created " << simulation.GetFluidList().size() << " fluids.\n";

	for (int i = 0; i < simulation.GetFluidList().size(); i++) {
		std::cout << "Fluid " << i << " has gamma=" << simulation.GetFluid(i).GetGamma() << " and piInf=" << simulation.GetFluid(i).GetPiInf() << "\n";
	}

	return 0;
}
