#include "Physics.h"

Physics::Physics() {
	time = 0;
}

void Physics::TimeStep() {
	time += 1;
	return;
}

float Physics::GetTime() {
	return time;
}
