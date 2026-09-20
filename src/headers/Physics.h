#ifndef PHYSICS_H
#define PHYSICS_H

class Physics {
	private:
		float time;
	public:
		Physics();

		void TimeStep();

		float GetTime();
};

#endif
