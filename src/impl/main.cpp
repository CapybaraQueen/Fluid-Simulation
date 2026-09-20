#include<iostream>
#include<sstream>
#include<string>

#include "Physics.h"
#include "Fluid.h"

int main() {
	int x,y,z;
	std::string dummy;

	std::cout << "Enter the volume coordinates as x y z: ";
	getline(std::cin, dummy);

	auto streamedString = std::istringstream(dummy);

	streamedString >> x >> y >> z;

	Fluid fluid(x,y,z);

	Physics physics;

	std::cout << "You entered " << x << ", " << y << ", " << z << "\n";

	std::cout << "The fluid volume is " << fluid.volume << "\n";

	std::cout << "Time = " << physics.GetTime() << "\n";

	std::cout << "DeltaTime = " << physics.GetDeltaTime() << "\n";

	return 0;
}
