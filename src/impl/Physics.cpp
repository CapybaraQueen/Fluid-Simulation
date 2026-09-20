#include "Physics.h"

Physics::Physics() {
	time = 0;
	deltaTime = 0.01;
}

void Physics::TimeStep() {
	time += 1;
	return;
}

float Physics::GetTime() {
	return time;
}

float Physics::GetDeltaTime() {
	return deltaTime;
}
