#ifndef PHYSICS_H
#define PHYSICS_H

class Physics {
	private:
		float time;
		float deltaTime;
	public:
		Physics();

		void TimeStep();

		float GetTime();

		float GetDeltaTime();
};

#endif
