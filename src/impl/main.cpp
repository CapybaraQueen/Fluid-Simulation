#include<iostream>
#include<sstream>
#include<string>
#include<memory>
#include<vector>

#include "Physics.h"
#include "Fluid.h"
#include "Problem.h"

int main() {
	int x,y,z;
	double h;
	double dt,iTol,epsilon;

	std::vector<std::unique_ptr<Fluid>> fluidList;
	double tmpGamma,tmpPiInf;

	std::string dummy;

	std::cout << "Enter the volume coordinates and grid resolution as x y z h: ";
	getline(std::cin, dummy);

	auto streamedString = std::istringstream(dummy);

	streamedString >> x >> y >> z >> h;

	Problem problem(x,y,z,h);

	std::cout << "Enter the deltaTime, interface tolerance, and epsilon as dt iTol epsilon: ";
	getline(std::cin, dummy);

	streamedString = std::istringstream(dummy);

	streamedString >> dt >> iTol >> epsilon;

	Physics physics(dt,iTol,epsilon);

	std::cout << "How many fluids are in this problem? ";
	getline(std::cin, dummy);

	streamedString = std::istringstream(dummy);
	int dummyInt;
	streamedString >> dummyInt;
	for (int i = 0; i < dummyInt; i++) {
		std::cout << "Enter gamma and piInf as gamma piInf: ";
		getline(std::cin, dummy);
		streamedString = std::istringstream(dummy);
		streamedString >> tmpGamma >> tmpPiInf;

		fluidList.push_back(std::make_unique<Fluid>(tmpGamma, tmpPiInf));
	}

	std::cout << "You entered " << problem.GetNx() << ", " << problem.GetNy() << ", " << problem.GetNz() << ", " << problem.GetGridResolution() << "\n";

	std::cout << "The fluid volume is " << problem.GetSize() * h << "\n";

	std::cout << "Time = " << physics.GetTime() << "\n";

	std::cout << "DeltaTime = " << physics.GetDeltaTime() << "\n";

	std::cout << "You created " << fluidList.size() << " fluids.\n";

	for (int i = 0; i < fluidList.size(); i++) {
		std::cout << "Fluid " << i << " has gamma=" << fluidList[i]->GetGamma() << " and piInf=" << fluidList[i]->GetPiInf() << "\n";
	}

	return 0;
}
